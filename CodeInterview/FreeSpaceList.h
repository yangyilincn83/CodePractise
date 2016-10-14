#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

namespace DataStructure
{
    template<class T>
    class LinkNode
    {
    private:
        static LinkNode<T>* freelist;
        static int freelistSize;
        static const int FREELISTMAXSIZE = 3;

    public:
        T value;
        LinkNode<T>* next;

        LinkNode(const T& v, LinkNode<T>* n = nullptr) : value(v), next(n) {}
        LinkNode(LinkNode<T>& n) : value(n.value), next(n.next) {}
        LinkNode() : value(0), next(nullptr) {}
        ~LinkNode() { next = nullptr; }

        static void* operator new(size_t sz)
        {
            if (freelist != nullptr)
            {
                cout << "allocate memory from freelist" << endl;
                void* result = freelist;
                freelist = freelist->next;
                freelistSize--;
                return result;
            }
            else
            {
                cout << "allocate memory from global heap" << endl;
                void* result = ::operator new(sz);
                return result;
            }
        }

        static void operator delete(void* p)
        {
            cout << "add deleted memory into freelist" << endl;
            LinkNode<T>* recycleNode = reinterpret_cast<LinkNode<T>*>(p);
            recycleNode->next = freelist;
            freelist = recycleNode;
            freelistSize++;

            if(freelistSize == FREELISTMAXSIZE)
            {
                cout << "freelist reaches max size, clear it" << endl;

                // clear freelist
                while (freelist != nullptr)
                {
                    void* temp = freelist;
                    freelist = freelist->next;

                    // use global delete operator here
                    ::operator delete(temp);
                }
                freelistSize = 0;
            }
        }
    };

    LinkNode<int>* LinkNode<int>::freelist = nullptr;
    int LinkNode<int>::freelistSize = 0;

    inline void FreeSpaceListTest()
    {
        // allocate memory from heap
        LinkNode<int>* node1 = new LinkNode<int>(1);
        LinkNode<int>* node2 = new LinkNode<int>(2);
        cout << "node1's value = " << node1->value << endl;
        cout << "node2's value = " << node2->value << endl;
        delete node1;
        delete node2;

        // allocate memory from freelist
        node1 = new LinkNode<int>(100);
        node2 = new LinkNode<int>();
        cout << "node1's value = " << node1->value << endl;
        cout << "node2's value = " << node2->value << endl;

        // allocate two more node to exceed freelist max size
        LinkNode<int>* node3 = new LinkNode<int>;
        LinkNode<int>* node4 = new LinkNode<int>;
        delete node1;
        delete node2;
        delete node3;
        delete node4;
    }
}