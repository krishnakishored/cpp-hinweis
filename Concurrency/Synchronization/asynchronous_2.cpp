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

#ifndef FUTURE
#define FUTURE
#include <future>
#endif

#ifndef THREAD
#define THREAD
#include <thread>
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

#ifndef STDEXCEPT
#define STDEXCEPT
#include <stdexcept>
#endif


#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional>
#endif

#ifndef UTILITY
#define UTILITY
#include <utility>
#endif


using std::cout;
using std::cin;
using std::thread;

void doSomething(std::promise<std::string> &p)
{
    try
    {
        // read character and throw exceptiopn if ’x’
        std::cout << "read char ('x' for exception): ";
        char c = std::cin.get();
        if (c == 'x')
        {
            throw std::runtime_error(std::string("char ") + c + " read");
        }
    }
    catch (...)
    {
        p.set_exception(std::current_exception()); //store exception
    }
}

// int main_promises()
int main()
{
    try {
// start thread using a promise to store the outcome
        std::promise<std::string> p; 
        std::thread t(doSomething,std::ref(p));
        t.detach();

        // create a future to process the outcome
        std::future<std::string> f(p.get_future());

        //process the outcome
        cout<<"result: "<<f.get() <<'\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "EXCEPTION " << std::endl;
    }

    return 0;
}
