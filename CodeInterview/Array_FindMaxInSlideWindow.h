#pragma once

#include "stdafx.h"
#include <queue>
#include <list>
#include <memory>
#include <cassert>
#include <iostream>

using namespace std;

namespace Algorithm
{
    vector<int> FindMaxInSlideWindow(int numbers[], int size, int k)
    {
        assert(size >= k);

        vector<int> v_max;
        list<int> q_aux;
        int tempMax = INT_MIN;
        int tempMaxIndex = -1;

        for (int currPos = 0; currPos < size; currPos++)
        {
            while(true)
            {
                if (q_aux.empty() || numbers[currPos] <= numbers[q_aux.back()])
                {
                    // push directly if quque is empty or less then the end element
                    q_aux.push_back(currPos);
                    break;
                }
                else
                {
                    // pop the end element and continue
                    q_aux.pop_back();
                }
            }

            // Need to push a max for each position >= k-1
            if (currPos >= k - 1)
            {
                if (currPos >= q_aux.front() + k)
                {
                    q_aux.pop_front();
                }

                v_max.push_back(numbers[q_aux.front()]);
            }
        }

        return v_max;
    }

    void FindMaxInSlideWindowTest()
    {
        int numbers1[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
        int numbers2[] = { 2, 2, 2, 2, 2, 2, 2, 2 };
        int numbers3[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        int numbers4[] = { 8, 3, 4, 9, 6, 2, 5, 3, 11 };

        vector<int> max = FindMaxInSlideWindow(numbers1, sizeof(numbers1) / sizeof(int), 3);
        for_each(max.begin(), max.end(), [&](int& value) -> void { cout << value << ";"; }); cout << endl;

        max = FindMaxInSlideWindow(numbers2, sizeof(numbers2) / sizeof(int), 3);
        for_each(max.begin(), max.end(), [&](int& value) -> void { cout << value << ";"; }); cout << endl;

        max = FindMaxInSlideWindow(numbers3, sizeof(numbers3) / sizeof(int), 3);
        for_each(max.begin(), max.end(), [&](int& value) -> void { cout << value << ";"; }); cout << endl;

        max = FindMaxInSlideWindow(numbers4, sizeof(numbers4) / sizeof(int), 3);
        for_each(max.begin(), max.end(), [&](int& value) -> void { cout << value << ";"; }); cout << endl;
    }
}