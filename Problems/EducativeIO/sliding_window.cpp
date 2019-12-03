#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::min;
using std::string;
using std::unordered_map;

// Given a string, find the length of the longest substring in it with no more than K distinct characters.




/*
Given an array of positive numbers and a positive number ‘S’, 
find the length of the smallest contiguous subarray whose sum is greater than or equal to ‘S’.
Return 0, if no such subarray exists.


This problem follows the Sliding Window pattern and we can use a similar strategy as discussed in Maximum Sum Subarray of Size K.
There is one difference though: in this problem, the size of the sliding window is not fixed. Here is how we will solve this problem:
First, we will add-up elements from the beginning of the array until their sum becomes greater than or equal to ‘S’.
These elements will constitute our sliding window. We are asked to find the smallest such window having a sum greater than or equal to ‘S’. 
We will remember the length of this window as the smallest window so far.
After this, we will keep adding one element in the sliding window (i.e. slide the window ahead), in a stepwise fashion.
In each step, we will also try to shrink the window from the beginning. We will shrink the window until the window’s sum is smaller than ‘S’ again. 
This is needed as we intend to find the smallest window. This shrinking will also happen in multiple steps; in each step we will do two things:
Check if the current window length is the smallest so far, and if so, remember its length.
Subtract the first element of the window from the running sum to shrink the sliding window.
*/

class MinSizeSubArraySum {
 public:
  static int findMinSubArray(int S, const vector<int>& arr) {
    int windowSum = 0, minLength = numeric_limits<int>::max();
    int windowStart = 0;
    for (int windowEnd = 0; windowEnd < arr.size(); windowEnd++) {
      windowSum += arr[windowEnd];  // add the next element
      // shrink the window as small as possible until the 'windowSum' is smaller than 'S'
      while (windowSum >= S) {
        minLength =  min(minLength, windowEnd - windowStart + 1);
        windowSum -= arr[windowStart];  // subtract the element going out
        windowStart++;                  // slide the window ahead
      }
    }

    return minLength == numeric_limits<int>::max() ? 0 : minLength;
  }
};




// Given an array of positive numbers and a positive number ‘k’, find the maximum sum of any contiguous subarray of size ‘k’.
class MaxSumSubArrayOfSizeK {
 public:
  static int findMaxSumSubArray(int k, const vector<int>& arr) {
    int maxSum = 0;
    // TODO: Write your code here
    int windowStart = 0;
    int windowSum = 0;
    for(int windowEnd=0;windowEnd < arr.size();windowEnd++){
      windowSum += arr[windowEnd];
      if(windowEnd >= k-1){
        maxSum = (maxSum>windowSum)?maxSum:windowSum;
        windowSum -= arr[windowStart];
        windowStart++;
      }
    }

    return maxSum;
  }
};

//Given an array, find the average of all contiguous subarrays of size ‘K’ in it.
class AverageOfSubarrayOfSizeK {
 public:
  static vector<double> findAverages(int K, const vector<int>& arr) {
    vector<double> result(arr.size() - K + 1);
    double windowSum = 0;
    int windowStart = 0;
    for (int windowEnd = 0; windowEnd < arr.size(); windowEnd++) {
      windowSum += arr[windowEnd];  // add the next element
      // slide the window, we don't need to slide if we've not hit the required window size of 'k'
      if (windowEnd >= K - 1) {
        result[windowStart] = windowSum / K;  // calculate the average
        windowSum -= arr[windowStart];        // subtract the element going out
        windowStart++;                        // slide the window ahead
      }
    }

    return result;
  }

  static vector<double> findAverages_brutefor(int K, const vector<int>& arr) {
    vector<double> result(arr.size() - K + 1);
    for (int i = 0; i <= arr.size() - K; i++) {
      // find sum of next 'K' elements
      double sum = 0;
      for (int j = i; j < i + K; j++) {
        sum += arr[j];
      }
      result[i] = sum / K;  // calculate average
    }

    return result;
  }
};




int main(int argc, char* argv[]) {
  vector<double> result =
      AverageOfSubarrayOfSizeK::findAverages(5, vector<int>{1, 3, 2, 6, -1, 4, 1, 8, 2});
  cout << "Averages of subarrays of size K: ";
  for (double d : result) {
    cout << d << " ";
  }
  cout << endl;
  cout << "Maximum sum of a subarray of size K: "
       << MaxSumSubArrayOfSizeK::findMaxSumSubArray(3, vector<int>{2, 1, 5, 1, 3, 2}) << endl;
  cout << "Maximum sum of a subarray of size K: "
       << MaxSumSubArrayOfSizeK::findMaxSumSubArray(2, vector<int>{2, 3, 4, 1, 5}) << endl;

  cout << endl;
  int result3 = MinSizeSubArraySum::findMinSubArray(7, vector<int>{2, 1, 5, 2, 3, 2});
  cout << "Smallest subarray length: " << result3 << endl;
  result3 = MinSizeSubArraySum::findMinSubArray(7, vector<int>{2, 1, 5, 2, 8});
  cout << "Smallest subarray length: " << result3 << endl;
  result3 = MinSizeSubArraySum::findMinSubArray(8, vector<int>{3, 4, 1, 1, 6});
  cout << "Smallest subarray length: " << result3 << endl;       

}