// C++ Recipes - Inheritance

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

// #include <cinttypes>
using std::cout;
using std::endl;
using std::string;

class Vehicle
{
  public:
    Vehicle() = default;
    // virtual uint32_t GetNumberOfWheels() const final // prevents the classes from overriding the method
    virtual uint32_t GetNumberOfWheels() const
    {
        return 2;
    }
};
class Car : public Vehicle
{
  public:
    Car() = default;

    // override keyword (optional) is a hint to the compiler that you expect this method to override a virtual method in the parent class. 
    uint32_t GetNumberOfWheels() const override
    {
        return 4;
    }
};
class Motorcycle : public Vehicle
{
  public:
    Motorcycle() = default;
};

class Bus: public Vehicle
{
    public:
    Bus()=default;
    uint32_t GetNumberOfWheels() const final
    {
        return 6;
    }

};

// class Volvo: public Bus
class Volvo: public Vehicle
{
public:
    Volvo()= default;
    uint32_t GetNumberOfWheels() const  //can't override Bus.GetNumberOfVehicles as its declared final
    {
        return 8;
    }
};


int main_polymorphism_1()
{
    Vehicle *pVehicle{};
    Vehicle myVehicle{};
    pVehicle = &myVehicle;
    cout << "A vehicle has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
    Car myCar{};
    pVehicle = &myCar;
    cout << "A car has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
    Motorcycle myMotorcycle;
    pVehicle = &myMotorcycle;
    cout << "A motorcycle has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;

    Volvo myVolvo{};
    pVehicle = &myVolvo;
    cout << "A volvo has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
    return 0;
}



class Person
{
  public:
    virtual void sleep() = 0;
    virtual void eat() = 0;
    virtual void walk() = 0;
    virtual void jump() = 0;
    virtual void setFirstName(const string &s) { firstName_ = s; }
    virtual void setLastName(const string& s) {lastName_ = s;}
    virtual string getFirstName() {return(firstName_);}
    virtual string getLastName() {return(lastName_);}
  protected:
    string firstName_;
    string lastName_;
};

class IAirborne
{

  public:
    virtual void fly() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
};

class Superhero : public Person, public IAirborne
{
  public:
    virtual void eat();
    virtual void sleep();
    virtual void walk();
    virtual void jump();
    virtual void fly();
    virtual void up(); 
    virtual void down(); 
    virtual string getLastName();
    virtual ~Superhero();
};
// Implement all of the pure virtuals in Superhero's superclasses...
void Superhero::fly() { // ...
    cout<<"fly" << " (Superhero)";
}
void Superhero::eat() { // ...
    cout<<" eat" << " (Superhero)";
}
void Superhero::walk() { // ...
    cout<<" walk" << " (Superhero)";
}
void Superhero::sleep() { // ...
    cout<<" sleep" << " (Superhero)";
}
void Superhero::jump() { // ...
    cout<<" jump" << " (Superhero)";
}
void Superhero::up() { // ...
    cout<<" up" << " (Superhero)";
}
void Superhero::down() { // ...
    cout<<" down" << " (Superhero)";
}
Superhero::~Superhero(){
    // cout<<"dtor (Superhero)";
}
string Superhero::getLastName() 
{
     return(Person::getLastName() + " (Superhero)");
}

int main_Interface_PureVirtualFunction()
{
    Superhero superman;
    superman.walk(); // Superman can walk like a person 
    superman.fly(); // or fly like a bird

    return 0;
}

int main(){
    main_Interface_PureVirtualFunction();
    main_polymorphism_1();
    return 0;
}