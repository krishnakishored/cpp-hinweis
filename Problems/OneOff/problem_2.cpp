// Add this to Project Properties -std=c++14

// https://www.udemy.com/introduction-to-algorithms-and-data-structures-in-c/learn/lecture/5409386#overview

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <ctime>
#include <cmath>

#include <iomanip> // std::setprecision
#include <fstream>

using std::cout;
using std::fixed;
using std::max;
using std::pow;
using std::setprecision;
using std::swap;

using std::ifstream;
using std::ofstream;

int main_sumUsingFStreams()
{
    ifstream f("data.in");
    ofstream g("data.out");

    int a, b, sum;
    f >> a >> b;
    sum = a + b;
    g << sum;
    return 0;
}

int main_sampleStdFunctions()
{
    int a = 5, b = 8, maximum;
    maximum = max(a, b);
    //double pow(double base, double exponent);
    double cubicRoot;
    cubicRoot = pow((double)a, 1.0 / 3); // pow takes only double
    cout << cubicRoot << "\n";
    cout << fixed << setprecision(2) << cubicRoot << "\n";
    swap(a, b);
    cubicRoot = pow((double)a, 1.0 / 3); // pow takes only double
    cout << cubicRoot << "\n";
    cout << fixed << setprecision(10) << cubicRoot << "\n";
    return 0;
}

int main_appearanceArray_countingSort()
{

    ifstream f("./DataFiles/data.in");
    ofstream g("./DataFiles/data.out");
    int appearanceArray[100], inputSize = 0, maximum = 0; // we have used numbers from [-10, 10]
    // if you don't know the interval of the input numbers, find the minimum number in the input
    // and add it to all numbers (instead of 10 used in this source)

    /** Input
        10 
        -8 -1 6 -10 -3 4 10 -9 2 -4
     */

    f >> inputSize;
    for (int i = 0; i < inputSize; ++i)
    {
        int x;
        f >> x;
        x = x + 10; // -10 is the smallest in the array. we add 10 to make it 0
        ++appearanceArray[x];
        maximum = max(maximum, x); //find max of appearanceArray
    }
    int key = -8; // element to find in the array
    if (appearanceArray[key + 10] > 0)
        g << "YES, it appears\n";
    else
        g << "NO, it's not\n";

    //use the appearance array to sort the sequence - Counting Sort
    for (int i = 0; i < maximum; i++)
    {
        if (appearanceArray[i] > 0)
        {
            for (int j = 0; j < appearanceArray[i]; j++)
            {
                g << i - 10 << " ";
            }
        }
    }
    /** output
        YES, it appears
        -10 -9 -8 -4 -3 -1 2 4 6 
     */
    return 0;
}

int main_marsTrickery()
{
    /** 
     * It's given an array (indexed from 1) of N elements on which we make M queries:
        add(Left, Right, X) - all the elements between the position Left and Right
        (1<=Left<=Right<=N) are raising their values with X.
        After all the operations are completed, print the array.
        Array: 1 1 1 4 5 6 |  operations: (1, 5, 2), (2, 3, 10)
        Final array: 3 13 13 6 7 6
    */
    ifstream f("./DataFiles/data.in");
    ofstream g("./DataFiles/data.out");
    int A[100], B[100], auxB, n, m, Aelements, i, j, Left, Right, X, nrQueries;

    f >> Aelements;

    for (i = 1; i <= Aelements; ++i)
        f >> A[i]; // input_array

    // a=a+b ==  a+=b

    f >> nrQueries;
    for (j = 1; j <= nrQueries; ++j)
    {
        f >> Left >> Right >> X;
        B[Left] += X;
        B[Right + 1] -= X;
    }

    for (i = 1; i <= Aelements; ++i)
    {
        auxB += B[i]; // in auxB we keep the sum B[1] + B[2] + ... + B[i]
        A[i] += auxB;

        g << A[i] << " ";
    }

    return 0;
    /* 
    Input: 
        10
        -8 -1 6 -10 -3 4 10 -9 2 -4
        3
        1 2 10
        2 6 5
        5 9 -2
    
    Output:
        2 14 11 -5 0 7 8 -11 0 -4 
     */

}

int BinarySearch(int A[], int n, int X, int OK)
{
    /*
        A[] - sorted array
        n - size of array
        X - element to search
        OK - first(1) or last(2) occurrence

        - This Binarysearch that also includes an arg to find first or last occurrence,
        - Returns result,  which will have the index
     */

    int Left = 0, Right = n - 1, mid;
    int result = -1;
    while (Left <= Right)
    {
        mid = (Left + Right) / 2;

        if (X == A[mid])
        {
            result = mid;
            if (OK == 1)
                Right = mid - 1; // First occurrence
            if (OK == 2)
                Left = mid + 1; //Last occurrence
        }
        else if (X < A[mid])
            Right = mid - 1;
        else
            Left = mid + 1;
    }
    return result;
}

int main_NumOfOccurrences()
{
    int A[] = {1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 5, 6, 6, 8, 9, 9};
    int elementToFind  = 6;
    int FirstOccurrence = BinarySearch(A, 16, elementToFind, 1);
    int LastOccurrence = BinarySearch(A, 16, elementToFind, 2);

    if (FirstOccurrence == -1)
        cout << "The element is not in the array";
    else
        cout << "The element appears " << LastOccurrence - FirstOccurrence + 1 << " times\n";

    return 0;
}

// int main(){

//     return 0;
// }

int main()
{

    // main_sumUsingFStreams();
    // main_sampleStdFunctions();
    // main_appearanceArray_countingSort();
    main_marsTrickery();
    // main_NumOfOccurrences();
    return 0;
}
