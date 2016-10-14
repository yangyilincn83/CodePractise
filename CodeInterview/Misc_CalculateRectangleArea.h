#pragma once

#include <iostream>
#include <cassert>
#include <deque>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

namespace Algorithm
{
    /*
        There are a set of rectangles which may overlap with each other. 
        Calculate the overall area composed of these rectangles.
    */
    class Rectangle
    {
    public:
        int xAxisLeft;
        int xAxisRight;
        int yAxisTop;
        int yAxisBottom;
    };

    class VerticalEdge
    {
    public:
        int xAxis;
        int yAxisTop;
        int yAxisBottom;
        bool isLeftEdge;

        bool operator < (VerticalEdge edge)
        {
            return xAxis < edge.xAxis;
        }
    };

    /*
        The overall area can be divided into multiple strips which is bound by two adjacent vertical edges, the highest and lowest involved horizontal edges.
    */
    int CalculateArea(Rectangle rects[], int count)
    {
        vector<VerticalEdge> verticalEdges;
        multiset<int> yAxis;
        int SumArea = 0;

        // push each vetical edge into the collection
        for (int i = 0; i < count; i++)
        {
            VerticalEdge ledge = { rects[i].xAxisLeft, rects[i].yAxisTop, rects[i].yAxisBottom, true };
            VerticalEdge redge = { rects[i].xAxisRight, rects[i].yAxisTop, rects[i].yAxisBottom, false };
            verticalEdges.push_back(ledge);
            verticalEdges.push_back(redge);
        }

        // sort the vertical edges
        sort(verticalEdges.begin(), verticalEdges.end());

        // initialize
        VerticalEdge strip_left_edge = verticalEdges[0];    // the first vetical edge must be a left edge
        yAxis.insert(strip_left_edge.yAxisTop);             // insert the edge's top
        yAxis.insert(strip_left_edge.yAxisBottom);          // insert the edge's bottom
        VerticalEdge strip_right_edge;

        // iterate through all the rest edges
        for (int index = 1; index < count; index++, strip_left_edge = strip_right_edge)
        {
            strip_right_edge = verticalEdges[index];

            // yAxis may be empty at some time point if there's one or more rectangles that don't overlap with any others
            if (!yAxis.empty())
            {
                // calculate the current strip area
                int yAxisLowerBound = *(yAxis.begin());
                int yAxisUpperBound = *(yAxis.rbegin());
                int stripArea = (strip_right_edge.xAxis - strip_left_edge.xAxis) * (yAxisUpperBound - yAxisLowerBound);
                SumArea += stripArea;
            }

            // need to do more work before moving to next strip
            if (strip_right_edge.isLeftEdge)
            {
                // this is a new rectange's left vertical edge 
                // insert new top/bottom into the yAxis collection
                yAxis.insert(strip_right_edge.yAxisTop);
                yAxis.insert(strip_right_edge.yAxisBottom);
            }
            else
            {
                // this is an existing rectangle's right vertical edge
                // remove this rectangle's top/bottom from yAxis collection
                multiset<int>::iterator iter_top = yAxis.find(strip_right_edge.yAxisTop);
                yAxis.erase(iter_top);
                multiset<int>::iterator iter_bottom = yAxis.find(strip_right_edge.yAxisBottom);
                yAxis.erase(iter_bottom);
            }
        }

        return SumArea;
    }
}