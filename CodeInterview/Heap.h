#pragma once

#include "stdafx.h"
#include <new>

using namespace std;

namespace DataStructure
{
    template<typename T>
    class Heap
    {
    private:
        unsigned int m_size;
        unsigned int m_capacity;
        T* m_elements;

    public:
        Heap(T elements[], unsigned int capacity) : m_elements(elements), m_capacity(capacity), m_size(0) {}

        ~Heap()
        {
            elements = nullptr;
            m_capacity = 0;
            m_size = 0;
        }

        void BuildHeap(unsigned int size);
        void Push(T& value);
        void Pop();
        const T& Top();
        const T& Remove(int index);
        void Update(int index, T newValue);
        void ShiftDown(int index);
        void ShiftUp(int index);
    };
}