#pragma once

#include <iostream>
#include <cassert>
#include <deque>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

namespace Algorithm
{
    /*
    Find all dependency elements given the dependency list:
    A   B   C
    B   C   E
    C   G
    D   A   F
    E   F
    F   H

    The dependency set for each element should be as follows:
    A   B C E F G H
    B   C E F G H
    C   G
    D   A B C E F G H
    E   F H
    F   H
    */
    set<char> FindDepedencySet(char target, map<char, vector<char>> dependencyGraph)
    {
        queue<char> processingQueue;
        set<char> resultSet;

        // put target into the queue
        processingQueue.push(target);

        do
        {
            // get the top element
            char current = processingQueue.front();

            // dequeue the element
            processingQueue.pop();

            // find all dependency elements
            if (dependencyGraph.find(current) != dependencyGraph.end())
            {
                vector<char>& dependencies = dependencyGraph[current];
                size_t size = dependencies.size();
                for (int i = 0; i < size; i++)
                {
                    if (resultSet.find(dependencies[i]) != resultSet.end())
                    {
                        // there is dependency cycle, report error
                    }
                    else
                    {
                        // put into the result set
                        resultSet.insert(dependencies[i]);

                        // enqueue the element
                        processingQueue.push(dependencies[i]);
                    }
                }
            }

        } while ((!processingQueue.empty()));
    }

}
