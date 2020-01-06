#include <iostream>
#include <vector>
#include <string>


using std::vector;
using std::cout;
using std::endl;

using std::string;


class Fibonacci {

public:

  //Basic recursion   
  virtual int CalculateFibonacci(int n) {
    if (n < 2) {
      return n;
    }
    return CalculateFibonacci(n - 1) + CalculateFibonacci(n - 2);
  }


    // Top-down with Memoization #
    virtual int CalculateFibonacciMemoization(int n) {
        vector<int> memoize(n + 1, 0);
        return CalculateFibonacciRecursive(memoize, n);
    }

    virtual int CalculateFibonacciRecursive(vector<int> &memoize, int n) {
        if (n < 2) {
        return n;
    }
     // if we have already solved this subproblem, simply return the result from the cache
    if(memoize[n] != 0)
      return memoize[n];
      
    memoize[n] = CalculateFibonacciRecursive(memoize, n - 1) + CalculateFibonacciRecursive(memoize, n - 2);
    return memoize[n];
  } 
    // Bottom-up with Tabulation #
  virtual int CalculateFibonacciTabulation(int n) {
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }

  // Memory optimization 
  int CalculateFibonacciTabulationWithMemOptimization(int n) {
    if (n < 2) {
      return n;
    }
    int n1 = 0, n2 = 1, temp;
    for (int i = 2; i <= n; i++) {
      temp = n1 + n2;
      n1 = n2;
      n2 = temp;
    }
    return n2;
  }



};

int main(int argc, char *argv[]) {
  Fibonacci *fib = new Fibonacci();
  cout << "5th Fibonacci is ---> " << fib->CalculateFibonacciMemoization(5) << endl;
  cout << "6th Fibonacci is ---> " << fib->CalculateFibonacciMemoization(6) << endl;
  cout << "7th Fibonacci is ---> " << fib->CalculateFibonacciMemoization(7) << endl;

  cout << "8th Fibonacci is ---> " << fib->CalculateFibonacciTabulation(8) << endl;
  cout << "9th Fibonacci is ---> " << fib->CalculateFibonacciTabulation(9) << endl;
  
  cout<< "10th Fibonacci is ---> " << fib->CalculateFibonacciTabulationWithMemOptimization(10) <<endl;
  cout<< "11th Fibonacci is ---> " << fib->CalculateFibonacciTabulationWithMemOptimization(11) <<endl;

  delete fib;

  return 0;
}