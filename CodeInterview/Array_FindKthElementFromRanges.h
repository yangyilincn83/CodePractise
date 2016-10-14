#pragma once

#include <iostream>
#include <cassert>

using namespace std;

namespace Algorithm
{
    /*
        For example, given ranges (2,8) (6,10) (11,16) (14,20) (18,30) (24,26)
        Find the kth number of all the numbers from the ranges, including the duplicate numbers.

        Solution:
        1. Sort all the start and end points of all ranges. In the above number, it'll be 2s, 6s, 8e, 10e, 11s, 14s, 16e, 18s, 20e, 24s, 26e, 30e
           Notes: s means starting point, e means ending point
        2. Set start_count = 1, curr_number = 2, total_count = 1
        3. Get the next number next_number and do the following
           - If that number is starting point, 
                -- the number count between curr_number and next_number(excluded) is start_count * (next_number - curr_number)
                -- start_count += 1
                -- curr_number = next_number
           - If the number is ending point, 
                -- the number count between curr_number and next_number(included) is start_count * (next_number - curr_number + 1)
                -- start_count -= 1
                -- curr_number = next_number + 1
           - Check whether the target is within this range
        4. Repeat step 3 until the end of those sorted points.
    */
    int FindithElementFromRanges(pair<int, int> ranges[], int index)
    {
        return 0;
    }

    void FindithElementFromRangesTest()
    {

    }
}