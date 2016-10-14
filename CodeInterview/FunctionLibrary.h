#pragma once

#define __STDC_WANT_LIB_EXT1__ 1

#include "stdafx.h"
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <ctime>

using namespace std;

namespace CPlusPlus
{
    struct A {
        A(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
        A(int& n) { std::cout << "lvalue overload, n=" << n << "\n"; }
    };

    class B {
    public:
        template<class T1, class T2, class T3>
        B(T1&& t1, T2&& t2, T3&& t3) :
            a1_{ std::forward<T1>(t1) },
            a2_{ std::forward<T2>(t2) },
            a3_{ std::forward<T3>(t3) }
        {
        }

    private:
        A a1_, a2_, a3_;
    };

    void CUtilityFunction()
    {
        /*
        assert = equal to conditional abort
        if (!condition)
        {
            abort();
        }
        */
        bool condition = true;
        assert(condition);

        // srand, rand, reseed
        std::srand(std::time(0)); //use current time as seed for random generator
        int random_variable = std::rand();
        std::cout << "Random value: " << random_variable << endl;

        // typeid operator, typeinfo class
        class TypeIdClass
        {
        };

        TypeIdClass obj1;
        TypeIdClass obj2;
        cout << "obj1 type hashcode = obj2 type hashcode: " << (typeid(obj1) == typeid(obj2)) << endl;
        cout << "obj1 type hashcode = obj2 type hashcode: " << (typeid(obj1).hash_code() == typeid(obj2).hash_code()) << endl;
        cout << "obj1 type name: " << typeid(obj1).name() << "; obj2 type name: " << typeid(obj2).name() << endl;

        /*
        std::forward

        When used according to the following recipe in a function template, forwards the argument to another function with the value category it had when passed to the calling function.
        For example, if used in wrapper such as the following, the template behaves as described below:

        template<class T>
        void wrapper(T&& arg)
        {
            foo(std::forward<T>(arg)); // Forward a single argument.
        }

        If a call to wrapper() passes an rvalue std::string, then T is deduced to std::string (not std::string&, const std::string&, or std::string&&), and std::forward ensures that an rvalue reference is passed to foo.
        If a call to wrapper() passes a const lvalue std::string, then T is deduced to const std::string&, and std::forward ensures that a const lvalue reference is passed to foo.
        If a call to wrapper() passes a non-const lvalue std::string, then T is deduced to std::string&, and std::forward ensures that a non-const lvalue reference is passed to foo.

        template<class T, class U>
        std::unique_ptr<T> make_unique(U&& u)
        {
            return std::unique_ptr<T>(new T(std::forward<U>(u)));
        }

        template<class T, class... U>
        std::unique_ptr<T> make_unique(U&&... u)
        {
            return std::unique_ptr<T>(new T(std::forward<U>(u)...));
        }

        */
        auto p1 = make_unique<A>(2); // rvalue
        int i = 1;
        auto p2 = make_unique<A>(i); // lvalue
        std::cout << "B\n";
        auto t = make_unique<B>(2, i, 3);

        //Since the second template parameter has a default value, it is possible
        //to use a braced-init-list as second argument. The expression below
        //is equivalent to std::exchange(v, std::vector<int>{1,2,3,4});
        std::vector<int> v = { 1,2 };
        vector<int> v_old = std::exchange(v, { 1,2,3,4 });
        cout << "vector after exchanging: ";
        for_each(v.begin(), v.end(), [](int value) {cout << value << ","; });
        cout << endl;
        cout << "returned vector after exchanging: ";
        for_each(v_old.begin(), v_old.end(), [](int value) {cout << value << ","; });
        cout << endl;

        // std::swap
        int x = 10, y = 20;                             // x:10 y:20
        std::swap(x, y);                                // x:20 y:10

        std::vector<int> v1(4, x), v2(6, y);          // foo:4x20 bar:6x10
        std::swap(v1, v2);                            // foo:6x10 bar:4x20

        std::cout << "v1 contains:";
        for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    void CStringFunction()
    {
        char teststr1[] = "this is a teststr1 string";
        char teststr2[] = "this is a teststr2 string";

        // find char in a string
        char* charPtr = strchr(teststr1, 's');
        printf("find the char in the test string: %c\n", *charPtr);

        // find a string in another string
        char* substrPtr = strstr(teststr1, "this");
        cout << "found string: " << substrPtr << endl;
        cout << "substring ptr is equal to test string ptr:" << (substrPtr == teststr1) << endl;

        // compare two strings
        int compare = strcmp(teststr1, teststr2);
        cout << "compare whole string between teststr1 and teststr2 is: " << compare << endl;
        compare = strncmp(teststr1, teststr2, 17);
        cout << "compare the first 17 characters between teststr1 and teststr2 is: " << compare << endl;

        // get the length of a string
        int length = strlen(teststr1);
        cout << "the length of teststr1 is: " << length << endl;

        char charArray[] = { 'a', 'b' };
        length = strlen(charArray);
        cout << "the length of charArray is a uncertain number: " << length << endl;

        length = strnlen_s(charArray, 50);
        cout << "the length of charArray is a uncertain number: " << length << endl;

        // copy a string to a destination string buffer
        char destStr1[100];
        char destStr2[100];
        char destStr3[100];
        char destStr4[100];
        char srcStr[] = "this is the source string";

        char* result = strcpy(destStr1, srcStr);
        cout << "the destination string after copy is: " << result << endl;

        errno_t err = strcpy_s(destStr2, sizeof(destStr2), srcStr);
        cout << "the destination string after copy is: " << destStr2 << endl;

        // If number isn't enough to include source string and ending '\0', no null-character is implicitly appended. This could cause overflow when access destination string
        result = strncpy(destStr3, srcStr, strlen(srcStr) + 1);
        cout << "the destination string after copy is: " << result << endl;

        err = strncpy_s(destStr4, sizeof(destStr4), srcStr, strlen(srcStr) + 1);
        cout << "the destination string after copy is: " << result << endl;

        // concatenate a string to another
        char str[50] = "Hello ";
        std::strcat(str, "World!");
        cout << "the string buffer after concatenation is: " << str << endl;

        err = strcat_s(str, sizeof(str), " Goodbye World!");
        cout << "the string buffer after concatenation is: " << str << endl;

        std::strncat(str, "OK!OK!OK!OK!", 3);
        cout << "the string buffer after concatenation is: " << str << endl;

        // find the tokens from a string
        char input[100] = "A bird came down the walk";
        char *token = std::strtok(input, " ");
        while (token != nullptr) {
            cout << token << '\n';
            token = std::strtok(nullptr, "e");
        }
    }

    void handle_param_errors(
        wchar_t const*,
        wchar_t const*,
        wchar_t const*,
        unsigned int,
        uintptr_t
        )
    {
        cout << "custom handler for handling invalid parameter." << endl;
    }

    void CMemoryFunction()
    {
        // memchr
        char str[] = "ABCDEFG";
        void* charPtr = memchr(str, 'B', strlen(str));
        cout << "Found character: " << *reinterpret_cast<char*>(charPtr) << endl;

        // memcmp
        const char* str1 = "abc";
        const char* str2 = "abd";
        int compare = memcmp(str, str2, strlen(str1));
        if (compare == 0)
        {
            cout << str1 << " equals to " << str2 << endl;
        }
        else if (compare < 0)
        {
            cout << str1 << " precedes " << str2 << endl;
        }
        else
        {
            cout << str1 << " follows " << str2 << endl;
        }

        // memcpy, memcpy_s
        void *p = malloc(3 * sizeof(int));  // allocated memory has no effective type
        int arr[3] = { 1,2, 3 };
        memcpy(p, arr, 3 * sizeof(int));    // allocated memory now has an effective type

        char src[] = "aaaaaaaaaa";
        char dst[] = "xyxyxyxyxy";
        int error_memcpy = memcpy_s(dst, sizeof(dst), src, 5);
        cout << "dst = " << dst << ", error = " << error_memcpy << endl;

        // memmove, memmove_s
        char teststr[] = "1234567890";
        cout << "before memmove: " << teststr << endl;
        memmove(teststr + 4, teststr + 3, 3); // copy from [4,5,6] to [5,6,7]
        cout << "after memmove: " << str << endl;

        _set_invalid_parameter_handler(handle_param_errors);
        errno_t error_memmove = memmove_s(dst, sizeof(dst), src, 5);
        cout << "before memmove_s dst = " << dst << ", error = " << error_memmove << endl;
        error_memmove = memmove_s(dst, 5, src, 7);
        cout << "after memmove_s dst = " << dst << ", error = " << error_memmove <<endl;

        // memset, memset_s
        char teststr2[] = "ghghghghghghghghghghgh";
        cout << "before memset: " << teststr2 << endl;
        memset(str, 'a', 5);
        cout << "after memset: " << teststr2 << endl;

        /*
        // no implementation yet
        _set_invalid_parameter_handler(handle_param_errors);
        errno_t error_memset = memset_s(teststr2, sizeof(teststr2), 'b', 5);
        printf("after memset = \"%s\", error = %d\n", teststr2, error_memset);
        r = memset_s(str, 5, 'c', 10);   // count is greater than destsz  
        printf("after memset = \"%s\", error = %d\n", teststr2, error_memset);
        */
    }
}