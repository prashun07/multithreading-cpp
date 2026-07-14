#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m_mutex;

int shared_data=0;
// void increment_data(int num){
//     unique_lock<mutex>lock(m_mutex); //create unique lock object 
//     // lock.lock(); //alread locked above
//     shared_data+=num;
//     cout<<"shared_data::"<<shared_data<<",number::"<<num<<endl;
//     // lock.unlock(); // no need to write it again as handled automatically
// }

// Create a unique_lock without acquiring the mutex.
// The mutex will be locked manually later.
void increment_data(int num){
    unique_lock<mutex>lock(m_mutex, std::defer_lock); //create unique lock object 
    lock.lock(); // manual lock required
    shared_data+=num;
    cout<<"shared_data::"<<shared_data<<",number::"<<num<<endl;
    // lock.unlock(); // manual unlock is not required , because it will automatically unlock when goes out of scope
    // You can use unlock only when you want to unlock mutex before the end of scope
}
int main()
{
    thread t1(increment_data,10);
    thread t2(increment_data,20);
    t1.join();
    t2.join();
    cout<<"Value of shared value::"<<shared_data<<endl;
    return 0;
}
