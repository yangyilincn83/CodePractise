#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

// http://en.cppreference.com/w/cpp/memory/new/operator_new
// http://en.cppreference.com/w/cpp/memory/new/operator_delete

namespace CPlusPlus
{
    class CustomClass
    {
    private:
        int m_ivalue;
        long m_lvalue;
        double m_dvalue;
    public:
        CustomClass()
        {
            cout << "custom class constructor" << endl;
        }

        ~CustomClass()
        {
            cout << "custom class destructor" << endl;
        }

        static void* operator new(size_t sz)
        {
            cout << "custom new for size " << sz << endl;
            return ::operator new(sz);
        }

        static void* operator new[](size_t sz)
        {
            std::cout << "custom new[] for size " << sz << '\n';
            return ::operator new[](sz);
        }

        static void operator delete(void* ptr)
        {
            cout << "custom delete for pointer " << ptr << endl;
            ::operator delete(ptr);
        }

        static void operator delete[](void* ptr)
        {
            cout << "custom delete[] for pointer " << ptr << endl;
            ::operator delete(ptr);
        }
    };
}

void* operator new[](std::size_t sz, char c)
{
    cout << "this is overloaded new[] operator" << endl;
    void* p = ::operator new[](sz);
    std::fill_n(reinterpret_cast<char*>(p), sz, c);
    return p;
}

void* operator new(size_t sz, char c)
{
    cout << "this is overloaded new operator" << endl;
    void* p = ::operator new(sz);
    std::fill_n(reinterpret_cast<char*>(p), sz, c);
    return p;
}

void OverloadedOperatorTest()
{
    // global new operator with char param
    char* p = (char*)new('6') double;
    p[sizeof(double) / sizeof(char) - 1] = '\0';
    cout << p << endl;
    delete[]p;

    // global new[] operator with char param
    int num = 2;
    p = (char*)new('6') double[num];
    p[(sizeof(double) * num / sizeof(char)) - 1] = '\0';
    cout << p << endl;
    delete[]p;

    CPlusPlus::CustomClass* obj = new CPlusPlus::CustomClass();
    delete obj;

    CPlusPlus::CustomClass* objs = new CPlusPlus::CustomClass[5];
    delete[] objs;
}