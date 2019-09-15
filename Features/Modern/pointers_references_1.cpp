/*
http://www.ntu.edu.sg/home/ehchua/programming/cpp/cp4_pointerreference.html
 - A pointer variable (or pointer in short) is basically the same as the other variables, which can store a piece of data.
   Unlike normal variable which stores a value (such as an int, a double, a char), a pointer stores a memory address.
 - A reference is an alias, or an alternate name to an existing variable
 -  When it is used in an expression, & denotes the address-of operator, which returns the address of a variable
    When & is used in a declaration (including function formal parameters), it is part of the type identifier and is used to declare a reference variable

References vs. Pointers
A reference works as a pointer. A reference is declared as an alias of a variable.
It stores the address of the variable. Pointers and references are equivalent, except:
- 1. A reference is a name constant for an address. You need to initialize the reference during declaration.
    Once a reference is established to a variable, you cannot change the reference to reference another variable.
- 2. To get the value pointed to by a pointer, you need to use the dereferencing operator * (e.g., if pNumber is a int pointer, *pNumber returns the value pointed to by pNumber.
     It is called dereferencing or indirection). To assign an address of a variable into a pointer, you need to use the address-of operator & (e.g., pNumber = &number).

     On the other hand, referencing and dereferencing are done on the references implicitly.

- 3. In pass-by-reference with reference arguments, you use the variable name as the argument.
     In pass-by-reference with pointer arguments, you need to use &varName (an address) as the argument.



"const" Function Reference/Pointer Parameters
- A const function parameter can receive both const and non-const argument.
  But a non-const function reference/pointer parameter can only receive non-const argument.

- You should not pass Function's local variable as return value by reference


*/

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#include <cstring>

// #include <cinttypes>
using std::cout;
using std::endl;

int main_Pointers_1()
{
    int number = 88;
    int *pNum = &number; //Initializing Pointers via the Address-Of Operator (&)

    int *pNum2;
    pNum2 = pNum;

    cout << *pNum << " " << *pNum2 << endl; //Indirection or Dereferencing Operator (*)
    cout << pNum << " " << pNum2 << endl;   // same: 0x7ffee95cf57c 0x7ffee95cf57c
    cout << &pNum << " " << &pNum2 << endl; //0x7ffee95cf570 0x7ffee95cf568
    //Pointer has a Type Too
    /*
    int i = 88;
    double d = 55.66;

    int *iPtr = &i;    // int pointer pointing to an int value
    double *dPtr = &d; // double pointer pointing to a double value

    // iPtr = &d; // ERROR, cannot hold address of different type
    // dPtr = &i; // ERROR
    // iPtr = i;  // ERROR, pointer holds address of an int, NOT int value
    int j = 99;
    iPtr = &j; // You can change the address stored in a pointer
    */

    //The following code fragment has a serious logical error!
    // You need to initialize a pointer by assigning it a valid address.
    // Most of the compilers does not signal an error or a warning for uninitialized pointer?!
    /*

        int * iPtr2;
        *iPtr2 = 55;
        cout << *iPtr2 << endl;

        The pointer iPtr was declared without initialization,
        i.e., it is pointing to "somewhere" which is of course an invalid memory location.
        The *iPtr = 55 corrupts the value of "somewhere"!
    */

    //null pointer
    /*
    int *iPtr2 = 0;
    int *iPtr2 = nullptr;
    cout<<*iPtr2<<endl; // // ERROR! STATUS_ACCESS_VIOLATION exception
    */
    return 0;
}

int main_References_1()
{
    int number1 = 88, number2 = 22;

    // Create a pointer pointing to number1
    int *pNumber1 = &number1;  // Explicit referencing
    *pNumber1 = 99;            // Explicit dereferencing
    cout << *pNumber1 << endl; // 99
    cout << &number1 << endl;  // 0x22ff18
    cout << pNumber1 << endl;  // 0x22ff18 (content of the pointer variable - same as above)
    cout << &pNumber1 << endl; // 0x22ff10 (address of the pointer variable)
    pNumber1 = &number2;       // Pointer can be reassigned to store another address

    // Create a reference (alias) to number1
    int &refNumber1 = number1;   // Implicit referencing (NOT &number1)
    refNumber1 = 11;             // Implicit dereferencing (NOT *refNumber1)
    cout << refNumber1 << endl;  // 11
    cout << &number1 << endl;    // 0x22ff18
    cout << &refNumber1 << endl; // 0x22ff18
    //refNumber1 = &number2;     // Error! Reference cannot be re-assigned
    // error: invalid conversion from 'int*' to 'int'
    refNumber1 = number2; // refNumber1 is still an alias to number1.
                          // Assign value of number2 (22) to refNumber1 (and number1).
    number2++;
    cout << refNumber1 << endl; // 22
    cout << number1 << endl;    // 22
    cout << number2 << endl;    // 23
    return 0;
}

