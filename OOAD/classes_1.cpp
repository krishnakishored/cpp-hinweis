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

#include<cstring>

// #include <cinttypes>
using std::cout;
using std::endl;


// The class in Listing 5-10 doesn’t store the value in a uint32_t member; instead, it stores a vector of Wheel objects.
class Wheel{};

class Vehicle_withWheels
{
private:
    using Wheels = std::vector<Wheel>;
    Wheels m_Wheels;

public:
    void SetNumberOfWheels(uint32_t numberOfWheels) // The SetNumberOfWheels method adds a new instance of Wheel to the vector for the number supplied as its numberOfWheels parameter.
    {
        m_Wheels.clear();
        for(uint32_t i=0;i<numberOfWheels;i++){
            m_Wheels.push_back({});//uniform initialization
        }
    }

    uint32_t GetNumberOfWheels()
    {
        return m_Wheels.size();// The GetNumberOfWheels method returns the size of the vector
    }
};

class Vehicle_basic
{

private:
        uint32_t m_NumberOfWheels{};// initialized using uniform initialization
        //  No value is supplied to the initializer, which causes the compiler to initialize the value to 0.

        // uint32_t m_NumberOfWheels;
public:
    //adding a constructor to the class means you can no longer construct default versions of this class;
    //overcome this limitation by adding an explicit default operator to the class.
    Vehicle_basic() = default;
    //ctor
    Vehicle_basic(uint32_t numberOfWheels):m_NumberOfWheels{numberOfWheels}{}
    void SetNumberOfWheels(uint32_t numberOfWheels)
    {
        m_NumberOfWheels = numberOfWheels;
    }
    uint32_t GetNumberOfWheels()
    {
        return m_NumberOfWheels;
    }

};

int main_Vehicle_basic(){
    Vehicle_basic myCar{ 4 };
    cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;
    Vehicle_basic myMotorcycle{ 2 };
    cout << "Number of wheels: " << myMotorcycle.GetNumberOfWheels() << endl;
    Vehicle_basic noWheels;
    cout << "Number of wheels: " << noWheels.GetNumberOfWheels() << endl;
    return 0;
}

int main_basic_Vehicle_withWheels()
{
    Vehicle_withWheels myCar;
    cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;//Number of wheels: 0
    // myCar.m_NumberOfWheels = 4;//access error - private member
     myCar.SetNumberOfWheels(4);
    // cout << "Number of wheels: " << myCar.m_NumberOfWheels << endl; // private member
    cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;

    Vehicle_withWheels myMotorcycle;
    myMotorcycle.SetNumberOfWheels(2);
    cout << "Number of wheels: " << myMotorcycle.GetNumberOfWheels() << endl;
    return 0;
}


//cleaning up classes - dtors
class Vehicle_withDestructor
{
private:
    std::string m_Name;
    uint32_t m_NumberOfWheels{};

public:
    Vehicle_withDestructor() = default;
    Vehicle_withDestructor(std::string name, uint32_t numberOfWheels):m_Name{name},m_NumberOfWheels{numberOfWheels}{}
    ~Vehicle_withDestructor(){
        cout << m_Name << " is being destroyed!" << endl;
    }

    // ~Vehicle_withDestructor() = default; // it's a good practice to be explicit

    uint32_t GetNumberOfWheels()
    {
        return m_NumberOfWheels;
    }
};
int main_Vehicle_withDestructor()
{
    Vehicle_withDestructor myCar{ "myCar", 4 };
    cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;
    Vehicle_withDestructor myMotorcycle{ "myMotorcycle", 2 };
    cout << "Number of wheels: " << myMotorcycle.GetNumberOfWheels() << endl;
    Vehicle_withDestructor noWheels;
    cout << "Number of wheels: " << noWheels.GetNumberOfWheels() << endl;
    // The Vehicle objects are destroyed in an order that’s the reverse of that in which they were created.
    return 0;
}


//Copying Classes - using explicit copy ctor & assignment operator
class Vehicle_shallowCopy
{
private:
    std::string m_Name;
    uint32_t m_NumberOfWheels{};
public:
    Vehicle_shallowCopy() = default;
    Vehicle_shallowCopy(std::string name, uint32_t numberOfWheels): m_Name{ name }, m_NumberOfWheels{ numberOfWheels }{}
    ~Vehicle_shallowCopy()
    {
        cout << m_Name << " at " << this << " is being destroyed!" << endl;
    }

