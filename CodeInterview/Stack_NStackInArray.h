#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include "BinaryTree.h"
#include <memory>
#include <algorithm>
#include <utility>

using namespace std;
using namespace DataStructure;

namespace Algorithm
{
    /*
        How can you implement n (n > 2) stacks in a single array, where no stack overflows until no space left in the entire array space?
    */
    struct ArrayLink
    {
        int position;
        int next;
    };

    class NStackInArray
    {
    private:
        int m_capacity;         // data buffer capacity
        int* m_buffer;          // data buffer
        int* m_links;           // link(array index) to the next node
        int* m_stackTops;       // stack top by array index
        const int m_count;      // stack count
        int m_freeListTop;      // free list top by array index
        int m_freeListSize;     // free list size

    public:
        NStackInArray(int* buffer, int capacity, int count) : m_buffer(buffer), m_capacity(capacity), m_count(count)
        {
            assert(buffer != nullptr && capacity > 0 && count > 0);

            // allocate memory
            m_links = new int[m_capacity];
            m_stackTops = new int[m_count];

            // init stack tops
            for_each(m_stackTops, m_stackTops + capacity, [](int& stackTop) -> void { stackTop = -1; });

            // init free list top and the links
            m_freeListTop = 0;
            m_freeListSize = capacity;
            for_each(m_links, m_links + capacity, [](int& link) { static int index = 0; link = ++index; });
            m_links[capacity - 1] = -1;
        }

        ~NStackInArray()
        {
            if (m_links != nullptr) delete[] m_links;
            if (m_stackTops != nullptr) delete[] m_stackTops;
        }

        void Push(int stackIndex, int value)
        {
            if (!Full())
            {
                int alloc = m_freeListTop;                  // get free list top
                m_freeListTop = m_links[m_freeListTop];     // point to next node in the free list
                m_freeListSize--;                           // update free list size

                int top = m_stackTops[stackIndex];          // get current stack top
                m_stackTops[stackIndex] = alloc;            // update current stack top to the new alloc
                m_links[alloc] = top;                       // link the new alloc with old stack top
                m_buffer[alloc] = value;                    // update the value
            }
        }

        int Top(int stackIndex)
        {
            if (m_stackTops[stackIndex] != -1)
            {
                return m_buffer[m_stackTops[stackIndex]];
            }
        }

        void Pop(int stackIndex)
        {
            if (m_stackTops[stackIndex] != -1)
            {
                int free = m_stackTops[stackIndex];                         // get the index to free up
                m_stackTops[stackIndex] = m_links[m_stackTops[stackIndex]]; // update stack top to the next node
                m_links[free] = m_freeListTop;
                m_freeListTop = free;
                m_freeListSize++;
            }
        }

        bool Full()
        {
            return (m_freeListSize == 0);
        }

        bool Empty()
        {
            return (m_freeListSize == m_capacity);
        }
    };
}
