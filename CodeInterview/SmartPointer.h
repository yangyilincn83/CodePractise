#pragma once

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

namespace CPlusPlus
{
    /*

    Objects of shared_ptr types have the ability of taking ownership of a pointer and share that ownership: once they take ownership, the group of owners
    of a pointer become responsible for its deletion when the last one of them releases that ownership.

    shared_ptr objects release ownership on the object they co-own as soon as they themselves are destroyed, or as soon as their value changes either by
    an assignment operation or by an explicit call to shared_ptr::reset.

    Once all shared_ptr objects that share ownership over a pointer have released this ownership, the managed object is deleted (normally by
    calling ::delete, but a different deleter may be specified on construction).

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    shared_ptr objects can only share ownership by copying their value.
    If two shared_ptr are constructed (or made) from the same (non-shared_ptr) pointer, they will both be owning the pointer without sharing it,
    causing potential access problems when one of them releases it (deleting its managed object) and leaving the other pointing to an invalid location.
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    Additionally, shared_ptr objects can share ownership over a pointer while at the same time pointing to another object.
    This ability is known as aliasing (see constructors), and is commonly used to point to member objects while owning the object they belong to.

    Because of this, a shared_ptr may relate to two pointers:
    1) A stored pointer, which is the pointer it is said to point to, and the one it dereferences with operator*.
    2) An owned pointer (possibly shared), which is the pointer the ownership group is in charge of deleting at some point, and for which it counts as a use.

    Generally, the stored pointer and the owned pointer refer to the same object, but alias shared_ptr objects (those constructed with the alias constructor and
    their copies) may refer to different objects.

    A shared_ptr that does not own any pointer is called an empty shared_ptr.
    A shared_ptr that points to no object is called a null shared_ptr and shall not be dereferenced.
    Notice though that an empty shared_ptr is not necessarily a null shared_ptr, and a null shared_ptr is not necessarily an empty shared_ptr.

    shared_ptr objects replicate a limited pointer functionality by providing access to the object they point to through operators * and ->.
    For safety reasons, they do not support pointer arithmetics.

    */
    inline void Shared_Ptr_Test()
    {
        /*
        *   shared_ptr
        */
        // Constructors
        {
            struct DataObj { int data; };

            std::shared_ptr<int> p1;
            std::shared_ptr<int> p2(nullptr);
            std::shared_ptr<int> p3(new int);
            std::shared_ptr<int> p4(new int, std::default_delete<int>());
            std::shared_ptr<int> p5(new int, [](int* p) -> void {delete p; }, std::allocator<int>());
            std::shared_ptr<int> p6(p5);
            std::shared_ptr<int> p7(std::move(p6));
            std::shared_ptr<int> p8(std::unique_ptr<int>(new int));
            std::shared_ptr<DataObj> obj(new DataObj);

            // The aliasing constructor: constructs a shared_ptr which shares ownership information with r, but holds an unrelated and unmanaged pointer ptr.
            // Even if this shared_ptr is the last of the group to go out of scope, it will call the destructor for the object originally managed by r.
            // However, calling get() on this will always return a copy of ptr.
            // It is the responsibility of the programmer to make sure that this ptr remains valid as long as this shared_ptr exists,
            // such as in the typical use cases where ptr is a member of the object managed by r or is an alias(e.g., downcast) of r.get()
            std::shared_ptr<int> p9(obj, &(obj->data));
            *p9 = 200;

            std::cout << "use_count:\n";
            std::cout << "p1: " << p1.use_count() << '\n';
            std::cout << "p2: " << p2.use_count() << '\n';
            std::cout << "p3: " << p3.use_count() << '\n';
            std::cout << "p4: " << p4.use_count() << '\n';
            std::cout << "p5: " << p5.use_count() << '\n';
            std::cout << "p6: " << p6.use_count() << '\n';
            std::cout << "p7: " << p7.use_count() << '\n';
            std::cout << "p8: " << p8.use_count() << '\n';
            std::cout << "p9: " << p9.use_count() << '\n';
            std::cout << "obj: " << obj.use_count() << '\n';
        }

        // Destructors
        {
            auto deleter = [](int *p) {
                std::cout << "[deleter called]\n";
                delete p;
            };

            std::shared_ptr<int> foo(new int, deleter);
            std::cout << "use_count: " << foo.use_count() << '\n';
        }

        // Reset
        {
            std::shared_ptr<int> sp;  // empty

            sp.reset(new int);       // takes ownership of pointer
            *sp = 10;
            std::cout << *sp << '\n';

            sp.reset(new int);       // deletes managed object, acquires new pointer
            *sp = 20;
            std::cout << *sp << '\n';

            sp.reset();               // deletes managed object
        }

        // Swap
        {
            std::shared_ptr<int> foo(new int(10));
            std::shared_ptr<int> bar(new int(20));

            foo.swap(bar);

            cout << "*foo: " << (*foo) << '\n';
            cout << "*bar: " << (*bar) << '\n';
        }

        // operator=
        {
            std::shared_ptr<int> foo;
            std::shared_ptr<int> bar(new int(10));
            std::shared_ptr<int> tor;

            foo = bar;                                              // copy
            tor = foo;                                              // copy
            cout << "foo's use count:" << foo.use_count() << endl;
            cout << "bar's use count:" << bar.use_count() << endl;
            cout << "tor's use count:" << tor.use_count() << endl;

            bar = std::make_shared<int>(20);                        // move assignment operator
            cout << "foo's use count:" << foo.use_count() << endl;
            cout << "bar's use count:" << bar.use_count() << endl;
            cout << "tor's use count:" << tor.use_count() << endl;

            std::unique_ptr<int> unique(new int(30));
            // std::shared_ptr<int> shared(unique);                 // compile error
            // std::shared_ptr<int> shared(std::move(unique));      // move constructor from unique_ptr
            foo = std::move(unique);                                // move operator from unique_ptr
            cout << "foo's use count:" << foo.use_count() << endl;
            cout << "bar's use count:" << bar.use_count() << endl;
            cout << "tor's use count:" << tor.use_count() << endl;

            std::cout << "*foo: " << *foo << '\n';
            std::cout << "*bar: " << *bar << '\n';
            std::cout << "*tor: " << *tor << '\n';
        }
    }

