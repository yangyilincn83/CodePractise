#pragma once

#include <iostream>
#include <cassert>
#include "FreeSpaceList.h"

using namespace std;
using namespace DataStructure;

namespace Algorithm
{
    template<typename T>
    void MergeTwoSortedLinkedList(LinkedNode<T>*& list1, LinkedNode<T>* list2)
    {
        if (list1 == nullptr || list2 == nullptr)
            return;

        LinkNode<T>* head = new LinkNode();
        LinkNode<T>* curr = head;
        LinkNode<T>* curr1 = list1;
        LinkNode<T>* curr2 = list2;

        // update the head of the merged list
        list1 = (curr1->value < curr2->value) ? curr1 : curr2;

        // merge sort
        while (curr1 != nullptr && curr2 != nullptr)
        {
            if (curr1->value < curr2->value)
            {
                curr->next = curr1;
                curr1++;
            }
            else
            {
                curr->next = curr2;
                curr2++;
            }

            curr = curr->next;
        }

        if (curr1 == nullptr)
        {
            // append list 2 directly
            curr->next = curr2;
        }
        else
        {
            curr->next = curr1;
        }

        // return result
        list1 = head->next;

        // clean up
        delete head;
        head = nullptr;
    }
}
