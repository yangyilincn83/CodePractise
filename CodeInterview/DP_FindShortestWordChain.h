#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
#include <deque>
#include <set>
#include <map>
#include <queue>
#include <stack>

using namespace std;

namespace Algorithm
{
    /*
        Accepts start and end words and, using words from the dictionary, builds a word chain between them.
        For example, you can turn "lead" into "gold" in four steps (lead, load, goad, gold), and "ruby" into "code" in six steps (ruby, rubs, robs, rods, rode, code).
    */

    #define INFINITE INT_MAX
    map<pair<string, string>, vector<string>> GlobalWordChain;  // memoization table for mininmum word chain of each pair of words
    map<pair<string, string>, int> GlobalWordChainLength;       // memoization table for mininmum word chain length of each pair of words

    /*
        Fake method to simulate vocabulary lookup
    */
    vector<string> FindNearbyWords(string str)
    {
        return vector<string>();
    }

    void FindShortestWordChain(string start, string end, vector<string>& currChain, vector<string>& resultChain)
    {
        vector<string> currentMinChain;
        int currentMinChainLength = INFINITE;
        vector<string> resultSubChain;

        // already reach the end, return without adding anything into resultChain
        if (start == end)
        {
            resultChain.clear();
            return;
        }

        // initialize global word chain legnth to ININITE
        if (GlobalWordChainLength.find(pair<string, string>(start, end)) == GlobalWordChainLength.end())
        {
            GlobalWordChainLength[pair<string, string>(start, end)] = currentMinChainLength;
        }
        else
        {
            // this pair has been queried before, return directly
            resultChain = GlobalWordChain[pair<string, string>(start, end)];
            return;
        }

        // find all nearby words
        vector<string> nearbyWords = FindNearbyWords(start);

        // check possibility for each nearby word as next word in the chain
        for (string& nearbyWord : nearbyWords)
        {
            resultSubChain.clear();

            // if the nearby word is already in the chain, continue to next nearby word
            if (find(currChain.begin(), currChain.end(), nearbyWord) != currChain.end())
            {
                continue;
            }

            // check memoization table
            if (GlobalWordChain.find(pair<string, string>(nearbyWord, end)) == GlobalWordChain.end())
            {
                // push this nearby word into current chain
                currChain.push_back(nearbyWord);

                // keep looking forward with current chain
                FindShortestWordChain(nearbyWord, end, currChain, resultSubChain);

                // pop this nearby word and try next one
                currChain.pop_back();
            }
            else
            {
                // already get the min distance before, directly use it
                resultSubChain = GlobalWordChain[pair<string, string>(nearbyWord, end)];
            }

            // compare the resultSubChain + 1 with currentMinChain
            if (resultSubChain.size() + 1 < currentMinChainLength)
            {
                // update temporary minimum chain and chain length
                currentMinChainLength = resultSubChain.size() + 1;
                resultSubChain.insert(resultSubChain.begin(), nearbyWord);
                currentMinChain = resultSubChain;
            }
        }

        // update memoization table at the end of this function
        if (GlobalWordChain.find(pair<string, string>(start, end)) == GlobalWordChain.end())
        {
            GlobalWordChain[pair<string, string>(start, end)] = currentMinChain;
            GlobalWordChainLength[pair<string, string>(start, end)] = currentMinChainLength;
        }

        // set result chain
        resultChain = currentMinChain;
    }
}