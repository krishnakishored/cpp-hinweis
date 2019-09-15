// Creating a Template Function
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

using std::cout;
using std::endl;
using std::ostream;

template <typename T>
T Add(const T &a, const T &b)
{
    return a + b;
}

template <typename T>
void Print(const T &value1, const T &value2, const T &result)
{
    cout << "The result of adding " << value1 << " to " << value2 << " is " << result << endl;
}

int main_templates_1()
{
    const int number1{1};
    const int number2{2};
    const int intResult{Add(number1, number2)};
    // cout << "The result of adding " << number1 << " to " << number2 << " is " << intResult <<endl;
    Print(number1, number2, intResult);

    // const float floatResult{ Add(static_cast<float>(number1), static_cast<float>(number2)) };
    //Print(number1,number2,floatResult);//warning: candidate template ignored: deduced conflicting types for parameter 'T'
    const auto number3{1.1};
    const auto number4{2.9};
    const auto result2{Add(number3, number4)};
    cout << "The result of adding " << number3 << " to " << number4 << " is " << result2 << endl;
    return 0;
}

class MyClass
{
    friend ostream& operator<<(ostream &os, const MyClass &myClass);

  private:
    int m_Value{0};

  public:
    MyClass() = default;
    MyClass(int value) : m_Value{value}
    {
    }
    MyClass(int number1, int number2) : m_Value{number1 + number2}
    {
    }

    int GetValue() const
    {
        return m_Value;
    }

    // MyClass& operator +(const MyClass &other) const
    // {
    //     return m_Value + other.m_Value; //initial value of reference to non-const must be an l-value
    // }
};

ostream &operator<<(ostream &os, const MyClass &myClass)
{
    os << myClass.m_Value;
    return os;
}

// partial template specialization
template <>
MyClass Add(const MyClass &myClass1, const MyClass &myClass2)
{
    return MyClass(myClass1.GetValue(), myClass2.GetValue());
}

template <>
void Print(const MyClass &value1, const MyClass &value2, const MyClass &result)
{
    cout << "The result of adding " << value1.GetValue() << " to " << value2.GetValue() << " is " << result.GetValue() << endl;
}

int main_partialTemplateSpecialization()
{
    const MyClass number1{1};
    const MyClass number2{2};
    const MyClass intResult{Add(number1, number2)};
    Print(number1, number2, intResult);
    // const MyClass doubleResult{ Add(static_cast<MyClass>(number1), static_cast<MyClass>(number2)) };
    // Print(number1, number2, doubleResult);
    return 0;
}

//Creating a Template Class
template <typename T, int numberOfElements>
class MyArray
{
  private:
    T m_Array[numberOfElements];

  public:
    MyArray() : m_Array{} {}

    T &operator[](const unsigned int index)
    {
        return m_Array[index];
    }
};

int main_classTemplate()
{
    const unsigned int ARRAY_SIZE{5};
    MyArray<int, ARRAY_SIZE> myIntArray;
    for (unsigned int i{0}; i < ARRAY_SIZE; ++i)
    {
        myIntArray[i] = i;
    }
    for (unsigned int i{0}; i < ARRAY_SIZE; ++i)
    {
        cout << myIntArray[i] << endl;
    }
    cout << endl;
    MyArray<float, ARRAY_SIZE> myFloatArray;
    for (unsigned int i{0}; i < ARRAY_SIZE; ++i)
    {
        myFloatArray[i] = static_cast<float>(i) + 0.5f;
    }
    for (unsigned int i{0}; i < ARRAY_SIZE; ++i)
    {
        cout << myFloatArray[i] << endl;
    }
    return 0;
}

int main()
{
	main_templates_1();
    main_partialTemplateSpecialization();
    main_classTemplate();
	return 0;
}