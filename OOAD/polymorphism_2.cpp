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

//Creating interfaces
class Vehicle_interface
{
  public:
    Vehicle_interface() = default;
    //pure virtual method:  This has the effect of ensuring that an object of type Vehicle can never be created.
    virtual uint32_t GetNumberOfWheels() const = 0;
};
class Car_interface : public Vehicle_interface
{
  public:
    Car_interface() = default;
    uint32_t GetNumberOfWheels() const override
    {
        return 4;
    }
};
class Motorcycle_interface : public Vehicle_interface
{
  public:
    Motorcycle_interface() = default;
    uint32_t GetNumberOfWheels() const override
    {
        return 2;
    }
};

int main_interfaces()
{
    Vehicle_interface *pVehicle{};
    Car_interface myCar{};
    pVehicle = &myCar;
    cout << "A car has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
    Motorcycle_interface myMotorcycle;
    pVehicle = &myMotorcycle;
    cout << "A motorcycle has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
    return 0;
}

// You can derive a class from multiple parents in C++ using a comma-separated list of parent classes.

class Printable
{
  public:
    virtual void Print() = 0;
};

class Vehicle
{
  public:
    Vehicle() = default;
    virtual uint32_t GetNumberOfWheels() const = 0;
};

class Car : public Vehicle, public Printable
{
  public:
    Car() = default;
    uint32_t GetNumberOfWheels() const override
    {
        return 4;
    }

    void Print() override
    {
        cout << "A car has " << GetNumberOfWheels() << " wheels." << endl;
    }
};

class Motorcycle: public Vehicle, public Printable
{
  public:
    Motorcycle() = default;
    uint32_t GetNumberOfWheels() const override
    {
        return 2;
    }
    void Print() override
    {
        cout << "A motorcycle has " << GetNumberOfWheels() << " wheels." << endl;
    }
};


int main_polymorphism_2()
{
    Printable *pPrintable{};
    Car myCar{};
    pPrintable = &myCar;
    pPrintable->Print();
    Motorcycle myMotorcycle;
    pPrintable = &myMotorcycle;
    pPrintable->Print();
    return 0;
}

int main(){
  main_interfaces();
  main_polymorphism_2();
  return 0;
}