//Pass-By-Reference into Functions with Reference Arguments vs. Pointer Arguments

int squarebyValue(int);      //Pass-by-value
void squarebyRef_Ptr(int *); // Pass-by-reference using Pointer
void squarebyRef_Ref(int &); //Pass-by-reference using reference

int main_PassByValue_PassByRef()
{
    int number = 8;
    cout << "In main: " << &number << endl;       // 0x22ff1c
    cout << number << endl;                         // 8
    cout << squarebyValue(number) << endl;          // 64
    cout << "Pass by Value:  " << number << endl;   // 8 - no change
    squarebyRef_Ptr(&number);                       // Explicit referencing to pass an address
    cout << "Pass by Ref_Ptr:  " << number << endl; // 64
    squarebyRef_Ref(number);                        // Implicit referencing (without '&')
    cout << "Pass by Ref_Ref:  " << number << endl; // 4096

    return 0;
}

int squarebyValue(int n)
{                                          // non-const
    cout << "In square(): " << &n << endl; // 0x22ff00
    n *= n;                                // clone modified inside the function
    return n;
}

void squarebyRef_Ptr(int *pNumber)
{                                               // Function takes an int pointer (non-const)
    cout << "In square(): " << pNumber << endl; // 0x22ff1c
    *pNumber *= *pNumber;                       // Explicit de-referencing to get the value pointed-to
}

void squarebyRef_Ref(int &rNumber)
{                                                // Function takes an int reference (non-const)
    cout << "In square(): " << &rNumber << endl; // 0x22ff1c
    rNumber *= rNumber;                          // Implicit de-referencing (without '*')
}

//"const" Function Reference/Pointer Parameters

int squareConst(const int);
int squareNonConst(int);
int squareConstRef(const int &);
int squareNonConstRef(int &);

int main_constRef()
{
    int number = 8;
    const int constNumber = 9;
    cout << squareConst(number) << endl;
    cout << squareConst(constNumber) << endl;
    cout << squareNonConst(number) << endl;
    cout << squareNonConst(constNumber) << endl;

    cout << squareConstRef(number) << endl;
    cout << squareConstRef(constNumber) << endl;
    cout << squareNonConstRef(number) << endl;
    // cout << squareNonConstRef(constNumber) << endl;
    // error: invalid initialization of reference of
    //  type 'int&' from expression of type 'const int'
    return 0;
}

int squareConst(const int number)
{
    // number *= number;  // error: assignment of read-only parameter
    return number * number;
}

int squareNonConst(int number)
{ // non-const parameter
    number *= number;
    return number;
}

int squareConstRef(const int &number)
{ // const reference
    return number * number;
}

int squareNonConstRef(int &number)
{ // non-const reference
    return number * number;
}

//Passing the Function's Return Value as reference or pointer
int &squareRef(int &);
int *squarePtr(int *);

int main_ReturnRefToLocal()
{
    int number1 = 8;
    cout << "In main &number1: " << &number1 << endl; // 0x22ff14
    int &result = squareRef(number1);
    cout << "In main &result: " << &result << endl; // 0x22ff14
    cout << result << endl;                           // 64
    cout << number1 << endl;                          // 64

    int number2 = 9;
    cout << "In main &number2: " << &number2 << endl; // 0x22ff10
    int *pResult = squarePtr(&number2);
    cout << "In main pResult: " << pResult << endl; // 0x22ff10
    cout << *pResult << endl;                         // 81
    cout << number2 << endl;                          // 81
    return 0;
}

int &squareRef(int &rNumber)
{
    cout << "In squareRef(): " << &rNumber << endl; // 0x22ff14
    rNumber *= rNumber;
    return rNumber;
}

int *squarePtr(int *pNumber)
{
    cout << "In squarePtr(): " << pNumber << endl; // 0x22ff10
    *pNumber *= *pNumber;
    return pNumber;
}
/*

//This program has a serious logical error, as local variable of function is passed back as return value by reference.
 Local variable has local scope within the function, and its value is destroyed after the function exits.

int * squarePtr_2(int number) {
   int localResult = number * number;
   return &localResult;
   //address of stack memory associated with local variable 'localResult' returned
}

int & squareRef_2(int number) {
   int localResult = number * number;
   return localResult;
//reference to stack memory associated with local variable 'localResult' returned
}

//Passing Dynamically Allocated Memory as Return Value by Reference
int * squarePtr(int number) {
   int * dynamicAllocatedResult = new int(number * number);
   return dynamicAllocatedResult;
}

int & squareRef(int number) {
   int * dynamicAllocatedResult = new int(number * number);
   return *dynamicAllocatedResult;
}
*/


