#include <iostream>
#include <thread>

using namespace std;

class helloClassThread{

    public:
    helloClassThread()
    {
        cout<<"helloClassThread constructor"<<endl;
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
    helloClassThread hct;
    std::thread pht(&helloClassThread::printHelloThread, &hct);
    std::thread phts(&helloClassThread::printHelloThreadStatic);
    std::thread nThread(&helloClassThread::numThread, &hct , 1);
    std::thread nStatic(&helloClassThread::numThreadStatic,2);
    pht.join();
    phts.join();
    nThread.join();
    nStatic.join();
    return 0;
}