#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>

#include <functional>

using std::cout;
using std::endl;

// 1. Created to store as a variable and to pass into other functions
double MultBy2(double num){
    return num * 2;
}

// 2. Functions can receive other functions
// the first double is the return type followed by the data types for the parameter
double DoMath(std::function<double(double)> func, double num){
    return func(num);
}

// 3. You can store functions in a vector
double MultBy3(double num){
    return num * 3;
}

// 4. ----- PROBLEM -----
// Checks for odd using modulus
bool IsItOdd(int num){
    if(num % 2 == 0){
        return false;
    } else {
        return true;
    }
}

// Receives a list and generates a list of odd values from that list 
std::vector<int> ChangeList(std::vector<int> list, std::function<bool(int)> func){
    std::vector<int> oddList;
    for(auto i: list){
        if(func(i)){
            oddList.push_back(i);
        }
    }
    return oddList;
}
// ----- 4. END OF PROBLEM -----

// ----- 5. PROBLEM -----
// Generates a random list from the possible values supplied
std::vector<char> GetHAndTList(std::vector<char> possibleValues, int numberValuesToGenerate)
{
    srand(time(NULL));
    std::vector<char> hAndTList;
    
    for(int x = 0; x < numberValuesToGenerate; ++x){
        int randIndex = rand() % 2;
        hAndTList.push_back(possibleValues[randIndex]);
    }
    return hAndTList;
}

// Receives a list and sums the number of matching chars
int GetNumberOfMatches(std::vector<char> list, char valueToFind)
{
    int numOfMatches = 0;
    
    for(char c: list){
        if(c == valueToFind){
            numOfMatches++;
        }
    }
    return numOfMatches;
}

// ----- 5. END OF PROBLEM -----

int main_vectorOfFunctions()
{
    // 1. You can store functions as variables
    auto times2 = MultBy2;
    std::cout << "5 * 2 = " << times2(5) << "\n";
    
    // 2. Pass a function into a function
    std::cout << "6 * 2 = " << DoMath(times2, 6) << "\n";
    
    // 3. You can store functions in a vector
    // Create a vector using the function parameters
    // and then load the functions into the vector
    std::vector<std::function<double(double)>> funcs (2);
    funcs[0] = MultBy2;
    funcs[1] = MultBy3;
    std::cout << "2 * 10 = " << funcs[0](10) << "\n";
    
    // 4. ----- PROBLEM -----
    // Create a function that receives a list and a function
    // The function passed will return True or False if a list
    // value is odd.
    // The surrounding function will return a list of odd
    // numbers
    std::vector<int> listOfNums {1,2,3,4,5};
    std::vector<int> oddList = ChangeList(listOfNums, IsItOdd);
    std::cout << "List of Odds\n";
    for(auto i: oddList){
        std::cout << i << "\n";
    }
    // ----- 4. END OF PROBLEM -----
    
    // ----- 5. PROBLEM -----
    // Create a function that creates a random list using a limited number of values
    // Create another function that checks for the number of matches in a list
    // Create a random list of Hs and Ts and then output how many of each were generated
    
    std::vector<char> possibleValues {'H', 'T'};
    std::vector<char> hAndTList = GetHAndTList(possibleValues, 100);
    std::cout << "Number of Heads : " <<
            GetNumberOfMatches(hAndTList, 'H')
            << "\n";
    std::cout << "Number of Tails : " <<
            GetNumberOfMatches(hAndTList, 'T')
            << "\n";
    
    // ----- 5. END OF PROBLEM -----
    
    
    return 0;
}


// Listing 2-1. The C++Most Vexing Parse Problem
class MyClass
{
    //   private:
  public:
    int m_Member{};

  public:
    MyClass() = default;
    MyClass(const MyClass &rhs) = default;
};

#ifndef ARRAY
#define ARRAY
#include <array>
#endif


int main_uniform_initialization()
{
    MyClass objectA{};

    /* A C++ compiler will not see this line as defining a variable named objectB of type MyClass calling a constructor that 
     * takes the object constructed by calling the MyClass constructor. 
     * This is what you might expect the compiler to see however what it actually sees is a function declaration. 
     * The compiler thinks that this line is declaring a function named objectB that returns a MyClass object and has a single, 
     * unnamed function pointer to a function that returns a MyClass object and is passed no parameters.
     */

    //MyClass objectB(MyClass()); //error: parentheses were disambiguated as a function declaration

    //MyClass objectB((MyClass()));  //note: add a pair of parentheses to declare a variable is also a solution

    MyClass objectB{MyClass{}}; //using uniform initialization

    //uniform initialization prevents narrowing conversions
    //Narrowing conversions occur when data is transferred from one type to another in where the destination type cannot store all of the values represented by the source type.

    int num{0};
    double bigNumber{1.0};
    /*
    char another{512};// A char type can store a maximum value of 255 therefore the value 512 would be narrowed into this data type.
    float littleNumber{ bigNumber };
    */

    // using static_cast to fix narrowing conversion
    char another{static_cast<char>(512)};
    float littleNumber{static_cast<float>(bigNumber)};
    //to supress unused variable warning:
    cout << num << bigNumber << another << littleNumber << objectA.m_Member << objectB.m_Member << endl;
    return 0;
}