// #include <cinttypes>
using std::cout;
using std::endl;

// C-string (of the C language) is a character array, terminated with a null character '\0'.

// Dynamic Memory Allocation
//Static allocated entities are manipulated through named variables. Dynamic allocated entities are handled through pointers.

int *p1, *p2; // Global int pointers

// This function allocates storage for the int*
// which is available outside the function
void allocate()
{
    p1 = new int;     // Allocate memory, initial content unknown
    *p1 = 88;         // Assign value into location pointed to by pointer
    p2 = new int(99); // Allocate and initialize
}

int main_dynamicAllocation()
{
    allocate();
    cout << *p1 << " ";  // 88
    cout << *p2 << endl; // 99
    delete p1;           // Deallocate
    delete p2;

    //  new and delete Operators
    const int SIZE = 5;
    int *pArray;

    pArray = new int[SIZE]; // Allocate array via new[] operator

    // Assign random numbers between 0 and 99
    for (int i = 0; i < SIZE; ++i)
    {
        *(pArray + i) = rand() % 100;
    }
    // Print array
    for (int i = 0; i < SIZE; ++i)
    {
        cout << *(pArray + i) << " ";
    }
    cout << endl;

    // C++03 does not allow your to initialize the dynamically-allocated array.
    int *p = new int[SIZE]{1, 2, 3, 4, 5}; //C++11 does with the brace initialization
    for (int i = 0; i < SIZE; i++)
    {
        cout << p[i] << " ";
    }
    delete[] pArray; // Deallocate array via delete[] operator
    return 0;
}

// Function prototypes
int max(const int arr[], int size);
void replaceByMax(int arr[], int size);
void print(const int arr[], int size);

void fun(const int *arr, int size);
int count(const char *str, const char c); // No need to pass the array size

//Array is Treated as Pointer
int main_ArrayAsAPointer()
{
    const int SIZE = 5;
    int numbers[SIZE] = {11, 22, 44, 21, 41}; // An int array
    // The array name numbers is an int pointer, pointing at the first item of the array,
    // i.e., numbers = &numbers[0]
    cout << &numbers[0] << endl;    // Print address of first element (0x22fef8)
    cout << numbers << endl;        // Same as above (0x22fef8)
    cout << *numbers << endl;       // Same as numbers[0] (11)
    cout << *(numbers + 1) << endl; // Same as numbers[1] (22)
    cout << *(numbers + 4) << endl; // Same as numbers[4] (41)

    int *iPtr = numbers;
    cout << iPtr << endl;        // 0x22cd30
    cout << iPtr + 1 << endl;    // 0x22cd34 (increase by 4 - sizeof int)
    cout << *iPtr << endl;       // 11
    cout << *(iPtr + 1) << endl; // 22
    cout << *iPtr + 1 << endl;   // 12

    cout << "sizeof in main is " << sizeof(numbers) << endl; // Size of entire array in bytes (20)
    fun(numbers, SIZE);                                        //sizeof in function is 8

    cout << sizeof(numbers[0]) << endl;                                       // Size of first element of the array in bytes (4)
    cout << "Array size is " << sizeof(numbers) / sizeof(numbers[0]) << endl; // (5)

    // Passing array in/out function
    cout << max(numbers, SIZE) << endl;
    replaceByMax(numbers, SIZE);
    print(numbers, SIZE);

    //C-string

    char msg1[] = "Hello";
    // char *msg2 = "Hello"; // warning: deprecated conversion from string literal to 'char*'

    cout << strlen(msg1) << endl; // 5
    cout << strlen("Hello") << endl;

    cout << count(msg1, 'l') << endl;           //2
    cout << count("Hello, world", 'l') << endl; //3
    return 0;
}

// Function definitions
void fun(const int *arr, int size)
{
    /*
    In main, the sizeof array is 20 (4 bytes per int, length of 5).
    Inside the function, the sizeof is 4, which is the sizeof int pointer (4-byte address).
    This is why you need to pass the size into the function.
    */
    cout << "sizeof in function is " << sizeof(arr) << endl;
    cout << "address in function is " << arr << endl;
}