    // The default copy and assignment operations carry out a shallow copy.
    Vehicle_shallowCopy(const Vehicle_shallowCopy& other) = default;
    Vehicle_shallowCopy& operator=(const Vehicle_shallowCopy& other) = default;

    //disallowing copy ctor & assignment operator
    // Vehicle(const Vehicle& other) = delete;
    // Vehicle& operator=(const Vehicle& other) = delete;


    uint32_t GetNumberOfWheels()
    {
        return m_NumberOfWheels;
    }
};


int main_Vehicle_shallowCopy(){
    Vehicle_shallowCopy myCar{ "myCar", 4 };
    cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;
    Vehicle_shallowCopy myMotorcycle{ "myMotorcycle", 2 };
    cout << "Number of wheels: " << myMotorcycle.GetNumberOfWheels() << endl;

    Vehicle_shallowCopy myCopiedCar{ myCar }; //fails if copy ctor(=delete) is disallowed
    cout << "Number of wheels: " << myCopiedCar.GetNumberOfWheels() << endl;

    Vehicle_shallowCopy mySecondCopy;
    mySecondCopy = myCopiedCar; // fails if assignment operator(=delete) is disallowed
    cout << "Number of wheels: " << mySecondCopy.GetNumberOfWheels() << endl;
    return 0;
}



class Vehicle
{

private:
    char* m_Name{};//C-Style string member
    uint32_t m_NumberOfWheels{};
public:
    Vehicle() = default;
    Vehicle(const char* name, uint32_t numberOfWheels): m_NumberOfWheels{ numberOfWheels }
    {
        const uint32_t length = strlen(name) + 1; // Add space for null terminator
        m_Name = new char[length]{};
        strcpy(m_Name, name);
    }
    ~Vehicle() {
        delete m_Name;
        m_Name = nullptr;
    }

    // Vehicle(const Vehicle& other) = default;
    // Vehicle& operator=(const Vehicle& other) = default;
    Vehicle(const Vehicle& other){
        const uint32_t length = strlen(other.m_Name)+1;
        m_Name = new char[length]{};
        strcpy(m_Name,other.m_Name);
        m_NumberOfWheels=other.m_NumberOfWheels;
    }

    Vehicle& operator=(const Vehicle& other){
        if(m_Name !=nullptr){
            delete m_Name;
        }
        const uint32_t length = strlen(other.m_Name) + 1; // Add space for null terminator
        m_Name = new char[length]{};
        strcpy(m_Name, other.m_Name);
        m_NumberOfWheels = other.m_NumberOfWheels;
        return *this;

    }


    // If the object you’re copying from is about to destroyed.
    // C++ allows you to optimize such situations using move semantics.


    // Move semantics work by providing class methods that take rvalue references as parameters.
    Vehicle(Vehicle&& other)
    {
        m_Name = other.m_Name;
        other.m_Name = nullptr;
        m_NumberOfWheels = other.m_NumberOfWheels;
    }

    Vehicle& operator=(Vehicle&& other)
    {
        if(m_Name != nullptr){
            delete m_Name;
        }
        m_Name = other.m_Name;
        /*
        The move assignment operator releases the memory that the object may already have been using for m_Name.
        Importantly, it then copies the address from other before setting other.m_Name to nullptr.
        */
        //Setting the other object’s pointer to nullptr prevents that object from deleting the memory in its destructor
        other.m_Name = nullptr;

        m_NumberOfWheels = other.m_NumberOfWheels;
        return *this;
    }

    char* GetName()
    {
        return m_Name;
    }
    uint32_t GetNumberOfWheels()
    {
        return m_NumberOfWheels;
    }

};

int main_Vehicle_MoveSemantics()
{
    Vehicle myAssignedCar;
    {
        Vehicle myCar{ "myCar", 4 };
        cout << "Vehicle name: " << myCar.GetName() << endl;


        // myAssignedCar = myCar;// default assignment operator with shallow copy

        myAssignedCar = std::move(myCar);
        // cout << "Vehicle name: " << myCar.GetName() << endl;//segmentation fault - myCar.m_Name is no longer available after move
        cout << "Vehicle name: " << myAssignedCar.GetName() << endl;
    }
    cout << "Vehicle name: " << myAssignedCar.GetName() << endl;//pointer being freed was not allocated
    return 0;
}

int main(){
    main_basic_Vehicle_withWheels();
    main_Vehicle_basic();
    main_Vehicle_MoveSemantics();
    main_Vehicle_shallowCopy();
    main_Vehicle_withDestructor();


    return 0;
}