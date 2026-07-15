# Multithreading in C++
Multithreading is a technique where a program is divided into smaller units of execution called threads. 
Threads are lightweight processes that share the same memory space and can perform tasks independently, enhancing the program's efficiency and responsiveness.
- main() is the main thread of execution containing the sub threads.
- Each thread runs independently but shares resources like memory. 
- Helps in improving performance by utilizing multiple cpu cores efficienlty. 
- #include<thread> header file. 
> thread thread_name(callable);
 -> thread_name : it is object of thread class. 
 -> callable : it is a callable object like function pointer,function object. 

Example:
```cpp
#include<iostream>
#include<thread>

void printHello()
{
    std::cout << "hello thread"<<std::endl;
}
int main(){
    std::thread t(printHello);
    t.join(); 
    return 0;
} 
```
#Output
> hello thread

# Callable
- A callable is an object that is passed to a thread and executed in parallel.

Callable can be divided into:
- Function Pointer
```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to be run 
// by the thread
void func(int n) {
    cout << n;
}

int main() {
    
    // Create a thread that runs 
    // the function func
    thread t(func, 4);
    
    // Wait for thread to finish
    t.join();
    return 0;
}
```

- Function Object
```cpp
#include <iostream>
#include <thread>
using namespace std;

// Define a function object (functor)
class SumFunctor {
public:
    int n;
    SumFunctor(int a) : n(a) {}

    // Overload the operator() to 
    // make it callable
    void operator()() const {
        cout << n;
    }
};

int main() {

    // Create a thread using 
    // the functor object
    thread t(SumFunctor(3));

    // Wait for the thread to 
    // complete
    t.join();
    return 0;
}
```

- Lambda Expression
```cpp
#include <iostream>
#include <thread>

using namespace std;

int main() {
    int n = 3;
    
    // Create a thread that runs 
    // a lambda expression
    thread t([](int n){
        cout << n;
    }, n);

    // Wait for the thread to complete
    t.join();
    return 0;
}
```

- Non static or static member function
```cpp
#include <iostream>
#include <thread>

using namespace std;

class MyClass {
public:
    // Non-static member function
    void f1(int num) {
        cout << num << endl;
    }

    // Static member function that takes one parameter
    static void f2(int num) {
        cout << num;
    }
};

int main() {
    
    // Member functions 
    // requires an object
    MyClass obj;
    
    // Passing object and parameter
    thread t1(&MyClass::f1, &obj, 3);
    
    t1.join(); 
    
    // Static member function can 
    // be called without an object
    thread t2(&MyClass::f2, 7);
    
    // Wait for the thread to finish
    t2.join();  

    return 0;
}
```
**Thread specific functions**

```cpp
#include <thread>
#include <chrono>

// These can be used within a thread

// Get thread ID of thread
std::this_thread::get_id();

// Give priority to other threads, pause execution
std::this_thread::yield();

// Sleep for some amount of time
std::this_thread::sleep_for(std::chrono::seconds(1));

// Sleep until some time
std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now()
                                                   + std::chrono::seconds(10);
std::this_thread::sleep_until(time_point);
```
---

# Thread Management
- `join()`: main() waits for the thread to finish execution. if you don't write join() thread will be lost as main() will not stop for it.
- `detach()`: Allows the thread to run independently from the main thread. After detaching, the thread cannot be joined.

Example for detach():
```cpp
#include <iostream>
#include <thread>
using namespace std;
void printHello()
{
    cout<<"Hello thread"<<endl;
}
int main()
{
    thread t1(printHello);
    t1.join();
    cout<<"Hello, Prashun "<<endl;
    t1.detach(); // Detach the thread
    return 0;
}
```
**OUTPUT:**

This program will compile and run, but at the end, it will throw the message:

    terminate called without an active exception

This happens because the thread is detached and `main()` is exiting before the thread has finished executing.

When `join()` is used, it consumes the thread and `joinable` becomes false. So, `detach()` will not have any thread to detach, and it will throw an error.

You can use `detach()` or `join()`, but not both.

Note : Joinable is a member function of the thread class that checks if the thread is joinable or not. A thread is joinable if it has been started and has not yet been joined or detached. If a thread is joinable, it means that it can be joined using the `join()` function, which will block the calling thread until the thread being joined has completed its execution.

