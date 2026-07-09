#include<iostream>
#include<thread>

//using namespace std;  // not encouraged to use in modern c++, use std:: instead
void func(int n)
{
    std::cout<<n<<std::endl;
}

int main(){

    std::thread t([](){
        std::cout << "hello thread"<<std::endl;
    }); //lambda expression

    std::thread fp_thread(func, 4); //function pointer
    fp_thread.join();
    t.join();
    return 0;
} 
// To compile use: g++ -std=c++11 your_file.cpp -o your_file -pthread
// Compiler needs to supports C++11 or higher ( thread added in c++) 