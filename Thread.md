# Multithreading in C++
Multithreading is a technique where a program is divided into smaller units of execution called threads. 
Threads are lightweight processes that share the same memory space and can perform tasks independently, enhancing the program's efficiency and responsiveness.
- Each thread runs independently but shares resources like memory. 
- Helps in improving performance by utilizing multiple cpu cores efficienlty. 
- <thread> header file. 
> thread thread_name(callable);
 -> thread_name : it is object of thread class. 
 -> callable : it is a callable object like function pointer,function object. 

```cpp
#include<iostream>
#include<thread>
int main(){

    std::thread t([](){
        std::cout << "hello thread"<<std::endl;
    }); //lambda expression as callable

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

# Thread Management
- `join()`: Waits for the thread to finish execution.
- `detach()`: Allows the thread to run independently from the main thread. After detaching, the thread cannot be joined.
- `mutex`: A synchronization primitive that prevents multiple threads from accessing shared resources simultaneously.
- `lock_guard`: A RAII-style mechanism for managing mutex locks. It locks the mutex when created and unlocks it when destroyed.
- `sleep_for`: Suspends the thread for a specified duration.
- `sleep_until`: Suspends the thread until a specified time point.

Problem with multithreading:
- Deadlock: A situation where two or more threads are blocked forever, waiting for each other to release resources.
- Race Condition: A situation where the outcome of a program depends on the sequence or timing of uncontrollable events. A race condition occurs when two or more threads access shared resources at the same time, and at least one of them modifies the resource. Since the threads are competing to read and write the data, the final result depends on the order in which the threads execute, leading to unpredictable or incorrect results.
- Starvation: A situation where a thread is perpetually denied access to resources it needs for execution, often due to other threads continuously acquiring those resources.


# Thread Synchronization:
A race condition occurs when two or more threads access shared resources at the same time, and at least one of them modifies the resource. Since the threads are competing to read and write the data, the final result depends on the order in which the threads execute, leading to unpredictable or incorrect results.

# Context Switching:
Context switching is the process of storing the state of a thread or process so that it can be resumed later. It allows multiple threads to share the same CPU core by switching between them, giving the illusion of parallel execution.

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