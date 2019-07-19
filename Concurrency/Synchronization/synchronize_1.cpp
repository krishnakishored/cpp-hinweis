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


std::mutex m;
std::condition_variable cv;


std::string data;
bool ready = false;
bool processed = false;


struct global_t
{
    std::mutex mtx;
    int value = {0};
    std::condition_variable be_odd, be_even, print_it;
    bool bye = {false};

    global_t() { be_odd.notify_all(); }
} global;


void odd_generator(){

    int my_odd = 1;
    for(;;)
    {
        std::unique_lock<std::mutex> lock(global.mtx);
        if(global.bye) return;
        global.be_odd.wait(lock);
        global.value = my_odd;
        my_odd +=2;
        // global.print_it.notify_one();
        global.print_it.notify_all();

        if(my_odd>100) global.bye=true;
    }//let RAII to manage wait states and unlocking
}


void even_generator(){

    int my_even = 2;
    for(;;)
    {
        std::unique_lock<std::mutex> lock(global.mtx);
        // if(global.bye) return;
        global.be_even.wait(lock);
        global.value = my_even;
        my_even +=2;
        global.print_it.notify_all();
        if(my_even>100) global.bye=true;
    }//let RAII to manage wait states and unlocking
}

void printer()
{
    for(;;)
    {
        std::unique_lock<std::mutex> lock(global.mtx);
        if(global.bye) return;
        global.print_it.wait(lock);
        std::cout << global.value << std::endl;
        ((global.value & 1)?global.be_even:global.be_odd).notify_one();
     }
}

//https://stackoverflow.com/questions/14641134/printing-odd-and-even-number-printing-alternately-using-threads-in-c
int main_printer_2()
{
    thread odd_thread(odd_generator),even_thread(even_generator),print_thread(printer);
    odd_thread.join(),even_thread.join(),print_thread.join();

    return 0;
}


std::mutex mu;
std::condition_variable cond;
int count = 1;

void PrintOdd()
{
    for(; count < 100;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker,[](){ return (count%2 == 1); });
        // std::cout << "From Odd:    " << count << std::endl;
        std::cout<< count <<" ";
        count++;
        locker.unlock();
        cond.notify_all();
    }

}

void PrintEven()
{
    for(; count < 100;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker,[](){ return (count%2 == 0); });
        // std::cout << "From Even: " << count << std::endl;
        std::cout<< count <<" ";
        count++;
        locker.unlock();
        cond.notify_all();
    }
}



int main_PrintEvenOdd()
{
    std::thread t1(PrintOdd);
    std::thread t2(PrintEven);
    t1.join();
    t2.join();
    return 0;
}



void worker_thread()
{
    //wait untill main() sends data
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return ready; });

    //after the wait,we own the lock
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // send data back to main()
    processed = true;
    cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again
    lk.unlock();
    cv.notify_one();
}




int main_synchronizing_1()
{
    std::thread worker(worker_thread);
    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    //wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk,[]{return processed;});
    }

    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
    return 0;
}

int main(){
    main_printer_2();
    main_PrintEvenOdd();
    main_synchronizing_1();

    return 0;
}


