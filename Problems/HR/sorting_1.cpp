#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#include<string>
#include<limits>
#include<algorithm>

using std::string;
using std::min;
using std::cin;
using std::cout;
using std::vector;

vector<string> split_string(string);


void countSwaps(vector<int> a) {
//o/p
// Array is sorted in 0 swaps.
// First Element: 1
// Last Element: 3

// Its value is the last index in the list
    int i = a.size() - 1; // Create the value that will decrement for the outer loop
    int numSwaps = 0;
    while(i >= 1){
        int j = 0;        
        while(j < i){                  
            if(a[j] >= a[j+1]){
                numSwaps++;                
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }             
            j += 1;
        }        
        i -= 1;
    }
    cout<<"Array is sorted in " << numSwaps <<" swaps.\n";
    cout<<"First Element: " << a[0] <<"\n";
    cout<<"Last Element: " << a[a.size()-1] <<"\n";
}


int main_countSwaps()
{
    // Complete the countSwaps function below.
//https://www.hackerrank.com/challenges/ctci-bubble-sort/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=sorting
    int n;
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split_string(a_temp_temp);

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    countSwaps(a);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}


int main()
{
    main_countSwaps();
    return 0;
}