// Return the maximum value of the given array.
// The array is declared const, and cannot be modified inside the function.
int max(const int arr[], int size)
{
    int max = arr[0];
    for (int i = 1; i < size; ++i)
    {
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}

/*
//using pointer notation
int max(const int *arr, int size) {
   int max = *arr;
   for (int i = 1; i < size; ++i) {
      if (max < *(arr+i)) max = *(arr+i);
   }
   return max;
}
*/

// Replace all elements of the given array by its maximum value
// Array is passed by reference. Modify the caller's copy.
void replaceByMax(int arr[], int size)
{
    int maxValue = max(arr, size);
    for (int i = 0; i < size; ++i)
    {
        arr[i] = maxValue;
    }
}

// Print the array's content
void print(const int arr[], int size)
{
    cout << "{";
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i];
        if (i < size - 1)
            cout << ",";
    }
    cout << "}" << endl;
}

// Count the occurrence of c in str
// No need to pass the size of char[] as C-string is terminated with '\0'
int count(const char *str, const char c)
{
    int count = 0;
    while (*str)
    { // same as (*str != '\0')
        if (*str == c)
            ++count;
        ++str;
    }
    return count;
}

//Function Pointer
/*
    In C/C++, functions, like all data items, have an address.
    The name of a function is the starting address where the function resides in the memory, and therefore, can be treated as a pointer.

// Function-pointer declaration
return-type (* function-ptr-name) (parameter-list)

// Examples
double (*fp)(int, int)  // fp points to a function that takes two ints and returns a double (function-pointer)
double *dp;             // dp points to a double (double-pointer)
double *fun(int, int)   // fun is a function that takes two ints and returns a double-pointer

double f(int, int);  // f is a function that takes two ints and returns a double
fp = f;  // Assign function f to fp function-pointer

*/

int arithmetic(int, int, int (*)(int, int));
// Take 3 arguments, 2 int's and a function pointer
//   int (*)(int, int), which takes two int's and return an int
int add(int, int);
int sub(int, int);

int add(int n1, int n2) { return n1 + n2; }
int sub(int n1, int n2) { return n1 - n2; }

int arithmetic(int n1, int n2, int (*operation)(int, int))
{
    return (*operation)(n1, n2);
}

int main_funPtr()
{
    int number1 = 5, number2 = 6;
    // add
    cout << arithmetic(number1, number2, add) << endl;
    // subtract
    cout << arithmetic(number1, number2, sub) << endl;
    return 0;
}
/*
//A void pointer can hold address of any data type (except function pointer).
We cannot operate on the object pointed to by void pointer, as the type is unknown.
We can use a void pointer to compare with another address.
*/


int main_pointerConsts()
{
    //1.Non-constant pointer to constant data:
    //Data pointed to CANNOT be changed; but pointer CAN be changed to point to another data.
    int i1 = 8, i2 = 9;
    const int * iptr1 = &i1;  // non-constant pointer pointing to constant data
    // *iptr1 = 9;   // error: assignment of read-only location
    iptr1 = &i2;  // okay
    cout<<iptr1<<endl;//0x7ffee2d755b4

    //2. Constant pointer to non-constant data:
    //Data pointed to CAN be changed; but pointer CANNOT be changed to point to another data.

    int * const iptr2 = &i1;  // constant pointer pointing to non-constant data
                         // constant pointer must be initialized during declaration
    *iptr2 = 9;   // okay
    // iptr2 = &i2;  // error: assignment of read-only variable
    cout<<iptr2<<endl;//0x7ffee2d755b8

    //3. Constant pointer to constant data:
    //Data pointed to CANNOT be changed; and pointer CANNOT be changed to point to another data.
    const int * const iptr3 = &i1;  // constant pointer pointing to constant data
    // *iptr3 = 9;   // error: assignment of read-only variable
    // iptr3 = &i2;  // error: assignment of read-only variable
    cout<<iptr3<<endl; //0x7ffee2d755b8

    // 4. Non-constant pointer to non-constant data:
    //Data pointed to CAN be changed; and pointer CAN be changed to point to another data.
    int * iptr4 = &i1;  // non-constant pointer pointing to non-constant data
    *iptr4 = 9;   // okay
    iptr4 = &i2;  // okay
    cout<<iptr4<<endl; //0x7ffee2d755b4
    return 0;
}

int main()
{
    main_Pointers_1();
    main_References_1();
    main_PassByValue_PassByRef();
    main_constRef();
    main_ReturnRefToLocal();
    main_dynamicAllocation();
    main_ArrayAsAPointer();
    main_funPtr();
    main_pointerConsts();
    return 0;
}
