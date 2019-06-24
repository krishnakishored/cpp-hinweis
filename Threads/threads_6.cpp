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
    Singleton(){cout << "created.. \n";}
public:
    static std::shared_ptr<Singleton> getInstance(){
        std::call_once(ptr_once,[](){return std::shared_ptr<Singleton>(new Singleton());});
    
        return ptr;
    }  
};


int main()
{

    // std::shared_ptr<Singleton> sptr = sptr->getInstance();


    return 0;
}