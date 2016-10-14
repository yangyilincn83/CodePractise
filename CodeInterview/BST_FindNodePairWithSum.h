#pragma once

#include <iostream>
#include <cassert>
#include <deque>
#include "BinaryTree.h"

using namespace std;
using namespace DataStructure;

namespace Algorithm
{
    /*
        Given a binary search tree, please check whether there are two nodes in it whose sum equals a given value.
    */
    pair<BinaryNode*, BinaryNode*> BSTFindNodesWithSum(BinaryNode* root, int sum)
    {
        // Solution 1: In order traversal and put every element into a queue. Take two pivots at both begin and end. Move those two pivots into the middle until they meet.
        // Every time only one pivot can move and that depends on whether the sum is greater or smaller than the target

        /*  Solution 2: 
            - Create a double ended queue and push the root
            - In order traversal forward(leftmost branch of the front element) 
            - In order traversal backward(rightmost of the end element)
            - Add up two elements from each end, return pair if equal to sum; pop the front and continue traversal forward if less than sum; pop the end and continue traversal backward if greater than sum
            - Continue the loop until the front and the end is equal in pointer or the front's value is greater than the end's key
         */
        deque<BinaryNode*> sequence;

        // push root first
        sequence.push_back(root);

        // push left most branch
        BinaryNode* curr = sequence.front();
        while (curr->left != nullptr)
        {
            sequence.push_front(curr->left);
            curr = curr->left;
        }

        // push right most branch
        curr = sequence.back();
        while (curr->right != nullptr)
        {
            sequence.push_back(curr->right);
            curr = curr->right;
        }

        while (true)
        {
            BinaryNode* front = sequence.front();
            BinaryNode* back = sequence.back();

            if (front == back || front->key > back->key)
            {
                break;
            }

            int tempSum = front->key + back->key;
            if (tempSum == sum)
            {
                return make_pair(front, back);
            }
            else if (tempSum < sum)
            {
                // pop up the front element
                sequence.pop_front();

                // traverse right subtree starting from leftmost branch
                auto& traversal = front->right;
                while (traversal != nullptr)
                {
                    sequence.push_front(traversal);
                    traversal = traversal->left;
                }
            }
            else
            {
                // pop up the ending element
                sequence.pop_back();

                auto& traversal = back->left;
                while (traversal != nullptr)
                {
                    sequence.push_back(traversal);
                    traversal = traversal->right;
                }
            }
        }

        return make_pair(nullptr, nullptr);
    }
}