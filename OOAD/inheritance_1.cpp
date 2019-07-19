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

class Vehicle
{
// private:
  protected:
    uint32_t m_NumberOfWheels{};

  public:
    Vehicle(uint32_t numberOfWheels): m_NumberOfWheels{numberOfWheels}{}
    Vehicle()=default;
    uint32_t GetNumberOfWheels() const
    {
        return m_NumberOfWheels;
    }
};


//The Car class and the Motorcycle class both inherit the properties of Vehicle and both set the appropriate number of wheels in their constructor.
class Car : public Vehicle
{
  public:
    Car(): Vehicle(4){}    

    //possible only if Vehicle.m_NumberOfWheels is protected or public
    // Car() {
    //     m_NumberOfWheels = 6;
    // }

};

class Motorcycle : public Vehicle
{
  public:
    Motorcycle(): Vehicle(2){}

    // hide methods in parent classes by defining a method with the same signature in the derived class.
    uint32_t GetNumberOfWheels() const
    {
        return m_NumberOfWheels + 100;
    }
};

// int main_inheritance_1()
int main()
{
    Car myCar{};
    cout << "A car has " << myCar.GetNumberOfWheels() << " wheels." << endl;
    Motorcycle myMotorcycle;
    cout << "A motorcycle has " << myMotorcycle.GetNumberOfWheels() << " wheels." << endl;
    // cout << "A motorcycle has " << myMotorcycle.m_NumberOfWheels << " wheels." << endl;//protected & private: inaccessible from calling code
    return 0;
}