#pragma once

#include <iostream>
#include <cassert>
#include <deque>
#include <algorithm>
#include <vector>

using namespace std;

namespace Algorithm
{
    bool IsWhiteLine(string& line)
    {
        return all_of(line.begin(), line.end(), [](char& ch) ->bool {
            return isblank(ch);
        });
    }

    bool IsSingleCommentLine(string& line)
    {
        for (int i = 0; i < line.length; i++)
        {
            if (!isblank(line[i]))
            {
                if (line[i] == '/')
                {
                    return (line[i + 1] == '/');
                }
                else
                {
                    return false;
                }
            }
        }

        return false;
    }

    bool IsMultipleCommentLineStart(string& line)
    {
        for (int i = 0; i < line.length; i++)
        {
            if (!isblank(line[i]))
            {
                if (line[i] == '/')
                {
                    return (line[i + 1] == '*');
                }
                else
                {
                    return false;
                }
            }
        }

        return false;
    }

    bool IsMultipleCommentLineEnd(string& line)
    {
        for (int i = line.length-1; i >=0; i--)
        {
            if (!isblank(line[i]))
            {
                if (line[i] == '/')
                {
                    return (line[i - 1] == '*');
                }
                else
                {
                    return false;
                }
            }
        }

        return false;
    }

    /*
    Count how many actual code lines in a document

    Lines with the following traits don't belong to a code line
    The comment line: // to the end of line, or /* to the next "\*\/"
    */
    int CountCodeLines(vector<string>& document)
    {
        size_t lineNumber = document.size();
        bool isInMultipleCommentLine = false;
        int codeLineTotal = 0;

        for (int i = 0; i < lineNumber; i++)
        {
            if (!isInMultipleCommentLine)
            {
                // continue if the current line is white line or if the current line is single comment line
                if (IsWhiteLine(document[i]) ||
                    IsSingleCommentLine(document[i]))
                {
                    continue;
                }

                // set flat to true and continue if the current line is the start line of multiple comment line
                if (IsMultipleCommentLineStart(document[i]))
                {
                    isInMultipleCommentLine = true;
                    continue;
                }

                codeLineTotal++;
            }
            else
            {
                isInMultipleCommentLine = !IsMultipleCommentLineEnd(document[i]);
            }
        }

        assert(!isInMultipleCommentLine);
        return codeLineTotal;
    }

}