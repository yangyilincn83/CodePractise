#pragma once

#include "stdafx.h"
#include <iostream>

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>

using namespace std;

namespace CPlusPlus
{
    class DataClass
    {
    public:
        DataClass() : m_value(0), m_char('\0') {}
        DataClass(int i) : m_value(i), m_char('\0') {}
        DataClass(int i, char c) : m_value(i), m_char(c) {}
        int GetIntValue() const { return m_value; }
        int GetCharValue() const { return m_char; }
        void SetIntValue(int val) { m_value = val; }

        bool operator<(const DataClass& obj) const
        {
            return this->m_value < obj.m_value;
        }

    private:
        int m_value;
        char m_char;
    };

    template<typename Container>
    void PrintAllElements(Container cont)
    {
        for (auto element : cont)
            cout << element << "    ";
        cout << endl;
    }

    namespace Container
    {
        /*
            An object of type std::initializer_list<T> is a lightweight proxy object that provides access to an array of objects of type const T.

            Initializer lists may be implemented as a pair of pointers or pointer and length. Copying a std::initializer_list does not copy the underlying objects.

            The underlying array is not guaranteed to exist after the lifetime of the original initializer list object has ended.
            The storage for std::initializer_list is unspecified (i.e. it could be automatic, temporary, or static read-only memory, depending on the situation).

            The underlying array is a temporary array, in which each element is copy-initialized (except that narrowing conversions are invalid) from the corresponding
            element of the original initializer list. The lifetime of the underlying array is the same as any other temporary object, except that initializing an
            initializer_list object from the array extends the lifetime of the array exactly like binding a reference to a temporary (with the same exceptions,
            such as for initializing a non-static class member).
            The underlying array may be allocated in read-only memory.
        */
        void InitializerListTest()
        {
            std::initializer_list<int> empty_list;
            std::cout << "empty_list.size(): " << empty_list.size() << '\n';

            // create initializer lists using list-initialization
            std::initializer_list<int> digits{ 1, 2, 3, 4, 5 };
            std::cout << "digits.size(): " << digits.size() << '\n';

            // special rule for auto means 'fractions' has the
            // type std::initializer_list<double>
            auto fractions = { 3.14159, 2.71828 };
            std::cout << "fractions.size(): " << fractions.size() << '\n';
        }

        /*
            This container is an aggregate type with the same semantics as a struct holding a C-style array T[N] as its only non-static data member.
            Unlike a C-style array, it doesn't decay to T* automatically.
            As an aggregate type, it can be initialized with aggregate-initialization given at most N initializers that are convertible to T: std::array<int, 3> a = {1,2,3};.
        */
        void ArrayTest()
        {
            array<int, 10> arr;
            cout << "array.size(): " << arr.size() << endl;
            cout << "array.maxsize(): " << arr.max_size() << endl;
            cout << "array.empty(): " << arr.empty() << endl;

            arr.fill(100);
            cout << "array.front(): " << arr.front() << endl;
            cout << "array.end(): " << arr.back() << endl;

            arr[0] = 1000;
            arr[9] = 1000;
            cout << "array.front(): " << arr.front() << endl;
            cout << "array.end(): " << arr.back() << endl;

            cout << "print all elements: ";
            PrintAllElements(arr);
            cout << endl;

            cout << "arr.data() == &(arr.front()): " << (arr.data() == &(arr.front())) << endl;
        }

        /*
            std::vector is a sequence container that encapsulates dynamic size arrays.

            The elements are stored contiguously, which means that elements can be accessed not only through iterators, but also using offsets on regular pointers to elements.
            This means that a pointer to an element of a vector may be passed to any function that expects a pointer to an element of an array.
        */
        void VectorTest()
        {
            vector<int> v = { 1, 2, 3, 4,5,6,7,8,9,10 };
            vector<DataClass> vdc;

            cout << "vector[0]:" << v[0] << endl;
            cout << "vector.at(0):" << v.at(0) << endl;
            cout << "vector.front():" << v.front() << endl;
            cout << "vector.back()" << v.back() << endl;
            cout << "vector.size()" << v.size() << endl;
            cout << "vector.capacity()" << v.capacity() << endl;
            v.resize(30);
            cout << "vector.capacity()" << v.capacity() << endl;

            // insert
            cout << "Insert element at first position:" << endl;
            vdc.insert(vdc.begin(), DataClass(1))->GetIntValue();
            vdc.insert(vdc.begin(), DataClass(2))->GetIntValue();

            // erase
            cout << "The first element after removing the first element:" << vdc.erase(vdc.begin())->GetIntValue() << endl;

            // emplace
            vdc.emplace(vdc.begin(), 3);

            // emplace_back
            vdc.emplace_back(4);

            // push_back
            vdc.push_back(DataClass(5));

            // pop_back
            vdc.pop_back();

            cout << "Print all elements: ";
            for (auto element : vdc)
                cout << element.GetIntValue() << ",";
            cout << endl;
        }

