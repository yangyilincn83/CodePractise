#pragma once

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

#include <iostream>
#include <hash_map>
#include<unordered_map>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

namespace Algorithm
{
    pair<int, int> FindShortestWindowWithAllKeywords(string words[], int wordsCount, string keywords[], int keywordsCount)
    {
        int startPos = -1;
        int endPos = -1;
        int minWindowSize = INT_MIN;
        int tempStartPos = 0;
        int tempEndPos = -1;
        unordered_map<string, int> keywordsHitMap;
        int keywordsHitTotal = 0;

        assert((wordsCount > 0) && (keywordsCount > 0));

        for (int i = 0; i < keywordsCount; i++)
        {
            keywordsHitMap[keywords[i]] = 0;
            keywordsHitTotal = 0;
        }

        while (true)
        {
            // find the next window candidate
            while (keywordsHitTotal < keywordsCount)
            {
                // moving forward end pos to include more words
                ++tempEndPos;

                // return current best result if reaching the end
                if (tempEndPos >= wordsCount)
                {
                    return make_pair(startPos, endPos);
                }

                // the current word is a keyword
                if (keywordsHitMap.find(words[tempEndPos]) != keywordsHitMap.end())
                {
                    keywordsHitMap[words[tempEndPos]]++;
                    if (keywordsHitMap[words[tempEndPos]] == 1)
                    {
                        // increase hit total if the first occurance of this string
                        keywordsHitTotal++;
                    }
                }
            }

            // update the window candidate if it's smaller
            if (tempEndPos - tempStartPos + 1 < minWindowSize)
            {
                endPos = tempEndPos;
                startPos = tempStartPos;
                minWindowSize = endPos - startPos + 1;
            }

            // move forward start pos forward until keywordsHitTotal is less than keywordsSize
            while (tempStartPos <= tempEndPos)
            {
                // the current word is a keyword
                if (keywordsHitMap.find(words[tempStartPos]) != keywordsHitMap.end())
                {
                    keywordsHitMap[words[tempStartPos]]--;
                    if (keywordsHitMap[words[tempStartPos]] == 0)
                    {
                        // decrease hit total if no occurance of this string
                        keywordsHitTotal--;
                        break;
                    }
                }

                // update the window since it's still a candidate and it's smaller
                tempStartPos++;
                startPos = tempStartPos;
                minWindowSize = endPos - startPos + 1;
            }
        }

        return make_pair(startPos, endPos);
    }
}