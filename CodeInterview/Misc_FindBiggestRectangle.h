#pragma once

#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

namespace Algorithm
{
    /*
     * This function is to find the biggest rectangle between two points at x axis. heights[i] represents the height at i on the x axis
     * The rectangle area between i and j is defined as min(height[i], height[j]) * |j - i|
     * Start from both ends and calculate the initial rectangle. Then pick the smallet height and move towards the center until find a bigger height.
     * Calculate the rectangle and update the ends if it's bigger. Continue until both ends meet.
     */
    pair<int, int> FindBiggestRectangle(int xAxis[], int yAxis[], int size)
    {
        int start = 0;
        int end = size - 1;
        int tempStart = start;
        int tempEnd = end;
        int maxRectSize = 0;

        while (tempStart < tempEnd)
        {
            // check if the current rectangle is bigger
            int height = std::min<int>(yAxis[tempStart], yAxis[tempEnd]);
            int currRectSize = height * (xAxis[end] - xAxis[start]);

            if (maxRectSize < currRectSize)
            {
                maxRectSize = currRectSize;
                start = tempStart;
                end = tempEnd;
            }

            // move the point of lower height towards the middle until finds a bigger height
            if (yAxis[tempStart] < yAxis[tempEnd])
            {
                // find new possible start
                for (; yAxis[++tempStart] <= height && tempStart < tempEnd;);
            }
            else
            {
                // find new possible end
                for (; yAxis[--tempEnd] <= height && tempStart < tempEnd;);
            }
        }

        return std::pair<int, int>(start, end);
    }
}