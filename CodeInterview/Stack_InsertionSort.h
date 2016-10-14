#pragma once

#include "stdafx.h"
#include <iostream>
#include <stack>

using namespace std;

namespace Algorithm
{
    void StackInsertSort(stack<int>& s)
    {
        if (s.size() == 1)
            return;

        int topElem = s.top();
        s.pop();
        StackInsertSort(s);

        stack<int> tempS;

        // find the first number that is greater than the top element
        while (!s.empty())
        {
            if (topElem < s.top())
            {
                break;
            }
            else
            {
                tempS.push(s.top());
                s.pop();
            }
        }

        // push the top element into the stack being sorted
        s.push(topElem);

        // pop all elements from tempS and push into s
        while (!tempS.empty())
        {
            s.push(tempS.top());
            tempS.pop();
        }
    }

    void StackInsertSortTest()
    {
        #define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])
        int numbers[] = { 34, 12, 9, 4, 5, 14, 11, 24, 25, 1 };
        stack<int> s;
        for (int i = 0; i < ARRAY_SIZE(numbers); i++)
            s.push(numbers[i]);

        StackInsertSort(s);

        while (!s.empty())
        {
            cout << s.top() << ",";
            s.pop();
        }
        cout << endl;
    }
}