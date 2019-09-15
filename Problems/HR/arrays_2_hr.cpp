#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#include<iterator>
#include <sstream>



using std::cin;
using std::cout;
using std::endl;

using std::ofstream;
using std::streamsize;
using std::string;
using std::vector;

// https://www.hackerrank.com/challenges/variable-sized-arrays/problem
/*

2 2
3 1 5 4
5 1 2 8 9 3
0 1
1 3

o/p:
5
9

*/
int main_variablesizedarray()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int num_of_arrays=0, num_of_queries=0;
    std::cin >> num_of_arrays >> num_of_queries;
    vector<string> lines(num_of_arrays);

    std::string input;
    
    while(std::getline(cin, input)){
        lines.push_back(input);
    }
    cout<<lines.size()<<" ";

    /*
    for(int i=0;i<num_of_arrays;i++){
        std::string input;
        std::getline(cin, input);
        cout<<input<<" ";
        lines.push_back(input);
        // std::istringstream parser(input);
        // input_lines[i].insert(input_lines[i].begin(),
    //                std::istream_iterator<int>(parser), std::istream_iterator<int> ());    
    }
    cout<<lines.size();
    */
    // vector<vector<int> > input_lines(num_of_arrays);
    // for(int i=0;i<num_of_arrays;i++){
    //     std::string input;
    //     std::getline(cin, input);
    //     std::istringstream parser(input);
    //     input_lines[i].insert(input_lines[i].begin(),
    //                std::istream_iterator<int>(parser), std::istream_iterator<int> ());

    // cout << input_lines[i].size();                   
    // }
    

    
    

    // numbers.insert(numbers.begin(),
    //                std::istream_iterator<int>(parser), std::istream_iterator<int> ());
    
    
    // string value="";
    // // vector<string> array_lines;
    // for(int i=0;i<num_of_arrays;i++){
    //     getline(cin,value);
    //     cout<<(value);
    // }

    // cin >> t;
    // while(t>0) {
    // 	int n,k;
    // 	cin >> n >> k;
    // 	int i;
    // 	int arr[n];
    // 	for(i=0;i<n;i++)
    //   		cin >> arr[i];

    // 	t--;
    // }

    return 0;
}

int main()
{
    main_variablesizedarray();
    return 0;
}