#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif


#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#ifndef STRING
#define STRING
#include<string>
#endif

// #include <cinttypes>
using std::cout;
using std::endl;


class Base
{
public:
    virtual void function1() {cout<<"Base fn1()"<<endl;};
    virtual void function2() {cout<<"Base fn2()"<<endl;};
};
 
class D1: public Base
{
public:
    virtual void function1() {cout<<"D1 fn1()"<<endl;};
};
 
class D2: public Base
{
public:
    virtual void function2() {cout<<"D2 fn2()"<<endl;};
};


int main()
{

    Base b;
    Base *bPtr = &b;
    bPtr->function1();
    bPtr->function2();

    D1 d1;
    Base *d1Ptr = &d1;
    d1Ptr->function1();
    d1Ptr->function2();

    D2 d2;
    Base *d2Ptr = &d2;
    d2Ptr->function1();
    d2Ptr->function2();

    return 0;
}