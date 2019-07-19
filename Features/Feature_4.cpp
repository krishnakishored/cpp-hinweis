#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <ctime>
#include <cmath>
#include <functional>
#include <array>
#include <algorithm>

using std::cout;
using std::endl;


std::vector<int> GenerateRandVec(int numOfNums,int min, int max);

std::vector<int> GenerateFibList(int maxNums);

int main_lambda_1() {
    
    // ----- LAMBDA EXPRESSIONS -----
    
    std::vector<int> vecVals = GenerateRandVec(10, 1, 50);
    
    // Lambda Expressions make it easy to perform list
    // operations in one line of code. You designate them with []
    // Here we sort a vector
    std::sort(vecVals.begin(), vecVals.end(), [](int x, int y){ return x < y; });
            
    for(auto val: vecVals)
        std::cout << val << "\n";
            
    std::cout << "\n";
    
    // copy_if works like filter does in other languages
    // Here we keep only even values in a new vector
    std::vector<int> evenVecVals;
    
    std::copy_if(vecVals.begin(), vecVals.end(),
                  std::back_inserter(evenVecVals), 
                  [](int x){ return (x % 2) == 0; });
            
    for(auto val: evenVecVals)
        std::cout << val << "\n";
            
    // ----- SUM A LIST -----
    int sum = 0;
    
    // for_each cycles through all values
    // [&] captures all variables used in the body of the lambda by reference
    std::for_each(vecVals.begin(), vecVals.end(),
            [&] (int x) {sum += x; });
            
            std::cout << "SUM : " << sum << "\n";
            
    // ----- END SUM A LIST -----
      
            
    // ----- MULTIPLY ALL VALUES BY 2 -----
    std::vector<int> doubleVec;
    
    // For_each cycles through all values in the vector and doubles them. 
    std::for_each(vecVals.begin(), vecVals.end(),
            [&](int x){doubleVec.push_back(x * 2);});
            
    for(auto val: doubleVec)
        std::cout << "DBL : " << val << "\n";
            
    // ----- END MULTIPLY ALL VALUES BY 2 -----
    
    // ----- PERFORMING OPERATIONS USING MULTIPLE VECTORS -----
    // Add values in separate vectors and save them to another
    std::vector<int> vec1 = {1,2,3,4,5};
    std::vector<int> vec2 = {1,2,3,4,5};
    std::vector<int> vec3(5);
    transform(vec1.begin(), vec2.end(),
            vec2.begin(), vec3.begin(),
            [](int x, int y) {return x + y;});
            
    for(auto val: vec3)
        std::cout << "vec3 " << val << "\n";
          
    // ----- END PERFORMING OPERATIONS USING MULTIPLE VECTORS -----       
            
    // ----- TERNARY OPERATOR -----
            
    // A ternary operator works like a compact if else
    // statement. If the condition is true the first
    // value is stored and otherwise the second
    int age = 43;
    bool canIVote = (age >= 18) ? true : false;
    // Shows bool values as true or false
    std::cout.setf(std::ios::boolalpha);
    std::cout << "Can Derek Vote : " << canIVote << "\n";
    
    // ----- END TERNARY OPERATOR -----
    

   
    
    return 0;
}

std::vector<int> GenerateRandVec(int numOfNums, int min, int max)
{
    std::vector<int> vecValues;
    srand(time(NULL));
    int i = 0, randVal = 0;
    while(i < numOfNums){
        randVal = min + std::rand() % ((max + 1) - min);
        vecValues.push_back(randVal);
        i++;
    }
    return vecValues;
}

// ----- PROBLEM GENERATE DYNAMIC VECTOR OF FIBS -----
//recursive function in lambda
std::vector<int> GenerateFibList(int maxNums){
    std::vector<int> listOfFibs;
    int i = 0;
    std::function<int(int)> Fib = 
    [&Fib](int n) {return n < 2 ? n : Fib(n-1) + Fib(n-2);};
    while(i < maxNums){
        listOfFibs.push_back(Fib(i));
        i++;
    }
    return listOfFibs;
}
// ----- END PROBLEM GENERATE DYNAMIC VECTOR OF FIBS -----

