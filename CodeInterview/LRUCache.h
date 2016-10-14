#pragma once

#include <unordered_map>
#include <iostream>
#include <cassert>

using namespace std;

/*
    Implement a LRU(Least Recently Used) cache that is composed of records with unique IDs.
*/
class Record
{
public:
    int m_id;
    int m_value;
};

template<class T>
class DLinkedNode
{
public:
    DLinkedNode(DLinkedNode<T>* prev, DLinkedNode<T>* next, T value)
    {
        m_prev = prev;
        m_next = next;
        m_value = value;
    }

    DLinkedNode<T>* m_prev;
    DLinkedNode<T>* m_next;
    T m_value;
};

template<class T>
class RecordPriorityList
{
private:
    DLinkedNode<T>* front;
    DLinkedNode<T>* back;

public:
    ~RecordPriorityList()
    {
        // delete all node in the linked list
    }

    void PushFront(DLinkedNode<T>* recordNode)
    {
        if (front == nullptr)
        {
            recordNode->m_next = nullptr;
            recordNode->m_prev = nullptr;
            front = recordNode;
        }
        else
        {
            front->m_prev = recordNode;
            recordNode->m_next = front;
            recordNode->m_prev = nullptr;
            front = recordNode;
        }
    }

    void PopBack()
    {
        if (back != nullptr)
        {
            if (back->m_prev == nullptr)
            {
                // the only node left
                delete back;
                front = back = nullptr;
            }
            else
            {
                DLinkedNode<T>* temp = back;
                back->m_prev->m_next = nullptr;
                back = back->m_prev;
                delete temp;
            }
        }
    }

    void Remove(DLinkedNode<T>* recordNode)
    {
        if (recordNode == nullptr)
            return;

        DLinkedNode<T>* prev = recordNode->m_prev;
        DLinkedNode<T>* next = recordNode->m_next;

        if (next != nullptr)
        {
            next->m_prev = prev;
        }
        else
        {
            // the node is the back, update the back
            back = prev;
        }

        if (prev != nullptr)
        {
            prev->m_next = next;
        }
        else
        {
            // the node is the front, update the front
            front = next;
        }

        delete recordNode;
    }

    DLinkedNode<T>* Back()
    {
        return back;
    }

    DLinkedNode<T>* Front()
    {
        return front;
    }
};

class Cache
{
public:
    Cache(const int size) : m_sizeLimit(size) {}
    ~Cache(){}

    void Put(Record record)
    {
        if (m_recordMap.find(record.m_id) != m_recordMap.end())
        {
            // a record of the same id exists, update it directly and the priority list
            DLinkedNode<Record>* node = m_recordMap[record.m_id];
            assert(node != nullptr);

            // update the record
            node->m_value = record;

            // move the node to the front 
            MoveToFront(node);
        }
        else
        {
            if (m_recordMap.size() == m_sizeLimit)
            {
                // cache is full, need to extract out the oldest record first
                DLinkedNode<Record>* swappedNode = m_recordPriorityList.Back();
                assert(swappedNode != nullptr);
                m_recordPriorityList.PopBack();
                m_recordMap.erase(swappedNode->m_value.m_id);
            }

            // allocate new node
            DLinkedNode<Record>* node = new DLinkedNode<Record>(nullptr, nullptr, record);

            // push to the front
            m_recordPriorityList.PushFront(node);

            // update the map
            m_recordMap[record.m_id] = node;
        }
    }

    Record Get(int id)
    {
        if (m_recordMap.find(id) != m_recordMap.end())
        {
            // get the DlinkedNode
            DLinkedNode<Record>* node = m_recordMap[id];
            assert(node != nullptr);

            // move the node to the front as it's accessed recently
            MoveToFront(node);

            return node->m_value;
        }
        else
        {
            // return empty record if the map doesn't include this id
            return Record();
        }
    }

    void MoveToFront(DLinkedNode<Record>* node)
    {
        if (node != nullptr)
        {
            m_recordPriorityList.Remove(node);
            m_recordPriorityList.PushFront(node);
            m_recordMap[node->m_value.m_id] = node;
        }
    }

private:
    unordered_map<int, DLinkedNode<Record>*> m_recordMap;
    RecordPriorityList<Record> m_recordPriorityList;
    const int m_sizeLimit;
};