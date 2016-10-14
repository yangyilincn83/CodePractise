#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

namespace Algorithm
{
    string String_FindLongestSubstringWithMUniqueCharacters(string str, int m)
    {
        int charCount[256] = {};
        string result = "";

        int length = str.length();
        if (length < m)
        {
            return "";
        }

        int begin = 0;
        int end = 0;
        int uniqueCharCount = 0;

        while (end < length)
        {
            // Increase unique character count if a new character
            if (charCount[str[end]] == 0)
            {
                uniqueCharCount++;
            }

            // Increase character count
            charCount[str[end]]++;
            cout << "character count:" << charCount[str[end]] << " for char:" << str[end] << endl;

            if(uniqueCharCount == m)
            {
                // continue to extend until a new character
                while ((charCount[str[end + 1]] > 0) && (end + 1 < length))
                {
                    end++;
                    charCount[str[end]]++;
                }

                // record it as a result if necessary
                if (result.length() < (end - begin + 1))
                {
                    result = str.substr(begin, end - begin + 1);
                    cout << "possible result: " << result.c_str() << endl;
                }
            }
            else if(uniqueCharCount < m)
            {
            }
            else
            {
                // move beginning forward until a character whose count is 1
                while ((charCount[str[begin]] > 1) && (begin <= end))
                {
                    charCount[str[begin]]--;
                    begin++;
                }

                if (charCount[str[begin]] == 1)
                {
                    charCount[str[begin]] = 0;
                    begin++;
                    uniqueCharCount--;
                    cout << "adjusted begin position is: " << begin << endl;
                    cout << "current unique char count is: " << uniqueCharCount << endl;
                    cout << "current end position is: " << end << endl;
                }
            }

            // continue to extend
            end++;
        }

        return result;
    }

    void FindLongestSubstringWithUniqueCharactersTest()
    {
        string string1 = "packagemanager";
        cout << String_FindLongestSubstringWithMUniqueCharacters(string1, 5).c_str() << endl;
    }
}