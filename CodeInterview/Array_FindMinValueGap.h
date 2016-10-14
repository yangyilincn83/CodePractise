#pragma once

#include "stdafx.h"
#include <string>
#include <math.h>

namespace Algorithm
{
    /*
    *  Find the smallest gap from the subtraction of two numbers from two arrays. The two arrays are sorted in order.
    */
    int FindMinValueGap(int numbers_a[], int count_a, int numbers_b[], int count_b)
    {
        int pos_a = 0;
        int pos_b = 0;
        int min = INT_MAX;

        while (pos_a < count_a && pos_b < count_b)
        {
            int minus = abs(numbers_a[pos_a] - numbers_b[pos_b]);
            if (minus < min)
            {
                min = minus;
            }

            if (numbers_a[pos_a] > numbers_b[pos_b])
            {
                pos_b++;
            }
            else
            {
                pos_a++;
            }
        }

        return min;
    }
}