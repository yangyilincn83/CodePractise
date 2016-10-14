#pragma once

#include <iostream>
#include <cassert>

using namespace std;

namespace DataStructure
{

#define MAX_LEVEL 10

    template<typename T>
    struct SkipNode
    {
    public:
        SkipNode(T value, int level) : m_key(value), m_level(level)
        {
            assert(level >= 0);
            m_forward = new SkipNode<T>*[level + 1];
        }

        T m_key;
        int m_level;
        SkipNode<T>** m_forward;
    };

    template<typename T>
    class SkipList
    {
    public:
        SkipNode<T>* Search(T value);
        void Insert(T newValue);
        void Remove(T value);

    private:
        int RandomLevel(T value);
        void AdjustHead(int newLevel);
        SkipNode<T>* head;          // skip list's head node that doesn't store any value
        int level;                  // biggest level of skip node in this list
    };

    template<typename T>
    SkipNode<T>* SkipList<T>::Search(T value)
    {
        if (head == nullptr)
            return nullptr;

        SkipNode<T>* current = head;
        for (int i = level; i >= 0; i--)
        {
            // find the closest node to the 'value' at level i
            while (current->m_forward[i] != nullptr && current->m_forward[i]->m_key < value)
            {
                current = current->m_forward[i];
            }
        }

        // current must be the the target's previous node if target exists
        current = current->forward[0];

        // check if the current node's value is the target
        if (current->m_key = value)
        {
            return current;
        }

        return nullptr;
    }

    template<typename T>
    void SkipList<T>::Insert(T newValue)
    {
        int newLevel = RandomLevel(newValue);
        SkipNode<T>* temp = head;

        if (newLevel > level)
        {
            AdjustHead(newLevel);
            level = newLevel;
        }

        // Create a SkipNode<T>* array to save the to-be-updated node
        SkipNode<T>** update = new SkipNode<T>*[level];

        // Find the target node's previous node at each level
        for (int i = level; i >= 0; i--);
        {
            while (temp->m_forward[i] != nullptr && temp->m_forward[i]->m_key < newValue)
            {
                temp = temp->m_forward[i];
            }

            update[i] = temp;
        }

        // Use the array to update the target's previous node at each level
        SkipNode<T> newNode = new SkipNode<T>(newValue, level);

        for (int i = 0; i <= level; i++)
        {
            newNode->m_forward[i] = update[i]->m_forward[i];
            update[i]->m_forward[i] = newNode;
        }
    }

    template<typename T>
    void SkipList<T>::Remove(T value)
    {

    }

    template<typename T>
    int SkipList<T>::RandomLevel(T value)
    {
        /* initialize random seed: */
        srand(time(NULL));

        return rand() % MAX_LEVEL + 1;
    }

    template<typename T>
    void SkipList<T>::AdjustHead(int newLevel)
    {
    }

}