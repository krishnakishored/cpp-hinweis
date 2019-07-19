#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "matrix.hpp"
#endif

#ifndef KMATRIX_HPP
#define KMATRIX_HPP
#include "kmatrix.hpp"
#endif

using std::accumulate;
using std::cout;
using std::endl;

int main_dynamicMatrix()
{

    //dynamically sized array
    valarray<int> v1(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;
    cout << v1[0] << ", " << v1[1] << ", " << v1[2] << endl;
    v1 = v1 + v1;
    cout << v1[0] << ", " << v1[1] << ", " << v1[2] << endl;
    v1 /= 2;
    cout << v1[0] << ", " << v1[1] << ", " << v1[2] << endl;

    // constant-sized numerical vectors
    kvector<int, 4> kv = {{1, 2, 3, 4}}; //suggest braces around initialization of subobject [-Wmissing-braces]
    cout << "sum = " << accumulate(kv.begin(), kv.end(), 0) << endl;
    kv *= 3;
    cout << "sum = " << accumulate(kv.begin(), kv.end(), 0) << endl;
    kv += 1;
    cout << "sum = " << accumulate(kv.begin(), kv.end(), 0) << endl;

    //Dynamically sized matrix
    matrix<int> m(2, 2);
    m = 0;
    m[0][0] = 1;
    m[1][1] = 1;
    m *= 2;
    cout << "(" << m[0][0] << "," << m[0][1] << ")" << endl;
    cout << "(" << m[1][0] << "," << m[1][1] << ")" << endl;

    return 0;
}

template <class Iter_T>
void outputRowOrColumn(Iter_T iter, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << iter[i] << " ";
    }
    cout << endl;
}
template <class Matrix_T>
void initializeMatrix(Matrix_T &m)
{
    int k = 0;
    for (int i = 0; i < m.rows(); ++i)
    {
        for (int j = 0; j < m.cols(); ++j)
        {
            m[i][j] = k++;
        }
    }
}
template <class Matrix_T>
void outputMatrix(Matrix_T &m)
{
    for (int i = 0; i < m.rows(); ++i)
    {
        cout << "Row " << i << " = ";
        outputRowOrColumn(m.row(i), m.cols());
    }
    for (int i = 0; i < m.cols(); ++i)
    {
        cout << "Column " << i << " = ";
        outputRowOrColumn(m.col(i), m.rows());
    }
}

//constant sized matrix
int main_FixedSizedMatrix() 
{
  kmatrix<int, 2, 4> m;
  initializeMatrix(m);
  m *= 2;
  outputMatrix(m);
  return 0;
}

template <class Iter_T, class Iter2_T>
double vectorDistance(Iter_T first, Iter_T last, Iter2_T first2)
{
    double ret = 0.0;
    while (first != last)
    {
        double dist = (*first++) - (*first2++);
        ret += dist * dist;
    }
    return ret > 0.0 ? sqrt(ret) : 0.0;
}

template <class Value_T>
struct DiffSquared
{
    Value_T operator()(Value_T x, Value_T y) const
    {
        return (x - y) * (x - y);
    }
};
template <class Iter_T, class Iter2_T>
double vectorDistance_2(Iter_T first, Iter_T last, Iter2_T first2)
{
    double ret = inner_product(first, last, first2, 0.0L, std::plus<double>(), DiffSquared<double>());
    return ret > 0.0 ? sqrt(ret) : 0.0;
}

template <typename Iter_T>
long double vectorNorm(Iter_T first, Iter_T last)
{
    return sqrt(std::inner_product(first, last, first, 0.0L));
}

//computing the dot product
int main_dotproduct()
{
    int v1[] = {1, 2, 3};
    int v2[] = {4, 6, 8};
    cout << "the dot product of (1,2,3) and (4,6,8) is ";
    cout << std::inner_product(v1, v1 + 3, v2, 0) << endl;

    // Computing the norm(the length)of a vector
    int v[] = {3,4};
    cout << "The length of the vector (3,4) is ";
    cout << vectorNorm(v, v + 2) << endl;


    int v3[] = { 1, 5 };
    int v4[] = { 4, 9 };
    cout << "distance between vectors (1,5) and (4,9) is "; 
    cout << vectorDistance(v3, v3 + 2, v4) << endl;
    cout<<"using inner_product: ";
    cout << vectorDistance_2(v3, v3 + 2, v4) << endl;


    return 0;
}


int main(){
    main_dotproduct();
    main_dynamicMatrix();
    main_FixedSizedMatrix();
    return 0;
}