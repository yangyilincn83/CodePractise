#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include <queue>
#include <functional>

using namespace std;

namespace Algorithm
{
    template<typename T>
    class CollectionWithMedian
    {
    private:
        priority_queue<T> m_smallerHalf;
        priority_queue<T, std::greater<T>> m_largerHalf;
        int m_size;

    public:
        CollectionWithMedian() : m_size(0) {}
        void Push(const T& value)
        {
            if (m_size % 2 == 0)
            {
                // m_size is even, insert a new element into larger half
                if (m_smallerHalf.empty() || m_smallerHalf.top() < value)
                {
                    m_largerHalf.push(value);
                }
                else
                {
                    // insert the new element into smaller half first
                    m_smallerHalf.push(value);

                    // insert the max element of the smaller half into larger half
                    m_largerHalf.push(m_smallerHalf.top());

                    m_smallerHalf.pop();
                }
            }
            else
            {
                // m_size is odd, insert a new element into smaller half
                if (m_largerHalf.top() > value)
                {
                    m_smallerHalf.push(value);
                }
                else
                {
                    // insert the new element into larger half first
                    m_largerHalf.push(value);

                    // insert the min element of the larger half into smaller half
                    m_smallerHalf.push(m_largerHalf.top());

                    m_largerHalf.pop();
                }
            }

            m_size++;
        }

        std::tuple<T> GetMedian()
        {
            if (m_size % 2 == 1)
            {
                return make_tuple(m_largerHalf.top());
            }
            else
            {
                return make_tuple(m_smallerHalf.top(), m_largerHalf.top());
            }
        }
    };
}