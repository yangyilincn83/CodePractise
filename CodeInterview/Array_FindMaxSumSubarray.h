#pragma once

#include <iostream>
#include <cassert>
#include <utility>
#include <algorithm>

using namespace std;

namespace Algorithm
{
    pair<int, int> FindMaxSumSubarray1(int numbers[], int size)
    {
        int start = 0;
        int end = 0;
        int sum = INT32_MIN;
        int tempStart = 0;
        int tempEnd = 0;
        int tempSum = 0;

        // Calculate the first temp sum
        for (int i = tempStart; i <= tempEnd; i++)
        {
            tempSum += numbers[i];
        }

        while (tempEnd < size)
        {
            // if tempSum is greater than sum, update sum
            // if not, keep moving forward if necessary
            if (tempSum > sum)
            {
                sum = tempSum;
                start = tempStart;
                end = tempEnd;
            }

            if (tempSum < 0)
            {
                // it doesn't make sense to keep including more elements
                // move forward to next window
                tempEnd++;
                tempStart = tempEnd;
                tempSum = numbers[tempStart];
            }
            else
            {
                // move forward temp end to see if there's a bigger window with bigger sum
                tempEnd++;
                tempSum += numbers[tempEnd];
            }
        }

        return pair<int, int>(start, end);
    }

    pair<int, int> FindMaxSumSubarray2(int numbers[], int size)
    {
        int maxSum = INT_MIN;
        int currSum = INT_MIN;
        pair<int, int> maxRange;
        pair<int, int> currRange;

        for (int i = 0; i < size; i++)
        {
            if (currSum + numbers[i] < numbers[i])
            {
                // abandon previous temporary max range and start a new one
                currRange = make_pair(i, i);
                currSum = numbers[i];
            }
            else
            {
                // move temporary max range forward
                currSum += numbers[i];
                currRange.second = i;
            }

            if (currSum >= maxSum)
            {
                // found a better max range
                maxSum = currSum;
                maxRange = currRange;
            }
        }

        return currRange;
    }
}