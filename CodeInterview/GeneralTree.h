#pragma once

#include <iostream>

using namespace std;

namespace DataStructure
{
    template<typename T>
    class GeneralTreeNode abstract
    {
    public:
        GeneralTreeNode(T& value, GeneralTreeNode<T>* leftChild, GeneralTreeNode<T>* rightSibling)
        {
            m_value = value;
            m_leftChild = leftChild;
            m_rightSibling = rightSibling;
        }

        GeneralTreeNode(GeneralTreeNode<T>& node) = default;

        GeneralTreeNode(GeneralTreeNode<T>&& node) = delete; // no move constructor
        GeneralTreeNode<T>& operator =(GeneralTreeNode<T>&& node) = delete; // no move assignment constructor

        bool IsLeaf()
        {
            return (nullptr == leftChild);
        }

        void SetLeftChild(GeneralTreeNode<T>* leftChild)
        {
            m_leftChild = leftChild;
        }

        GeneralTreeNode<T>* GetLeftChild()
        {
            return m_leftChild;
        }

        void SetRightSibling(GeneralTreeNode<T>* rightSibling)
        {
            m_rightSibling = rightSibling;
        }

        GeneralTreeNode<T>* GetRightSibling()
        {
            return m_rightSibling;
        }

        void SetValue(T& value)
        {
            m_value = value;
        }

        void GetValue()
        {
            return m_value;
        }

    private:
        T m_value;
        GeneralTreeNode<T>* leftChild;
        GeneralTreeNode<T>* rightSibling;
    };
}