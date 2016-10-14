#pragma once

#include <iostream>

using namespace std;

namespace Algorithm
{
    class BinNode
    {
    public:
        BinNode* left;      // left child
        BinNode* right;     // right child
        int leftMax;        // the max node depth of left tree
        int rightMax;       // the max node depth of right tree
        int key;
    };

    int MaxDistance = 0;

    void FindMaxDistance(BinNode* root)
    {
        int tempMax = 0;

        if (root == nullptr)
            return;

        // left tree is null, update leftMax to 0
        if (root->left == nullptr)
        {
            root->leftMax = 0;
        }

        // right tree is null, update rightMax to 0
        if (root->right == nullptr)
        {
            root->rightMax = 0;
        }

        // left tree is not null, process the left tree in a recursive way
        if (root->left != nullptr)
        {
            FindMaxDistance(root->left);
        }

        // right tree is not null, process the right tree in a recursive way
        if (root->right != nullptr)
        {
            FindMaxDistance(root->right);
        }

        if (root->left->leftMax > root->left->rightMax)
        {
            tempMax = root->left->leftMax;
        }
        else
        {
            tempMax = root->left->rightMax;
        }
        root->leftMax = tempMax + 1;

        if (root->right->leftMax > root->right->rightMax)
        {
            tempMax = root->right->leftMax;
        }
        else
        {
            tempMax = root->right->rightMax;
        }
        root->rightMax = tempMax + 1;

        if (root->leftMax + root->rightMax > MaxDistance)
        {
            MaxDistance = root->leftMax + root->rightMax;
        }
    }
}