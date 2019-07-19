// Modern C++ provides the capability to automatically manage dynamically allocated memory.
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef MEMORY
#define MEMORY
#include <memory>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

//Handling < c++14
#if __cplusplus > 200400L && __cplusplus < 201200L
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args... args)
{
    return unique_ptr<T>{new T(args...)};
}
#endif

using std::cout;
using std::endl;

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;

using std::weak_ptr;

class MyClass
{
  private:
    std::string m_Name;
    int m_Value{10};

  public:
    MyClass() = default;
    MyClass(const std::string &name, int value) : m_Name{name}, m_Value{value}
    {
        cout << m_Name << " Constructing!" << endl;
    }
    ~MyClass()
    {
        cout << "Destructing!" << endl;
    }
    const std::string &GetName() const
    {
        return m_Name;
    }
    int GetValue() const
    {
        return m_Value;
    }
};

int main_uniquePtr_basic()
{
    // The make_unique template handles calling new and the unique_ptr object handles calling delete when the unique_ptr instance goes out of scope.
    // std::unique_ptr<MyClass> uniquePointer{std::make_unique<MyClass>()};
    unique_ptr<MyClass> uniquePointer{make_unique<MyClass>("MyClass", 10)};
    cout << uniquePointer->GetValue() << endl;
    return 0;
}

using MyUniquePtr = unique_ptr<MyClass>;
auto PassUniquePtr(MyUniquePtr ptr)
{
    cout << "In Function Name: " << ptr->GetName() << endl;
    return ptr;
}

int main_uniquePtr_move()
{
    auto uniquePointer = make_unique<MyClass>("MyClass", 10);
    auto newUniquePointer = PassUniquePtr(move(uniquePointer));
    if (uniquePointer)
    {
        cout << "First Object Name: " << uniquePointer->GetName() << endl;
    }
    cout << "Second Object Name: " << newUniquePointer->GetName() << endl;
    return 0;
}

using MySharedPtr = shared_ptr<MyClass>;

auto PassSharedPtr(MySharedPtr ptr)
{
    cout << "In Function Name: " << ptr->GetName() << endl;
    return ptr;
}

int main_sharedPtr()
{
    auto sharedPointer = make_shared<MyClass>("MyClass", 10);
    {
        auto newSharedPointer = PassSharedPtr(sharedPointer);
        if (sharedPointer)
        {
            cout << "First Object Name: " << sharedPointer->GetName() << endl;
        }
        cout << "Second Object Name: " << newSharedPointer->GetName() << endl;
    }
    return 0;
}

using MySharedPtr = shared_ptr<MyClass>;
using MyWeakPtr = weak_ptr<MyClass>;

int main_WeakPtr()
{
    MyWeakPtr weakPtr;
    {
        auto sharedPointer = make_shared<MyClass>("MyClass", 10);
        weakPtr = sharedPointer;
        {
            auto newSharedPointer = PassSharedPtr(sharedPointer);
            if (sharedPointer)
            {
                cout << "First Object Name: " << sharedPointer->GetName() << endl;
            }
            cout << "Second Object Name: " << newSharedPointer->GetName() << endl;
            auto sharedFromWeak1 = weakPtr.lock();
            if (sharedFromWeak1)
            {
                cout << "Name From Weak1: " << sharedFromWeak1->GetName() << endl;
            }
        }
    }
    auto sharedFromWeak2 = weakPtr.lock();
    if (!sharedFromWeak2)
    {
        cout << "Shared Pointer Out Of Scope!" << endl;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    /* code */
    main_WeakPtr();
    main_sharedPtr();
    main_uniquePtr_move();
    main_uniquePtr_basic();
    return 0;
}
