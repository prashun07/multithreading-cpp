#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex m_mutex;
int v = 1;

void critical_section(int change_v) {
    m_mutex.lock();
    v += change_v;
    // v += 1;
    cout<<"v:"<<v<<",change_v:"<<change_v<<endl;
    m_mutex.unlock();
}
int main() {
    std::thread t1(critical_section, 4);
    std::thread t2(critical_section, 2);
    t1.join();
    t2.join();

    // std::this_thread::sleep_for(chrono::milliseconds(100));
    std::cout << v << std::endl; // What will be final output without mutex ?
    return 0;
}
//https://github.com/changkun/modern-cpp-tutorial/blob/master/book/en-us/07-thread.md