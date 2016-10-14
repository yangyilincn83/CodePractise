#pragma once

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <cassert>

using namespace std;

namespace Algorithm
{
    int FindLongestCommonSubsequence(int sequence1[], int size1, int index1, int sequence2[], int size2, int index2)
    {
        int maxSequenceLength = 0;

        if ((index1 == size1) || (index2 == size2))
        {
            return 0;
        }

        if (sequence1[index1] == sequence2[index2])
        {
            int tempMaxLength = FindLongestCommonSubsequence(sequence1, size1, index1 + 1, sequence2, size2, index2 + 1) + 1;
            if (maxSequenceLength < tempMaxLength)
            {
                maxSequenceLength = tempMaxLength;
            }
        }
        else
        {
            int tempMaxLength1 = FindLongestCommonSubsequence(sequence1, size1, index1, sequence2, size2, index2 + 1);
            int tempMaxLength2 = FindLongestCommonSubsequence(sequence1, size1, index1 + 1, sequence2, size2, index2);
            maxSequenceLength = tempMaxLength1 < tempMaxLength2 ? tempMaxLength2 : tempMaxLength1;
        }

        return maxSequenceLength;
    }

    void FindLongestCommonSubsequenceTest()
    {
        int sequence1[] = { 1, 13, 5, 8, 9, 24, 25, 26, 34, 40, 41 };
        int len1 = sizeof(sequence1) / sizeof(int);
        int sequence2[] = { 8, 21, 9, 6, 26, 40, 23, 16, 13, 41 };
        int len2 = sizeof(sequence2) / sizeof(int);
        cout << "Max common subsequence is: " << FindLongestCommonSubsequence(sequence1, len1, 0, sequence2, len2, 0) << " long" << endl;
    }
}