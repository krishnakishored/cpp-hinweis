#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>

using namespace std::chrono_literals; // for operator""s
using std::cout;


// ThreadSafe Singleton - Using call_once and once_flag

class  Singleton{
private:
    static std::shared_ptr<Singleton> ptr;
    static std::once_flag ptr_once;
    int data;
    Singleton(){
        data = 0;
        cout << "created.. \n";
        }
public:
    static std::shared_ptr<Singleton> getInstance(){
        std::call_once(ptr_once,[](){
            cout<<"in call_once\n";
            // return std::shared_ptr<Singleton>(new Singleton());
            ptr = std::shared_ptr<Singleton>(new Singleton());
            });
        // When this method is invoked second time, ptr is returned (nullptr)
        cout<<"in get_instance\n";
        return ptr;
    }  
    void print(){
        cout<<"inside Singleton: "<<data++ <<"\n";
    }

};

std::shared_ptr<Singleton> Singleton::ptr = nullptr;
std::once_flag Singleton::ptr_once;

int main()
{

    // std::shared_ptr<Singleton> sptr = sptr->getInstance();
    std::shared_ptr<Singleton> S1 =  Singleton::getInstance();
    std::shared_ptr<Singleton> S2 =  Singleton::getInstance();
    if(nullptr == S2)
        cout<<  "It's the same object\n";
    S1->print();
    S2->print();

    return 0;
}