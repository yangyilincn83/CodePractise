#pragma once

#include <iostream>
#include <cassert>

using namespace std;

namespace Algorithm
{
    struct Range
    {
        int     startIndex;
        int     endIndex;
        bool    isIncreasing;
    };

    /*
    Merge two adjacent sorted ranges. These two ranges could be both increasing, both descreasing or one increasing another decreasing
    */
    Range MergeRanges(int* numbers, Range range1, Range range2)
    {
        return { 0, 0, false };
    }

    /*
        A number array may be composed of long wave sequences. The wave sequence means the numbers are increasing for some numbers, and
        then decreasing for some number, etc...
    */
    void SortWaveRanges(int numbers[], int count)
    {
        vector<Range> rangeList;
        vector<Range> auxRangeList;

        int start = 0;
        int end = 0;
        bool increasing = true;
        while (true)
        {
            if (start == count - 1)
            {
                // read the end range
                rangeList.push_back({ start, start, increasing });
                break;
            }

            // mark range direction
            increasing = (numbers[start] <= numbers[start + 1]);

            // move forward to the end of the current increasing/decreasing range
            if (increasing)
            {
                
                for (; (end < count - 1) && (numbers[end] <= numbers[end + 1]); end++);
            }
            else
            {
                for (; (end < count - 1) && (numbers[end] > numbers[end + 1]); end++);
            }

            // push this range
            rangeList.push_back({ start, end, increasing });

            // update start and end for next range
            start = end + 1;
            end = start;
        }

        // Iterate until there's only one range left
        while (rangeList.size() > 1)
        {
            int rangeCount = rangeList.size();

            // merge every two adjacent ranges
            for (int i = 0; i < rangeCount - 1; i += 2)
            {
                Range range = MergeRanges(numbers, rangeList[i], rangeList[i + 1]);
                auxRangeList.push_back(range);
            }

            // push last range if the range count is odd because it is not merged with any other range in this iteration
            if (rangeCount % 2 == 1)
            {
                auxRangeList.push_back(rangeList[rangeCount - 1]);
            }

            // exchange range list with aux range list for next iteration
            rangeList = std::move(auxRangeList);

            // clear up aux range list
            auxRangeList.clear();
        }

        // Revert the array if the direction is decreasing
        if (!rangeList[0].isIncreasing)
        {
            std::reverse(numbers, numbers + count);
        }
    }
}
