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

using std::rotate;


// Complete the makeAnagram function below.
int makeAnagram(string a, string b) {
    int alpha [26] = {0};
    for(auto letter:a){
        alpha[letter-97]+=1;
    }
    for (auto letter:b){
        alpha[letter-97]-=1;
    }
    int sum =0;
    for(int i=0;i<26;i++){
        sum+=abs(alpha[i]);
    }
    return sum;

}

int main_makeAnagram()
{
    std::ofstream fout("./DataFiles/stringOutput.txt");
    // std::ofstream fout(getenv("OUTPUT_PATH"));


    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    fout << res << "\n";

    fout.close();

    return 0;
}
// Complete the alternatingCharacters function below.
int alternatingCharacters(string s) 
{
    int count =0;
    for(int i=0;i<s.length()-1;i++)
    {
        if (s[i]==s[i+1]){
            count++;
        }
    }
    return count;
}

int main_alternatingCharacters()
{
    std::ofstream fout("./DataFiles/stringOutput.txt");
    // ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = alternatingCharacters(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

int main()
{
    /* code */

    // main_makeAnagram();
    main_alternatingCharacters();
    
    return 0;
}
