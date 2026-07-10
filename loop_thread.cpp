#include <iostream>
#include <thread>

using namespace std;

class loop_thread{

    public:
    loop_thread()
    {
        cout<<"loop_thread constructor"<<endl;
    }
    //Non static member function
    void printHelloThread()
    {
        cout<<"Hello thread from non static member function"<<endl;
    }
    //static member function
    static void printHelloThreadStatic()
    {
        cout<<"Hello thread from static member function"<<endl;
    } 
    //Hello thread with number
    //Non static
    void numThread(int num)
    {
        cout<<"Hello Non static Thread!! ";
        cout<<"Given number:"<<num<<endl;
    }
    //Static
    static void numThreadStatic(int num)
    {
        cout<<"Hello Static Thread, Given  number::"<<num<<endl;
    }
};

int main()
{
    loop_thread lthread;
    std::thread printHT(&loop_thread::printHelloThread, &lthread);
    std::thread printHTs(&loop_thread::printHelloThreadStatic);
    int loop_end=4;
    for(auto index=1;index<loop_end;index++) // This produce non deterministic output
    {
    std::thread nThread(&loop_thread::numThread, &lthread , index);
    std::thread nStatic(&loop_thread::numThreadStatic,index);
    nThread.join();
    nStatic.join();
    }
    printHT.join();
    printHTs.join();
   
    return 0;
}