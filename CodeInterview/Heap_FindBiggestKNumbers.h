#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <algorithm>
#include <queue>

using namespace std;

namespace Algorithm
{
    inline vector<int> FindBiggestKNumbersUsingHeap(int numbers[], int size, int k)
    {
        assert(size >= k);

        // Construct a k-size vector
        vector<int> tempHeap;
        for (int i = 0; i < k; i++)
        {
            tempHeap.push_back(numbers[i]);
        }

        // Make the vector into a min-hep
        make_heap(tempHeap.begin(), tempHeap.end(), greater<int>());

        // Traverse the rest of the array and if the number is greater than the min, pop out the min and insert this number into the min-heap instead
        for (int i = k; i < size; i++)
        {
            if (numbers[i] > tempHeap.front())
            {
                // pop_heap to move the min to the end
                pop_heap(tempHeap.begin(), tempHeap.end(), greater<int>());

                // pop back the min
                tempHeap.pop_back();

                // push back the new number
                tempHeap.push_back(numbers[i]);

                // push_heap to maintain the heap
                push_heap(tempHeap.begin(), tempHeap.end(), greater<int>());
            }
        }

        return tempHeap;
    }

    inline vector<int> FindFirstKNumbersUsingPriorityQueue(int numbers[], int size, int k)
    {
        assert(size >= k);

        vector<int> result;
        priority_queue<int, vector<int>, greater<int>> queue;

        for (int i = 0; i < k; i++)
        {
            queue.push(numbers[i]);
        }

        for (int i = k; i < size; i++)
        {
            if (queue.top() < numbers[i])
            {
                queue.pop();
                queue.push(numbers[i]);
            }
        }

        while (!queue.empty())
        {
            result.push_back(queue.top());
            queue.pop();
        }

        return result;
    }

    inline vector<int> FindBiggestKNumbersUsingQuickSort(int numbers[], int size, int k)
    {
        assert(size >= k);
        vector<int> result;

        int start = 0;
        int end = size - 1;

        while (start < end)
        {
            // select the middle number as the pivot and swap with the end
            // similar to quick sort
            int middle = (start + end) / 2;
            int pivot = numbers[middle];
            swap(numbers[middle], numbers[end]);
            cout << "current pivot is at index[" << middle << "], value is: " << pivot << endl;
            cout << "current range is from index[" << start << "] to : [" << end << "]" << endl;

            int forward = start;
            int backward = end - 1;
            while (forward < backward)
            {
                if (numbers[forward] < pivot)
                {
                    forward++;
                }
                else
                {
                    swap(numbers[forward], numbers[backward]);
                    backward--;
                }
            }

            // swap pivot back
            // backward should be one position ahead of the first number not smaller than pivot
            swap(numbers[backward + 1], numbers[end]);

            int biggerRangeSize = end - (backward + 1) + 1;
            if (biggerRangeSize > k)
            {
                // search in the greater number range
                start = backward + 1;
            }
            else if (biggerRangeSize < k)
            {
                // search in the smaller number range
                end = backward;
                k = k - biggerRangeSize;
            }
            else
            {
                // return the result from the divider element to size - 1
                for (int i = backward + 1; i <= size - 1; i++)
                {
                    result.push_back(numbers[i]);
                }

                // quit the loop
                break;
            }
        }

        return result;
    }

    inline void FindBiggestKNumbersTest()
    {
        int numbers[] = { 21, 1, 4, 11, 5, 9, 4 ,6, 23, 7, 10, 9, 2, 15, 14, 8, 19 };
        int size = sizeof(numbers) / sizeof(int);
        vector<int> result = FindBiggestKNumbersUsingQuickSort(numbers, size, 5);
        cout << "result size: " << result.size() << endl;
        for_each(result.begin(), result.end(), [&](const int& value) -> void { cout << value << ", "; });
    }
}