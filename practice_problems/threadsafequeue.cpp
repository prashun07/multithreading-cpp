#include "threadsafequeue.h"

//Test the object handling in thread
struct student{
    string name;
    string age;
    student(string name_, string age_): name(name_),age(age_){}
};

int main()
{
    // ThreadSafeQueue<int>TSQ;
    // TSQ.push(1);
    // TSQ.push(2);
    // TSQ.push(3);
    student s1("prashun","25");
    student s2("raja","20");
    student s3("shruti","23");

    ThreadSafeQueue<student>s_queue;
    s_queue.push(s1);
    s_queue.push(s2);
    s_queue.push(s3);
    while(!s_queue.is_empty())
    {
        cout<<s_queue.pop().name<<endl;
    }

    // for(;!TSQ.is_empty();)
    // {
    // cout<<TSQ.pop()<<endl;
    // }
    return 0;
}