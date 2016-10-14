#pragma once

#include <iostream>
#include <cassert>

using namespace std;

void ShiftKElementsToRight(int *numbers, int size, int k)
{
    // If k is greater than size, get the remainder number to shift
    if (k > size)
    {
        k = k % size;
    }

    // Reverse the array contents from [size-k] to [size-1]

    // Reverse the array contents from [0] to [size-k-1]

    // Reverse the whole array contents
}
