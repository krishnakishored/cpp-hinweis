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

#ifndef STACK
#define STACK
#include <stack>
#endif

#include <unordered_set>
#include <unordered_map>

#include <limits>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::numeric_limits;
using std::ofstream;
using std::stack;
using std::streamsize;
using std::string;
using std::vector;

/*
    1. https://www.hackerrank.com/challenges/balanced-brackets/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
    2. https://www.hackerrank.com/challenges/ctci-queue-using-two-stacks/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
    3. https://www.hackerrank.com/challenges/largest-rectangle/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
    4. https://www.hackerrank.com/challenges/min-max-riddle/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
    5. https://www.hackerrank.com/challenges/castle-on-the-grid/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
    6. https://www.hackerrank.com/challenges/poisonous-plants/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
*/

vector<string> split_string(string);

// Complete the poisonousPlants function below.
int poisonousPlants(vector<int> p)
{

    return 0;
}

int main_poisonousPlants()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split_string(p_temp_temp);

    vector<int> p(n);

    for (int i = 0; i < n; i++)
    {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    int result = poisonousPlants(p);

    fout << result << "\n";

    fout.close();

    return 0;
}

// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY)
{
    /*
3
.X.
.X.
...
0 0 0 2

o/p: 3
*/
    return 0;
}

int main_minimumMoves()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> grid(n);

    for (int i = 0; i < n; i++)
    {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string startXStartY_temp;
    getline(cin, startXStartY_temp);

    vector<string> startXStartY = split_string(startXStartY_temp);

    int startX = stoi(startXStartY[0]);

    int startY = stoi(startXStartY[1]);

    int goalX = stoi(startXStartY[2]);

    int goalY = stoi(startXStartY[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    fout << result << "\n";

    fout.close();

    return 0;
}

// Complete the riddle function below.
vector<long> riddle(vector<long> arr)
{
    // complete this function
    /*
    4
    2 6 1 12

    o/p: 12 2 1 1
    */
    vector<long> v{0};

    return v;
}

int main_minMax_riddle()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<long> arr(n);

    for (int i = 0; i < n; i++)
    {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<long> res = riddle(arr);

    for (int i = 0; i < res.size(); i++)
    {
        fout << res[i];

        if (i != res.size() - 1)
        {
            fout << " ";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

// Complete the largestRectangle function below.
long largestRectangle(vector<int> h)
{
    /*
    5
    1 2 3 4 5
    o/p: 9
    */
    long z{0};

    return z;
}

int main_largestRectangle()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string h_temp_temp;
    getline(cin, h_temp_temp);

    vector<string> h_temp = split_string(h_temp_temp);

    vector<int> h(n);

    for (int i = 0; i < n; i++)
    {
        int h_item = stoi(h_temp[i]);

        h[i] = h_item;
    }

    long result = largestRectangle(h);

    fout << result << "\n";

    fout.close();

    return 0;
}

class MyQueue
{

public:
    stack<int> stack_newest_on_top, stack_oldest_on_top;
    void push(int x)
    {
        stack_newest_on_top.push(x);

    }

    void pop()
    {
        int elem = 0;
        if (stack_newest_on_top.empty() && stack_oldest_on_top.empty())
        {
            exit(0);
        }
        else if (stack_oldest_on_top.empty())
        {
            while (!stack_newest_on_top.empty())
            {
                elem = stack_newest_on_top.top();
                stack_oldest_on_top.push(elem);
                stack_newest_on_top.pop();
            }
            stack_oldest_on_top.pop();
        }
        else
        {
            stack_oldest_on_top.pop();
        }
    }

    int front()
    {
        int elem = 0;
        if (stack_newest_on_top.empty() && stack_oldest_on_top.empty())
        {
            exit(0);
        }
        else if (stack_oldest_on_top.empty())
        {
            while (!stack_newest_on_top.empty())
            {
                elem = stack_newest_on_top.top();
                stack_oldest_on_top.push(elem);
                stack_newest_on_top.pop();
            }
        }
        return stack_oldest_on_top.top();
    }
};

int main_MyQueue()
{

    /*
    10
    1 42
    2
    1 14
    3
    1 28
    3
    1 60
    1 78
    2
    2

    o/p: 14
         14
    */
    MyQueue q1;
    int q, type, x;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        cin >> type;
        if (type == 1)
        {
            cin >> x;
            q1.push(x);
        }
        else if (type == 2)
        {
            q1.pop();
        }
        else
            cout << q1.front() << endl;
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}



string isBalanced_2(string s) {
    stack<char> st;  
    
    for (auto c: s) {
        switch (c) {
            case '{':
            case '(':
            case '[':
                st.push(c);
                break;
            case '}':
                if (st.empty() || (st.top() != '{')) {
                    return "NO";
                }
                st.pop();
                break;
            case ')':
                if (st.empty() || (st.top() != '(')) {
                    return "NO";
                }
                st.pop();
                break;
            case ']':
                if (st.empty() || (st.top() != '[')) {
                    return "NO";
                }
                st.pop();
                break;
        }
    }    
    return st.empty() ? "YES" : "NO";
}


// Complete the isBalanced function below.
string isBalanced(string s)
{
    /*
3
{[()]}
{[(])}
{{[[(())]]}}

o/p: YES
      NO
     YES
*/
    
    std::unordered_set<char> open{'[', '(', '{'};
    std::unordered_map<char, char> match({{'}', '{'},{']','[',},{')','(',}});
    std::stack<char> container;

    for (auto letter : s)
    {
        if (open.find(letter) != open.end())
        {
            container.push(letter);
        }
        else
        {
            if(container.empty()|| container.top() != match[letter])
            {
                return "NO";
            }
            else
            {
                container.pop();
            }
        }
    }
    return (container.size() > 0) ? "NO" : "YES";
}

int main_BalancedBrackets()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    
    std::ofstream fout("./DataFiles/stringOutput.txt");

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        string s;
        getline(cin, s);

        // string result = isBalanced(s);
        string result = isBalanced_2(s);
        fout << result << "\n";
    }

    fout.close();

    return 0;
}
// https://www.hackerrank.com/challenges/maximum-element/problem
struct node{
    int data;
    node* next;
    node* max;
};

int main_maximumElement_usingCustomlinkedList(){
//to do
return 0;
} 


int main_maximumElement() 
{
	//using two stacks
	int iterations = 0, choice = 0, number = 0, max = 0;
	std::stack<int> elements;
    std::stack<int> max_elem;

	cin >> iterations;
	while (iterations) {
		cin >> choice;
		switch (choice) {
		case 1:
			cin>> number;
            elements.push(number);
            if(max_elem.empty() || ( number > max_elem.top()))
            {
                max_elem.push(number);
            }
			break;
		case 2:
            if (elements.top() == max_elem.top()){
                max_elem.pop();
            }
    		elements.pop();
			break;
		case 3:
		    std::cout << max_elem.top()<<endl;
			break;
		default:
			return 0;
		}
		iterations--;
	}
	return 0;
}

int main()
{
    // main_poisonousPlants();
    // main_minimumMoves();
    // main_minMax_riddle();
    // main_largestRectangle();
    // main_BalancedBrackets();
    // main_MyQueue();
    main_maximumElement();
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