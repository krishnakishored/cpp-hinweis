// ——- ANIMAL.CPP ——-
#include "Animal.h"

Animal::Animal() {}

Animal::Animal(const Animal& orig) {}

Animal::~Animal() {}

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>

#include <deque>
#include <iterator>


using std::cout;
using std::endl;

// ----- PREPROCESSOR DIRECTIVES -----

// Anything that starts with a # is a preprocessor
// directive and they run before the program compiles

// Right click Header Files -> New -> C++ Header File
// and then include it here
#include "Animal.h"

// This is a macro constant that will replace 
// PI with 3.14159 in the code before execution
#define PI 3.14159

// This is a macro function that will do the same with
// a function
#define AREA_CIRCLE(radius) (PI * (std::pow(radius, 2)))

// ----- END PREPROCESSOR DIRECTIVES -----

// ----- TEMPLATE FUNCTIONS -----

// We use templates to create functions or classes
// that can work with many types
// Templates differ from function overloading in that
// instead of having a function that does similar
// things with different objects a template does the
// same thing with different objects

// This says this is a function template that generates
// functions that except 1 parameter
template <typename T>
void Times2(T val)
{
    std::cout << val << " * 2 = " << val * 2 << "\n";
}

// Receive multiple parameters and return a value
template <typename T>
T Add(T val, T val2){
    return val + val2;
}

// Work with chars and strings
template <typename T>
T Max(T val, T val2){
    return (val < val2) ? val2 : val;
}

// ----- END OF TEMPLATE FUNCTIONS -----

// ----- TEMPLATE CLASSES -----

// Template classes are classes that can work with 
// different data types

// You can define that you may receive parameters
// with different types, but they don't have to
// be different
template <typename T, typename U>
class Person{  
public:
    T height;
    U weight;
    static int numOfPeople;
    Person(T h, U w){
        height = h, weight = w;
        numOfPeople++;
    }   
    void GetData(){
        std::cout << "Height : " << height 
                  << " and Weight : " 
                  << weight << "\n";
    }
};

// You have to initialize static class members
template<typename T, typename U> int Person<T, U>::numOfPeople;


// ----- END OF TEMPLATE CLASSES -----

int main_TemplateClass()
{
    Animal spot = Animal();
    spot.name = "Spot";
    std::cout << "The Animal is named " << spot.name << "\n";
    
    std::cout << "Circle Area : " << AREA_CIRCLE(5) << "\n";
    
    // ----- TEMPLATE FUNCTIONS -----
    // The template function can receive ints or floats
    Times2(5);
    Times2(5.3);
    
    // Multiple parameters and returned value
    std::cout << "5 + 4 = " << Add(5,4) << "\n";
    std::cout << "5.5 + 4.6 = " << Add(5.5,4.6) << "\n";

    // Get biggest value
    std::cout << "Max 4 or 8 = " << Max(4, 8) << "\n";
    std::cout << "Max A or B = " << Max('A', 'B') << "\n";
    std::cout << "Max Dog or Cat = " << Max("Dog", "Cat") << "\n";
    // ----- END OF TEMPLATE FUNCTIONS -----
    
    // ----- TEMPLATE CLASSES -----
    
    // When creating the object you must define the 
    // data types used
    Person<double, int> mikeTyson (5.83, 216);
    mikeTyson.GetData();
    
    // You access static values using the object and not the class
    std::cout << "Number of people : " << mikeTyson.numOfPeople << "\n";
    
    // ----- END OF TEMPLATE CLASSES -----
    
    // ----- CONTAINERS -----
    // We have already seen the STL container vector
    // There are many other special ways of storing data
    
    // ----- DOUBLE ENDED QUEUE -----
    
    // A double ended queue (Deque) is a dynamic array that can 
    // be expanded or contracted on both ends
    std::deque<int> nums = {1,2,3,4};
    nums.push_front(0);
    nums.push_back(5);
    for(int x: nums)
        std::cout << x << "\n";
    
    // You can access index values, but they are costly
    // because values aren't stored contigously, but instead use multiple arrays
    std::cout << nums[0] << "\n";
    
    // ----- END DOUBLE ENDED QUEUE -----
    
    // ----- ITERATORS -----
    // Iterators are used to point at container memory locations
    std::vector<int> nums2 = {1,2,3,4};
    
    // Define an iterator as the same type
    std::vector<int>::iterator itr;
    
    // Refer to the vectors begin and end while incrementing the iterator
    for(itr = nums2.begin(); itr < nums2.end(); itr++)
    {    
        // Get value at the pointer
        std::cout << *itr << "\n";
    }
    
    // You can also increment a set number of spaces
    // Create an iterator and point it at the beginning of the vector
    std::vector<int>::iterator itr2 = nums2.begin();
    
    // Advance 2 spaces
    advance(itr2, 2);
    std::cout << *itr2 << "\n";
    
    // Next works like advance, but it returns an iterator
    auto itr3 = next(itr2, 1);
    std::cout << *itr3 << "\n";
    
    // Previous moves a set number of indexes and returns an iterator
    auto itr4 = prev(itr2, 1);
    std::cout << *itr4 << "\n";
    
    // You can also insert at a defined index
    std::vector<int> nums3 = {1,4,5,6};
    std::vector<int> nums4 = {2,3};
    auto itr5 = nums3.begin();
    advance(itr5, 1);
    copy(nums4.begin(), nums4.end(), inserter(nums3, itr5));
    
    for(int &i: nums3)
        std::cout << i << "\n";
      
    // ----- END ITERATORS -----
    
    // ----- END OF CONTAINERS -----
    
    return 0;
}


