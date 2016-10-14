#pragma once

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

namespace CPlusPlus
{
    void CQuickSortTest()
    {
        DataClass objects[] = { 5,4,3,12,43,7,9 };
        int size = sizeof(objects) / sizeof(DataClass);
        qsort(objects, size, sizeof(DataClass), [] (const void* obj1, const void* obj2) -> int
        {
            const DataClass* dobj1 = static_cast<const DataClass*>(obj1);
            const DataClass* dobj2 = static_cast<const DataClass*>(obj2);
            if (dobj1->GetIntValue() < dobj2->GetIntValue())
            {
                return -1;
            }
            else
            {
                if (dobj1->GetIntValue() > dobj2->GetIntValue())
                    return 1;
                else
                    return 0;
            }
        });

        cout << "values after sorting: ";
        for_each(&objects[0], &objects[size], [](DataClass& obj) {cout << obj.GetIntValue() << ","; });
        cout << endl;
    }

    void CBinarySearchTest()
    {
        DataClass objects[] = { 1, 4, 8, 12, 15, 16, 20, 25, 40 };
        int size = sizeof(objects) / sizeof(DataClass);
        DataClass key(40);
        void* result = bsearch(&key, objects, size, sizeof(DataClass), [](const void* obj1, const void* obj2) -> int
        {
            const DataClass* dobj1 = static_cast<const DataClass*>(obj1);
            const DataClass* dobj2 = static_cast<const DataClass*>(obj2);

            if (dobj1->GetIntValue() < dobj2->GetIntValue())
            {
                return -1;
            }
            else if (dobj1->GetIntValue() > dobj2->GetIntValue())
            {
                return 1;
            }
            else
            {
                return 0;
            }
        });

        cout << "Found value: " << static_cast<DataClass*>(result)->GetIntValue() << endl;
    }

    void MinMaxTest()
    {
        DataClass a = 10;
        DataClass b = 20;
        const DataClass& c = min<DataClass>(a, b, [](const DataClass&a, const DataClass& b)
        {
            return a.GetIntValue() < b.GetIntValue();
        });
        cout << "addressof(c)" << addressof(c) << endl;
        cout << "addressof(a)" << addressof(a) << endl;
        cout << "the min number is: " << c.GetIntValue() << endl;
        a.SetIntValue(100);
        cout << "the min number is: " << c.GetIntValue() << endl;
    }

    void HeapOperationTest()
    {
        vector<int> vec = { 4, 5 ,8, 23, 9, 2, 40 };

        // create a min-heap
        make_heap(vec.begin(), vec.end(), greater<int>());

        // push a new element into the heap
        vec.push_back(6);
        push_heap(vec.begin(), vec.end(), greater<int>());

        // pop the top value from the heap
        pop_heap(vec.begin(), vec.end(), greater<int>());
        vec.pop_back();

        // print out all heap elements
        cout << "heap elements";
        for_each(vec.begin(), vec.end(), [](int value) {
            cout << value << ";";
        });
        cout << endl;

        // sort heap
        sort_heap(vec.begin(), vec.end(), greater<int>());

        // print out all heap elements
        cout << "elements after sorting the heap";
        for_each(vec.begin(), vec.end(), [](int value) {
            cout << value << ";";
        });
        cout << endl;
    }

    void BinarySearchOperationTest()
    {
        // lower_bound, upper_bound
        std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
        auto lower = std::lower_bound(data.begin(), data.end(), 4);
        auto upper = std::upper_bound(data.begin(), data.end(), 4);
        std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));

        // binary_search
        std::vector<int> haystack{ 1, 3, 4, 5, 9 };
        std::vector<int> needles{ 1, 2, 3 };
        for (auto needle : needles) {
            std::cout << "Searching for " << needle << '\n';
            if (std::binary_search(haystack.begin(), haystack.end(), needle)) {
                std::cout << "Found " << needle << '\n';
            }
            else {
                std::cout << "no dice!\n";
            }
        }

        // equal_range
        std::vector<DataClass> vec = { { 1,'A' },{ 2,'B' },{ 2,'C' },{ 2,'D' },{ 4,'G' },{ 3,'F' } };
        auto p = std::equal_range(vec.begin(), vec.end(), DataClass(2, '?'));
        for (auto i = p.first; i != p.second; ++i)
            std::cout << i->GetCharValue() << ' ';
    }

    template<class ForwardIt, class T>
    std::pair<ForwardIt, ForwardIt>
    equal_range(ForwardIt first, ForwardIt last, const T& value)
    {
        return std::make_pair(std::lower_bound(first, last, value), std::upper_bound(first, last, value));
    }

    void SortingOperationTest()
    {
        std::array<int, 10> s = { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

        // sort using the default operator<
        std::sort(s.begin(), s.end());
        for (int a : s) {
            std::cout << a << " ";
        }
        std::cout << '\n';

        // sort using a standard library compare function object
        std::sort(s.begin(), s.end(), std::greater<int>());
        for (int a : s) {
            std::cout << a << " ";
        }
        std::cout << '\n';
    }

    void ModifyingSequenceOperationTest()
    {
        // std::copy
        std::vector<int> from_vector(10);
        std::iota(from_vector.begin(), from_vector.end(), 0);

        std::vector<int> to_vector;
        std::copy(from_vector.begin(), from_vector.end(), back_inserter<vector<int>>(to_vector));

        // std::vector<int> to_vector(10);
        // std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());

        for (vector<int>::iterator iter = to_vector.begin(); iter != to_vector.end(); iter++)
        {
            cout << *iter << ",";
        }
        cout << endl;

        // std::move

        // std::fill

        // std::swap

        // std::remove

        // std::reverse

        // std::unique

        // std::rotate
    }

    void NonModifyingSequenceOperationTest()
    {
        // std::all_of, std::any_of, std::not_of
        vector<int> vec = { 1,2,3,4,5,6,7,8 };
        cout << "all_of: " << all_of(vec.begin(), vec.end(), [](int value) -> bool {return value % 2 == 0; }) << endl;
        cout << "any_of: " << any_of(vec.begin(), vec.end(), [](int value) -> bool {return value % 2 == 0; }) << endl;
        cout << "none_of: " << none_of(vec.begin(), vec.end(), [](int value) -> bool {return value % 2 == 0; }) << endl;

        // std::for_each

        // std::count
        int data[] = { 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
        std::vector<int> v1(data, data + 10);
        int target1 = 3;
        int target2 = 5;
        int num_items1 = std::count(v1.begin(), v1.end(), target1);
        int num_items2 = std::count(v1.begin(), v1.end(), target2);
        std::cout << "number: " << target1 << " count: " << num_items1 << '\n';
        std::cout << "number: " << target2 << " count: " << num_items2 << '\n';

        // std::equal
        const string s = "radar";
        cout << s << " is a palindrome: " << std::equal(s.begin(), s.begin() + s.length() / 2, s.rbegin()) << endl;

        // std::find
        int n1 = 3;
        int n2 = 5;
        std::vector<int> v2{ 0, 1, 2, 3, 4 };
        auto result1 = std::find(std::begin(v2), std::end(v2), n1);
        auto result2 = std::find(std::begin(v2), std::end(v2), n2);

        if (result1 != std::end(v2)) {
            std::cout << "v contains: " << n1 << '\n';
        }
        else {
            std::cout << "v does not contain: " << n1 << '\n';
        }

        if (result2 != std::end(v2)) {
            std::cout << "v contains: " << n2 << '\n';
        }
        else {
            std::cout << "v does not contain: " << n2 << '\n';
        }
    }
}