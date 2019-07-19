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

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

#ifndef ALGORITHM
#define ALGORITHM
#include <algorithm>
#endif

#ifndef CCTYPE
#define CCTYPE
#include <cctype> //for isspace()
#endif

#ifndef EXCEPTION
#define EXCEPTION
#include <exception>
#endif

#include <locale>

using std::basic_string;
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::min;
using std::ofstream;
using std::string;
using std::vector;
using std::wcout;
using std::wstring;

// The generic approach
template <typename T>
void pad(basic_string<T> &s, typename basic_string<T>::size_type n, T c)
{
    // 4.1 Padding a String
    if (n > s.length())
        s.append(n - s.length(), c);
}

int main_padding()
{
    //Use string’s insert and append member functions to pad a string with characters on the beginning or end.
    string s1 = "foo";
    cout << s1 << endl;

    s1.append(20 - s1.length(), 'X');
    cout << s1 << endl;
    s1.insert(s1.begin(), 30 - s1.length(), 'X');
    cout << s1 << endl;

    string s = "Appendix A";
    pad(s, 20, '*');
    cout << s << std::endl;
    //    wstring ws = L"Acknowledgments"; // The "L" indicates that this is a wide char literal
    //    pad(ws, 20, L'*');
    //    wcout << ws << std::endl;     // You shouldn't be able to run these at the same time
    return 0;
}

// The approach for narrow character strings
void rtrim(std::string &s, char c)
{
    // 4.2 Trimming a String
    if (s.empty())
        return;
    std::string::iterator p;
    for (p = s.end(); p != s.begin() && *--p == c;)
        ;

    if (*p != c)
        p++;
    s.erase(p, s.end());
}
// The generic approach for trimming single characters from a string
template <typename T>
void rtrim(basic_string<T> &s, T c)
{
    if (s.empty())
        return;
    typename basic_string<T>::iterator p;
    for (p = s.end(); p != s.begin() && *--p == c;)
        ;
    if (*p != c)
        p++;
    s.erase(p, s.end());
}

int main_TrimACharacter()
{
    //    string s = "Great!!!!";
    //    rtrim(s, '!');
    //    cout << s << '\n';
    wstring ws = L"Super!!!!";
    rtrim(ws, L'!');
    wcout << ws << L'\n';
    return 0;
}

template <typename T, typename F>
void rtrimws(basic_string<T> &s, F f)
{
    // Trim trailing whitespace
    if (s.empty())
        return;
    typename basic_string<T>::iterator p;
    for (p = s.end(); p != s.begin() && f(*--p);)
        ;
    if (!f(*p))
        p++;
    s.erase(p, s.end());
}

// Overloads to make cleaner calling for client code
void rtrimws(string &s)
{
    rtrimws(s, isspace);
}
void rtrimws(wstring &ws)
{
    rtrimws(ws, iswspace);
}
int main_TrimWhiteSpace()
{
    string s = "zing         ";
    cout << s << "|\n";
    rtrimws(s);
    cout << s << "|\n";
    //  wstring ws = L"zong rtrimws(s);
    // rtrimws(ws);
    // wcout << ws << L"|\n";
    return 0;
}

// 4.3 Storing Strings in a Sequence: Use a vector for array-like storage of your strings.
int main_printVectorStrings()
{
    vector<string> v;
    string s = "one";
    v.push_back(s);
    s = "two";
    v.push_back(s);
    s = "three";
    v.push_back(s);

    // for(auto i:v)
    //     cout<<  i << endl;
    cout << v.size() << endl; //segmentation fault
    // for (int i = 0; i < v.size(); i++)
    // {
    //     cout << v[i] << endl;
    // }

    // for(auto i=v.begin();i!=v.end();i++){
    //     cout<<*i<<endl;
    // }
    return 0;
}

int main_VectorOutofBounds()
{
    // char carr[] = {'a', 'b', 'c', 'd', 'e'};
    // cout << carr[100000] << '\n'; // Whoops, who knows what's going to happen
    vector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    v.push_back('d');
    v.push_back('e');
    try
    {
        cout << v.at(10000) << '\n'; // at checks bounds and throws
    }
    catch (std::out_of_range &e)
    { // out_of_range if it's invalid
        std::cerr << e.what() << '\n';
    }
    return 0;
}

