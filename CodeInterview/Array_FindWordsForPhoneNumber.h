#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

namespace Algorithm
{
    const char CharMap[10][4] = {
        '\0', '\0', '\0',
        '\0', '\0', '\0',
        'A', 'B', 'C', '\0',
        'D', 'E', 'F', '\0',
        'G', 'H', 'I', '\0',
        'J', 'K', 'L', '\0',
        'M', 'N', 'O', '\0',
        'P', 'Q', 'R', 'S',
        'T', 'U', 'V', '\0',
        'W', 'X', 'Y', 'Z'
    };

    const int ChoiceTotal[] = {
        0,
        0,
        3,
        3,
        3,
        3,
        3,
        4,
        3,
        4
    };

    void FindWords(const int numbers[], const int digits, int* choices, int index)
    {
        if (index == digits)
        {
            for (int i = 0; i < digits; i++)
            {
                cout << CharMap[numbers[i]][choices[i]];
            }
            cout << endl;
        }

        for (choices[index] = 0; choices[index] < ChoiceTotal[numbers[index]]; choices[index]++)
        {
            FindWords(numbers, index + 1, choices, digits);
        }
    }
}