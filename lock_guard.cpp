#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m_mutex;

int shared_data=0;
void increment_data(int num){
    lock_guard<mutex>lock(m_mutex); //create lockgurad object 
    shared_data+=num;
    cout<<"shared_data::"<<shared_data<<",number::"<<num<<endl;
    //unlock automatically
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
