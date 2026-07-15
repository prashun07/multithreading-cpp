#include<iostream>
#include<thread>
#include<future>
#include<stdexcept>

using namespace std;

void func(promise<int>&&do_promise) //for move()
// void func(promise<int>&do_promise) //for ref()
{
    int ans=100;
    do_promise.set_value(ans);
}


int main()
{
    promise<int>do_promise; //create a promise object
    future<int>do_future = do_promise.get_future(); //create future object from promise

    // thread t1(func, ref(do_promise));
    thread t1(func, std::move(do_promise));
    
    int result = do_future.get();
    cout<<"Result::"<<result<<endl;

    t1.join();
    return 0;
}
//ref(dom_promise) is actually std::ref(do_promise)
/*
Read [](file:///Users/prashunjha/Documents/multithreading-cpp/promise_future.cpp)

In that line, `ref(do_promise)` is `std::ref(do_promise)`.

`std::thread` by default copies (or moves) the arguments you pass to the new thread. But your thread function `func` takes `promise<int>&`, i.e. a reference, and `promise` is not copyable. So you use `std::ref` to tell `std::thread` to store/pass a reference wrapper instead of trying to copy the `promise` object.

So:

- `thread t1(func, ref(do_promise));`

means: start thread `t1`, calling `func` with `do_promise` passed by reference.

Without `ref`, the thread constructor would try to copy `do_promise`, which would fail for `std::promise`.
*/