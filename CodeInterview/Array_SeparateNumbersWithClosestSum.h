#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

namespace Algorithm
{
    static vector<int> ResultSequence;
    static int MinDiff = INT_MAX;

    inline void FindClosestGap(int numbers[], int index, int size, int numOfElements, int capacity, vector<int>& temp)
    {
        // found a perface sum equal to original capacity
        if (capacity == 0)
        {
            MinDiff = 0;
            ResultSequence = temp;
        }

        if (numOfElements == 0 && capacity < MinDiff)
        {
            MinDiff = capacity;
            ResultSequence = temp;
        }

        for (int i = index; i < size; i++)
        {
            if (capacity < numbers[i])
            {
                continue;
            }

            // try pushing each element
            temp.push_back(i);

            // find the closest gap with the above element pushed
            FindClosestGap(numbers, i + 1, size, numOfElements - 1, capacity - numbers[i], temp);

            // backtracking and try next element
            temp.pop_back();
        }
    }

    inline void SeparateNumberWithClosestSum(int numbers[], int size)
    {
        assert(size % 2 == 0);

        int K = size / 2;
        int SUM = 0;
        vector<int> trackingSequence;
        for (int i = 0, SUM = 0; i < size, SUM += numbers[i]; i++);

        // For two parts of K numbers the sum of which is SUM, the closer the two parts, the closer each part is to SUM/2.
        // So the question is to find the K numbers the SUM of which is closest to SUM/2.
        FindClosestGap(numbers, size, 0, size / 2, SUM / 2, trackingSequence);

        // print out result sequence
        for_each(trackingSequence.begin(), trackingSequence.end(), [=](auto& value) { cout << value << ", "; });
    }
}