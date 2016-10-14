#pragma once

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;

namespace Algorithm
{
    /*
         Question 1: Given an array, please get the length of the longest arithmetic sequence.
         The element order in the arithmetic sequence should be same as the element order in the array.
         For example, in the array {1, 6, 3, 5, 9, 7}, the longest arithmetic sequence is 1, 3, 5, and 7,
         whose elements have same order as they are in the array, and the length is 4.
     */
    int FindLongestArithmaticSequence(int numbers[], int length)
    {
        // pair map organized by number difference
        // the pairs with same difference are put into one ordered set (ordered by first number)
        unordered_map<int, set<pair<int, int>>> pairMap;

        // for a specific set, record max sequence length for each beginning number
        unordered_map<int, int> seqLength;

        // recorded maximum length
        int maxLength = 0;

        // Find all pairs and put them into a hash map with key as their difference
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < j; i++)
            {
                pairMap[numbers[j] - numbers[i]].emplace(i, j);
            }
        }

        // For each gap difference, find the longest sequence in those pairs
        // Update the max legnth against each consecutive sequence
        for (auto& iter : pairMap)
        {
            int tempMaxLength = 0;
            for (pair<int, int> pair : iter.second)
            {
                if (seqLength.find(pair.first) == seqLength.end())
                {
                    seqLength[pair.second] = 2;
                }
                else
                {
                    seqLength[pair.second] = seqLength[pair.first] + 1;
                }

                if (seqLength[pair.second] > tempMaxLength)
                {
                    tempMaxLength = seqLength[pair.second];
                }
            }

            cout << "The longest arithmatic sequence for number difference " << iter.first << " is: " << tempMaxLength << endl;

            if (tempMaxLength > maxLength)
            {
                maxLength = tempMaxLength;
            }

            seqLength.clear();
        }

        return maxLength;
    }

    void FindLongestArithmaticSequenceTest()
    {
        int numbers[] = { 1, 6, 3, 5, 9, 7, 11, 15, 13, 12, 15, 19, 18, 23, 21, 27 };
        cout << "The longest arithmetic sequence is: " << FindLongestArithmaticSequence(numbers, sizeof(numbers) / sizeof(int)) << endl;
    }

    /*
    Question 3: Given an array, please get the length of the longest consecutive sequence.
    A consecutive sequence is an arithmetic sequence with common difference 1.
    The element order in the consecutive sequence is not necessarily same as the element order in the array.
    The solution should not cost more than O(n) time and space if the length of the input array is n.
    For example, in the array {1, 6, 3, 5, 9, 7}, the longest consecutive sequence is 5, 6, and 7 whose length is 3.
    */
    int FindConsecutiveSequence(int numbers[], int length)
    {
        unordered_set<int> set;
        int maxSeqLength = 0;

        for (int i = 0; i < length; i++)
        {
            set.insert(numbers[i]);
        }

        while (!set.empty())
        {
            int num = *(set.begin());   // pick any number from the set
            int pivot = num;            // use this number as pivot
            int tempSeqLength = 0;

            // move pivot up to find more numbers
            while (true)
            {
                if (set.find(++pivot) == set.end())
                {
                    break;
                }

                tempSeqLength++;
                set.erase(pivot);
            }

            // move pivot down to find more numbers
            pivot = num;
            while (true)
            {
                if (set.find(--pivot) == set.end())
                {
                    break;
                }

                tempSeqLength++;
                set.erase(pivot);
            }

            tempSeqLength++; // including num in the sequence
            set.erase(num);

            if (tempSeqLength > maxSeqLength)
            {
                maxSeqLength = tempSeqLength;
            }
        }

        return maxSeqLength;
    }

    void FindConsecutiveSequenceTest()
    {
        int numbers[] = { 1, 6, 3, 2, 4, 10, 11, 15, 13, 12, 5, 14, 8, 23, 21, 7, 16, 18, 17 };
        cout << "The longest consecutive sequence is: " << FindConsecutiveSequence(numbers, sizeof(numbers) / sizeof(int)) << endl;
    }
}
