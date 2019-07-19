#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional>
#endif

#ifndef ALGORITHM
#define ALGORITHM
#include <algorithm>
#endif

#ifndef NUMERIC
#define NUMERIC
#include <numeric>
#endif

#ifndef CMATH
#define CMATH
#include <cmath>
#endif

#ifndef CTIME
#define CTIME
#include <ctime>
#endif

#ifndef ITERATOR
#define ITERATOR
#include <iterator>
#endif

#ifndef CSTDLIB
#define CSTDLIB
#include <cstdlib>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#include "bitset_arithmetic.hpp"
#include "big_int.hpp"

#ifndef COMPLEX
#define COMPLEX
#include <complex>
#endif

using std::bitset;
using std::cin;
using std::complex;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::polar;
using std::string;
using std::vector;


double doubleRand()
{
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

int main_RandomNumbers()
{
    srand(static_cast<unsigned int>(clock()));
    cout << "expect 5 numbers within the interval [0.0, 1.0)" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << doubleRand() << "\n";
    }
    cout << endl;
    return 0;
}

//Initializing a Container with Random Numbers

struct RndIntGen
{
    RndIntGen(int l, int h)
        : low(l), high(h)
    {
    }
    int operator()() const
    {
        return low + (rand() % ((high - low) + 1));
    }

  private:
    int low;
    int high;
};

/*
// Sample implementations of generate and generate_n
template <class Iter_T, class Fxn_T>
void generate(Iter_T first, Iter_T last, Fxn_T f)
{
    while (first != last)
        *first++ = f();
}
template <class Iter_T, class Fxn_T>
void generate_n(Iter_T first, int n, Fxn_T f)
{
    for (int i = 0; i < n; ++i)
        *first++ = f();
}
*/

int main_FillingAContainer()
{
    srand(static_cast<unsigned int>(clock()));
    vector<int> v(5);
    generate(v.begin(), v.end(), RndIntGen(1, 6));
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\n"));
    return 0;
}

// Using complex template class to represent polar coordinates
int main_polarCoordinates()
{
    double rho = 3.0;            // magnitude
    double theta = 3.141592 / 2; // angle
    complex<double> coord = polar(rho, theta);
    cout << "rho = " << abs(coord) << ", theta = " << arg(coord) << endl;
    coord += polar(4.0, 0.0);
    cout << "rho = " << abs(coord) << ", theta = " << arg(coord) << endl;
    return 0;
}

int main_BitSet()
{

    bitset<(unsigned int)10> bits1(string("100010001"));
    bitset<(unsigned int)10> bits2(string("000000011"));
    // bitsetAdd(bits1, bits2);//ToDo: ??? Error: //no instance of function template "bitsetAdd" matches the argument list -- argument types are: (std::__1::bitset<10UL>, std::__1::bitset<10UL>)
    cout << bits1.to_string<char, std::char_traits<char>, std::allocator<char>>() << endl;
    return 0;
}

// //Representing Large Fixed-Width Integers //ToDo: fix Compilation errors
// void outputBigInt(BigInt<1024> x)
// {
//     vector<int> v;
//     if (x == 0)
//     {
//         cout << 0;
//         return;
//     }
//     while (x > 0)
//     {
//         v.push_back((x % 10).toUlong());
//         x /= 10;
//     }
//     copy(v.rbegin(), v.rend(), ostream_iterator<int>(cout, ""));
//     cout << endl;
// }
// int mainBigInt()
// {
//     BigInt<1024> n(1);
//     // compute 32 factorial
//     for (int i = 1; i <= 32; ++i)
//     {
//         n = n*i;
//     }
//     outputBigInt(n);
// }

template <int E>
struct BasicFixedReal
{
    typedef BasicFixedReal self;
    static const int factor = 1 << (E - 1);
    BasicFixedReal() : m(0) {}
    BasicFixedReal(double d) : m(static_cast<int>(d * factor)) {}
    self &operator+=(const self &x)
    {
        m += x.m;
        return *this;
    }
    self &operator-=(const self &x)
    {
        m -= x.m;
        return *this;
    }
    self &operator*=(const self &x)
    {
        m *= x.m;
        m >>= E;
        return *this;
    }
    self &operator/=(const self &x)
    {
        m /= x.m;
        m *= factor;
        return *this;
    }
    self &operator*=(int x)
    {
        m *= x;
        return *this;
    }
    self &operator/=(int x)
    {
        m /= x;
        return *this;
    }
    self operator-() { return self(-m); }
    double toDouble() const { return double(m) / factor; }
    // friend functions
    friend self operator+(self x, const self &y) { return x += y; }
    friend self operator-(self x, const self &y) { return x -= y; }
    friend self operator*(self x, const self &y) { return x *= y; }
    friend self operator/(self x, const self &y) { return x /= y; }
    // comparison operators
    friend bool operator==(const self &x, const self &y) { return x.m == y.m; }
    friend bool operator!=(const self &x, const self &y) { return x.m != y.m; }
    friend bool operator>(const self &x, const self &y) { return x.m > y.m; }
    friend bool operator<(const self &x, const self &y) { return x.m < y.m; }
    friend bool operator>=(const self &x, const self &y) { return x.m >= y.m; }
    friend bool operator<=(const self &x, const self &y) { return x.m <= y.m; }

  private:
    int m;
};

typedef BasicFixedReal<10> FixedReal;

int main_FixedRealNum()
{
    FixedReal x(0);
    for (int i = 0; i < 100; ++i)
    {
        x += FixedReal(0.0625);
    }
    cout << x.toDouble() << endl;

    return 0;
}

int main()
{
    main_BitSet();
    main_FillingAContainer();
    main_FixedRealNum();
    main_polarCoordinates();
    main_RandomNumbers();

    return 0;
}