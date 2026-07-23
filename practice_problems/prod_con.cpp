#include "threadsafequeue.h"
#include<iostream>
#include<vector>

using namespace std;
template<typename T>
class data_packet{
        public:
            data_packet(vector<T>&data_):data(data_){}
            vector<T> get_data()
            {
                return data;
            }
            void set_data(vector<T>&&data_)
            {
                this->data=std::move(data_);
            }
            // ~ data_packet()=default; why this will not do compiler do "move"?
        private:
            vector<T>data;
};
template<typename T>
ThreadSafeQueue<data_packet<T>>server;

template<typename T>
class sender{
    public:
        sender(data_packet<T>&_sdata):sender_data(_sdata){}
        void set_data(data_packet<T>&&_sdata)
        {
            this->sender_data = std::move(_sdata);
            // acknowledge();
        }
        void send_data()
        {
            server<T>.push(std::move(sender_data));
            acknowledge();
        }
        void acknowledge()
        {
            cout<<"Data sent successfully"<<endl;
        }   
        ~sender()=default;
    private:
        data_packet<T>sender_data;
};

template<typename T>
class client{
    public:
        client()
        {
            cout<<"client is ready"<<endl;
        }
        void receive_data()
        {
            client_data = server<T>.pop().get_data();
            cout<<"Data received successfully"<<endl;
        }
        void print_data()
        {
            cout<<"received data"<<endl;
            for(auto data: client_data)
            {
                cout<<data<<"\t";
            }
            cout<<endl;
        }
        ~client()=default;
    private:
        vector<T>client_data;
};

int main()
{
    vector<int>data ={1,2,3,4,5};
    data_packet<int>d_packet(data);

    sender<int>s_master(d_packet);
    client<int>slave;


    thread sender_thread(&sender<int>::send_data, &s_master);
    thread receiver_thread([&slave]()
    {
        slave.receive_data();
        slave.print_data();
    });

    sender_thread.join();
    receiver_thread.join();
    
    return 0;
}
//convert sender and receiver into a thread and run both at the same time