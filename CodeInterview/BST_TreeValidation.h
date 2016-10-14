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
        Determine whether an input array is a post-order traversal sequence of a binary search tree or not.
        If it is, return true; otherwise return false. Assume all numbers in an input array are unique.
    */
    bool VerifyBSTPostOrderTraversal(int* numbers, int size)
    {
        if (size == 0 || size == 1)
        {
            return true;
        }

        // find the stop position where the left is the left substree of the BST rooted at pivot
        int pivot = numbers[size - 1];
        int stop = 0;
        while (numbers[stop] < pivot)
        {
            stop++;
        }

        // it's necessary to inspect the right subtree of the BST rooted at pivot
        for (int i = stop; i < size - 1; i++)
        {
            if (numbers[i] < pivot)
                return false;
        }

        return VerifyBSTPostOrderTraversal(numbers, stop - 1) && VerifyBSTPostOrderTraversal(numbers + stop, size - stop - 1);
    }

    /*
        How to verify whether a binary tree is a binary search tree?

        Option 1:
            verify each substree from the root within the scope from min to max
    */
    bool BSTVerify1(BinaryNode* root, int min, int max)
    {
        if (root == nullptr)
        {
            return true;
        }

        if (root->key < min || root->key > max)
        {
            return false;
        }

        return BSTVerify1(root->left, min, root->key) && BSTVerify1(root->right, root->key, max);
    }

    /*
        How to verify whether a binary tree is a binary search tree?

        Option 2:
            in order traversal with validation against the last visited node value
            verify the current value is greater than the previous value
    */
    bool BSTVerify2(BinaryNode* root, int& min, int& max)
    {
        assert(root != nullptr);

        bool isLeftTreeBST = false;
        bool isRightTreeBST = false;
        int leftMin, leftMax;
        int rightMin, rightMax;

        if (root->left == nullptr)
        {
            min = root->key;
            isLeftTreeBST = true;
        }
        else
        {
            isLeftTreeBST = BSTVerify2(root->left, leftMin, leftMax);
            if (!isLeftTreeBST || (root->key <= leftMax))
            {
                return false;
            }

            min = leftMin;
        }

        if (root->right == nullptr)
        {
            max = root->key;
            isRightTreeBST = true;
        }
        else
        {
            isRightTreeBST = BSTVerify2(root->right, rightMin, rightMax);
            if (!isRightTreeBST || (root->key > rightMin))
            {
                return false;
            }

            max = rightMax;
        }

        return true;
    }
}