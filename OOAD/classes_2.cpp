// C++ Recipes - Classes

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

#ifndef LIST
#define LIST
#include <list>
#endif

#include<algorithm>

// #include <cinttypes>
using std::cout;
using std::endl;
using std::string;
using std::list;

//Initializing Class member variables
// Members are initialized in the order they are declared in the class declaration, not in the order they are declared in the initializer list.
class Foo
{
  public:
    Foo() : counter_(0), str_(NULL) {}
    Foo(int c, string *p) : counter_(c), str_(p) {
        cout<< counter_ << " " << *str_<<endl; // [-Wunused-private-field]
    }

  private:
    int counter_;
    string *str_;
};

class HasARef{
    public:
        int &ref;
        HasARef(int &aref):ref(aref){}//this is required in case of a ref. is a member variable
};

int main_initializerList()
{
    string s = "bar";
    Foo(2, &s);
    // HasARef me; //the default constructor of "HasARef" cannot be referenced -- it is a deleted function
    return 0;
}

// using a function to create objects - Factory pattern
class Session
{
};

class SessionFactory
{
  public:
    Session Create();
    Session *CreatePtr();
    void Create(Session *&p);
    //..
};

//return a copy of a stack object
Session SessionFactory::Create(){
    Session s;
    return (s);
}

// Return a pointer to a heap object
Session *SessionFactory::CreatePtr()
{
    return (new Session());
}

//Update the caller's pointer with the address of a new object
void SessionFactory::Create(Session *&p)
{
    p = new Session();
}

static SessionFactory f; // The one factory object

int main_FactoryMethod()
{
    Session *p1;
    Session *p2 = new Session();
    *p2 = f.Create();// Just assign the object returned from Create
    p1 = f.CreatePtr();// or return a pointer to a heap object
    f.Create(p1); // or update the pointer with the new address
    return 0;
}



//Automatically Adding New Class Instances to a Container
//Keeping track of objects

class MyClass {
protected:
    int value_;
public:
    static list<MyClass* > instances_;
    MyClass(int val);
    ~MyClass();
    static void showList();
};

list<MyClass*> MyClass::instances_;

MyClass::MyClass(int val){
    instances_.push_back(this);
    value_ = val;
}
MyClass::~MyClass(){
    list<MyClass*>::iterator p = find(instances_.begin(),instances_.end(),this);
    if(p!=instances_.end()){
        instances_.erase(p);
    }
}

void MyClass::showList(){
    for(list<MyClass*>::iterator p = instances_.begin();p!=instances_.end();++p){
        cout<<(*p)->value_<<endl;
    }
}


// Static.h
class OneStatic
{
  public:
    int getCount() { return count; }
    OneStatic();
  protected:
    static int count;
};

int OneStatic::count = 0;
OneStatic::OneStatic()
{
    count++;
}

class Base
{
  public:
    virtual ~Base() {} // Make this a polymorphic class
};
class Derived : public Base
{
  public:
    virtual ~Derived() {}
};

int main_keepTrackOfObjects_staticMember()
{
    MyClass a1(1);
    MyClass b1(10);
    MyClass c1(100);
    MyClass::showList();
    //Ensuring a Single Copy of a Member Variable
    OneStatic a;
    OneStatic b;
    OneStatic c;
    cout << a.getCount() << endl;
    cout << b.getCount() << endl;
    cout << c.getCount() << endl;
    return 0;
}

int main_dynamicCast()
{

    //Using runtime type identification
    Base b2, bb;
    Derived d;
    // Use typeid to test type equality
    if (typeid(b2) == typeid(d))
    { // No
        cout << "b2 and d are of the same type.\n";
    }
    if (typeid(b2) == typeid(bb))
    { // Yes
        cout << "b and bb are of the same type.\n";
    }
    if (typeid(d) == typeid(Derived))
    { // Yes
        cout << "d is of type Derived.\n";
    }
    std::cout << typeid(d).name() << std::endl;
    std::cout << typeid(bb).name() << std::endl;


    //Determining class relationships
    if(dynamic_cast<Base*> (&d)){
        cout << "Derived is a subclass of Base" << endl;
    }
    else{
        cout << "Derived is NOT a subclass of Base" << endl;
    }
    return 0;
}

int main(){
     main_dynamicCast();
     main_FactoryMethod();
     main_initializerList();
     main_keepTrackOfObjects_staticMember();

    return 0;
}