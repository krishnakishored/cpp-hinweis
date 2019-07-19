#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef SSTREAM
#define SSTREAM
#include <sstream>
#endif

#ifndef THREAD
#define THREAD
#include <thread>
#endif


#ifndef CONDITION_VARIABLE
#define CONDITION_VARIABLE
#include <condition_variable>
#endif


#ifndef MUTEX
#define MUTEX
#include <mutex>
#endif

using std::endl;
using std::cout;
using std::thread;

/** Thread safe cout class
  * Exemple of use:
  *    PrintThread{} << "Hello world!" << std::endl;
  */
class PrintThread: public std::ostringstream
{
public:
    PrintThread() = default;

    ~PrintThread()
    {
        std::lock_guard<std::mutex> guard(_mutexPrint);
        std::cout << this->str();
    }

private:
    static std::mutex _mutexPrint;
};
std::mutex PrintThread::_mutexPrint{};


std::mutex mu;
std::condition_variable cv;
int ready = 1;

int sender_1()
{
    for(int i=0;i<100;i++)
    {
        std::unique_lock<std::mutex> locker(mu);
        // cond.wait(locker,[](){ return (count%2 == 0); });
        cv.wait(locker,[](){return (1==ready);});
        cout<<ready<<" ";
        ready=2;//signal sender_2
        locker.unlock();
        cv.notify_all();
    }
    return 0;
}
int sender_2( )
{
     for(int i=0;i<100;i++)
    {
        std::unique_lock<std::mutex> locker(mu);
        // cond.wait(locker,[](){ return (count%2 == 0); });
        cv.wait(locker,[](){return (2==ready);});
        cout<<ready<<" ";
        ready=3;//signal sender_3
        locker.unlock();
        cv.notify_all();
    }
    return 0;
}

int sender_3( )
{
     for(int i=0;i<100;i++)
    {
        std::unique_lock<std::mutex> locker(mu);
        // cond.wait(locker,[](){ return (count%2 == 0); });
        cv.wait(locker,[](){return (3==ready);});
        cout<<ready<<endl;
        ready=1;//signal sender_1
        locker.unlock();
        cv.notify_all();
    }
    return 0;
}

// int main_printer123()
int main()
{
    PrintThread printer;
    
    thread t1(sender_1);
    thread t2(sender_2);
    thread t3(sender_3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
