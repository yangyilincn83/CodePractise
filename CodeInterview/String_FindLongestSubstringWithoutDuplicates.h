#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Algorithm
{
    string FindLongestSubstringWithoutDuplicates(string source)
    {
        int length = source.length();
        if (length == 0)
            return "";

        pair<int, int> substrIndex;
        int start = 0;
        int end = 0;
        int maxLength = 0;
        int currLength = 0;
        int charMap[256];
        for_each(charMap, charMap + 256, [](int& index) { index = -1; });

        while (end < length)
        {
            if (charMap[source[end]] >= 0)
            {
                start = charMap[source[end]] + 1;
                charMap[source[end]] = end;
                currLength = end - start + 1;
            }
            else
            {
                charMap[source[end]] = end;
                currLength = end - start + 1;
            }

            if (currLength > maxLength)
            {
                maxLength = currLength;
                substrIndex.first = start;
                substrIndex.second = end;
            }

            end++;
        }

        return source.substr(start, maxLength);
    }

    void FindLongestSubstringWithoutDuplicatesTest()
    {
        string s = "ABCDEFGACDHIJ";
        cout << "The longest substring is "<< FindLongestSubstringWithoutDuplicates(s).c_str() << endl;
    }
}
