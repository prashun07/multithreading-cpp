#include <iostream>
#include <mutex>
#include <thread>

int v = 1;

void critical_section(int change_v) {
    static std::mutex mtx;
    // std::lock_guard<std::mutex> lock(mtx);
    std::unique_lock<std::mutex>lock(mtx);
    // execute contention works
    v = change_v;

    // mtx will be released after leaving the scope
    std::cout << v << std::endl;
    // release the lock
    lock.unlock();

    // during this period,
    // others are allowed to acquire v

    // start another group of contention operations
    // lock again
    lock.lock();
    v += 1;
    std::cout << v << std::endl;
}
int main() {
    std::thread t1(critical_section, 4), t2(critical_section, 2);
    t1.join();
    t2.join();

    // std::cout << v << std::endl;
    return 0;
}
//https://github.com/changkun/modern-cpp-tutorial/blob/master/book/en-us/07-thread.md