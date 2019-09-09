#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif


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

    cin >> num_of_arrays >> num_of_queries;
    
    // string value="";
    // // vector<string> array_lines;
    // for(int i=0;i<num_of_arrays;i++){
    //     getline(cin,value);
    //     cout<<(value);
    // }

    while(num_of_arrays){

    }

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