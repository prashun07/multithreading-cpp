#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int global_var=0;
int times=10000000;
std::mutex m_mutex;
std::mutex n_mutex;

void critical_section1()
{
    m_mutex.lock();
    cout<<"locking mutex n in critical section 1"<<endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    n_mutex.lock();
    for(int i=0;i<times;i++)
    {
        global_var++;
    }
    m_mutex.unlock();
    n_mutex.unlock();
}
void critical_section2()
{
    n_mutex.lock();
    cout<<"locking mutex m in critical section 2"<<endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    m_mutex.lock();
    for(int i=0;i<times;i++)
    {
        global_var++;
    }
    n_mutex.unlock();
    m_mutex.unlock();
}
int main()
{
    thread t1(critical_section1);
    thread t2(critical_section2);
    
    t1.join();
    t2.join();
    cout<<global_var<<endl;
    return 0;
}

// use lldb ./deadlock in mac to debug
// select thread 1
// bt to print call stack
// compare with other thread
