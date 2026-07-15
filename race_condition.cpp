#include<iostream>
#include<thread>

using namespace std;

int counter=0;
int times=100000;

void count_()
{
    for(int i=0;i<times;i++)
    {
        ++counter;   // shared data accessed by both thread simulatenously 
    }
}

int main()
{
    thread t1(count_);
    thread t2(count_);
    t1.join();
    t2.join();
    cout<<counter<<endl;

    return 0;
}