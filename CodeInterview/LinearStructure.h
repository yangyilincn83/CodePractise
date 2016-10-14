#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

namespace DataStructure
{
    template<class T>
    class ArrayList
    {
    private:
        static const int DEFAULT_CAP = 100;
        T* m_array;
        int m_capacity;
        int m_size;
        int m_currPos;

    public:
        ArrayList(const int capacity = DEFAULT_CAP)
        {
            m_array = new T[capacity];
            m_capacity = capacity;
            m_size = 0;
            currPos = 0;
        }

        ~ArrayList()
        {
            delete[] m_array;
        }

        int Length()
        {
            return m_size;
        }

        bool IsEmpty()
        {
            return m_size == 0;
        }

        void Clear()
        {
            m_size = 0;
            currPos = 0;
        }

        void Append(const T& value)
        {
            assert(m_size < capacity);
            array[m_size++] = value;
        }

        void Insert(const T& value)
        {
            assert(m_size < capacity);
            
            // Move forward elements from currPos to m_size-1
            for (int i = m_size; i > currPos; i--)
            {
                array[i] = array[i - 1];
            }

            array[currPos] = value;
            m_size++;
        }
    };

    template<class T>
    class LinkedList
    {

    };

    template<class T>
    class ArrayStack
    {

    };

    template<class T>
    class LinkedStatck
    {

    };

    template<class T>
    class ArrayQueue
    {

    };

    template<class T>
    class LinkedQueue
    {

    };
}
