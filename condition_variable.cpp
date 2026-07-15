#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>

using namespace std;

mutex m_mutex;
condition_variable m_cv;
bool data_ready = false;

void producer()
{
    lock_guard<mutex>lock(m_mutex);
    data_ready =true;
    cout<<"Data produced"<<endl;
    m_cv.notify_one();
}
void consumer()
{
    unique_lock<mutex> lock(m_mutex);
    m_cv.wait(lock , []{ return data_ready;});
    cout<<"Data consumed"<<endl;
}
void printHello()
{
    cout<<"Hello , World!"<<endl;
}
int main()
{
    thread t_consumer(consumer);
    thread t_producer(producer);
    thread t_hello(printHello);
    t_consumer.join();
    t_producer.join();
    t_hello.join();
    return 0;
}