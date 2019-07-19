#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif


#ifndef SSTREAM
#define SSTREAM
#include <sstream>
#endif

#ifndef THREAD
#define THREAD
#include <thread>
#endif


#ifndef FUTURE
#define FUTURE
#include <future>
#endif


#ifndef RANDOM
#define RANDOM
#include <random>
#endif


#ifndef CHRONO
#define CHRONO
#include <chrono>
#endif

#ifndef EXCEPTION
#define EXCEPTION
#include <exception>
#endif


using std::cout;

int addNumbers(int a, int b){
    return a+b;
}

int addNumbers_Promise(int a, int b, std::promise<int>p){
    p.set_value(a+b);
    return 0;// can be different
}

int main_async_addNumbers()

{
    auto fut = std::async(addNumbers,1,2);
    cout<<"result from future: " << fut.get() << '\n';

    std::packaged_task<int(int,int)> pt(addNumbers);//packaged_task provides a little more control over the execution of a function.

    std::future<int> fut2 = pt.get_future();//Got the future but haven't executed the task yet

    std::thread t(std::move(pt),3,4);
    t.join();

    cout<<"result from packaged_task in a separate thread: " << fut2.get() << '\n';


    std::promise<int> pr;
    auto fut3 = pr.get_future();
    std::thread t2(addNumbers_Promise,5,7,std::move(pr));
    t2.join();
    cout<<"result from promise in a separate thread: "<< fut3.get()<<'\n';

    return 0;
}


using std::cout;
using std::cin;
using std::thread;

int doSomething(char c)
{
    // random-number generator (use c as seed to get different sequences)
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);
    // loop to print character after a random period of time
    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
    return c;
}

int func1()
{
    return doSomething('.');
}

int func2()
{
    return doSomething('+');
}


int main_async_basic()
{
    std::cout << "starting func1() in background" << " and func2() in foreground:" << '\n';
    std::future<int> result1(std::async(func1)); // start func1() asynchronously (now or later or never):
    int result2 = func2(); //// call func2() synchronously (here and now)
    // print result (wait for func1() to finish and add its result to result2
    int result = result1.get() + result2;
    std::cout << "\nresult of func1()+func2(): " << result << '\n';
    return 0;
}

//test for exception in the background task
void task1()
{
    // endless insertion and memory allocation
    // - will sooner or later raise an exception // - BEWARE: this is bad practice
    std::list<int> v;
    while (true)
    {
        for (int i = 0; i < 1000000; ++i)
        {
            v.push_back(i);
        }
        cout.put('.').flush();
    }
}

int main_future_exception()
{
    cout << "starting 2 tasks" << '\n';
    cout << "- task1: process endless loop of memory consumption" << '\n';
    cout << "- task2: wait for <return> and then for task1" << '\n';

    auto f1 = std::async(task1); // start task1() asynchronously (now or later or never)
    cin.get();                   // read a character (like getchar())
    cout << "\nwait for the end of task1: " << '\n';

    try{
        f1.get(); // wait for task1() to finish (raises exception if any)
    }
    catch(const std::exception& e){
        std::cerr <<"EXCEPTION: " <<e.what() <<'\n';
    }

    return 0;
}


//Waiting for two Tasks

int main_waitingForTasks()
{
    cout << "starting 2 operations asynchronously" << '\n';
    // start two loops in the background printing characters . or +
    auto f1 = std::async([] { doSomething('.'); });
    auto f2 = std::async([] { doSomething('+'); });

    // if at least one of the background tasks is running
    if (f1.wait_for(std::chrono::seconds(0)) != std::future_status::deferred ||
        f2.wait_for(std::chrono::seconds(0)) != std::future_status::deferred)
    {
        // poll until at least one of the loops finished
        while (f1.wait_for(std::chrono::seconds(0)) != std::future_status::ready &&
               f2.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
        {                              //...;
            std::this_thread::yield(); // hint to reschedule to the next thread
        }
    }
    cout.put('\n').flush();
    // wait for all loops to be finished and process any exception
    try
    {
        f1.get();
        f2.get();
    }
    catch (const std::exception &e)
    {
        cout << "\nEXCEPTION: " << e.what() << '\n';
    }
    cout << "\ndone" << '\n';
    return 0;
}



//shared_future

int queryNumber()
{
    // read number
    cout << "read number: ";
    int num;
    cin >> num;
    // throw exception if none
    if (!cin)
    {
        throw std::runtime_error("no number read");
    }
    return num;
}

void doSomething_2(char c, std::shared_future<int> f)
{
    try
    {
        // wait for number of characters to print
        int num = f.get(); // get result of queryNumber()
        for (int i = 0; i < num; ++i)
        {
           std::this_thread::sleep_for(std::chrono::milliseconds(100));
            cout.put(c).flush();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION in thread " << std::this_thread::get_id() << " : " << e.what() << '\n';
    }
}

int main_sharedFutures()
{
    try
    {
        // start one thread to query a number
        std::shared_future<int> f = std::async(queryNumber);
        // start three threads each processing this number in a loop
        auto f1 = std::async( doSomething_2, '.', f);
        auto f2 = std::async(std::launch::async, doSomething_2, '+', f);
        auto f3 = std::async(std::launch::async, doSomething_2, '*', f);
    

        // wait for all loops to be finished
        f1.get();
        f2.get();
        f3.get();
    }
    catch (const std::exception &e)
    {
        cout << "\nEXCEPTION: " << e.what() << '\n';
    }
    cout << "\ndone" << '\n';
    return 0;
}


//Low-level Interface - threads

void doSomething_3(int num, char c)
{
    try
    {
        // random-number generator (use c as seed to get different sequences) 
        std::default_random_engine dre(42*c); 
        std::uniform_int_distribution<int> id(10,1000);
        for (int i = 0; i < num; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
            cout.put(c).flush();
            
        }
    }
    // make sure no exception leaves the thread and terminates the program
    catch (const std::exception &e)
    {
        std::cerr << "THREAD-EXCEPTION (thread "
             << std::this_thread::get_id() << "): " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "THREAD-EXCEPTION (thread "
             << std::this_thread::get_id() << ")" << '\n';
    }
}

int main_threads()
{

    try
    {
        thread t1(doSomething_3, 5,'.');
        cout << "- started fg thread " << t1.get_id() << '\n';

        // print other characters in other background threads
        for (int i = 0; i < 5; ++i)
        {
            thread t(doSomething_3, 10, 'a' + i); // print 10 chars in separate thread
            cout << "- detach started bg thread " << t.get_id() << '\n';
            t.detach(); // detach thread into the background
        }
        cin.get();
        cout << "-join fg thread " << t1.get_id() << '\n';
        t1.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << '\n';
    }
    return 0;
}


int main()
{
    main_async_addNumbers();
    main_async_basic();
    main_future_exception();
    main_sharedFutures();
    main_threads();
    main_waitingForTasks();
    
    return 0;
}