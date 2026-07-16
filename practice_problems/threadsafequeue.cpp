#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>
using namespace std;

// Interview questions for a 4-year experienced candidate:
// 1. How would you implement a thread-safe queue in C++? What synchronization primitives would you use and why?
// 2. What is the difference between std::mutex, std::lock_guard, and std::unique_lock?
// 3. Why is it important to use a condition variable with a predicate in wait()?
// 4. What are spurious wakeups and how do you handle them?
// 5. How would you add a timeout-enabled pop to this queue?
// 6. In a producer-consumer scenario, how do you avoid busy waiting?
// 7. What is the difference between notify_one() and notify_all()?
// 8. How would you safely shut down the queue so consumers can exit when no more work is coming?
// 9. When would you use a lock-free queue instead of a mutex-based one?
// 10. What thread-safety guarantees does this implementation provide, and what limitations remain?
// 11. How would you extend this queue to support multiple producers and multiple consumers?
// 12. How does std::move affect push() when accepting the queue element?
// 13. What are potential problems if you use this queue with non-copyable or non-movable types?
// 14. Explain the difference between data race and race condition.
// 15. How do you debug deadlocks and priority inversion in concurrent code?

template<typename T>
class ThreadSafeQueue{
    public:
        void push(T data);
        T pop();
        bool is_empty();
    private:
        queue<T> t_queue;
        mutex t_mutex;
        condition_variable t_cv;
};

template<typename T>
void ThreadSafeQueue<T>::push(T data)
{
    unique_lock<mutex> lock(t_mutex);
    t_queue.push(data);
    t_cv.notify_all();
}

template<typename T>
T ThreadSafeQueue<T>::pop()
{
    unique_lock<mutex> lock(t_mutex);
    t_cv.wait(lock, [this]() { return !is_empty(); });
    auto data = t_queue.front();
    t_queue.pop();
    return data;
}


template<typename T>
bool ThreadSafeQueue<T>::is_empty()
{
    return t_queue.empty();
}

int main()
{
    ThreadSafeQueue<int>TSQ;
    TSQ.push(1);
    TSQ.push(2);
    TSQ.push(3);
    for(;!TSQ.is_empty();)
    {
    cout<<TSQ.pop()<<endl;
    }
    return 0;
}