#pragma once

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

namespace Algorithm
{
    class StackWithMaxElement
    {
        /*
            Solution 1: Create an auxiliary stack.
            - Push the element into the aux stack if it's the first element pushed into original stack
            - When pushing a new element into the original stack, compare it with the top of aux stack. If it's bigger, push it into aux stack; otherwise push the top of aux stack into aux stack
            - When poping an element, pop the element from aux stack as well.
        */

        // Solution 2 (only apply to number type)
    private:
        stack<int> dataStack;
        int max;

    public:
        StackWithMaxElement(stack<int>&& s)
        {
            dataStack.swap(s);
        }

        StackWithMaxElement()
        {
        }

        int size()
        {
            return dataStack.size();
        }

        bool empty()
        {
            return dataStack.empty();
        }

        void Push(const int& value)
        {
            if (dataStack.empty())
            {
                max = value;
                dataStack.push(value);
            }
            else
            {
                if (max >= value)
                {
                    dataStack.push(value);
                }
                else
                {
                    dataStack.push(2 * value - max);
                    max = value;
                }
            }
        }

        int Top()
        {
            assert(!dataStack.empty());
            
            return (dataStack.top() > max) ? max : dataStack.top();
        }

        void Pop()
        {
            assert(!dataStack.empty());

            if (dataStack.top() > max)
            {
                max = 2 * max - dataStack.top();
            }

            dataStack.pop();
        }

        int GetMax()
        {
            assert(!dataStack.empty());
            return max;
        }
    };
}
