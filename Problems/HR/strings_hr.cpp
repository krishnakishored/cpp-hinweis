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

int main()
{
    /* code */

    main_makeAnagram();
    return 0;
}
