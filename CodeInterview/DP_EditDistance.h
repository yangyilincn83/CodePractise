#pragma once

#include <iostream>
#include <cassert>
#include <string>

using namespace std;

namespace Algorithm
{
    int MinValue(int v1, int v2, int v3)
    {
        return min(min(v1, v2), v3);
    }

    /**
        Calculate the distance between two strings.

        For string A and B, there are a series operations
        1. Change a character
        2. Add a character
        3. Delete a character

        The distance is the smallest number of operations that can change A into B.
     */
    int CalculateDistance(string strA, int iABegin, int iAEnd, string strB, int iBBegin, int iBEnd)
    {
        // edge case
        if (iABegin > iAEnd)
        {
            if (iBBegin > iBEnd)
            {
                return 0;
            }
            else
            {
                return iBEnd - iBBegin + 1;
            }
        }

        // edge case
        if (iBBegin > iBEnd)
        {
            if (iABegin > iAEnd)
            {
                return 0;
            }
            else
            {
                return iAEnd - iABegin + 1;
            }
        }

        if (strA[iABegin] == strB[iBBegin])
        {
            return CalculateDistance(strA, iABegin + 1, iAEnd, strB, iBBegin + 1, iBEnd);
        }
        else
        {
            // Delete strA's first character and calculate distance between strA[2,...,lenA] and strB[1,...,lenB] ---> d1
            // Delete strB's first character and calculate distance between strA[1,...,lenA] and strB[2,...,lenB] ---> d2
            // Modify strA's first character and calculate distance between strA[2,...,lenA] and strB[2,...,lenB] ---> d3
            // Modify strB's first character and calculate distance between strA[2,...,lenA] and strB[2,...,lenB] ---> d3
            // Add strB's first character before strA and calculate distance between strA[1,...,lenA] and strB[2,...,lenB] ---> d2
            // Add strA's first character before strB and calculate distance between strA[2,...,lenA] and strB[1,...,lenB] ---> d1
            int d1 = CalculateDistance(strA, iABegin + 1, iAEnd, strB, iBBegin, iBEnd);
            int d2 = CalculateDistance(strA, iABegin, iAEnd, strB, iBBegin + 1, iBEnd);
            int d3 = CalculateDistance(strA, iABegin + 1, iAEnd, strB, iBBegin + 1, iBEnd);
            return MinValue(d1, d2, d3) + 1;
        }
    }
}