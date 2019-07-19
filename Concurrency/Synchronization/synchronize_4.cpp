// Mutexes, condition_variables
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef THREAD
#define THREAD
#include <thread>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STACK
#define STACK
#include <stack>
#endif

#ifndef CONDITION_VARIABLE
#define CONDITION_VARIABLESTACK
#include <condition_variable>
#endif

#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional>
#endif

using std::condition_variable;
using std::cout;
using std::endl;
using std::lock_guard;
using std::mutex;
using std::reference_wrapper;
using std::stack;

using std::thread;
using std::unique_lock;
using std::vector;
using namespace std::literals;
using std::function;

//Accessing Shared Objects Using Mutual Exclusion
class MyManagedObject
{
  private:
    static const unsigned int MAX_OBJECTS{8};
    using MyManagedObjectCollection = vector<MyManagedObject>;
    static MyManagedObjectCollection s_ManagedObjects;
    static stack<unsigned int> s_FreeList;
    static mutex s_Mutex;
    unsigned int m_Value{0xFFFFFFFF};

  public:
    MyManagedObject() = default;
    MyManagedObject(unsigned int value)
        : m_Value{value}
    {
    }
    void *operator new(size_t numBytes)
    {
        void *objectMemory{};
        // s_Mutex.lock();

        //lock_guard automatically locks a mutex on construction & frees the mutex on destrucion
        lock_guard<mutex> lock{s_Mutex};

        if (s_ManagedObjects.capacity() < MAX_OBJECTS)
        {
            s_ManagedObjects.reserve(MAX_OBJECTS);
        }
        if (numBytes == sizeof(MyManagedObject) &&
            s_ManagedObjects.size() < s_ManagedObjects.capacity())
        {
            unsigned int index{0xFFFFFFFF};
            if (s_FreeList.size() > 0)
            {
                index = s_FreeList.top();
                s_FreeList.pop();
            }
            if (index == 0xFFFFFFFF)
            {
                s_ManagedObjects.push_back({});
                index = s_ManagedObjects.size() - 1;
            }
            objectMemory = s_ManagedObjects.data() + index;
        }
        else
        {
            objectMemory = malloc(numBytes);
        }
        s_Mutex.unlock();
        return objectMemory;
    }
    void operator delete(void *pMem)
    {
        // s_Mutex.lock();
        lock_guard<mutex> lock{s_Mutex};
        const intptr_t index{
            (static_cast<MyManagedObject *>(pMem) - s_ManagedObjects.data()) /
            static_cast<intptr_t>(sizeof(MyManagedObject))};
        if (0 <= index && index < static_cast<intptr_t>(s_ManagedObjects.size()))
        {
            s_FreeList.emplace(static_cast<unsigned int>(index));
        }
        else
        {
            free(pMem);
        }
        s_Mutex.unlock();
    }
};

MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects{};
stack<unsigned int> MyManagedObject::s_FreeList{};
mutex MyManagedObject::s_Mutex;

void ThreadTask_2()
{
    MyManagedObject *pObject4{new MyManagedObject(5)};
    cout << "pObject4: " << pObject4 << endl;
    MyManagedObject *pObject5{new MyManagedObject(6)};
    cout << "pObject5: " << pObject5 << endl;
    delete pObject4;
    pObject4 = nullptr;
    MyManagedObject *pObject6{new MyManagedObject(7)};
    cout << "pObject6: " << pObject6 << endl;
    pObject4 = new MyManagedObject(8);
    cout << "pObject4: " << pObject4 << endl;
    delete pObject5;
    pObject5 = nullptr;
    delete pObject6;
    pObject6 = nullptr;
    delete pObject4;
    pObject4 = nullptr;
}
int main_lockguard_mutex()
{
    cout << std::hex << std::showbase;
    thread myThread{ThreadTask_2};
    MyManagedObject *pObject1{new MyManagedObject(1)};
    cout << "\npObject1: " << pObject1 << endl;
    MyManagedObject *pObject2{new MyManagedObject(2)};
    cout << "\npObject2: " << pObject2 << endl;
    delete pObject1;
    pObject1 = nullptr;
    MyManagedObject *pObject3{new MyManagedObject(3)};
    cout << "\npObject3: " << pObject3 << endl;
    pObject1 = new MyManagedObject(4);
    cout << "\npObject1: " << pObject1 << endl;
    delete pObject2;
    pObject2 = nullptr;
    delete pObject3;
    pObject3 = nullptr;
    delete pObject1;
    pObject1 = nullptr;
    myThread.join();
    return 0;
}

