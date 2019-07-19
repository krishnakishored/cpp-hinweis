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

#ifndef ALGORITHM
#define ALGORITHM
#include <algorithm>
#endif

#ifndef NUMERIC
#define NUMERIC
#include <numeric>
#endif

#ifndef ITERATOR
#define ITERATOR
#include <iterator>
#endif

#ifndef STDEXCEPT
#define STDEXCEPT
#include <stdexcept>
#endif


#ifndef CMATH
#define CMATH
#include <cmath>
#endif

using std::cin;
using std::cout;
using std::endl;
using std::istream_iterator;
using std::vector;


//Generic function for returning the minimum and maximum value
template <class Iter_T, class Value_T>
void computeMinAndMax(Iter_T first, Iter_T last, Value_T &min, Value_T &max)
{
    min = *min_element(first, last); //returns iterator & hence dereferenced
    max = *max_element(first, last);
}

// Finding the maximum element for user-defined types
struct ChessPlayer
{
    ChessPlayer(const char *name, int rating) : name_(name), rating_(rating)
    {
    }
    const char *name_;
    int rating_;
};

struct IsWeakerPlayer
{
    bool operator()(const ChessPlayer &x, const ChessPlayer &y)
    {
        return x.rating_ < y.rating_;
    }
};

struct OutOfRange
{
    OutOfRange(int min, int max)
        : min_(min), max_(max)
    {
    }
    bool operator()(int x)
    {
        return (x < min_) || (x > max_);
    }
    int min_;
    int max_;
};


int main_ElementCount_MinMax()
{
    vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);

    //Computing the Number of Elements in a Container
    cout << v.size() << endl;
    /*
    When working with iterators, you often don’t have access to the type of the container or to its member functions.
    */
    //cout << distance<vector<int>::iterator>(v.begin(), v.end()) << endl; // distance is template function
    cout << distance(v.begin(), v.end()) << endl;

    //Find the maximum or minimum value in a container.
    int min = -1;
    int max = -1;
    computeMinAndMax(v.begin(), v.end(), min, max);
    cout << "min integer = " << min << endl;
    cout << "max integer = " << max << endl;

    // Finding the maximum element for user-defined types

    ChessPlayer kasparov("Garry Kasparov", 2805);
    ChessPlayer anand("Viswanathan Anand ", 2788);
    ChessPlayer topalov("Veselin Topalov", 2788);
    vector<ChessPlayer> v2;
    v2.push_back(kasparov);
    v2.push_back(anand);
    v2.push_back(topalov);
    cout << "The best player: " << max_element(v2.begin(), v2.end(), IsWeakerPlayer())->name_ << endl;

    v.push_back(6);
    v.push_back(12);
    v.push_back(18);
    v.push_back(24);
    v.push_back(30); 
    cout<<"remove_copy_if:";
    remove_copy_if(v.begin(), v.end(),
            std::ostream_iterator<int>(cout, " "), OutOfRange(10,25));

    return 0;
}


/* //does not work for istreams

//An istream_iterator allows only a single pass over the data, 
//so you can call either accumulate or distance but once you call either function, 
//the data is invalidated and any further attempts to iterate over the data will likely fail.

template<class Iter_T>
double computeMean(Iter_T first, Iter_T last) {
  return static_cast<double>(accumulate(first, last, 0.0))
    / distance(first, last);
}
*/

template <class Value_T, class Iter_T>
Value_T computeMean(Iter_T first, Iter_T last)
{
    if (first == last)
        throw std::domain_error("mean is undefined");
    Value_T sum{0};
    int cnt = 0;
    while (first != last)
    {
        sum += *first++;
        ++cnt;
    }
    return sum / cnt;
}

//  Computing the sum and mean of a container
int main_Accumulate_istreams()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    int sum = accumulate(v.begin(), v.end(), 0); //numeric
    //The accumulate function generally provides the most efficient and simplest method to find the sum of all the elements in a container.
    double mean = double(sum) / v.size();
    cout << "sum = " << sum << endl;
    cout << "count = " << v.size() << endl;
    cout << "mean = " << mean << endl;

    cout << "please type in several integers separated by newlines" << endl;
    cout << "and terminated by an EOF character (i.e., Ctrl-Z)" << endl;
    double mean2 = computeMean<double>( istream_iterator<int>(cin), istream_iterator<int>());
    cout << "the mean is " << mean2 << endl;
    return 0;
}



template <int N, class T>
T nthPower(T x)
{
    T ret = x;
    for (int i = 1; i < N; ++i)
    {
        ret *= x;
    }
    return ret;
}

template <class T, int N>
struct SumDiffNthPower
{
    SumDiffNthPower(T x) : mean_(x){};
    T operator()(T sum, T current)
    {
        return sum + nthPower<N>(current - mean_);
    }
    T mean_;
};
template <class T, int N, class Iter_T>
T nthMoment(Iter_T first, Iter_T last, T mean)
{
    size_t cnt = distance(first, last);
    return accumulate(first, last, T(), SumDiffNthPower<T, N>(mean)) / cnt;
}
template <class T, class Iter_T>
T computeVariance(Iter_T first, Iter_T last, T mean)
{
    return nthMoment<T, 2>(first, last, mean);
}
template <class T, class Iter_T>
T computeStdDev(Iter_T first, Iter_T last, T mean)
{
    return sqrt(computeVariance(first, last, mean));
}
template <class T, class Iter_T>
T computeSkew(Iter_T begin, Iter_T end, T mean)
{
    T m3 = nthMoment<T, 3>(begin, end, mean);
    T m2 = nthMoment<T, 2>(begin, end, mean);
    return m3 / (m2 * sqrt(m2));
}

template <class T, class Iter_T>
T computeKurtosisExcess(Iter_T begin, Iter_T end, T mean)
{
    T m4 = nthMoment<T, 4>(begin, end, mean);
    T m2 = nthMoment<T, 2>(begin, end, mean);
    return m4 / (m2 * m2) - 3;
}
template <class T, class Iter_T>
void computeStats(Iter_T first, Iter_T last, T &sum, T &mean,
                  T &var, T &std_dev, T &skew, T &kurt)
{
    size_t cnt = distance(first, last);
    sum = accumulate(first, last, T());
    mean = sum / cnt;
    var = computeVariance(first, last, mean);
    std_dev = sqrt(var);
    skew = computeSkew(first, last, mean);
    kurt = computeKurtosisExcess(first, last, mean);
}

/*
// Sample implementation of accumulate
template <class Iter_T, class Value_T, class BinOp_T>
Iter_T accumulate(Iter_T begin, Iter_T end, Value_T value, BinOp_T op)
{
    while (begin != end)
    {
        value = op(value, *begin++)
    }
    return value;
}
*/

int main_statisticalFunctions()
{
    vector<int> v;
    v.push_back(2);
    v.push_back(4);
    v.push_back(8);
    v.push_back(10);
    v.push_back(99);
    v.push_back(1);
    double sum, mean, var, dev, skew, kurt;
    computeStats(v.begin(), v.end(), sum, mean, var, dev, skew, kurt);
    cout << "count = " << v.size() << "\n";
    cout << "sum = " << sum << "\n";
    cout << "mean = " << mean << "\n";
    cout << "variance = " << var << "\n";
    cout << "standard deviation = " << dev << "\n";
    cout << "skew = " << skew << "\n";
    cout << "kurtosis excess = " << kurt << "\n";
    cout << endl;

    return 0;
}

int main()
{
    main_Accumulate_istreams();
    main_ElementCount_MinMax();
    main_statisticalFunctions();
    return 0;
}