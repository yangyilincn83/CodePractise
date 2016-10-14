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
        Convert a binary search tree to a sorted double-linked list. We can only change the target of pointers, but cannot create any new nodes.
        For example, if we input a binary search tree as shown on the left side of the Figure 1, the output double-linked list is shown on the right side.
    */
    void BSTToDoubleLinkedList(BinaryNode* root, BinaryNode*& head, BinaryNode*& tail)
    {
        if (root == nullptr)
        {
            head = tail = nullptr;
            return;
        }

        // head and tail pointer of the double-linked tree after it's been converted
        // Convert the left tree
        if (root->left == nullptr)
        {
            head = root;
        }
        else
        {
            BinaryNode* head_l = nullptr;
            BinaryNode* tail_l = nullptr;
            BSTToDoubleLinkedList(root->left, head_l, tail_l);
            tail_l->right = root;
            root->left = tail_l;
            head = head_l;
        }

        // Convert the right tree
        if (root->right == nullptr)
        {
            tail = root;
        }
        else
        {
            BinaryNode* head_r = nullptr;
            BinaryNode* tail_r = nullptr;
            BSTToDoubleLinkedList(root->right, head_r, tail_r);
            head_r->left = root;
            root->right = head_r;
            tail = tail_r;
        }
    }
}