    inline void Weak_Ptr_Test()
    {
        std::shared_ptr<int> sp(new int);
        std::weak_ptr<int> wp(sp);
        std::shared_ptr<int> sp1 = sp;

        std::cout << "use_count:\n";
        std::cout << "wp use_count: " << wp.use_count() << '\n'; // always returns the number of shared_ptr objects that manage the object 
        std::cout << "sp use_count: " << sp.use_count() << '\n';

        std::cout << "after wp.lock:\n";
        shared_ptr<int> sp2 = wp.lock();
        std::cout << "sp use_count: " << sp.use_count() << '\n';
        std::cout << "wp use_count: " << wp.use_count() << '\n';

        std::cout << "after wp.reset:\n";
        wp.reset(); // doesn't referenced the managed object but shared_ptr use count doesn't change
        std::cout << "sp use_count: " << sp.use_count() << '\n';
        std::cout << "wp use_count: " << wp.use_count() << '\n';

        sp.reset();
        sp1.reset();
        sp2.reset();
        std::cout << "after all shread_ptr objects reset:\n";
        std::cout << "wp expired: " << wp.expired() << '\n';
    }

    /*
    std::unique_ptr is a smart pointer that retains sole ownership of an object through a pointer and destroys that object when the unique_ptr goes out of scope.
    No two unique_ptr instances can manage the same object.

    The object is destroyed and its memory deallocated when either of the following happens:
    1) unique_ptr managing the object is destroyed
    2) unique_ptr managing the object is assigned another pointer via operator= or reset().

    The object is destroyed using a potentially user-supplied deleter by calling Deleter(ptr).
    The deleter calls the destructor of the object and dispenses the memory.

    A unique_ptr may alternatively own no object, in which case it is called empty.

    There are two versions of std::unique_ptr:
    1) Manages the lifetime of a single object (e.g. allocated with new)
    2) Manages the lifetime of a dynamically-allocated array of objects (e.g. allocated with new[])

    The class satisfies the requirements of MoveConstructible and MoveAssignable, but not the requirements of either CopyConstructible or CopyAssignable.

    */
    inline void Unique_Ptr_Test()
    {
        struct Foo
        {
        public:
            Foo() { std::cout << "Foo::Foo\n"; }
            ~Foo() { std::cout << "Foo::~Foo\n"; }
            void bar() { std::cout << "Foo::bar\n"; }
            static void f(const Foo &)
            {
                std::cout << "f(const Foo&)\n";
            }
        };

        // auto p1 = make_unique<Foo>();
        unique_ptr<Foo> p1(new Foo);  // p1 owns Foo
        if (p1)
        {
            p1->bar();
        }

        {
            unique_ptr<Foo> p2(std::move(p1));  // now p2 owns Foo
            Foo::f(*p2);
            p1 = std::move(p2);  // ownership returns to p1
            std::cout << "destroying p2...\n";
        }

        if (p1)
        {
            p1->bar();
        }
    }

