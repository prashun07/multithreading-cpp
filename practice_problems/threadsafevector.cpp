#include<iostream>
#include<vector>
#include<mutex>
#include<thread>

using namespace std;
template<typename T>
class ThreadSafeVector{
    public:
        void push_back(T &&data)
        {   
            unique_lock<mutex>u_lock(t_mtx);
            t_vector.push_back(std::move(data));
            t_cv.notify_one();
        }
        T pop_back()
        {
            unique_lock<mutex> u_lock(t_mtx);

            if (t_vector.empty())
            {
                throw runtime_error("Vector is empty");
            }

            T val = t_vector.back();
            t_vector.pop_back();
            return val;
        }
    private:
        vector<T>t_vector;
        std::mutex t_mtx;
        std::condition_variable t_cv;
};

int main()
{
    ThreadSafeVector<int>ts_vector;

    thread push_thread([&ts_vector]
    {
        ts_vector.push_back(1);
        ts_vector.push_back(2);
        ts_vector.push_back(3);
        ts_vector.push_back(4); 
        ts_vector.push_back(5);
        ts_vector.push_back(6);  

    });
    thread pop_thread([&ts_vector]
    {
        cout<<ts_vector.pop_back()<<endl;
    });
    // cout<<ts_vector.pop_back()<<endl;
    push_thread.join();
    pop_thread.join();

    return 0;
}

//it still have a problem, can you find it?