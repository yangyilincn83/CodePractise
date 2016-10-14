#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include "BinaryTree.h"

using namespace std;
using namespace DataStructure;

namespace Algorithm
{
    /*
        All nodes along children pointers from root to leaf nodes form a path in a binary tree.
        Given a binary tree and a number, please print out all of paths where the sum of all nodes value is same as the given number.
    */
    void FindPath(BinaryNode* root, int targetSum, list<BinaryNode*>& resultList)
    {
        assert(root != nullptr);

        if (root->IsLeaf())
        {
            if (root->key == targetSum)
            {
                resultList.push_back(root);

                // print out resultList

                resultList.pop_back();
            }

            return;
        }

        if (root->left != nullptr)
        {
            resultList.push_back(root);
            FindPath(root->left, targetSum - root->key, resultList);
            resultList.pop_back();
        }

        if (root->right != nullptr)
        {
            resultList.push_back(root);
            FindPath(root->right, targetSum - root->key, resultList);
            resultList.pop_back();
        }
    }
}
