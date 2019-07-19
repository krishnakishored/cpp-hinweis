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

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::numeric_limits;
using std::ofstream;
using std::streamsize;
using std::string;
using std::vector;

/*
    1. https://www.hackerrank.com/challenges/ctci-ransom-note/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps
    2. https://www.hackerrank.com/challenges/two-strings/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps
    3. https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps
    4. https://www.hackerrank.com/challenges/count-triplets-1/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps
    5. https://www.hackerrank.com/challenges/frequency-queries/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps
*/



string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int>> queries) {

    vector<int> v{0};
    return v;
}
/*
The first line contains of an integer q, the number of queries. 
Each of the next q lines contains two integers denoting the 2-d array .

 Operation   Array   Output
(1,1)       [1]
(2,2)       [1]
(3,2)                   0
(1,1)       [1,1]
(1,1)       [1,1,1]
(2,1)       [1,1]
(3,2)                   1
 */

int main_freqQuery()
{
    cout<<"freqQuery"<<endl;
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> ans = freqQuery(queries);

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

/*
The first line contains two space-separated integers n and r , the size of arr and the common ratio. 
The next line contains n space-seperated integers arr[i]
4 2
1 2 2 4
//Return the count of triplets that form a geometric progression.

o/p: 2
indices: (0,1,3)(0,2,3)

5 5
1 5 5 25 125

o/p: 4 
(0,1,3)(0,2,3)(1,3,4)(2,3,4)

*/


// Complete the countTriplets function below.
long countTriplets(vector<long> arr, long r) {

return 0;
}

int main_countTriplets()
{
    cout<<"countTriplets"<<endl;
    ofstream fout(getenv("OUTPUT_PATH"));

    string nr_temp;
    getline(cin, nr_temp);

    vector<string> nr = split(rtrim(nr_temp));

    int n = stoi(nr[0]);

    long r = stol(nr[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    long ans = countTriplets(arr, r);

    fout << ans << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        // find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
        find_if(s.begin(), s.end(), [](int ch){return !std::isspace(ch);})
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);
    //std::ptr_fun was deprecated in C++11, and will be removed completely in C++17.
    //  std::not1 is deprecated in c++17
    s.erase(
        // find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        find_if(s.rbegin(), s.rend(), [](int ch){return !std::isspace(ch);}).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}



/*
Input Format
The first line contains an integer , the number of queries. 
Each of the next  lines contains a string  to analyze.

//Given a string, find the number of pairs of substrings of the string that are anagrams of each other.
2
abba
abcd

o/p: 4 --> (a,a),(b,b),(abb,bba) (ab,ba) 
     0


ifailuhkqq
kkkk

3
10

*/

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {

return 0;
}


int main_sherlockAndAnagrams()
{
    cout<<"sherlockAndAnagrams"<<endl;
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}



/*
Input:
6 4
give me one grand today night
give one grand today
Output: YES
*/

vector<string> split_string(string);

// Complete the checkMagazine function below.
void checkMagazine(vector<string> magazine, vector<string> note)
{
    //convert magzine from vector of strings to set of strings
    //iterate over note to find if all of the words are present

}

int main_CheckMagazine()
{
    cout<<"CheckMagazine"<<endl;
    string mn_temp;
    getline(cin, mn_temp);

    vector<string> mn = split_string(mn_temp);

    int m = stoi(mn[0]);

    int n = stoi(mn[1]);

    string magazine_temp_temp;
    getline(cin, magazine_temp_temp);

    vector<string> magazine_temp = split_string(magazine_temp_temp);

    vector<string> magazine(m);

    for (int i = 0; i < m; i++)
    {
        string magazine_item = magazine_temp[i];

        magazine[i] = magazine_item;
    }

    string note_temp_temp;
    getline(cin, note_temp_temp);

    vector<string> note_temp = split_string(note_temp_temp);

    vector<string> note(n);

    for (int i = 0; i < n; i++)
    {
        string note_item = note_temp[i];

        note[i] = note_item;
    }

    checkMagazine(magazine, note);

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

//Given two strings, determine if they share a common substring.
/*
hell well  --> YES
*/

// Complete the twoStrings function below.
string twoStrings(string s1, string s2)
{
    //also what's largest substring
    return "True";
}

int main_twoStrings()
{
   cout<<"TwoStrings"<<endl;
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        string s1;
        getline(cin, s1);

        string s2;
        getline(cin, s2);

        string result = twoStrings(s1, s2);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

int letterBits(const string &s)
{
    int bits = 0;
    for (char ch : s)
        bits |= 1 << (ch - 'a');
    return bits;
}

int main_twoStringsBitManipulation()
{
    int testCases;
    cin >> testCases;
    while (testCases--)
    {
        string strA, strB;
        cin >> strA >> strB;
        int bitsA = letterBits(strA);
        int bitsB = letterBits(strB);
        cout << (bitsA & bitsB ? "YES" : "NO") << endl;
    }
    return 0;
}

int main(){
    main_countTriplets();
    main_freqQuery();
    main_CheckMagazine();
    main_twoStrings();
    main_twoStringsBitManipulation();
    main_sherlockAndAnagrams();
    return 0;
}