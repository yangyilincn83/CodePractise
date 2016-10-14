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

/*
    Swap numbers without temporary variable
*/
void Swap(int &a, int &b)
{
    b = a ^ b;
    a = a ^ b;
    b = b ^ a;
}

/*
    Shuffle the deck so that the probablility of each ordering is equal
*/
void ShuffleDeck(int decks[], int number)
{
    srand(time_t());
    for (int i = 0; i < number; i++)
    {
        int j = rand() % (number - i) + i; // find a random number from current index to the end
        swap(decks[i], decks[j]);
    }
}