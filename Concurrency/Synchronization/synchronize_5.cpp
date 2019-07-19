// Retrieving Results from a Thread
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef THREAD
#define THREAD
#include <thread>
#endif

#ifndef FUTURE
#define FUTURE
#include <future>
#endif

#ifndef CHRONO
#define CHRONO
#include <chrono>
#endif

using std::cout;
using std::endl;
using std::future;
using std::promise;
using std::thread;

using std::async;
using namespace std::chrono;

//C++ provides promise and future objects that can be used to transfer data between threads.
using FactorialPromise = promise<long long>;

long long Factorial(unsigned int value)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return value == 1 ? 1 : value * Factorial(value - 1);
}

int main_PromiseInSameThread()
{
    FactorialPromise promise;
    future<long long> taskFuture{promise.get_future()};
    promise.set_value(Factorial(3));
    cout << "Factorial result was " << taskFuture.get() << endl;
    return 0;
}
//Moving a promise to a Second Thread
void ThreadTask(FactorialPromise &&threadPromise, unsigned int value) //error: without && attempt to use a deleted function
{
    threadPromise.set_value(Factorial(value));
}

int main_PromiseFromSeparateThread()
{

    FactorialPromise promise;
    future<long long> taskFuture{promise.get_future()};
    thread taskThread{ThreadTask, std::move(promise), 3};
    while (taskFuture.wait_until(system_clock::now() + seconds(1)) != std::future_status::ready)
    {
        cout << "Still Waiting!" << endl;
    }
    cout << "Factorial result was " << taskFuture.get() << endl;
    taskThread.join();
    return 0;
}
/*
The packaged_task template, which removes the need for you to create your own thread function. 
A packaged_task constructor takes the function to call as a parameter; 
a corresponding thread constructor that can take a packaged_task. 
A thread constructed in this way can automatically call the method in the supplied packaged_task and call set_value on its internal promise.
*/
int main_packagedTask()
{
    // ThreadTask function is no longer needed when using a packaged_task.
    // The packaged_task constructor takes a function pointer as a parameter.
    // The packaged_task template also supplies a get_future method and is passed to a thread using move semantics.
    std::packaged_task<long long(unsigned int)> task{Factorial};
    future<long long> taskFuture{task.get_future()};
    thread taskThread{std::move(task), 3};
    while (taskFuture.wait_until(system_clock::now() + seconds(1)) != std::future_status::ready)
    {
        cout << "Still Waiting!" << endl;
    }
    cout << "Factorial result was " << taskFuture.get() << endl;
    taskThread.join();
    return 0;
}
//The async function returns a future that can be used to get the value returned from the function supplied to async.
//There is no guarantee, however, that the function will be called on another thread.
//All async guarantees is that the function will be called sometime between where you create the object and when you call get on the future.
int main_async()
{

    cout << "main thread: " << std::this_thread::get_id() << endl;
    auto taskFuture1 = async(Factorial, 3);
    cout << "Factorial result was (taskFuture1) " << taskFuture1.get() << endl;
    auto taskFuture2 = async(std::launch::async, Factorial, 3);
    cout << "Factorial result was (taskFuture2) " << taskFuture2.get() << endl;
    auto taskFuture3 = async(std::launch::deferred, Factorial, 3);
    cout << "Factorial result was (taskFuture3) " << taskFuture3.get() << endl;
    auto taskFuture4 = async(std::launch::async | std::launch::deferred, Factorial, 3);
    cout << "Factorial result was (taskFuture4) " << taskFuture4.get() << endl;
    return 0;
}


int main(){
    main_async();
    main_packagedTask();
    main_PromiseFromSeparateThread();
    main_PromiseInSameThread();
    return 0;
}