---




**A common interview question:**

What if we remove both `join()` and `detach()`?

```cpp
thread t1(printHello);
return 0;
```

When `main()` ends, the destructor of `std::thread` is called. Since the thread is still joinable, the destructor calls `std::terminate()`. Every `std::thread` must be either joined or detached before it is destroyed.





---

- `sleep_for`: Suspends the thread for a specified duration.
```cpp
std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for 100 milliseconds
```

- `sleep_until`: Suspends the thread until a specified time point.
```cpp
std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1)); // Sleep until 1 second from now
``` 
---

# Problem with multithreading:

- Deadlock: A situation where two or more threads are blocked forever, waiting for each other to release resources.
- Race Condition: A situation where the outcome of a program depends on the sequence or timing of uncontrollable events. A race condition occurs when two or more threads access shared resources at the same time, and at least one of them modifies the resource. Since the threads are competing to read and write the data, the final result depends on the order in which the threads execute, leading to unpredictable or incorrect results.
- Starvation: A situation where a thread is perpetually denied access to resources it needs for execution, often due to other threads continuously acquiring those resources.
- Non-deterministic behavior: The behavior of a multithreaded program can be unpredictable due to the non-deterministic nature of thread scheduling, leading to different outcomes in different runs of the same program.


# Context Switching:
Context switching is the process of storing the state of a thread or process so that it can be resumed later. It allows multiple threads to share the same CPU core by switching between them, giving the illusion of parallel execution.

# Thread Synchronization: (solution to the problem of multithreading)

# Mutex
Mutex (short for mutual exclusion) is a synchronization primitive that allows only one thread to access a shared resource at a time.
- std::mutex: A standard mutex provided by the C++ Standard Library.
- <mutex> header file.
- Mutexes are used to protect shared data from being accessed by multiple threads simultaneously, preventing data races and ensuring thread safety.
- They provide a way to lock and unlock access to shared resources, allowing for safe concurrent execution of threads.

<img src="https://media.geeksforgeeks.org/wp-content/uploads/20231111130347/mutex-locks.webp" alt="Mutex Locks" width="600">

```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx; // Global mutex
int shared_data = 0; // Shared resource
void print(int id) {
    mtx.lock(); // Lock the mutex
    shared_data += id; // Access shared resource
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate some work
    cout << "Shared data: " << shared_data << endl;
    cout << "Thread " << id << " is running." << endl;
    mtx.unlock(); // Unlock the mutex
}
int main() {
    thread t1(print, 1);
    thread t2(print, 2);
    
    t1.join();
    t2.join();
    
    cout << "Final shared data: " << shared_data << endl; // Output final value of shared_data
    return 0;
}
```
# Output
```
Shared data: 1
Thread 1 is running.
Shared data: 3
Thread 2 is running.
Final shared data: 3
```
* Brainstorming: can we decide which thread will run first or can we control the order of execution of threads? 
- No, we cannot control the order of execution of threads. it is done by the operating system's scheduler but we can make some thread wait for other thread to finish execution using condition variable(discussed later).
- The main job of mutex is to protect shared resource from being accessed by multiple threads at the same time. it does not control the order of execution of threads.

**Difference between lock_guard and unique_lock(Most Important interview question)**
# lock_guard
- Simple mutex wrapper that locks a mutex during construction and automatically unlocks it during destruction(when object goes out of scope).
- designed for minimal overhead and exception safety.
- simple to use
- RAII (Resource Acquisition Is Initialization) principle: ensures that resources are properly released when they are no longer needed, even in the presence of exceptions.
- Does not allow manual unlocking of the mutex.
```cpp
std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
// Access shared resource
// Mutex will be automatically unlocked when lock goes out of scope
```
Example : [lock_guard.cpp](lock_guard.cpp)

# unique_lock
- Flexible mutex wrapper that supports manual locking and unlocking, deferred locking, timed locking, and ownership transfer.
- Suitable for situations where more control over the locking mechanism is needed.
- Ownership transfer: it allows transferring ownership of the lock from one `unique_lock` object to another, enabling more complex locking strategies and resource management.
- Used when we need to defer lock or conditionally lock a mutex.
- When we require timed locking or unlocking of a mutex.
- When transfer of ownership of lock if required between different scopes or threads.

