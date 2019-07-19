// 11-1. Using Threads to Execute Concurrent Tasks
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

using std::cout;
using std::endl;
using std::stack;
using std::thread;
using std::vector;

void ThreadTask_1()
{
    for (unsigned int i{0}; i < 20; ++i)
    {
        cout << "Output from thread:" << i << endl;
    }
}

// The join method causes the program to wait for a running thread to complete before continuing, but the detach method doesn’t.
// The detach method allows you to create threads that outlive the execution of your program

int main_CreateThread()
{
    const unsigned int numberOfProcessors{thread::hardware_concurrency()};
    cout << "This system can run " << numberOfProcessors << " concurrent tasks" << endl;

    if (numberOfProcessors > 1)
    {
        thread myThread{ThreadTask_1};
        cout << "Output from main: " << endl;
        myThread.join(); //absence causes a thread leak
        //  myThread.detach(); //  Once an execution context in a thread has been detached, you can never reattach it.
    }
    else
    {
        cout << "CPU does not have multiple cores." << endl;
    }
    return 0;
}

class MyManagedObject
{
  private:
    using MyManagedObjectCollection = vector<MyManagedObject>;
    // static const unsigned int MAX_OBJECTS{4};
    // static MyManagedObjectCollection s_ManagedObjects;
    // static stack<unsigned int> s_FreeList;
    
    static thread_local const unsigned int MAX_OBJECTS;
    static thread_local MyManagedObjectCollection s_ManagedObjects;
    static thread_local stack<unsigned int> s_FreeList;

    
    


    unsigned int m_Value{0xFFFFFFFF};

  public:
    MyManagedObject() = default;
    MyManagedObject(unsigned int value) : m_Value{value} {}
    void *operator new(size_t numBytes)
    {
        void *objectMemory{};
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
        else // doesn’t actually enforce the limit; it simply falls back to dynamic allocation when the limit has been reached.
        {
            objectMemory = malloc(numBytes);
        }
        return objectMemory;
    }
    void operator delete(void *pMem)
    {
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
    }
};
// MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects{8};
// stack<unsigned int> MyManagedObject::s_FreeList{};


thread_local const unsigned int MyManagedObject::MAX_OBJECTS{ 8 };
thread_local MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects{};
thread_local stack<unsigned int> MyManagedObject::s_FreeList{};


int main_classUsingStaticData()
{
    cout << std::hex << std::showbase;
    MyManagedObject *pObject1{new MyManagedObject(1)};
    cout << "pObject1: " << pObject1 << endl;
    MyManagedObject *pObject2{new MyManagedObject(2)};
    cout << "pObject2: " << pObject2 << endl;
    delete pObject1;
    pObject1 = nullptr;
    MyManagedObject *pObject3{new MyManagedObject(3)};
    cout << "pObject3: " << pObject3 << endl;
    pObject1 = new MyManagedObject(4);
    cout << "pObject1: " << pObject1 << endl;
    delete pObject2;
    pObject2 = nullptr;
    delete pObject3;
    pObject3 = nullptr;
    delete pObject1;
    pObject1 = nullptr;
    return 0;
}
//Using a thread to Create MyManagedObject Instances
void ThreadTask()
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

//static pool can be accessed simultaneously from two locations
//A data race is a more subtle problem and results in unexpected memory corruption
/*
The impact of this change is that the main function and the ThreadTask function have separate s_ManagedObjects, s_FreeList, and MAX_OBJECT variables in their own execution context. 
Now that there are two copies of each, you have twice the number of potential objects, because as the pools have been duplicated. 
*/
int main_ThreadLocal()
{
    cout << std::hex << std::showbase;
    thread myThread{ThreadTask};
    MyManagedObject *pObject1{new MyManagedObject(1)};
    cout << "pObject1: " << pObject1 << endl;
    MyManagedObject *pObject2{new MyManagedObject(2)};
    cout << "pObject2: " << pObject2 << endl;
    delete pObject1;
    pObject1 = nullptr;
    MyManagedObject *pObject3{new MyManagedObject(3)};
    cout << "pObject3: " << pObject3 << endl;
    pObject1 = new MyManagedObject(4);
    cout << "pObject1: " << pObject1 << endl;
    delete pObject2;
    pObject2 = nullptr;
    delete pObject3;
    pObject3 = nullptr;
    delete pObject1;
    pObject1 = nullptr;
    myThread.join();
    return 0;
}


int main()
{
    main_classUsingStaticData();
    main_CreateThread();
    main_ThreadLocal();
    main_classUsingStaticData();
	return 0;
}

