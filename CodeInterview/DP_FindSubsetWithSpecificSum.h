#pragma once

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <cassert>
#include <algorithm>

using namespace std;

namespace Algorithm
{
    /*
        Find a given sum of an array subset

        numbers: number array
        index:   last index of the subset
    */
    void FindSubsetWithSpecificSum(int numbers[], int index, int sum)
    {
        static stack<int> resultStack;

        // sum is zero with non empty stack
        if (sum == 0 && !resultStack.empty())
        {
            cout << "Found subset: ";
            for_each(
                resultStack._Get_container().begin(),
                resultStack._Get_container().end(),
                [] (const int& element) {
                cout << element << " ; ";
            });
            cout << endl;
        }

        // reach out of bound, return directly
        if (index < 0)
        {
            return;
        }

        // keep searching
        for (int i = index; i >= 0; i--)
        {
            resultStack.push(numbers[i]);
            FindSubsetWithSpecificSum(numbers, i - 1, sum - numbers[i]);
            resultStack.pop();
        }
    }

    void FindSubsetWithZeroSumTest()
    {
        int numbers[] = { -3, 4, 6, -7, -8, 3, 5 };
        FindSubsetWithSpecificSum(numbers, sizeof(numbers) / sizeof(int), 0);
    }
}