void write(const string &s)
{
    cout << s << '\n';
}

int main_stringsInList()
{
    //Storing strings in a list
    list<string> lst;
    string s = "knife";
    lst.push_front(s);
    s = "fork";
    lst.push_back(s);
    s = "spoon";
    lst.push_back(s);
    // A list doesn't have random access, so // use for_each() instead
    for_each(lst.begin(), lst.end(), write); //segmentation fault ???
    return 0;
}


int main_LengthCapacity()
{
    //String length and capacity
    string s = "";
    string sr = "";
    sr.reserve(9000);
    cout << "s.length = " << s.length() << '\n';
    cout << "s.capacity= " << s.capacity() << '\n';
    cout << "s.max_size = " << s.max_size() << '\n';
    cout << "sr.length = " << sr.length() << '\n';
    cout << "sr.capacity= " << sr.capacity() << '\n';
    cout << "sr.max_size = " << sr.max_size() << '\n';
    for (int i = 0; i < 10000; ++i)
    {
        if (s.length() == s.capacity())
        {
            cout << "s reached capacity of " << s.length()
                 << ", growing...\n";
        }
        if (sr.length() == sr.capacity())
        {
            cout << "sr reached capacity of " << sr.length() << ", growing...\n";
        }
        s += 'x';
        sr += 'x';
    }
    return 0;
}


int main_reverseString()
{
    string s = "Los Angeles";
    std::reverse(s.begin(),s.end()); //in place
    cout<<s <<endl; //selegnA soL 
    string ra;
    ra.assign(s.rbegin(),s.rend()); //creates a copy
    cout<<ra <<endl; //Los Angeles
    return 0;
}

//4.6 Splitting a String
void split(const string &s, char c, vector<string> &v)
{
    string::size_type i = 0;
    string::size_type j = s.find(c);
    while (j != string::npos)
    {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);
        if (j == string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

int main_SplitString()
{
    vector<string> v;
    string s = "Account Name|Address 1|Address 2|City";
    split(s, '|', v);

    for (auto s : v)
    {
        cout << s << endl;
    }

    return 0;
}

// String tokenizer class.
class StringTokenizer
{
  public:
    StringTokenizer(const string &s, const char *delim = NULL) : str_(s), count_(-1), begin_(0), end_(0)
    {
        if (!delim)
            delim_ = " \f\n\r\t\v"; //default to whitespace
        else
            delim_ = delim;
        // Point to the first token
        begin_ = str_.find_first_not_of(delim_);
        end_ = str_.find_first_of(delim_, begin_);
    }
    size_t countTokens()
    {
        if (count_ >= 0) // return if we've already counted
            return (count_);
        string::size_type n = 0;
        string::size_type i = 0;
        for (;;)
        {
            // advance to the first token
            if ((i = str_.find_first_not_of(delim_, i)) == string::npos)
                break;
            // advance to the next delimiter
            i = str_.find_first_of(delim_, i + 1);
            n++;
            if (i == string::npos)
                break;
        }
        return (count_ = n);
    }
    bool hasMoreTokens() { return (begin_ != end_); }
    void nextToken(string &s)
    {
        if (begin_ != string::npos && end_ != string::npos)
        {
            s = str_.substr(begin_, end_ - begin_);
            begin_ = str_.find_first_not_of(delim_, end_);
            end_ = str_.find_first_of(delim_, begin_);
        }
        else if (begin_ != string::npos && end_ == string::npos)
        {
            s = str_.substr(begin_, str_.length() - begin_);
            begin_ = str_.find_first_not_of(delim_, end_);
        }
    }

  private:
    StringTokenizer(){};
    string delim_;
    string str_;
    int count_;
    int begin_;
    int end_;
};

int main_StringTokenizer()
{
    string s = " razzle dazzle giddyup ";
    string tmp;
    StringTokenizer st(s);
    cout << "there are " << st.countTokens() << " tokens.\n";
    while (st.hasMoreTokens())
    {
        st.nextToken(tmp);
        cout << "token = " << tmp << '\n';
    }
    return 0;
}


int main(){
main_StringTokenizer();
main_padding();
main_TrimACharacter();
main_TrimWhiteSpace();
main_printVectorStrings();
main_VectorOutofBounds();
main_stringsInList();
main_LengthCapacity();
main_reverseString();
main_SplitString();
    return 0;
}