// Creating Threads that Wait for Events

// A condition_variable requires a mutex to be effective.
// It works by waiting for some condition to become true and then attempting to acquire a lock on the mutex protecting a shared resource.
// uses a mutex, a unique_lock, and a condition_variable to communicate between threads when a producer thread has queued work for two consumer threads.

using ProducerQueue = vector<unsigned int>;
//  A reference_wrapper essentially stores a pointer to the object you’re trying to share between threads, 
//but it helps overcome the problem where you would normally have to account for a null pointer by ensuring that the value can’t be null. 
void ThreadTask(
    reference_wrapper<condition_variable> condition,
    reference_wrapper<mutex> queueMutex,
    reference_wrapper<ProducerQueue> queueRef,
    reference_wrapper<bool> die)
{
    ProducerQueue queue{queueRef.get()};
    while (!die.get() || queue.size())
    {
        unique_lock<mutex> lock{queueMutex.get()};
        function<bool()> predicate{
            [&queue]() {
                return !queue.empty();
            }};
        condition.get().wait(lock, predicate);
        unsigned int numberToCreate{queue.back()};
        queue.pop_back();
        cout << "Creating " << numberToCreate << " objects on thread " << std::this_thread::get_id() << endl;
        for (unsigned int i = 0; i < numberToCreate; ++i)
        {
            MyManagedObject *pObject{new MyManagedObject(i)};//unused variable 'pObject' [-Wunused-variable]
        }
    }
}
/*
 The unlock call is carried out by the wait method in the first instance.
The condition_variable::wait method unlocks the mutex and waits for a signal from another thread that it should continue.
Unfortunately, this waiting isn’t completely reliable, because some operating systems can decide to unblock threads without the appropriate signal being sent. 
For this reason, it’s a good idea to have a backup plan—and the wait method provides this by taking a predicate parameter. 
The predicate takes a variable that can be called like a function. We provide a closure that determines whether the queue is empty. 
When the thread wakes, because it has been signaled to wake either by the program or by the operating system, it first checks to see if the predicate is true before attempting to reacquire the lock on the supplied mutex. 
If the predicate is true, the wait function calls lock and returns; doing so allows the thread's function to continue execution. 
The ThreadTask function creates the appropriate number of objects before starting over due to the while loop.
At the end of each iteration of the while loop, the unique_lock wrapper for the mutex goes out of scope; its destructor calls unlock on the mutex, allowing other threads to be unblocked.
*/
int main_conditionVariable()
{
    condition_variable condition;
    mutex queueMutex;
    ProducerQueue queue;
    bool die{false};
    thread myThread1{ThreadTask, std::ref(condition), std::ref(queueMutex), std::ref(queue), std::ref(die)};
    thread myThread2{ThreadTask, std::ref(condition), std::ref(queueMutex), std::ref(queue), std::ref(die)};
    queueMutex.lock();
    queue.emplace_back(300000);
    queue.emplace_back(400000);
    queueMutex.unlock();
    condition.notify_all();
    std::this_thread::sleep_for(10ms);
    while (!queueMutex.try_lock())
    {
        cout << "Main waiting for queue access!" << endl;
        std::this_thread::sleep_for(100ms);
    }
    queue.emplace_back(100000);
    queue.emplace_back(200000);
    std::this_thread::sleep_for(1000ms);
    condition.notify_one();
    std::this_thread::sleep_for(1000ms);
    condition.notify_one();
    std::this_thread::sleep_for(1000ms);
    queueMutex.unlock();
    die = true;
    cout << "main waiting for join!" << endl;
    myThread1.join();
    myThread2.join();
    return 0;
}


int main()
{
    main_conditionVariable();
    main_lockguard_mutex();
	return 0;
}