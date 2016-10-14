#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace CPlusPlus
{
    /*
        template<
            class CharT,
            class Traits = std::char_traits<CharT>,
            class Allocator = std::allocator<CharT>
        > class basic_string;

        The char_traits class is a traits class template that abstracts basic character and string operations for a given character type.
        The defined operation set is such that generic algorithms almost always can be implemented in terms of it.
        It is possible to use such algorithms with almost any possible character or string type, just by supplying customized char_traits class.
    */
    void BasicStringTest()
    {
        // create the string
        string s1 = "Hello World!";
        string s2 = "Today is a fantastic day.";
        string s3 = "";

        // at()
        cout << "at(0) = " << s1.at(0) << endl;

        // operator[]
        cout << "s1[0] = " << s1[0] << endl;

        // front() returns the first character
        cout << "s1.front() " << s1.front() << endl;

        // back() returns the first character
        cout << "s1.back() " << s1.back() << endl;

        // data() returns a pointer to the first character
        // c_str() returns a pointer to a null-terminated character array with data equivalent to those stored in the string 
        // c_str() and data() perform the same function. (since C++11)
        cout << "s1.data() == s1.c_str(): " << (s1.data() == s1.c_str()) << endl;

        // empty() checks whether a string is empty
        cout << "s3.empty(): " << s3.empty() << endl;

        // size(), length()
        cout << "s1.length(): " << s1.length() << ", s1.size(): " << s1.size() << endl;

        // capacity()
        cout << "s1.capacity(): " << s1.capacity() << endl;

        // substr, find
        cout << "s1.substr(0, 5) = " << s1.substr(0, 5) << endl;
        cout << "s1[s1.find('!')] = " << s1[s1.find('!')] << endl;
        cout << "s1.substr(s1.find(\"Hello World\"), 5) = " << s1.substr(s1.find("Hello World"), 5) << endl;
        cout << "s1.find(\"non existing substr\") == std::string::npos : " << (s1.find("non existing substr") == std::string::npos) << endl;

        // iteration
        string::iterator iter = s1.begin();
        cout << "s1.begin() = " << iter.operator->() << endl;
        string::const_iterator iter_const = s1.cbegin();
        cout << "s1.cbegin() = " << iter_const.operator->() << endl;
        string::reverse_iterator iter_reverse = s1.rbegin();
        cout << "s1.rbegin() = " << iter_reverse.operator->() << endl;
        string::const_reverse_iterator iter_const_reverse = s1.crbegin();
        cout << "s1.crbegin() = " << iter_const_reverse.operator->() << endl;

        // push, pop
        s1.push_back('@');
        s1.pop_back();

        // append
        string s4 = s1 + s2;
        s1.append(s2.c_str());
        cout << "s1.append(s2.c_str()) = " << s1 << endl;

        // compare
        cout << "s1.compare(s1 + s2) = " << s1.compare(s4) << endl;

        // insert
        s1.insert(0, "Marry, ");
        cout << "s1.insert(0, \"Marry, \") = " << s1 << endl;;

        // erase
        s1.erase(0, 7);
        cout << "s1.erase(0, 7) = " << s1 << endl;

        // replace
        s1.replace(0, s1.length(), "Hello");
        cout << "s1.replace(0, s1.length(), \"Hello\") = " << s1 << endl;
    }
}