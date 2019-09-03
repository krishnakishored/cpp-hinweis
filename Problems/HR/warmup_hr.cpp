#include<iostream>
#include<vector>
#include<array>
#include<string>
#include <algorithm>
#include <numeric>



using std::string;
using std::vector;

using std::cout;
using std::cin;

vector<string> split_string(string);

// Complete the miniMaxSum function below.
void miniMaxSum(vector<int> arr) {
    // int sum = std::accumulate(arr.begin(), arr.end(), 0);
    // nth_element(arr.begin(),arr.end(),arr.end());
    // cout<< sum - *(arr.end()-1)<<" ";
    // nth_element(arr.begin(),arr.begin(),arr.end());
    // cout<< sum - *arr.begin();


    //single pass
    long int sum=0,min=0,max=0;
    vector<int>::iterator it = arr.begin();
    min = *it;
    max = *it;
    for(auto it = arr.begin();it!=arr.end();it++){
        if(min>*it) min = *it;
        if(max<*it) max = *it;
        sum+=*it;
    }
    cout<< sum-max <<" " <<sum-min;
}

int main_minMaxSum()
{
    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(5);

    for (int i = 0; i < 5; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    miniMaxSum(arr);

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

    splits.push_back(input_string.substr(i, std::min(pos, input_string.length()) - i + 1));

    return splits;
}


// Complete the flippingBits function below.
long flippingBits(long n) {
    return (unsigned)~n;

}

int main_flippingBits()
{
    long n = 802743475;
    long result = flippingBits(n);
    cout<<result<<"\n";


    /*
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        long n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        long result = flippingBits(n);

        fout << result << "\n";
    }

    fout.close();
    */

    return 0;
}

// https://www.hackerrank.com/challenges/c-tutorial-for-loop/problem

int main_forloop()
{

        // Complete the code.
    std::array<std::string,9> numbers ={"one","two","three","four","five","six","seven","eight", "nine"};
    int a=0,b=0;
    cin>>a>>b;
    string result="";
    for(int i=a;i<=b;i++){
        if(i<=numbers.size()){
            result = numbers[i-1];
        }
        else{
            result = ((i-1)%2)?"even":"odd";
        }
        cout << result<<"\n";
    }

    return 0;
}

int main()
{
    // main_minMaxSum();
    // main_flippingBits();
    main_forloop();
    return 0;
}