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

//https://www.hackerrank.com/challenges/virtual-functions/problem

using std::cin;

class Person{
// private:
public:
  std::string name;
  int age;
  virtual void getdata()=0;
  virtual void putdata()=0;
};

class Professor : public Person
{
private:
  int publication;
  int cur_id;
  static int prof_counter;
public:
  void getdata() override
   {
    //  std::string name,int age,int publication
    cin>>this->name >> age >> publication;
    // this->cur_id = ++prof_counter;
  }
  void putdata() override
  {
    std::cout<<this->name << " " <<this->age<< " " << this->publication << " " << this->cur_id << "\n";
  }
  Professor(){
    prof_counter++;
    this->cur_id = prof_counter;
  }
  
};
int Professor::prof_counter = 0;

class Student : public Person
{
   int marks[6];
   int cur_id;
   static int student_counter;
   int sum;
public:
  void getdata() override
  {
    cin>>this->name>>age;
    this->sum = 0;
    for(int i=0;i<6;i++){
      cin>>this->marks[i];
      this->sum+=this->marks[i];
    }
  }
  
  void putdata() override
  {
    
    std::cout<<this->name << " " <<this->age<< " " << this->sum << " " << this->cur_id<< "\n";
  }

  Student()
  {
    student_counter++;
    this->cur_id = student_counter;
  }

};

int Student::student_counter = 0;

int main_HR_virtualFunction()
{

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}




int main()
{
  // main_interfaces();
  // main_polymorphism_2();
  main_HR_virtualFunction();
  return 0;
}