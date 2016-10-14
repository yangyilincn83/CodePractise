#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

namespace Algorithm
{
    void RemoveDuplidates(int * sortedNumArray, int size)
    {
        _ASSERTE(sortedNumArray != NULL);
        _ASSERTE(size > 0);

        int currWritePos = 0;
        int currTraversePos = 0;

        while (currTraversePos < size)
        {
            if (sortedNumArray[currWritePos] != sortedNumArray[currTraversePos])
            {
                currWritePos++;
                sortedNumArray[currWritePos] = sortedNumArray[currTraversePos];
            }

            currTraversePos++;
        }
    }
}