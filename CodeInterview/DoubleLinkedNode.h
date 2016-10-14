#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

namespace DataStructure
{
    template<typename T>
    struct DoubleLinkedNode
    {
        T value;
        DoubleLinkedNode<T>* prev;
        DoubleLinkedNode<T>* next;
    };
}