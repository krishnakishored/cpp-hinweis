#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>

// 1. Created to store as a variable and to pass into other functions
double MultBy2(double num){
    return num * 2;
}

// 2. Functions can receive other functions
// the first double is the return type followed by the data types for the parameter
double DoMath(std::function<double(double)> func, double num){
    return func(num);
}

// 3. You can store functions in a vector
double MultBy3(double num){
    return num * 3;
}

// 4. ----- PROBLEM -----
// Checks for odd using modulus
bool IsItOdd(int num){
    if(num % 2 == 0){
        return false;
    } else {
        return true;
    }
}

// Receives a list and generates a list of odd values from that list 
std::vector<int> ChangeList(std::vector<int> list, std::function<bool(int)> func){
    std::vector<int> oddList;
    for(auto i: list){
        if(func(i)){
            oddList.push_back(i);
        }
    }
    return oddList;
}
// ----- 4. END OF PROBLEM -----

// ----- 5. PROBLEM -----
// Generates a random list from the possible values supplied
std::vector<char> GetHAndTList(std::vector<char> possibleValues, int numberValuesToGenerate)
{
    srand(time(NULL));
    std::vector<char> hAndTList;
    
    for(int x = 0; x < numberValuesToGenerate; ++x){
        int randIndex = rand() % 2;
        hAndTList.push_back(possibleValues[randIndex]);
    }
    return hAndTList;
}

// Receives a list and sums the number of matching chars
int GetNumberOfMatches(std::vector<char> list, char valueToFind)
{
    int numOfMatches = 0;
    
    for(char c: list){
        if(c == valueToFind){
            numOfMatches++;
        }
    }
    return numOfMatches;
}

// ----- 5. END OF PROBLEM -----

int main()
{
    // 1. You can store functions as variables
    auto times2 = MultBy2;
    std::cout << "5 * 2 = " << times2(5) << "\n";
    
    // 2. Pass a function into a function
    std::cout << "6 * 2 = " << DoMath(times2, 6) << "\n";
    
    // 3. You can store functions in a vector
    // Create a vector using the function parameters
    // and then load the functions into the vector
    std::vector<std::function<double(double)>> funcs (2);
    funcs[0] = MultBy2;
    funcs[1] = MultBy3;
    std::cout << "2 * 10 = " << funcs[0](10) << "\n";
    
    // 4. ----- PROBLEM -----
    // Create a function that receives a list and a function
    // The function passed will return True or False if a list
    // value is odd.
    // The surrounding function will return a list of odd
    // numbers
    std::vector<int> listOfNums {1,2,3,4,5};
    std::vector<int> oddList = ChangeList(listOfNums, IsItOdd);
    std::cout << "List of Odds\n";
    for(auto i: oddList){
        std::cout << i << "\n";
    }
    // ----- 4. END OF PROBLEM -----
    
    // ----- 5. PROBLEM -----
    // Create a function that creates a random list using a limited number of values
    // Create another function that checks for the number of matches in a list
    // Create a random list of Hs and Ts and then output how many of each were generated
    
    std::vector<char> possibleValues {'H', 'T'};
    std::vector<char> hAndTList = GetHAndTList(possibleValues, 100);
    std::cout << "Number of Heads : " <<
            GetNumberOfMatches(hAndTList, 'H')
            << "\n";
    std::cout << "Number of Tails : " <<
            GetNumberOfMatches(hAndTList, 'T')
            << "\n";
    
    // ----- 5. END OF PROBLEM -----
    
    
    return 0;
}