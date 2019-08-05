
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
#include<limits>
#include <numeric>

using std::string;
using std::min;
using std::cin;
using std::cout;
using std::vector;
using std::numeric_limits;
using std::streamsize;

#include<unordered_map>


vector<string> split_string(string);

// Complete the whatFlavors function below.
void whatFlavors(vector<int> cost, int money) 
{
    /**
        2
        8
        5
        4 3 2 5 7
        12
        5
        7 2 5 4 11
     * o/p
        2 4
        1 3
     */
    
    std::unordered_map<int,vector<int> >  cost_map;
    for(int i=0;i<cost.size();i++){
        auto it= cost_map.find(cost[i]);
        if(it==cost_map.end())
        {
           vector<int> v={i+1};
           cost_map.emplace(std::make_pair(cost[i],v));
        }
        else
        {
            it->second.push_back(i+1);
        }
        
    }

    std::unordered_map<int,vector<int>>::iterator it1,it2;

    for(auto elem:cost){
        it1 = cost_map.find(elem);
        it2 = cost_map.find(money-elem);
        
        if(it1 != cost_map.end() && it2 != cost_map.end() && (it1->second[0] != it2->second[0]))
        {
            cout<< (it1->second[0]) << " " << (it2->second[0]) << "\n";
            
            break;
        }
        else if(it1->second.size()>=2)
        
                cout<< (it1->second[0])  << " " << (it1->second[1]) << "\n";
                break;

        }
        // if(it1 != cost_map.end() && it2 != cost_map.end() ){
        //     if(it1==it2){
        //          cout<< (it1->second[0])  << " " << (it1->second[1]) << "\n";
        //          break;
        //     }
        //     else{
        //          cout<< (it1->second[0]) << " " << (it2->second[0]) << "\n";
        //          break;
        //     }
        // }        
    
    
    
    
    // std::unordered_multimap<int,int> cost_map;
    // for(int i=0;i<cost.size();i++){
    //     // cost_map.insert(cost[i],i);
    //     cost_map.emplace(std::make_pair(cost[i], i));
    // }

    // std::unordered_map<int,int>::iterator it1,it2;
    
    // for(int i=0;i<cost.size();i++)
    // {
    //     it1 = cost_map.find(cost[i]);
    //     it2 = cost_map.find(money-cost[i]);

    //     if ((it1 != cost_map.end()) && (it2 != cost_map.end()) && (it1!=it2))
    //     {
    //         cout << (it1->second) + 1 << " " << (it2->second) + 1 << "\n";
    //         break;
    //     }    
    //     else if (it1 == it2)
    //     {
    //         // std::pair<std::unordered_multimap<int,int>::iterator, std::unordered_multimap<int,int>::iterator> ret;
    //         auto ret = cost_map.equal_range(cost[i]);
    //         auto duplicate = ret.first;
    //         it2 = ++duplicate;
    //         if (it2 != ret.second)
    //         {                
    //             cout << (it1->second) + 1 << " " << (it2->second) + 1 << "\n";
    //             break;
    //         }
    //     }
    // }   
     
}

int main_whatFlavors()
{
    vector<int> cost ={4,3,2,5,7};
    // {2, 2, 4, 3}; //
    
    // std::sort(begin(cost),end(cost));
    int money = 8;
    whatFlavors(cost, money);
    /*
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int money;
        cin >> money;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string cost_temp_temp;
        getline(cin, cost_temp_temp);

        vector<string> cost_temp = split_string(cost_temp_temp);

        vector<int> cost(n);

        for (int i = 0; i < n; i++) {
            int cost_item = stoi(cost_temp[i]);

            cost[i] = cost_item;
        }

        whatFlavors(cost, money);
    }

    */

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

int main(){
    
    main_whatFlavors();
    return 0;
}