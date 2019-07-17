#include <iostream>
#include <fstream>
#include <limits>

#include <string>
#include <vector>
#include <unordered_set>

#include <algorithm> //unique

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::unordered_set;
using std::unordered_multiset;
using std::vector;

// using namespace std;

//###########################################################################//

vector<string> split_string(string);

// Complete the checkMagazine function below.
// https://www.hackerrank.com/challenges/ctci-ransom-note/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps
void checkMagazine(vector<string> magazine, vector<string> note)
{
    /*
    i/p
        6 5 
        two times three is not four
        two times two is four
        
    o/p
        No
     */
    std::unordered_multiset<string> mag_set(magazine.begin(), magazine.end());
    // // print the set
    // for (const string &i: mag_set) {
    //     std::cout << i << " ";
    // }
    std::unordered_multiset<string>::iterator it;
    for (const string &word : note)
    {
        it = mag_set.find(word);
        if (it == mag_set.end())
        {
            cout << "No\n";
            return;
        }
        else
        {
            mag_set.erase(it);
        }
    }
    cout << "Yes\n";
}

int main_checkMagazine()
{
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

//###########################################################################//

// Complete the twoStrings function below.
string twoStrings(string s1, string s2)
{

    //using find of strings
    // for (auto it = s1.cbegin(); it != s1.cend(); it++)
    // {
    //     // cout<<*it<<" ";
    //     if(s2.find(*it) != string::npos){
    //         return "YES";
    //     }     
    // }

    //using find of unordered_set
    unordered_set<char> s1_set(s1.begin(),s1.end());
    for(const char &c:s2){
        if(s1_set.find(c) != s1_set.end()){
            return "YES";          
        }
    }

    return "NO";  
}

int main_twoStrings()
{
    // std::ofstream fout(getenv("OUTPUT_PATH"));
    std::ofstream fout("./DataFiles/stringOutput.txt");

    int q;
    cin >> q;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

//###########################################################################//

int main()
{
    // main_checkMagazine();
    main_twoStrings();
    return 0;
}