// Creating a Template Function
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef CASSERT
#define CASSERT
#include <cassert>
#endif

using std::cout;
using std::endl;
using std::ostream;

//creating Singletons
// The Singleton class template contains a static pointer to an abstract type that can be used to represent any type of class you like

template <typename T>
class Singleton
{
  private:
    static T *m_Instance;

  public:
    Singleton()
    {
        assert(m_Instance == nullptr);
        m_Instance = static_cast<T *>(this);
    }
    virtual ~Singleton()
    {
        m_Instance = nullptr;
    }
    static T &GetSingleton()
    {
        return *m_Instance;
    }
    static T *GetSingletonPtr()
    {
        return m_Instance;
    }
};

template <typename T>
T *Singleton<T>::m_Instance = nullptr;

class Manager : public Singleton<Manager>
{
  public:
    void Print() const
    {
        cout << "Singleton Manager Successfully Printing!";
    }
};
int main_singletonTemplate()
{
    new Manager();
    Manager &manager{Manager::GetSingleton()};
    manager.Print();
    delete Manager::GetSingletonPtr();
    return 0;
}

// Calculating Values at Compile Time to avoid computing them at runtime
unsigned int SDBMHash(const std::string &key)
{
    unsigned int result{0};
    for (unsigned int character : key)
    {
        result = character + (result << 6) + (result << 16) - result;
    }
    return result;
}

int main_SDBMHash()
{
    std::string data{"Bruce Sutherland"};
    unsigned int sdbmHash{SDBMHash(data)};
    cout << "The hash of " << data << " is " << sdbmHash;
    return 0;
}

//  replacing this function with a template metaprogram.
template <int stringLength>
struct SDBMCalculator
{
    constexpr static unsigned int Calculate(const char *const stringToHash, unsigned int &value)
    {
        unsigned int character{
            SDBMCalculator<stringLength - 1>::Calculate(stringToHash, value)};
        value = character + (value << 6) + (value << 16) - value;
        return stringToHash[stringLength - 1];
    }
    constexpr static unsigned int CalculateValue(const char *const stringToHash)
    {
        unsigned int value{};
        unsigned int character{SDBMCalculator<stringLength>::Calculate(stringToHash, value)};
        value = character + (value << 6) + (value << 16) - value;
        return value;
    }
};
template <>
struct SDBMCalculator<1>
{
    constexpr static unsigned int Calculate(const char *const stringToHash, unsigned int &value)
    {
        return stringToHash[0];
    }
};
constexpr unsigned int sdbmHash{SDBMCalculator<16>::CalculateValue("Bruce Sutherland")};

int main_templateMetaProgram()
{
    cout << "The hash of Bruce Sutherland is " << sdbmHash << endl;
    return 0;
}

int main()
{
    main_SDBMHash();
    main_singletonTemplate();
    main_templateMetaProgram();
    return 0;
}