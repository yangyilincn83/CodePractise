#pragma once

#include <mutex>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

namespace CPlusPlus
{
    // http://www.bogotobogo.com/cplusplus/multithreaded4_cplusplus11.php
    // http://en.cppreference.com/w/cpp/thread/thread
    // https://www.justsoftwaresolutions.co.uk/threading/locks-mutexes-semaphores.html
    // http://www.codeproject.com/Articles/598695/Cplusplus-threads-locks-and-condition-variables

    /*
        An important thing to note is that if a thread function throws an exception it won't be caught with a regular try-catch block.
        This function won't work as expected
    */
    void exception_thread()
    {
        static std::mutex s_mutex;
        static std::vector<exception_ptr> s_exceptions;

        try
        {
            throw exception("foo with exception thrown\n");
        }
        catch (...)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            s_exceptions.push_back(std::current_exception());
        }
    }

    void Thread_CatchException()
    {
        try
        {
            thread t1(exception_thread);
            t1.join();
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    /*
        std::this_thread methods
    */
    void current_thread()
    {
        std::thread::id tid = std::this_thread::get_id();

        // Provides a hint to the implementation to reschedule the execution of threads, allowing other threads to run
        std::this_thread::yield();

        // Block the execution of the current thread for 5 seconds
        std::this_thread::sleep_for(5s);

        // Blocks the execution of the current thread until specified sleep_time has been reached
        // std::this_thread::sleep_until(xxxxx);
    }

    /*
        Thread RAII class
    */
    class thread_RAII
    {
        thread& t;
    public:
        thread_RAII(thread& th) :t(th)
        {
            cout << "thread_RAII constructor\n";
        }

        ~thread_RAII()
        {
            if (t.joinable())
            {
                cout << "if joinable(), then t.join()\n";
                t.join();
            }
            cout << "thread_RAII destructor\n";
        }

    private:
        // copy constructor
        thread_RAII(const thread_RAII& thr) = delete;

        // copy-assignment operator
        thread_RAII& operator=(const thread_RAII& thr) = delete;
    };

    /*
        Functor Class
    */
    class task
    {
    public:
        task(double d, string& s) : m_d(d), m_s(s)
        {
            cout << "task constructor\n";
        }

        void operator()()
        {
            cout << "operator()\n";
            cout << "Number and String transferred into the thread function: " << m_d << m_s.c_str() << endl;
        }

    private:
        double m_d;
        string& m_s;
    };

    void func1() { std::cout << "func1()\n"; }
    void func2() { std::cout << "func2()\n"; }

    void Thread_Join_Detach()
    {
        // functor object
        string s = "local string";
        task tsk(1.0, s);
        thread t1(tsk);
        t1.join();  // t1's completion needs to be guaranteed. Otherwise, s could be accessed from tsk when it goes out of scope with this current function exiting.

        // uniform initializer
        thread t2{ task(1.0, string("temp string")) };
        t2.join();

        // function initializer
        thread t3(func1);
        t3.detach();
        assert(!t3.joinable());

        // lamda function initializer
        thread t4([] {
            func1();
            func2();
        });
        t4.join();
    }

    void ThreadProc(double d, const string& str)
    {
        cout << "Number and String transferred into the thread function: " << d << str.c_str() << endl;
    }

    void Thread_With_Argument(float param)
    {
        char buf[1024];
        sprintf_s(buf, 1024, "%f", param);

        // Threads begin execution immediately upon construction of the associated thread object (pending any OS scheduling delays).
        // No two std::thread objects may represent the same thread of execution; std::thread is not CopyConstructible or CopyAssignable, although it is MoveConstructible and MoveAssignable.

        thread t1(ThreadProc, 3.14, buf); // if transfer by 'buf', it might be invalid when the thread starts if this function already exits at that time
        thread t2(ThreadProc, 3.14, string(buf)); // this is a safer solution

        // teststr won't be changed because there is an internal copy transferred to t3 when constructing the thread object
        string teststr("this is a test string");
        thread t3(ThreadProc, 3.14, teststr);

        // teststr will be changed because the reference to it is transferred to t4 when constructing it
        thread t4(ThreadProc, 3.14, std::ref(teststr));

        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }

    /*
        mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.
        mutex offers exclusive, non-recursive ownership semantics:
            1. A calling thread owns a mutex from the time that it successfully calls either lock or try_lock until it calls unlock.
            2. When a thread owns a mutex, all other threads will block (for calls to lock) or receive a false return value (for try_lock) if they attempt to claim ownership of the mutex.
            3. A calling thread must not own the mutex prior to calling lock or try_lock.

        recursive_mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.
        recursive_mutex offers exclusive, recursive ownership semantics:
            1. A calling thread owns a recursive_mutex for a period of time that starts when it successfully calls either lock or try_lock.
                During this period, the thread may make additional calls to lock or try_lock.
                The period of ownership ends when the thread makes a matching number of calls to unlock.
            2. When a thread owns a recursive_mutex, all other threads will block (for calls to lock) or receive a false return value (for try_lock) if they attempt to claim ownership of the recursive_mutex.
            3. The maximum number of times that a recursive_mutex may be locked is unspecified, but after that number is reached, calls to lock will throw std::system_error and calls to try_lock will return false.

        shared_mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.
        In contrast to other mutex types which facilitate exclusive access, a shared_mutex has two levels of access: 
            1. shared - several threads can share ownership of the same mutex.
                Shared mutexes are usually used in situations when multiple readers can access the same resource at the same time without causing data races, but only one writer can do so. 
            2. exclusive - only one thread can own the mutex.
                Exclusive ownership works just like ownership of a plain mutex: 
                Only one thread may hold an exclusive lock on the mutex and only that thread can release the lock.
                No other thread may hold any type of lock on the mutex whilst that thread holds its lock.
        Shared ownership is more lax. Any number of threads may take shared ownership of a mutex at the same time. No thread may take an exclusive lock on the mutex while any thread holds a shared lock.

        The class shared_lock is a general-purpose shared mutex ownership wrapper allowing deferred locking, timed locking and transfer of lock ownership. Locking a shared_lock locks the associated shared mutex in shared mode
        (to lock it in exclusive mode, std::unique_lock can be used)
        The shared_lock class is movable, but not copyable -- it meets the requirements of MoveConstructible and MoveAssignable but not of CopyConstructible or CopyAssignable.

        The class unique_lock is a general-purpose mutex ownership wrapper allowing deferred locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with condition variables.
        The class unique_lock is movable, but not copyable. It meets the requirements of MoveConstructible and MoveAssignable but not of CopyConstructible or CopyAssignable.
    */
    void Mutex_Test()
    {
        mutex g_mutex;
        int g_value;

        thread t1([&]() {
            lock_guard<mutex> lock(g_mutex);

            // do mutual exclusive stuff

            // lock_guard will release the lock automatically
        });

        thread t2([&]() {
            lock_guard<mutex> lock(g_mutex);

            // do mutual exclusive stuff

            // lock_guard will release the lock automatically
        });

        t1.join();
        t2.join();
    }

    // shared_mutex
    void Shared_Mutex_Test()
    {
        shared_timed_mutex g_mutex; // lockable object for the below resource
        int g_value = 0;            // mutual exclusive resource

        thread rt1 = thread([&]() {
            shared_lock<shared_timed_mutex> lock(g_mutex);
            cout << "read g_value from reader thread 1:" << g_value << endl;
            this_thread::sleep_for(5s);
        });

        thread rt2 = thread([&]() {
            this_thread::sleep_for(20s);
            shared_lock<shared_timed_mutex> lock(g_mutex);
            cout << "read g_value from reader thread 2:" << g_value << endl;
        });

        thread wt1 = thread([&]() {
            this_thread::sleep_for(10s);

            // lock_guard acquires an exclusive lock on a shared mutex.
            // this operation will wait if any shared_lock or lock_guard is on hold of the mutext
            lock_guard<shared_timed_mutex> lock(g_mutex);
            g_value = 100;
            cout << "write g_value to " << g_value << " from writer thread 1:" << g_value << endl;

            // hold the exclusive lock for a long time
            this_thread::sleep_for(20s);
        });

        thread wt2 = thread([&]() {
            this_thread::sleep_for(3s);
            lock_guard<shared_timed_mutex> lock(g_mutex);
            g_value = 200;
            cout << "write g_value to " << g_value << " from writer thread 2:" << g_value << endl;
            
        });

        rt1.join();
        rt2.join();
        wt1.join();
        wt2.join();
    }

    /*
        unique_lock
    */
    void Unique_Lock_Test()
    {
        struct bank_account {
            explicit bank_account(int balance) : balance(balance) {}
            int balance;
            std::mutex m;
        };

        bank_account checkings(100);
        bank_account savings(200);

        thread t1([&]() {
            /*
            Solution 1
            */
            // lock both mutexes without deadlock
            std::lock(checkings.m, savings.m);

            // make sure both already-locked mutexes are unlocked at the end of scope
            std::lock_guard<std::mutex> lock1(checkings.m, std::adopt_lock);
            std::lock_guard<std::mutex> lock2(savings.m, std::adopt_lock);

            checkings.balance -= 100;
            savings.balance += 100;

            cout << "checkings accout balance after thread 1: " << checkings.balance << endl;
            cout << "savings accout balance after thread 1: " << savings.balance << endl;
        });

        thread t2([&]() {
            /*
            Solution 2
            */
            this_thread::sleep_for(10s);

            // don't actually take the locks yet
            std::unique_lock<std::mutex> lock1(checkings.m, std::defer_lock);
            std::unique_lock<std::mutex> lock2(savings.m, std::defer_lock);

            // lock both unique_locks without deadlock
            std::lock(lock1, lock2);

            checkings.balance += 300;
            savings.balance -= 300;

            cout << "checkings accout balance after thread 2: " << checkings.balance << endl;
            cout << "savings accout balance after thread 2: " << savings.balance << endl;

            // release the two locks
            lock1.unlock();
            lock2.unlock();
        });

        t1.join();
        t2.join();
    }

    void Unique_Lock_Move_Test()
    {
        mutex g_mutex;

        auto f = [&]() {
            unique_lock<mutex> guard(g_mutex);

            // do some stuff

            return std::move(guard);
        };

        std::unique_lock<mutex> guard(f());

        // do more stuff

        guard.unlock();
    }

    /*
        condition_variable
    */

    /*
        thread_local
    */
    thread_local unsigned int range = 1;
    mutex range_mutex;

    void IncreaseRange(const string& thread_name)
    {
        ++range; // modifying outside a lock is okay; this is a thread-local variable
        std::lock_guard<std::mutex> lock(range_mutex);
        std::cout << "Range counter for " << thread_name << ": " << range << '\n';
    }

    void ThreadLocalStorageTest()
    {
        thread a(IncreaseRange, string("a"));
        thread b(IncreaseRange, string("b"));

        {
            std::lock_guard<std::mutex> lock(range_mutex);
            std::cout << "Rage counter for main: " << range << '\n';
        }

        a.join();
        b.join();
    }
}