        /*
            std::deque (double-ended queue) is an indexed sequence container that allows fast insertion and deletion at both its beginning and its end.

            In addition, insertion and deletion at either end of a deque never invalidates pointers or references to the rest of the elements.

            As opposed to std::vector, the elements of a deque are not stored contiguously.
            Typical implementations use a sequence of individually allocated fixed-size arrays.

            The storage of a deque is automatically expanded and contracted as needed.
            Expansion of a deque is cheaper than the expansion of a std::vector because it does not involve copying of the existing elements to a new memory location.

            The complexity (efficiency) of common operations on deques is as follows:
            Random access - constant O(1)
            Insertion or removal of elements at the end or beginning - constant O(1)
            Insertion or removal of elements - linear O(n)
        */
        void DequeTest()
        {
            deque<char> charDeque;

            // push_back
            for (char chr = 'a'; chr <= 'z'; chr++)
            {
                charDeque.push_back(chr);
            }

            // print all
            PrintAllElements(charDeque);
            cout << endl;

            // pop_back
            while (!charDeque.empty())
            {
                charDeque.pop_back();
            }

            // push_front
            for (char chr = 'a'; chr <= 'z'; chr++)
            {
                charDeque.push_front(chr);
            }

            // print all
            PrintAllElements(charDeque);
            cout << endl;

            // pop_front
            while (!charDeque.empty())
            {
                charDeque.pop_front();
            }

            // emplace_front
            for (char chr = 'a'; chr <= 'z'; chr++)
            {
                charDeque.emplace_front(chr);
            }

            // print all
            PrintAllElements(charDeque);
            cout << endl;
        }

        /*
            std::forward_list is a container that supports fast insertion and removal of elements from anywhere in the container.

            Fast random access is not supported.
            It is implemented as a singly-linked list and essentially does not have any overhead compared to its implementation in C.

            Compared to std::list this container provides more space efficient storage when bidirectional iteration is not needed.
            Adding, removing and moving the elements within the list, or across several lists, does not invalidate the iterators currently referring to other elements in the list.
            However, an iterator or reference referring to an element is invalidated when the corresponding element is removed (via erase_after) from the list.
        */
        void ForwardListTest()
        {
            forward_list<int> fwlist = { 1,2,7,7,8,9, 2,3,4,4,5,6,1 };

            // insert_after, emplace_after, erase_after
            fwlist.insert_after(fwlist.before_begin(), 200);
            fwlist.insert_after(fwlist.begin(), 100);
            fwlist.erase_after(fwlist.begin());

            // print all
            PrintAllElements(fwlist);
            cout << endl;

            // push_front, pop_front, emplace_front
            fwlist.push_front(200);
            fwlist.pop_front();
            PrintAllElements(fwlist);
            cout << endl;

            // unique, removes consecutive duplicate elements
            fwlist.unique();
            PrintAllElements(fwlist);
            cout << endl;

            // reverse
            fwlist.reverse();
            PrintAllElements(fwlist);
            cout << endl;

            // sort from large to small
            fwlist.sort(std::greater<int>());
            PrintAllElements(fwlist);
            cout << endl;

            // remove values greater than 5
            fwlist.remove_if([](int value) {return value > 5; });
            PrintAllElements(fwlist);
            cout << endl;
        }

        /*
            std::list is a container that supports constant time insertion and removal of elements from anywhere in the container.

            Fast random access is not supported.
            It is usually implemented as a doubly-linked list.

            Compared to std::forward_list this container provides bidirectional iteration capability while being less space efficient.

            In addition, removing and moving the elements within the list or across several lists does not invalidate the iterators or references.
            An iterator is invalidated only when the corresponding element is deleted.
        */
        void ListTest()
        {
            list<int> num_list;

            for (int i = 0; i < 10; i++)
            {
                num_list.emplace_front(i);
            }

            for (int i = 100; i > 40; i--)
            {
                num_list.emplace_back(i);
            }

            num_list.insert(num_list.begin(), 100);
            num_list.sort();

            list<int>::iterator iter = num_list.begin();
            PrintAllElements(num_list);
        }

