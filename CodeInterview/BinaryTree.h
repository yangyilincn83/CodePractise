#pragma once

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <forward_list>
#include <list>

using namespace std;

namespace DataStructure
{
    class BinaryNode
    {
    public:
        int key;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(int key, BinaryNode* left = nullptr, BinaryNode* right = nullptr) : key(key), left(left), right(right) {}

        bool IsLeaf() { return left == nullptr && right == nullptr; }

    private:
        static BinaryNode* freelist;
    };

    BinaryNode* BinaryNode::freelist = nullptr;

    class BinarySearchTree
    {
    private:
        BinaryNode* root;

    public:
        BinarySearchTree(BinaryNode* rt = nullptr) : root(rt){}
        ~BinarySearchTree(){}

        bool IsEmpty() { return root == nullptr; }

        void Insert(int value)
        {
            InsertHelp(root, value);
        }

        void InsertHelp(BinaryNode*& rt, int value)
        {
            if (rt == nullptr)
            {
                BinaryNode* newNode = new BinaryNode(value);
                rt = newNode;
            }

            (value >= rt->key) ? InsertHelp(rt->right, value) : InsertHelp(rt->left, value);
        }

        // delete the min-value node of the BST pointed by rt
        // the min-value node will be returned and rt will be updated to the new formed BST after deletion
        BinaryNode* DeleteMin(BinaryNode*& rt)
        {
            assert(rt != nullptr);

            if (rt->left != nullptr)
            {
                return DeleteMin(rt->left);
            }

            BinaryNode* minNode = rt;
            rt = rt->right;

            return minNode;
        }

        void Remove(int value)
        {
            RemoveHelp(root, value);
        }

        void RemoveHelp(BinaryNode*& rt, int value)
        {
            // not found, return directly
            if (rt == nullptr)
                return;

            // remove the root
            if (rt->key == value)
            {
                // right tree is empty, update rt to left tree root directly
                if (rt->right == nullptr)
                {
                    BinaryNode* temp = rt;
                    rt = rt->left;
                    delete temp;
                }
                else
                {
                    // find min-value node in the right tree
                    BinaryNode* minNode = DeleteMin(rt->right);
                    rt->key = minNode->key;
                    delete minNode;
                    minNode = nullptr;
                }
            }

            (rt->key > value) ? RemoveHelp(rt->right, value) : RemoveHelp(rt->left, value);
        }

        BinaryNode* Find(int value)
        {
            return FindHelp(root, value);
        }

        BinaryNode* FindHelp(BinaryNode* rt, int value)
        {
            if (rt == nullptr)
                return nullptr;

            if (rt->key == value)
                return rt;

            if (rt->key > value)
                return FindHelp(rt->right, value);
            else
                return FindHelp(rt->left, value);
        }
    };
}