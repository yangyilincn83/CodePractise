#pragma once

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <memory>

using namespace std;

namespace Algorithm
{
    /*
        Find the longest subsequence in which the elements' value are increasing. The elements are not necessarily consecutive.

        Analysis:
                      /  F(i) + 1   A[i] <= A[j] && 0<=i<=j
         F(j) =  Max |
                      \  1          A[i] > A[j] && 0<=i<=j
    */
    int FindLongestNonConsecutiveIncrementalSequence(int numbers[], int size)
    {
        int* tempMaxLength = new int[size];

        for (int i = 0; i < size; i++)
        {
            // max sequence length ending with numbers[i]
            int currMax = 0;

            for (int j = 0; j <= i; j++)
            {
                if (i == j)
                {
                    currMax = currMax > 1 ? currMax : 1;
                }
                else
                {
                    if (numbers[i] < numbers[j])
                    {
                        currMax = currMax > 1 ? currMax : 1;
                    }
                    else
                    {
                        currMax = currMax > (tempMaxLength[j] + 1) ? currMax : (tempMaxLength[j] + 1);
                    }
                }
            }

            tempMaxLength[i] = currMax;
        }

        for (int i = 0; i < size; i++)
        {
            cout << "Length of Longest Incremental Subsequence Ending with numbers[" << i << "]: " << tempMaxLength[i] << endl;
        }

        int globalMaxLength = *(std::max_element(tempMaxLength, tempMaxLength + size));
        cout << "Length of Longest Incremental Subsequence: "<< globalMaxLength << endl;

        delete[] tempMaxLength;
        return globalMaxLength;
    }

    /*
        Find the longest consecutive incremental subsequence.
    */
    pair<int, int> FindLongestConsecutiveIncrementalSequence(int numbers[], int size)
    {
        int start = 0;
        int end = 0;
        int length = 0;

        int tempStart = start;
        int tempEnd = end;
        while (tempEnd < size)
        {
            // Find next incremental segment
            for (; tempEnd < size - 1 && numbers[tempEnd] <= numbers[tempEnd + 1]; tempEnd++);

            // Get this incremental segment legnth
            int tempLength = tempEnd - tempStart + 1;

            // If this length is better than result candidate, log it as a new candidate
            if (tempLength > length)
            {
                start = tempStart;
                end = tempEnd;
                length = tempLength;
            }

            tempEnd++;
            tempStart = tempEnd;
        }

        return make_pair(start, end);
    }

    pair<int, int> FindLongestIncrementalSequenceWithCircleBack(int numbers[], int size)
    {
        int start = 0;
        int end = 0;
        int length = 0;

        int tempStart = start;
        int tempEnd = end;
        while (tempEnd < size)
        {
            // Find next incremental segment
            for (; tempEnd < size - 1 && numbers[tempEnd] <= numbers[tempEnd + 1]; tempEnd++);

            // Get this incremental segment legnth
            int tempLength = tempEnd - tempStart + 1;

            // If this length is better than result candidate, log it as a new candidate
            if (tempLength > length)
            {
                start = tempStart;
                end = tempEnd;
                length = tempLength;
            }

            // If temporary segment end is the end of array, continue to search from the beginning
            if (tempEnd == size - 1)
            {
                for (; numbers[tempEnd] <= numbers[(tempEnd + 1) % size];)
                {
                    tempEnd = (tempEnd + 1) % size;
                    tempLength++;
                }

                start = tempStart;
                end = tempEnd;
                length = tempLength;

                break;
            }

            tempEnd++;
            tempStart = tempEnd;
        }

        return pair<int, int>(start, end);
    }
}