int main_lambda_2() {

      // ----- RECURSIVE LAMBDA FUNCTIONS -----
    
    // Recursive Lambda to calculate Fibonacci Numbers
    std::function<int(int)> Fib = 
    [&Fib](int n) {return n < 2 ? n : Fib(n-1) + Fib(n-2);};
    
    // Fib(0) = 0
    // Fib(1) = 1
    // Fib(2) = 1
    // Fib(3) = 2
    // Fib(4) = 3
    std::cout << "Fib 4 : " << Fib(4) << "\n";
    
    // ----- END RECURSIVE LAMBDA FUNCTIONS -----

 
    // ----- PROBLEM GENERATE DYNAMIC VECTOR OF FIBS -----
    std::vector<int> listOfFibs = GenerateFibList(10);
    for(auto val: listOfFibs)
        std::cout << val << "\n";
    // ----- END PROBLEM GENERATE DYNAMIC VECTOR OF FIBS -----
    return 0;
}
int main_lambda_3()
{
    std::vector<int> vecVals = GenerateRandVec(10, 1, 50);
    // ----- PROBLEM DYNAMIC LIST DIVISABLE BY A VALUE -----
            
    // You can define what value is checked for divisability
    // by passing the value to check in the capture list which lies between [] 

    // Send a value entered by the user through the capture list and create a list based on it
    int divisor;
    std::vector<int> vecVals2;
    std::cout << "List of values divisable by : ";
    std::cin >> divisor;
    std::copy_if(vecVals.begin(), vecVals.end(),
            std::back_inserter(vecVals2), 
            [divisor](int x){ return (x % divisor) == 0; });
    for(auto val: vecVals2)
        std::cout << val << "\n";
            
    // ----- END PROBLEM DYNAMIC LIST DIVISABLE BY A VALUE -----  
  return 0;
}

// to write programs that utilize unnamed function objects.

/*
 A lambda is the source code construct that defines an anonymous or unnamed function. 
 The compiler uses this syntax to create a closure object from the lambda.
*/

int main_lambaexpression()
{
    using MyArray = std::array<uint32_t, 5>;
    MyArray myArray{{10, 20, 30, 40, 50}}; //warning: suggest braces around initialization of subobject [-Wmissing-braces]
    //uses a lambda to print out all of the values in an array
    std::for_each(myArray.cbegin(),
                  myArray.cend(),
                  [](auto &&number) {
                      std::cout << number << std::endl;
                  });

    auto myClosure = [](auto &&number) { cout << number << " "; }; //captures the lambda into an auto typed variable.
    cout << typeid(myClosure).name() << std::endl;
    std::for_each(myArray.cbegin(), myArray.cend(), myClosure);
    return 0;
}

// Passing a Closure into a Function
using MyArray = std::array<uint32_t, 5>;
using MyVector = std::vector<MyArray::value_type>;

//create closures and pass them around your program using the function template
void PrintArray(const std::function<void(MyArray::value_type)> &myFunction)
{
    MyArray myArray{{1, 2, 3, 4, 5}};
    std::for_each(myArray.begin(), myArray.end(), myFunction);
}

int main_functionTemplate_closure()
{
    auto myClosure = [](auto &&number) { std::cout << number << std::endl; };
    std::cout << typeid(myClosure).name() << std::endl;
    PrintArray(myClosure);
    return 0;
}

//to copy an array into a vector through a lambda using the capture block.

int main_captureByReference()
{
    MyVector myCopy;
    //use the lambda capture to store a reference to the object myCopy in the closure.
    // auto myClosure = [&myCopy](auto &&number) {
    //     std::cout << number << " ";
    //     myCopy.push_back(number);
    // };

    //c++11 compatible
    auto myClosure = [&myCopy](const MyArray::value_type& number) {
        std::cout << number << " ";
        myCopy.push_back(number);
    };

    std::cout << typeid(myClosure).name() << std::endl;
    PrintArray(myClosure);
    //  The main function ends by printing all of the values stored by myCopy to show that
    // the closure was sharing the same vector as main thanks to the reference capture.
    std::cout << std::endl<< "My Copy: " << " ";
    std::for_each(myCopy.cbegin(), myCopy.cend(),
                  [](const MyVector::value_type&  number) { std::cout << number << " "; });
    return 0;
}

//The mutable keyword is used to tell the compiler that the lambda function should generate a closure with non-const members that have been copied by value.
// The closures created by the compiler when they encounter a lambda function are const by default. 
// This causes the compiler to create a type for the closure that can no longer be implicitly converted to a standard function pointer. 
int main_mutable_capture()
{
    MyVector myCopy;
    auto myClosure = [myCopy](auto &&number) mutable {
        std::cout << number << std::endl;
        myCopy.push_back(number);
    };
    std::cout << typeid(myClosure).name() << std::endl;
    PrintArray(myClosure);
    std::cout << std::endl<< "My Copy: " << " ";
    std::for_each(myCopy.cbegin(), myCopy.cend(),
                  [](auto &&number) { std::cout << number << " "; });
    return 0;
}

int main(){
//   main_lambda_1();
  // main_lambda_2();
  // main_lambda_3();

//   main_lambaexpression();
//   main_functionTemplate_closure();
//   main_captureByReference();
  main_mutable_capture();
  return 0;
}