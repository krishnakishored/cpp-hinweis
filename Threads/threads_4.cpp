// ---------- C++ TUTORIAL 16 ----------

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

// ---------- hardware_concurrency -----------
using std::cout;
using std::string;

std::mutex cout_mutex;

enum JoinOrDetach {join, detach};

// RAAI Thread
class RThread{
    std::thread thread;
    JoinOrDetach joinOrDetach;
public:
    RThread(std::thread&& thread,JoinOrDetach joinOrDetach)
        : thread(std::move(thread)),joinOrDetach(joinOrDetach){}
    RThread(const RThread&) = delete;
    RThread(RThread&&) = delete;

    ~RThread(){
        if(thread.joinable()){
            if(JoinOrDetach::join == joinOrDetach){
                thread.join();
            }
            else{
                thread.detach();
            }
        }
    }
};


// --- Thread Argument GotCha

class Person
{
private:
    /* data */
    int age;
public:
    Person(int age): age(age){}
    int getAge() const {return age;}
    void growOlder() {age++;}
    ~Person();
};
Person::~Person(){}

void grow(Person& person){
    cout<< "Increasing age...\n";
    person.growOlder();
}

int main_ThreadArgumentRef()
{
    Person sam(2);
    // std::thread thread1(grow,sam); // 2  //   ??? compilation_err: attempt to use a deleted function
    std::thread thread1(grow,std::ref(sam)); // 3s
    thread1.join();
    cout<< sam.getAge() << "\n";
    return 0;
}



void printThreadInfo(string msg)
{
    cout << "In " << msg << " " << std::this_thread::get_id() << "\n";
}

void printThreadInfoWithMutex(string msg)
{
    cout_mutex.lock();
    cout << "In " << msg << " " << std::this_thread::get_id() << "\n";   
    cout_mutex.unlock();
}

// () operator overloaded
class Sample{
    public:
        void operator()(){cout << std::this_thread::get_id() << " howdy\n";} 
};

int main_usingFunction()
{
    cout<< "hardware_concurrency: " <<std::thread::hardware_concurrency()<< "\n";
    // printThreadInfo("main"); # jumbled o/p;
    printThreadInfoWithMutex("main");
    std::thread thread1 (printThreadInfoWithMutex,"thread1");
    std::thread thread2 (printThreadInfoWithMutex,"thread2");
    cout<<thread1.joinable() << "\n"; // 1
    cout<<thread2.joinable() << "\n"; // 1
    thread1.join();
    thread2.detach();
    cout<<thread1.joinable() << "\n"; // 0
    cout<<thread2.joinable() << "\n"; // 0
    return 0;
}

int main_usingClassObject()
{
    Sample sample;
    std::thread thread1 (sample);
    std::thread thread2 (sample);
    thread1.join();
    thread2.join();
    return 0;
}

int main_RAIIThread(){
    RThread thread(std::thread(printThreadInfoWithMutex,"th1"),JoinOrDetach::join);
    //troublesomeFunction(); //that throws exception
    return 0;
}

int main(int argc, char const *argv[])
{
    // main_usingFunction();
    // main_RAIIThread();
    // main_usingClassObject();
    main_ThreadArgumentRef();
    return 0;
}