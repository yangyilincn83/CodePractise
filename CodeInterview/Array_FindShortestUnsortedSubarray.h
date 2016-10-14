#pragma once

#include "stdafx.h"
#include <string>
#include <utility>

using namespace std;

namespace Algorithm
{
    /*
        Find the shortest length subarray, which makes the whole array sorted if it is being sorted.
    */
    pair<int, int> FindShortestUnsortedSubarray(int numbers[], int size)
    {
        pair<int, int> result;

        // find first inversion
        int first_inversion_index = -1;
        for (int i = 0; i < size - 1; i++)
        {
            if (numbers[i] > numbers[i + 1])
            {
                first_inversion_index = i;
                break;
            }
        }

        if (first_inversion_index == -1)
        {
            // sorted array, return directly
            return make_pair(0, 0);
        }

        int min = INT_MIN;
        int max = INT_MAX;
        int last_inversion_index = first_inversion_index;
        for (int i = last_inversion_index; i < size - 1; i++)
        {
            // update min and max
            if (numbers[i] < min) min = numbers[i];
            if (numbers[i] > max) max = numbers[i];

            // find next inversion
            if (numbers[i] > numbers[i + 1])
            {
                last_inversion_index = i;
            }
        }

        // set result to the range temporarily
        result.first = first_inversion_index;
        result.second = last_inversion_index + 1;

        // For the range from first inversion to last inversion,
        // - Find the first number on the left that's less than min
        // - Find the last number on the right that's bigger than max
        for (int i = 0; i < result.first; i++)
        {
            if (numbers[i] > numbers[result.first])
            {
                result.first = i;
                break;
            }
        }

        for (int i = size -1; i > result.second; i--)
        {
            if (numbers[i] < numbers[result.second])
            {
                result.first = i;
                break;
            }
        }

        return result;
    }
}