        /*
            std::set is an associative container that contains a sorted set of unique objects of type Key.
            Sorting is done using the key comparison function Compare. Search, removal, and insertion operations have logarithmic complexity.

            Sets are usually implemented as red-black trees.

            Everywhere the standard library uses the Compare concept, uniqueness is determined by using the equivalence relation.
            In imprecise terms, two objects a and b are considered equivalent (not unique) if neither compares less than the other: !comp(a, b) && !comp(b, a).
        */
        void SetTest()
        {
            set<char> dictSet;

            for (char chr = 'a'; chr <= 'z'; chr++)
            {
                dictSet.insert(chr);
            }
            cout << "set size: " << dictSet.size() << endl;

            for (char chr = 'a'; chr <= 'z'; chr++)
            {
                dictSet.insert(chr);
            }
            cout << "set size: " << dictSet.size() << endl;

            set<char>::iterator iter = dictSet.find('p');
            cout << "found char: " << *iter << endl;

            int removed = dictSet.erase('p');
            cout << "number of char 'p' removed: " << removed << endl;
        }

        /*
            Multiset is an associative container that contains a sorted set of objects of type Key.
            Unlike set, multiple keys with equivalent values are allowed.
            Sorting is done using the key comparison function Compare. Search, insertion, and removal operations have logarithmic complexity.

            Everywhere the standard library uses the Compare concept, equivalence is determined by using the equivalence relation as described on Compare.
            In imprecise terms, two objects a and b are considered equivalent if neither compares less than the other: !comp(a, b) && !comp(b, a).
            The order of the elements that compare equivalent is the order of insertion and does not change.
        */
        void MultiSetTest()
        {
            multiset<char> dictMultiset;

            for (char chr = 'a'; chr <= 'z'; chr++)
            {
                dictMultiset.insert(chr);
            }
            cout << "multiset size: " << dictMultiset.size() << endl;

            for (char chr = 'a'; chr <= 'z'; chr++)
            {
                dictMultiset.insert(chr);
            }
            cout << "multiset size: " << dictMultiset.size() << endl;

            set<char>::iterator iter = dictMultiset.find('p');
            cout << "found char: " << *iter << endl;

            int removed = dictMultiset.erase('p');
            cout << "number of char 'p' removed: " << removed << endl;
        }

        /*
            std::map is a sorted associative container that contains key-value pairs with unique keys.
            Keys are sorted by using the comparison function Compare.
            Search, removal, and insertion operations have logarithmic complexity.

            Maps are usually implemented as red-black trees.

            Everywhere the standard library uses the Compare concept, uniqueness is determined by using the equivalence relation.
            In imprecise terms, two objects a and b are considered equivalent (not unique) if neither compares less than the other: !comp(a, b) && !comp(b, a).
        */
        void MapTest()
        {
            map<char, int> dict_index;

            for (char cap = 'a'; cap <= 'z'; cap++)
            {
                dict_index[cap] = (cap - 'a' + 1) * 1000;
            }

            dict_index.at('a') = 1;

            map<char, int>::iterator begin_iter = dict_index.begin();
            map<char, int>::iterator end_iter = dict_index.end();
            for (; begin_iter != end_iter; begin_iter++)
            {
                pair<char, int> value_pair = *begin_iter;
                cout << "value pair:" << value_pair.first << "," << value_pair.second << endl;
            }

            cout << "map size:" << dict_index.size() << endl;
        }

        /*
            Multimap is an associative container that contains a sorted list of key-value pairs.
            Sorting is done according to the comparison function Compare, applied to the keys.
            Search, insertion, and removal operations have logarithmic complexity.

            The order of the key-value pairs whose keys compare equivalent is the order of insertion and does not change. (since C++11)
        */
        void MultiMapTest()
        {
            multimap<char, int> dict_index;

            for (char cap = 'a'; cap <= 'z'; cap++)
            {
                dict_index.insert(pair<char, int>(cap, (cap - 'a' + 1) * 10));
            }

            for (char cap = 'a'; cap <= 'z'; cap++)
            {
                dict_index.insert(pair<char, int>(cap, (cap - 'a' + 1) * 100));
            }

            multimap<char, int>::iterator iter = dict_index.find('a');
            cout << "Found key 'a': " << iter->first << ", " << iter->second << endl;

            int count = dict_index.count('a');
            cout << "Found key 'a': " << count << " times." << endl;

            pair<multimap<char, int>::iterator, multimap<char, int>::iterator> p = dict_index.equal_range('a');
            for (iter = p.first; iter != p.second; iter++)
            {
                cout << "Found key 'a': " << iter->first << ", " << iter->second << endl;
            }
        }

