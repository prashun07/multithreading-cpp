#include<iostream>
#include<thread>

using namespace std; 
void func(int n)
{
    cout<<"Hello thread from function, parameter passed :";
    std::cout<<n<<std::endl;
}

int main(){

    auto lambda = ([](){
        std::cout << "hello thread from lambda expression"<<std::endl;
    }); //lambda expression

    std::thread fp_thread(func, 4); //function pointer
    fp_thread.join();

    thread t(lambda);
    t.join();
    return 0;
} 
// To compile use: g++ -std=c++11 your_file.cpp -o your_file -pthread
// Compiler needs to supports C++11 or higher ( thread added in c++) 