```cpp
std::mutex mtx; // Global mutex
std::unique_lock<std::mutex>lock(mtx); // Lock the mutex
// Access shared resource
// lock() and unlock() will only be used with defer lock else it will throw an error.
// because unique_lock automatically locks and unlocks the mutex like lockguard.
// unlock will be called when unique_lock goes out of scope automatically.
// if you want to unlock mutex before the end of scope, you can use unlock() method of unique_lock.
lock.unlock(); // Manually unlock the mutex
lock.lock(); // Manually lock the mutex again
```
Example : [unique_lock.cpp](unique_lock.cpp)
- defer lock : std::defer_lock is a tag to tell a lock wrapper to just wrap the mutex without locking it. the thread will be manually locked later.
- Overhead: lockguard has less overhead because it only stores a reference or pointer to the mutex it is managing, while unique_lock stores additional state information to support its advanced features. This extra state information can lead to slightly higher memory usage and performance overhead compared to lock_guard.

*Brainstorming:* Can we use lock_guard and unique_lock together in the same program?
- Yes, we can use lock_guard and unique_lock together in the same program. However, we should be careful to avoid deadlocks and ensure that the locking order is consistent. It is generally recommended to use one type of lock consistently within a given scope or function to maintain clarity and avoid confusion.

*Brainstorming:* Mutex will lock/unlock the resources but how will you synchronize threads? How will you decide which thread will run first? How will you make one thread wait for another thread to finish execution?

# Condition Variable
- Condition variables are synchronization primitives that allow threads to wait for certain conditions to be met before proceeding with their execution. They are used in conjunction with mutexes to provide a way for threads to communicate and synchronize their actions.
- Used to coordinate communication between threads and avoid unnecessary busy-waiting, which can lead to inefficient CPU usage.
- Defined by <condition_variable> header file.
- Allow one thread to wait while another thread signals that a task or resource is ready.
- commonly used in producer-consumer, sender-receiver, and task scheduling scenarious.


```cpp
std::condition_variable variable_name; // Declare a condition variable
```
- wait() : Tells the current thread to wait unil the condition variable is notified.
- wait_for(): Suspends the current thread for a specified relative time duration or until the condition variable is notified, whichever comes first.
- wait_until(): Similar to wait_for(), but here the time duration is definied as the absolute time.
- notify_one(): Wakes up one thread that is waiting on the condition variable. The thread selection is random.
- notify_all(): Wakes up all threads that are waiting on the condition variable.

Example : [condition_variable.cpp](condition_variable.cpp)

**Common Issue with Condition Variables**
- Spurious Wakeups: A waiting thread may wake up without a notification.
- Lost wakeup: A thread may miss a notification if it has not started waiting yet.
- Incorrect predicate usage: Failing to check a conditon after waking up can lead to incorrect behavior.
- Deadlocks: Incorrect locking and waiting logic can cause threads to block indefinitely, leading to deadlocks.


* Brainstorming: How will you avoid spurious wakeups and lost wakeups?
- To avoid spurious wakeups, always use a predicate (a condition check) in a loop when waiting on a condition variable. This ensures that the thread only proceeds when the desired condition is actually met, even if it wakes up spuriously.
- To avoid lost wakeups, ensure that the condition variable is notified after the waiting thread has started waiting. This can be achieved by using proper synchronization mechanisms, such as mutexes, to protect the shared state and ensure that the notification is sent after the waiting thread has acquired the lock and is ready to wait.   

# Atomic 
- Provides a way to perform operations on shared data without the need for explicit locking mechanisms like mutexes.
- Defined in <atomic> header file.
- prevent data races by ensuring that operation on shared variables are performed atomically.
- Provides lock free synchronization, which can lead to better performance in certain scenarios.
- Enables safe communication between multiple threads without explicti mutexes.

**Note: Do check common atomic operations and flags in the atomic header file.** [atomic operations](https://www.geeksforgeeks.org/cpp/cpp-11-atomic-header/)
