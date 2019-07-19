#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef MEMORY
#define MEMORY
#include <memory>
#endif

using std::cout;
using std::endl;

//using static memory
unsigned int counter{0};

void IncreaseCounter()
{
    counter += 10;
    cout << "counter is " << counter << endl;
}
int main_StaticVariable()
{
    counter += 5;
    cout << "counter is " << counter << endl;
    IncreaseCounter();
    return 0;
}

void Function()
{
    int a{0};
    cout << a;
}
class MyClass1
{
  public:
    MyClass1()
    {
        cout << "Constructor called!" << endl;
    }
    ~MyClass1()
    {
        cout << "Destructor called!" << endl;
    }
};

//Creating Multiple Scopes
class MyClass
{
  private:
    static int m_Count;
    int m_Instance{-1};

  public:
    MyClass() : m_Instance{m_Count++}
    {
        cout << "Constructor called on " << m_Instance << endl;
    }
    ~MyClass()
    {
        cout << "Destructor called on " << m_Instance << endl;
    }
};

int MyClass::m_Count{0};

int main_stack_multipleScopes()
{
    // Function();
    MyClass1 myClass;
    cout << "Function body!" << endl;

    MyClass myClass1;
    {
        MyClass myClass2;
        {
            MyClass myClass3;
        }
    }
    return 0;
}

int main_HeapMemory()
{
    //This code uses the new operator to allocate enough memory to store a single int variable.
    //A pointer is returned from new and stored in the variable pInt.
    int *pInt{new int};
    *pInt = 100;
    cout << std::hex << "The address at pInt is " << pInt << endl;
    cout << std::dec << "The value at pInt is " << *pInt << endl;
    delete pInt;
    pInt = nullptr;
    return 0;
}

class MyClass2
{
  private:
    int m_Number{0};

  public:
    MyClass2() = default;
    MyClass2(int value) : m_Number{value}
    {
    }
    ~MyClass2()
    {
        cout << "Destroying " << m_Number << endl;
    }
    void operator=(const int value)
    {
        m_Number = value;
    }
    int GetNumber() const { return m_Number; }
};

int main_deleteArrayOnHeap()
{
    const unsigned int NUM_ELEMENTS{5};
    MyClass2 *pObjects{new MyClass2[NUM_ELEMENTS]};
    pObjects[0] = 100;
    pObjects[1] = 45;
    pObjects[2] = 31;
    pObjects[3] = 90;

    pObjects[4] = 58;
    delete[] pObjects; //deleting an array
    pObjects = nullptr;
    return 0;
}

//Using Automated Shared Memory

using SharedMyClass = std::shared_ptr<MyClass2>;

//Transferring Dynamic Memory between Functions
void ChangeSharedValue(SharedMyClass sharedMyClass)
{
    if (sharedMyClass != nullptr)
    {
        *sharedMyClass = 100;
    }
}
int main_sharedPtr()
{
    SharedMyClass sharedMyClass{new MyClass2(10)};
    //You now have two instances of the SharedMyClass template, both pointing to the same MyClass instance.
    ChangeSharedValue(sharedMyClass);
    return 0;
}

using UniqueMyClass = std::unique_ptr< MyClass2 >;
void CreateUniqueObject()
{
    //The unique_ptr is created inside a function to demonstrate that the instance of 
    //the dynamically created object is destroyed when the unique_ptr goes out of scope
    UniqueMyClass uniqueMyClass{ std::make_unique<MyClass2>(20) };
}

void CreateUniqueObject2(UniqueMyClass& referenceToUniquePtr)
{
    UniqueMyClass uniqueMyClass{ std::make_unique<MyClass2>(10) };
    cout << std::hex << std::showbase;
    cout << "Address in uniqueMyClass " << uniqueMyClass.get() << endl;
    referenceToUniquePtr.swap(uniqueMyClass);
    cout << "Address in uniqueMyClass " << uniqueMyClass.get() << endl;
}

int main_UniquePtr()
{
    cout << "Begin Main!" << endl;
    CreateUniqueObject();
    //Transferring Dynamically Allocated Memory Between unique_ptr instances
    UniqueMyClass uniqueMyClass;
    CreateUniqueObject2(uniqueMyClass);
    cout << "Address in main's uniqueMyClass " << uniqueMyClass.get() << endl;
    cout << std::dec << std::noshowbase << "Back in Main!" << endl;
    return 0;
}

int main(){
    main_deleteArrayOnHeap();
    main_HeapMemory();
    main_sharedPtr();
    main_stack_multipleScopes();
    main_StaticVariable();
    main_UniquePtr();
    return 0;
}