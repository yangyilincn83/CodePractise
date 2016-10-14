#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

namespace Algorithm
{
    bool FindEqualSum(int sum, int numbers[], int index)
    {
        if (sum == 0)
        {
            return true;
        }

        if (index < 0)
        {
            return false;
        }

        for (int i = index; i >= 0; i--)
        {
            if (FindEqualSum(sum - numbers[i], numbers, i - 1))
            {
                return true;
            }
        }

        return false;
    }

    bool FindEqualSumSequence(int numbers[], int size)
    {
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += numbers[i];
        }

        if(sum %2 != 0)
        {
            cout << "Sum is not even. Impossible to separate the array" << endl;
            return false;
        }
        else
        {
            return FindEqualSum(sum / 2, numbers, size - 1);
        }
    }
}