// Initializing Objects with Initializer Lists
//Modern C++ provides initializer lists that can be used to supply many objects of the same type to a constructor.

int main_initializerlists()
{
    using MyVector = std::vector<int>;
    //The first parameter to a vector constructor determines how many values the initial vector will be set up to store
    // and in this case we are asking it to store a single variable
    MyVector vectorA(1); //The vectorA variable will be initialized with a single int containing 0.
    cout << vectorA.size() << " " << vectorA[0] << endl;
    MyVector vectorB(1, 10); //a vector that contains one value and that value is 10.
    cout << vectorB.size() << " " << vectorB[0] << endl;

    MyVector vectorC{1, 10}; //uses an initializer list in conjunction with uniform initialization to construct a vector that contains two elements with the specified values
    cout << vectorC.size() << " " << vectorC[0] << " " << vectorC[1] << endl;

    std::initializer_list<int> initList{30, 10}; //an explicit initializer_list that is used to construct a vector.
    MyVector vectorD(initList);
    cout << vectorD.size() << " " << vectorD[0] << endl; //2 30
    return 0;
}

//You would like to write portable code that doesn’t have a high maintenance cost when changing types.
// C++ provides the auto keyword that can be used to let the compiler deduce the type for a variable automatically.

// how to create a variable with automatically deduced type in C++.

// int main_typeid_auto()

//run this ./bin/probe | c++filt -t

int main_auto_initializerlist()
{
    auto variable = 1;
    cout << "Type of variable: " << typeid(variable).name() << endl; //i

    auto variable2 = MyClass();
    cout << "Type of variable: " << typeid(variable2).name() << endl; //7MyClass

    auto variable3{MyClass{}};
    cout << "Type of variable: " << typeid(variable3).name() << endl;

    return 0;
}

// Modern C++ allows you to use type deduction for function parameters and for return types.
/*
C++ allows you to utilize type deduction when working with function using two methods. 
Types can be deduced for function parameters by creating a template function and calling that function without explicit specializers. 
The return type can be deduced for a function using the auto keyword in place of its return type
*/

// auto AutoFunctionFromReturn(int parameter) -> int // for c++11 compiler
auto AutoFunctionFromReturn(int parameter)
{
    return parameter;
}

template <typename T>
auto AutoFunctionFromParameter(T parameter) -> decltype(parameter)
{
    return parameter;
}
// C++14 rectifies this situation by allowing auto to be used on functions without having the trailing return type even when used with templates

int main_auto_return_type()
{
    auto value = AutoFunctionFromReturn(100);
    cout << value<< " "<< typeid(value).name()<< endl;//100 int

    auto value2 = AutoFunctionFromParameter(2.0);
    cout << value2<<" "<< typeid(value2).name()<< endl; //2 double
    return 0;
}


//Working with Compile Time Constants
// To optimize the runtime operation of your program using compile time constant.
constexpr uint32_t ArraySizeFunction(uint32_t parameter)
{
    // return parameter;
    //To limit the array size
    uint32_t value{ parameter };
    if(value>5) value = 5;
    return value;
}

class MyClass_2{
    private:
        uint32_t m_Member;
    public:
        constexpr MyClass_2(uint32_t parameter):m_Member{parameter}{}
        constexpr uint32_t GetValue() const{return m_Member;}
};

int main_constexpr()
{
    // constexpr uint32_t ARRAY_SIZE{5};
    constexpr uint32_t ARRAY_SIZE{ ArraySizeFunction(10) }; //using constexpr func.
    cout<<"Array size is limited to: "<<ARRAY_SIZE<<endl;
    // constexpr uint32_t ARRAY_SIZE{MyClass_2{5}.GetValue()}; //using a class with constexpr constructor
    std::array<uint32_t, ARRAY_SIZE> myArray{ {1, 2, 3, 4, 5} };

    for (auto &&number : myArray)
    {
        std::cout << number << std::endl;
    }
    return 0;
}

int main()
{
    main_vectorOfFunctions();
    main_auto_return_type();
    main_constexpr();
    main_auto_initializerlist();
    main_initializerlists();
    return 0;
}