    /*
        Self-defined Smart Pointer
    */
    template<class T>
    class SmartPtr
    {
    private:
        T* m_ref;
        unsigned int* m_refCount;

        void Retain()
        {
            (*m_refCount)++;
        }

        void Release()
        {
            (*m_refCount)--;
            if (*m_refCount == 0)
            {
                delete m_ref;
                m_ref = NULL;
                delete m_refCount;
                m_refCount = NULL;
            }
        }
    public:
        // constructor
        SmartPtr(T* ptr)
        {
            cout << "SmartPtr constructor called" << endl;
            _ASSERTE(ptr != NULL);
            this->m_ref = ptr;
            this->m_refCount = new unsigned int(0);
            Retain();
        }

        // destructor
        ~SmartPtr()
        {
            Release();
        }

        // copy constructor
        SmartPtr(const SmartPtr<T>& sptr)
        {
            cout << "SmartPtr copy constructor called" << endl;
            this->m_ref = sptr.m_ref;
            this->m_refCount = sptr.m_refCount;
            Retain();
        }

        // move constructor
        SmartPtr(SmartPtr<T>&& sptr)
        {
            cout << "SmartPtr move constructor called" << endl;

            // swap the value with rvalue reference
            m_ref = sptr.m_ref;
            m_refCount = sptr.m_refCount;
            sptr.m_ref = nullptr;
            sptr.m_refCount = nullptr;
        }

        // assignment operator
        SmartPtr<T>& operator =(const SmartPtr<T>& sptr)
        {
            cout << "SmartPtr assignedment operator called" << endl;
            if (this->m_ref != sptr.m_ref)
            {
                Release();
                m_ref = sptr.m_ref;
                m_refCount = sptr.m_refCount;
                Retain();
            }

            return *this;
        }

        // move assignment operator
        SmartPtr<T>& operator =(SmartPtr<T>&& sptr)
        {
            if (this->m_ref != sptr.m_ref)
            {
                cout << "SmartPtr move assignedment operator called" << endl;

                std::swap(this->m_ref, sptr.m_ref);
                std::swap(this->m_refCount, sptr.m_refCount);
            }

            return *this;
        }

        // overloaded * operator
        T& operator*()
        {
            return *m_ref;
        }

        explicit operator T*()
        {
            return m_ref;
        }

        T* operator->()
        {
            return m_ref;
        }

        bool operator==(const SmartPtr<T> &sptr)
        {
            return (m_ref == sptr.m_ref);
        }

        unsigned int use_count()
        {
            return *m_refCount;
        }
    };

    inline void SmartPtrTest()
    {
        class TestClass
        {
        public:
            void Print()
            {
                cout << "TestClass::Print()" << endl;
            }
        };

        int* a = new int(10);
        SmartPtr<int> sptr1(a);
        SmartPtr<int> sptr2(sptr1); // copy constructor
        sptr2 = sptr1;              // no actual assignment operation
        sptr2 = std::move(sptr1);   // no actual move assignment operator

        cout << "sptr1 == sptr2 : " << (sptr1 == sptr2) << endl;
        cout << "*sptr1 = : " << *sptr1 << endl;
        cout << "*sptr2 = : " << *sptr2 << endl;

        // move assignedment operator
        int* b = new int(20);
        SmartPtr<int> sptr3(b);
        sptr3 = std::move(sptr1);
        cout << "sptr1.use_count() = " << sptr1.use_count() << endl;
        cout << "sptr2.use_count() = " << sptr2.use_count() << endl;
        cout << "sptr3.use_count() = " << sptr3.use_count() << endl;

        // -> operator overload
        SmartPtr<TestClass> sptr(new TestClass());
        sptr->Print();

        // T* operator overload
        TestClass* ptr_tc = (TestClass*)sptr;

        // addressof
        SmartPtr<TestClass>* sptr_addrof = addressof(sptr);
    }
}