        /*
            Unordered set is an associative container that contains a set of unique objects of type Key.
            Search, insertion, and removal have average constant-time complexity.

            Internally, the elements are not sorted in any particular order, but organized into buckets.
            Which bucket an element is placed into depends entirely on the hash of its value.
            This allows fast access to individual elements, since once a hash is computed, it refers to the exact bucket the element is placed into.
        */
        void UnorderedSetTest()
        {
        }

        void UnorderedMultiSetTest()
        {
        }

        /*
            Unordered map is an associative container that contains key-value pairs with unique keys.
            Search, insertion, and removal of elements have average constant-time complexity.
            
            Internally, the elements are not sorted in any particular order, but organized into buckets.
            Which bucket an element is placed into depends entirely on the hash of its key.
            This allows fast access to individual elements, since once hash is computed, it refers to the exact bucket the element is placed into.
        */
        void UnorderedMapTest()
        {
            // Create an unordered_map of three strings (that map to strings)
            std::unordered_map<std::string, std::string> u = {
                { "RED","#FF0000" },
                { "GREEN","#00FF00" },
                { "BLUE","#0000FF" }
            };

            // Iterate and print keys and values of unordered_map
            for (const auto& n : u) {
                std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
            }

            // Add two new entries to the unordered_map
            u["BLACK"] = "#000000";
            u["WHITE"] = "#FFFFFF";

            // Output values by key
            std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
            std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n";
        }

        /*
            Unordered multimap is an unordered associative container that supports equivalent keys
            (an unordered_multimap may contain multiple copies of each key value) and that associates values of another type with the keys.
            The unordered_multimap class supports forward iterators. Search, insertion, and removal have average constant-time complexity.
        */
        void UnorderedMultiMapTest()
        {

        }
    }

    namespace ContainerAdapter
    {
        /*
            The std::queue class is a container adapter that gives the programmer the functionality of a queue - specifically, a FIFO (first-in, first-out) data structure.
            The class template acts as a wrapper to the underlying container - only a specific set of functions is provided.
            The queue pushes the elements on the back of the underlying container and pops them from the front.

            The type of the underlying container to use to store the elements. The container must satisfy the requirements of SequenceContainer.
            Additionally, it must provide the following functions with the usual semantics:
                back()
                front()
                push_back()
                pop_front()

            The standard containers std::deque and std::list satisfy these requirements.
        */
        void QueueTest()
        {
            queue<int> q1;
            queue<int, deque<int>> q2;
            queue<int, list<int>> q3;

            // enqueue
            q1.push(1);
            q1.push(2);

            // dequeue and print all
            cout << "queue elements: ";
            while (!q1.empty())
            {
                cout << q1.front() << ",";
                q1.pop();
            }
            cout << endl;

            cout << "queue.empty() = " << q1.empty() << endl;
        }

        /*
            The std::stack class is a container adapter that gives the programmer the functionality of a stack - specifically, a FILO (first-in, last-out) data structure.
            The class template acts as a wrapper to the underlying container - only a specific set of functions is provided.
            The stack pushes and pops the element from the back of the underlying container, known as the top of the stack.

            The type of the underlying container to use to store the elements. The container must satisfy the requirements of SequenceContainer.
            Additionally, it must provide the following functions with the usual semantics:
                back()
                push_back()
                pop_back()

            The standard containers std::vector, std::deque and std::list satisfy these requirements.
        */
        void StackTest()
        {
            stack<int> s;
            s.push(1);
            s.push(2);
            cout << "s.top() = " << s.top() << endl;
        }

        /*
            A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.
            A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top().
            Working with a priority_queue is similar to managing a heap in some random access container, with the benefit of not being able to accidentally invalidate the heap.

            The type of the underlying container to use to store the elements. The container must satisfy the requirements of SequenceContainer, and its iterators must satisfy the requirements of RandomAccessIterator. Additionally, it must provide the following functions with the usual semantics:
                front()
                push_back()
                pop_back()

            The standard containers std::vector and std::deque satisfy these requirements.
        */
        void PriorityQueueTest()
        {

        }
    }
}