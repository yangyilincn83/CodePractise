#pragma once

#include <iostream>
#include <cassert>
#include <set>
#include <map>

using namespace std;

namespace Algorithm
{
    int PermutationTotal = 0;

    // Print all permutations of a given string (duplicate characters considered)
    void PrintPermutation(char* str, int index)
    {
        assert(str != nullptr);

        int size = 0;
        std::set<char> exchangeSet;

        size = strlen(str);
        if (size == 0)
            return;

        if (index == size - 1)
        {
            // last character, print out the permutation
            PermutationTotal++;
            printf("Found one permuation: %s\n", str);
            return;
        }

        // With first char unchanged, print the permutation for the rest
        PrintPermutation(str, index + 1);

        // Starting from second char, exchange with the first char if the char is different and never exchagned before
        for (int i = index + 1; i < size; i++)
        {
            if ((str[i] != str[index]) &&
                (exchangeSet.find(str[i]) == exchangeSet.cend()))
            {
                exchangeSet.insert(str[i]);
                std::swap(str[index], str[i]);
                PrintPermutation(str, index + 1);
                std::swap(str[index], str[i]);
            }
        }
    }

    void RemoveDuplicates(char* str)
    {
        assert(str != nullptr);
        int size = strlen(str);
        int writePos = 0;
        std::unordered_map<char, int> countMap; // or int count[256] 

        // count the occurances
        for_each(str, str + size, [&](char ch) -> void {
            countMap[ch]++;
        });

        for_each(str, str + size, [&](char ch) -> void {
            if (countMap[ch] <= 1)
            {
                str[writePos++] = ch;
            }
        });

        str[writePos] = '\0';
    }

    bool IsShuffle(const char* target, const char* source1, const char* source2)
    {
        assert(target != nullptr && source1 != nullptr && source2 != nullptr);

        bool isShuffle = false;
        int len = strlen(target);
        int len1 = strlen(source1);
        int len2 = strlen(source2);

        // end of the target string, must decide
        if (len == 0)
        {
            // is a shuffle if both end of the two source strings are reached
            isShuffle = (len1 == 0) && (len2 == 0);
            return isShuffle;
        }

        if ((len1 > 0) && (*target == *source1))
        {
            isShuffle = IsShuffle(target + 1, source1 + 1, source2);
        }

        if (!isShuffle)
        {
            if ((len2 > 0) && (*target == *source2))
            {
                isShuffle = IsShuffle(target + 1, source1, source2 + 1);
            }
        }

        return isShuffle;
    }
}