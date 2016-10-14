#pragma once

#include "stdafx.h"
#include <iostream>
#include <stack>

using namespace std;

namespace Algorithm
{
    /*
        Solution 1: Use two stack A and B to implement the queue.
        For each stack, there's an additional stack AMax, BMax being created to push/pop the current Max
        element for each push/pop operation happening in A and B.
    */
    template<typename T>
    class QueueWithMax1
    {
    private:
        stack<T> m_EnqueueStack;
        stack<T> m_DequeueStack;
        stack<T> m_EnqueueStackMax;
        stack<T> m_DequeueStackMax;
        int m_size;

        void TransferElements()
        {
            // Pop each element from m_EnqueueStack and push into m_DequeueStack
            while (!m_EnqueueStack.empty())
            {
                // push the top element of m_EnqueueStack to m_DequeueStack
                m_DequeueStack.push(m_EnqueueStack.top());

                // update m_DequeueStackMax
                if (m_DequeueStackMax.empty())
                {
                    m_DequeueStackMax.push(m_DequeueStack.top());
                }
                else
                {
                    m_DequeueStackMax.push(m_DequeueStack.top() > m_DequeueStackMax.top() ? m_DequeueStack.top() : m_DequeueStackMax.top());
                }

                // pop the top element from m_EnqueueStack
                m_EnqueueStack.pop();

                // remove the top max element from m_EnqueueStackMax 
                m_EnqueueStackMax.pop();
            }
        }

    public:
        QueueWithMax1(int size) : m_size(size) { assert(size > 0); }

        void Enqueue(const T& value)
        {
            if ((m_EnqueueStack.size() == m_size) && (!m_DequeueStack.empty()))
            {
                // if m_EnqueueStack is full and m_DequeueStack isn't empty, no enqueue is allowed
                return;
            }

            if (m_EnqueueStack.size() == m_size)
            {
                TransferElements();
            }

            // update m_EnqueueStackMax
            if (m_EnqueueStackMax.empty())
            {
                m_EnqueueStackMax.push(value);
            }
            else
            {
                m_EnqueueStackMax.push(value > m_EnqueueStack.top() ? value : m_EnqueueStack.top());
            }

            // directly push the element into m_EnqueueStack
            m_EnqueueStack.push(value);
        }

        T Dequeue()
        {
            assert(!m_DequeueStack.empty());

            T retVal = m_DequeueStack.top();
            m_DequeueStack.pop();
            m_DequeueStackMax.pop();

            if (m_DequeueStack.empty())
            {
                TransferElements();
            }

            return retVal;
        }

        T MaxElement()
        {
            assert(!m_DequeueStack.empty());
            return (m_DequeueStack.top() > m_DequeueStack.top() ? m_DequeueStack.top() : m_DequeueStack.top());
        }
    };

    /*
        Solution 1: Use one queue Q and one deque DQ
        - When enqueuing a new element into Q, pop back DQ when the element is greater than the end of DQ.
        - Insert the element into DQ
        - When dequeuing an element from Q, compare this element with front of DQ, if equal, pop front DQ as well
    */
    template<class T>
    class QueueWithMax2
    {
    private:
        queue<T> m_q;
        deque<T> m_maxq;

    public:
        void Enque(const T& value)
        {
            m_q.push(value);

            if (m_maxq.empty())
            {
                // only one element, push it as max
                m_maxq.push_back(value);
            }
            else
            {
                while (!m_maxq.empty() && m_maxq.back() < value)
                {
                    m_maxq.pop_back();
                }

                m_maxq.push_back(value);
            }
        }

        T Dequque()
        {
            // get the front element
            T& result = m_q.front();
            m_q.pop();

            // update max queue
            if (result == m_maxq.front())
            {
                m_maxq.pop_front();
            }

            return result;
        }

        T GetMax()
        {
            return m_maxq.front();
        }

        int size()
        {
            return m_q.size();
        }

        bool empty()
        {
            return m_q.empty();
        }
    };
}