#pragma once

#include <iostream>
#include <cassert>
#include "DoubleLinkedNode.h"

using namespace std;
using namespace DataStructure;

namespace Algorithm
{
    template<typename T>
    void ReverseDoubleLinkedList(DoubleLinkedNode<T>*& head)
    {
        if (head == nullptr)
            return;

        DoubleLinkedNode<T>* prev = nullptr;
        DoubleLinkedNode<T>* curr = head;
        DoubleLinkedNode<T>* next = curr->next;

        while (next != nullptr)
        {
            curr->next = prev;
            if (prev != nullptr)
            {
                prev->prev = curr;
            }

            prev = curr;
            curr = next;
            next = curr->next;
        }

        head = curr;
        head->prev = nullptr;
    }
}