class MyClass
{
  private:
    static int s_Counter;
    int *m_Member{&s_Counter};

  public:
    MyClass()
    {
        ++(*m_Member);
        cout << "Constructing: " << GetValue() << endl;
    }

    MyClass(const MyClass &rhs) : m_Member(rhs.m_Member)
    {
        ++(*m_Member);
        cout << "Copying: " << GetValue() << endl;
    }

    MyClass(MyClass &&rhs) : m_Member{rhs.m_Member}
    {
        cout << std::hex << std::showbase;
        cout << "Moving: " << &rhs << " to " << this << endl;
        cout << std::noshowbase << std::dec;
        rhs.m_Member = nullptr;
    }

    // ~MyClass()
    // {
    //     --(*m_Member);
    //     m_Member = nullptr;
    //     cout << "Destructing: " << s_Counter << endl;
    // }

    ~MyClass()
    {
        if (m_Member)
        {
            --(*m_Member);
            m_Member = nullptr;
            cout << "Destructing: " << s_Counter << endl;
        }
        else
        {
            cout << "Destroying moved-from instance" << endl;
        }
    }

    int GetValue() const
    {
        return *m_Member;
    }
};

MyClass CopyMyClass(MyClass parameter)
{
    return parameter;
}

int MyClass::s_Counter{0};

int main_moveConstuctor()
{
    auto object1 = MyClass();
    // cout << object1.GetValue() << endl;
    {
        auto object2 = MyClass();
        // cout << object2.GetValue() << endl;
    }
    auto object3 = MyClass();
    // cout << object3.GetValue() << endl;

    // This has the impact of needing two copies,
    // one to copy object3 into parameter and one to copy parameter into object4.
    auto object4 = CopyMyClass(object3);
    return 0;
}

// Comparing Copy Constructors with Move Constructors

using namespace std::literals;
using namespace std::chrono;

class MyClass_2
{
  private:
    std::vector<std::string> m_String{
        "This is a pretty long string that"
        " must be copy constructed into"
        " copyConstructed!"s};
    int m_Value{1};

  public:
    MyClass_2() = default;
    MyClass_2(const MyClass_2 &rhs) = default;
    MyClass_2(MyClass_2 &&rhs) = default;
    int GetValue() const
    {
        return m_Value;
    }
};

int main_MoveCopy_compare()
{
    using MyVector = std::vector<MyClass_2>;
    constexpr unsigned int ITERATIONS{1000000U};
    MyVector copyConstructed(ITERATIONS);
    int value{0};
    auto copyStartTime = high_resolution_clock::now();
    for (unsigned int i = 0; i < ITERATIONS; ++i)
    {
        MyClass_2 myClass;
        copyConstructed.push_back(myClass);
        value = myClass.GetValue();
    }
    auto copyEndTime = high_resolution_clock::now();
    MyVector moveConstructed(ITERATIONS);
    auto moveStartTime = high_resolution_clock::now();
    for (unsigned int i = 0; i < ITERATIONS; ++i)
    {
        MyClass_2 myClass;
        moveConstructed.push_back(std::move(myClass));
        value = myClass.GetValue();
    }
    auto moveEndTime = high_resolution_clock::now();
    cout << value << endl;
    auto copyDuration = duration_cast<milliseconds>(copyEndTime - copyStartTime);
    cout << "Copy lasted: " << copyDuration.count() << "ms" << endl;
    auto moveDuration = duration_cast<milliseconds>(moveEndTime - moveStartTime);
    cout << "Move lasted: " << moveDuration.count() << "ms" << endl;

    return 0;
}



int main_systemclock()
{
    auto currentTimePoint = std::chrono::system_clock::now();
    cout << "currentTimePoint: " << typeid(currentTimePoint).name() << endl;
    auto currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
    cout << "currentTime: " << typeid(currentTime).name() << endl;
    auto timeText = ctime(&currentTime);
    cout << "timeText: " << typeid(timeText).name() << endl;
    cout << endl
         << timeText << endl;
    return 0;
}

using namespace std::literals ; 

//use the STL time capabilities to compare one time to another
int main_durationcast()
{
    auto startTimePoint = std::chrono::system_clock::now();
    std::this_thread::sleep_for(5s);
    auto endTimePoint = std::chrono::system_clock::now();
    // auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimePoint - startTimePoint);
    auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(endTimePoint - startTimePoint);

    cout << "Time Taken: " << timeTaken.count() << endl;

    return 0;
}


int main()
{
    main_TemplateClass();
    main_MoveCopy_compare();
    main_moveConstuctor();
    main_MoveCopy_compare();
    main_durationcast();
    main_systemclock();
    return 0;
}