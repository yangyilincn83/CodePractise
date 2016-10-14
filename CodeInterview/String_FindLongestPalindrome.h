#pragma once

#include <iostream>
#include <cassert>
#include <set>
#include <map>

using namespace std;

namespace Algorithm
{

    /*
        Solution 1: Dynamic Programming
    */
    int MaxSubstrLength = 0;
    int MaxSubstrIndex = -1;
    std::map<std::pair<int, int>, int> MemoizationTable;

    int FindLongestCommonSubstr(const char* source, int index1, const char* comparison, int index2)
    {
        assert(source != nullptr && comparison != nullptr);
        int substrLength = 0;

        // check memoization table, return the result if it exists
        if (MemoizationTable.find(std::make_pair(index1, index2)) != MemoizationTable.end())
        {
            return MemoizationTable[make_pair(index1, index2)];
        }

        // If one of the strings reaches the end, substr is length 0
        if ((strlen(source) == index1) || (strlen(comparison) == index2))
        {
            MemoizationTable[make_pair(index1, index2)] = 0;
            return 0;
        }

        // If the first char of the two strings are equal, try to check the following chars' values
        if (*(source + index1) == *(comparison + index2))
        {
            substrLength = 1 + FindLongestCommonSubstr(source, index1 + 1, comparison, index2 + 1);
            if (substrLength > MaxSubstrLength)
            {
                MaxSubstrLength = substrLength;
                MaxSubstrIndex = index1;
            }
        }

        // Continue to process the subproblem with their results ignored 
        // if there's better result, it will update the global variable anyway
        FindLongestCommonSubstr(source, index1 + 1, comparison, index2);
        FindLongestCommonSubstr(source, index1, comparison, index2 + 1);

        MemoizationTable[make_pair(index1, index2)] = substrLength;
        return substrLength;
    }

    std::pair<int, int> FindLongestPalindrome(const char* str)
    {
        assert(str != nullptr);

        int size = strlen(str);
        char* reversedStr = nullptr;

        reversedStr = reinterpret_cast<char*>(calloc(size + 1, sizeof(char)));
        if (reversedStr == nullptr)
        {
            throw bad_alloc();
        }

        // copy original str to reversedStr
        strcpy(reversedStr, str);

        // reverse the string value in reversedStr
        std::reverse(reversedStr, reversedStr + size);

        // find the longest substring which is the result palindrome
        FindLongestCommonSubstr(str, 0, reversedStr, 0);

        free(reversedStr);
        return make_pair(MaxSubstrIndex, MaxSubstrLength);
    }

    /*
        Manacher's Algorithm
    */
}