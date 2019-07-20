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


#ifndef ARRAY
#define ARRAY
#include <array>
#endif

#include<algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::numeric_limits;
using std::ofstream;
using std::streamsize;
using std::string;
using std::vector;

/**
 * 1. https://www.hackerrank.com/challenges/2d-array/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrayss
 * 2. https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays
 * 3. https://www.hackerrank.com/challenges/new-year-chaos/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays
 * 4. https://www.hackerrank.com/challenges/minimum-swaps-2/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays
 *
 *
 *

 */


vector<string> split_string(string);



// Complete the arrayManipulation function below.
long arrayManipulation(int n, vector<vector<int>> queries) {

    /*
    a b k
    1 5 3
    4 8 7
    6 9 1


    index->	 1 2 3  4  5 6 7 8 9 10
	[0,0,0, 0, 0,0,0,0,0, 0]
	[3,3,3, 3, 3,0,0,0,0, 0]
	[3,3,3,10,10,7,7,7,0, 0]
	[3,3,3,10,10,8,8,8,1, 0]
    o/p: 10

    5 3
    1 2 100
    2 5 100
    3 4 100

    o/p: 200
    */

    long num{0};
    return num;
}


int main_arrayManipulation()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = arrayManipulation(n, queries);

    fout << result << "\n";

    fout.close();

    return 0;
}


// Complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {

/*

7
1 3 5 2 4 6 7
o/p: 3
*/

return 0;
}

int main_minimumSwaps()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int res = minimumSwaps(arr);

    fout << res << "\n";

    fout.close();

    return 0;
}

void minimumBribes(vector<int> q) {
/*

2
5
2 1 5 3 4
5
2 5 1 3 4

o/p: 3
    Too chaotic

*/

}

int main_minimumBribes()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

    return 0;
}




// Complete the rotLeft function below.
vector<int> rotLeft(vector<int> a, int d) {
    /*
        Given an array  of  integers and a number, , perform  left rotations on the array. Return the updated array to be printed as a single line of space-separated integers.
        5 4
        1 2 3 4 5

        o/p: 5 1 2 3 4
    */
    vector<int> v{0};
    return v;
}

int main_rotLeft()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split_string(a_temp_temp);

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    vector<int> result = rotLeft(a, d);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}


int hourglassSum(vector<vector<int>> arr) {

    // Complete the function hourglassSum in the editor below. It should return an integer, the maximum hourglass sum in the array.
    /*

    a b c
    d
    e f g

    1 1 1 0 0 0
    0 1 0 0 0 0
    1 1 1 0 0 0
    0 0 2 4 4 0
    0 0 0 2 0 0
    0 0 1 2 4 0

    o/p: 19

    2 4 4
    2
    1 2 4

    */

return 0;
}

int main_hourglassSum()
{
    cout<<"hourglassSum"<<endl;
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> arr(6);
    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) {
            cin >> arr[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = hourglassSum(arr);

    fout << result << "\n";

    fout.close();

    return 0;
}



vector<string> split_string(string input_string)
{
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ')
    {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos)
    {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

int main()
{
    main_arrayManipulation();
    main_minimumSwaps();
    main_minimumBribes();
    main_rotLeft();
    main_hourglassSum();
    return 0;
}