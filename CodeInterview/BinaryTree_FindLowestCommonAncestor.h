#pragma once

#include "stdafx.h"

namespace Algorithm
{
    namespace LowestCommonAncestor
    {
        class BinNode
        {
        public:
            BinNode *left;
            BinNode *right;
            int key;
        };

        // This function returns pointer to LCA of two given values v1 and v2.
        // This function assumes that v1 and v2 are present in Binary Tree
        BinNode* FindLCA(BinNode* root, int v1, int v2)
        {
            // Base case
            if (root == NULL) return NULL;

            // If either v1 or v2 matches with root's key, report
            // the presence by returning root (Note that if a key is
            // ancestor of other, then the ancestor key becomes LCA
            if (root->key == v1 || root->key == v2)
                return root;

            // Look for keys in left and right subtrees
            BinNode *left_lca = FindLCA(root->left, v1, v2);
            BinNode *right_lca = FindLCA(root->right, v1, v2);

            // If both of the above calls return Non-NULL, then one key
            // is present in once subtree and other is present in other,
            // So this node is the LCA
            if (left_lca && right_lca)  return root;

            // Otherwise check if left subtree or right subtree is LCA
            return (left_lca != NULL) ? left_lca : right_lca;
        }

        // This function returns pointer to LCA of two given node n1 and n2.
        // This function assumes that n1 and n2 are present in Binary Tree
        BinNode* FindLCA(BinNode* root, BinNode* n1, BinNode* n2)
        {
            // Base case
            if (root == NULL) return NULL;

            // If either n1 or n2 matches with root's key, report
            // the presence by returning root (Note that if a key is
            // ancestor of other, then the ancestor key becomes LCA
            if (root == n1 || root == n2)
                return root;

            // Look for keys in left and right subtrees
            BinNode *left_lca = FindLCA(root->left, n1, n2);
            BinNode *right_lca = FindLCA(root->right, n1, n2);

            // If both of the above calls return Non-NULL, then one key
            // is present in once subtree and other is present in other,
            // So this node is the LCA
            if (left_lca && right_lca)  return root;

            // Otherwise check if left subtree or right subtree is LCA
            return (left_lca != NULL) ? left_lca : right_lca;
        }
    }
}
