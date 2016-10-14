#pragma once

#include "stdafx.h"
#include <iostream>
#include <functional>

using namespace std;

namespace CPlusPlus
{
    // std::reference_wrapper possible implementation
    template <class T>
    class reference_wrapper {
    public:
        // types
        typedef T type;

        // construct/copy/destroy
        reference_wrapper(T& ref) noexcept : _ptr(std::addressof(ref)) {}
        reference_wrapper(const reference_wrapper&) noexcept = default;

        // assignment operator
        reference_wrapper& operator=(const reference_wrapper& x) noexcept = default;

        // no move constructor
        reference_wrapper(T&&) = delete;

        // access
        operator T& () const noexcept { return *_ptr; }
        T& get() const noexcept { return *_ptr; }

        template< class... ArgTypes >
        typename std::result_of<T&(ArgTypes&&...)>::type
            operator() (ArgTypes&&... args) const {
            return std::invoke(get(), std::forward<ArgTypes>(args)...);
        }

    private:
        T* _ptr;
    };

    void TransferByRef(int& refValue)
    {
        refValue = 100;
    }

    void TransferByConstRef(const int& refValue)
    {
        cout << "const int transferred in: " << refValue << endl;
    }

    void ReferenceWrapperTest()
    {
        int a = 10000;
        const int b = 20000;

        cout << "a's value before function is: " << a << endl;
        TransferByRef(std::ref(a));
        cout << "a's value before function is: " << a << endl;

        std::reference_wrapper<const int> stdRefWrap(b);
        TransferByConstRef(stdRefWrap);
        TransferByConstRef(std::cref(b));

        std::vector<int> v = { 1, 2, 3, 4, 5 };
        std::vector<reference_wrapper<int>> refv(v.begin(), v.end());

        for (auto& i : v) i = i * 2;
        cout << "Contents of the original vector:";
        for (auto& i : v) cout << i << " "; cout << endl;
        cout << "Contents of the ref vector:";
        for (auto& i : refv) cout << i << " "; cout << endl;
    }

    // std::addressof possible implementation
    // Obtains the actual address of the object or function arg, even in presence of overloaded operator&
    template< class T >
    T* addressof(T& arg)
    {
        /*
        Unlike static_cast, but like const_cast, the reinterpret_cast expression does not compile to any CPU instructions.
        It is purely a compiler directive which instructs the compiler to treat the sequence of bits (object representation) of expression as if it had the type new_type.
        */
        return reinterpret_cast<T*>(
            &const_cast<char&>(
                reinterpret_cast<const volatile char&>(arg)));
    }

    template<class T>
    struct CustomPtr
    {
    private:
        T* _pad; // add padding to show difference between 'this' and 'data'
        T* _data;
    public:
        CustomPtr(T* data) : _pad(nullptr), _data(data){}
        ~CustomPtr() { delete _data; _data = nullptr; }
        T* operator&() { return _data; }
    };

    template<class T>
    void PrintPointer(CustomPtr<T>* cptr)
    {
        cout << "CustomPtr<T>* overload called with p=" << cptr << endl;
    }

    template<class T>
    void PrintPointer(T* ptr)
    {
        cout << "T* overload called with p=" << ptr << endl;
    }

    void PointerAddressTest()
    {
        CustomPtr<int> cp(new int(100));
        PrintPointer(&cp);
        PrintPointer(std::addressof(cp));
    }
}