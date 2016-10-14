#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

// http://thbecker.net/articles/rvalue_references/section_01.html

namespace CPlusPlus
{
    class ResourceClass
    {
    private:
        vector<int>* m_pResource; // representing expensive resource that is allocated for each object

    public:
        int m_value;
        ResourceClass(){}
        ResourceClass(const ResourceClass& lhs) {}
        ResourceClass(ResourceClass&& rhs){}
        ResourceClass& operator=(const ResourceClass& rhs);
        ResourceClass& operator=(ResourceClass&& rhs);
    };

    ResourceClass& ResourceClass::operator=(const ResourceClass& rhs)
    {
        // [...]
        // Make a clone of what rhs.m_pResource refers to.
        // Destruct the resource that m_pResource refers to. 
        // Attach the clone to m_pResource.
        // [...]
        return *this;
    }

    ResourceClass& ResourceClass::operator=(ResourceClass&& rhs)
    {
        swap(this->m_pResource, rhs.m_pResource);
        return *this;
    }

    void Right_Value_Test()
    {
        class X
        {
        public:
            static X bar()
            {
                return X();
            }
        };

        X x;
        x = X::bar();

        /*
        The above last line
          - clones the resource from the temporary returned by bar,
          - destructs the resource held by x and replaces it with the clone,
          - destructs the temporary and thereby releases its resource.

        In other words, in the special case where the right hand side of the assignment is an rvalue, we want the copy assignment operator to act like this: swap m_pResource and rhs.m_pResource
        This is called move semantics. With C++11, this conditional behavior can be achieved via an overload : X& X::operator=(<mystery type> rhs)
        {
            swap this->m_pResource and rhs.m_pResource
        }

        If X is any type, then X&& is called an rvalue reference to X. For better distinction, the ordinary reference X& is now also called an lvalue reference.
        An rvalue reference is a type that behaves much like the ordinary reference X&, with several exceptions.
        The most important one is that when it comes to function overload resolution, lvalues prefer old-style lvalue references, whereas rvalues prefer the new rvalue references :
            void foo(X& x);         // foo can be called on l-values
            void foo(X&& x);        // foo can be called on r-values
            void foo(X const &);    // foo can be called on r-values, but it's not possible to distinguish beteween l-value and r-values.

        It is permitted to form references to references through type manipulations in templates or typedefs, in which case the reference collapsing rules apply: rvalue reference to rvalue reference collapses to rvalue reference, all other combinations form lvalue reference:
            typedef int&  lref;
            typedef int&& rref;
            int n;
            lref&  r1 = n; // type of r1 is int&
            lref&& r2 = n; // type of r2 is int&
            rref&  r3 = n; // type of r3 is int&
            rref&& r4 = 1; // type of r4 is int&
        (This, along with special rules for template argument deduction when T&& is used in a function template, forms the rules that make std::forward possible.)

        std::move

        template<class T>           ->      template<class T>
        void swap(T& a, T& b)       ->      void swap(T& a, T& b)
        {                           ->      {
            T tmp(a);               ->          T tmp(std::move(a));
            a = b;                  ->          a = std::move(b);
            b = tmp;                ->          b = std::move(tmp);
        }                           ->      }

        Using std::move wherever we can, as shown in the swap function above, gives us the following important benefits:
        1.  For those types that implement move semantics, many standard algorithms and operations will use move semantics and thus experience a potentially significant performance gain.
            An important example is inplace sorting: inplace sorting algorithms do hardly anything else but swap elements, and this swapping will now take advantage of move semantics for all types that provide it.
        2.  The STL often requires copyability of certain types, e.g., types that can be used as container elements. Upon close inspection, it turns out that in many cases, moveability is enough.
            Therefore, we can now use types that are moveable but not copyable (unique_pointer comes to mind) in many places where previously, they were not allowed. For example, these types can now be used as STL container elements.
        3.  The functions that accept rvalue reference parameters (including move constructors, move assignment operators, and regular member functions such as std::vector::push_back) are selected, by overload resolution, when called with rvalue arguments (either prvalues such as a temporary objects or xvalues such as the one produced by std::move).
            If the argument identifies a resource-owning object, these overloads have the option, but aren't required, to move any resources held by the argument. For example, a move constructor of a linked list might copy the pointer to the head of the list and store nullptr in the argument instead of allocating and copying individual nodes.
        4.  Names of rvalue reference variables are lvalues and have to be converted to xvalues to be bound to the function overloads that accept rvalue reference parameters, which is why move constructors and move assignment operators typically use std::move:

        */
    }

    /*
    if-it-has-a-name rule
    */
    ResourceClass goo()
    {
        return ResourceClass();
    }

    void foo(ResourceClass&& x)
    {
        ResourceClass x1 = x;       // calls X(X const & rhs) because x has a name and is considered a lvalue inside the function

        ResourceClass x2 = goo();   // calls X(X&& rhs) because the thing on the right hand side has no name
    }

    class DerivedResourceClass : public ResourceClass
    {
    public:
        // wrong: rhs is an lvalue
        // DerivedResourceClass(DerivedResourceClass&& rhs) : ResourceClass(rhs) {}

        // good, calls ResourceClass(ResourceClass&& rhs)
        DerivedResourceClass(DerivedResourceClass&& rhs) : ResourceClass(std::move(rhs)) {}
    };
}