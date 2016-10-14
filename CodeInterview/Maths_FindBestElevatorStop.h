#pragma once

#include <iostream>
#include <cassert>

using namespace std;

namespace Algorithm
{
    /*
     * The function finds the floor at which the elevator stops so that people need to take the least number of steps on foot
     * nPerson[i] represents the number of persons take off at floor i
     *
     * Algorithm:
     *  For floor i, take N1 as the number of people take off under floor i, N2 as the number of people take off at floor i, N3
     *  as the number of people take off above floor i, and Y as the total number of steps people need to take on foot.
     *  For floor i-1, the total number of steps will be Y - (N1 - N2 - N3)
     *  For floor i+1, the total number of steps will be Y + (N1 + N2 - N3)
     *  Start from floor 2 and increase to the next floor until N1 + N2 >= N3 and stop there. (because for the next floor N1 + N2 >= N3 is still true)
     *
     */
    pair<int, int> FindBestStop(int nPerson[], int floors)
    {
        assert(floors >= 2);

        int TotalSteps = 0;

        // Initialize the status for floor 2
        int N1 = 0;
        int N2 = nPerson[1];
        int N3 = 0;
        int TargetFloor = 1;
        for (int i = 2; i < floors; i++)
        {
            N3 += nPerson[i];
            TotalSteps += nPerson[i] * (i - 1);
        }

        // Compare with the next floor and move up one floor if N1 + N2 < N3
        for (int i = 2; i < floors; i++)
        {
            if (N1 + N2 < N3)
            {
                TargetFloor = i;
                TotalSteps += (N1 + N2 - N3);
                N1 += N2;
                N2 = nPerson[i];
                N3 -= nPerson[i];
            }
            else
            {
                break;
            }
        }

        return pair<int, int>(TotalSteps, TargetFloor);
    }
}