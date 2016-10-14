#pragma once

#include "stdafx.h"
#include <string>

using namespace std;

/*
 *  Find the shortest distance between two strings in a document
 */
int GetShortestDistranceInDocument(string documentWords[], int count, string word1, string word2)
{
    int word1_pos = -1;
    int word2_pos = -1;
    int curr_pos = 0;
    int distance = INT_MIN;

    while (curr_pos < count)
    {
        if (documentWords[curr_pos] == word1)
        {
            word1_pos = curr_pos;
            if ((word2_pos != -1) && (distance > word1_pos - word2_pos))
            {
                distance = word1_pos - word2_pos;
            }
        }
        else if (documentWords[curr_pos] == word2)
        {
            word2_pos = curr_pos;
            if ((word1_pos != -1) && (distance > word2_pos - word1_pos))
            {
                distance = word2_pos - word1_pos;
            }
        }

        curr_pos++;
    }

    return distance;
}