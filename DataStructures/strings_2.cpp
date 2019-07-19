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

#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional>
#endif

#ifndef CCTYPE
#define CCTYPE
#include <cctype> //for isspace()
#endif

#ifndef CWCTYPE
#define CWCTYPE
#include <cwctype>
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
using std::min;
using std::ofstream;
using std::string;
using std::vector;
using std::wcout;
using std::wstring;

//Joining a Sequence of Strings
void join(const vector<string> &v, char c, string &s)
{
    s.clear();
    for (vector<string>::const_iterator p = v.begin(); p != v.end(); ++p)
    {
        s += *p;
        if (p != v.end() - 1)
            s += c;
    }
}

int main_JoinStrings()
{
    vector<string> v;
    vector<string> v2;
    string s;
    v.push_back(string("fee"));
    v.push_back(string("fi"));
    v.push_back(string("foe"));
    v.push_back(string("fum"));
    join(v, '/', s);
    cout << s << '\n';
    return 0;
}

template <typename T>
void join(const T *arr[], size_t n, T c, std::basic_string<T> &s)
{
    s.clear();
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] != NULL)
            s += arr[i];
        if (i < n - 1)
            s += c;
    }
}
const static int MAGIC_NUMBER = 4;

int main_joinStrings2()
{
    std::wstring ws;
    const wchar_t *arr[MAGIC_NUMBER];
    arr[0] = L"you";
    arr[1] = L"ate";
    arr[2] = L"my";
    arr[3] = L"breakfast";
    join(arr, MAGIC_NUMBER, L'/', ws);
    wcout << ws << endl; //you/ate/my/breakfast%
    return 0;
}

//return after removing duplicates in the string
int uniqueStr(const std::string &str, string &noDuplicates)
{
    for (const char &c : str)
    {
        if (noDuplicates.find_first_of(c) == string::npos)
        {
            noDuplicates += c;
        }
    }
    return noDuplicates.length();
}

int main_uniqueStr()
{
    std::string myString("abracadabra");
    std::string noDup{0};

    cout << "with " << uniqueStr(myString, noDup) << " unique chars: " << noDup << endl;
    return 0;
}

int main_findInString()
{
    std::string s = "Charles Darwin";
    std::cout << "string.length: " << s.length() << endl;
    std::cout << s.find("ar") << '\n';                   // Search from the beginning
    std::cout << s.rfind("ar") << '\n';                  // Search from the end
    std::cout << s.find_first_of("swi") << '\n';         // Find the first of any of these chars
    std::cout << s.find_first_not_of("Charles") << '\n'; // Find the first that's not in this set
    std::cout << s.find_last_of("abg") << '\n';          // Find the first of any of these chars starting from the end
    std::cout << s.find_last_not_of("aDinrw") << '\n';   // Find the first that's not in this set, starting from the end

    return 0;
}

template <typename T>
int countUnique(const std::basic_string<T> &s)
{
    using std::basic_string;
    basic_string<T> chars;
    for (typename basic_string<T>::const_iterator p = s.begin(); p != s.end(); ++p)
    {
        if (chars.find(*p) == basic_string<T>::npos)
            chars += *p;
    }
    return (chars.length());
}

int main_countUnique()
{
    std::string s = "Abracadabra";
    std::cout << countUnique(s) << '\n';

    return 0;
}

// Finding the nth Instance of a Substring Problem

int nthSubstr(int n, const string &s, const string &p)
{
    string::size_type i = s.find(p);
    // Find the first occurrence
    int j;
    for (j = 1; j < n && i != string::npos; ++j)
        i = s.find(p, i + 1); // Find the next occurrence
    if (j == n)
        return (i);
    else
        return (-1);
}

template <typename T>
int nthSubstrg(int n, const basic_string<T> &s,
               const basic_string<T> &p,
               bool repeats = false)
{
    string::size_type i = s.find(p);
    string::size_type adv = (repeats) ? 1 : p.length();
    int j;
    for (j = 1; j < n && i != basic_string<T>::npos; ++j)
        i = s.find(p, i + adv);
    if (j == n)
        return (i);
    else
        return (-1);
}

int main_nthSubString()
{
    string s = "the wind, the sea, the sky, the trees";
    string p = "the";
    cout << nthSubstr(1, s, p) << '\n';
    cout << nthSubstr(2, s, p) << '\n';
    cout << nthSubstr(5, s, p) << '\n';

    string s2 = "AGATGCCATATATATACGATATCCTTA";
    string p2 = "ATAT";
    cout << p2 << " as non-repeating occurs at "
         << nthSubstrg(3, s2, p2) << '\n';
    cout << p2 << " as repeating occurs at "
         << nthSubstrg(3, s2, p2, true) << '\n';
    return 0;
}

//Remove all substrings from a string (generic version)

// template <typename T> //error: missing 'typename' prior to dependent type name 'basic_string<T>::size_type'
void removeSubstrs(basic_string<char> &s, const basic_string<char> &p)
{
    basic_string<char>::size_type n = p.length();
    for (basic_string<char>::size_type i = s.find(p);
         i != basic_string<char>::npos;
         i = s.find(p))

        s.erase(i, n);
}

int main_removeSubstrs()
{
    string s = "One fish, two fish, red fish, blue fish";
    string p = "fish";
    removeSubstrs(s, p);
    cout << s << '\n';
    return 0;
}

template <typename C>
void toUpper2(basic_string<C> &s, const std::locale &loc = std::locale())
{
    typename basic_string<C>::iterator p;
    for (p = s.begin(); p != s.end(); ++p)
    {
        *p = std::use_facet<std::ctype<C>>(loc).toupper(*p);
        // *p = std::use_facet<std::ctype<C> >(loc).tolower(*p);
    }
}

int main_toUpperCase()
{
    //    string s = "shazam";
    wstring ws = L"wham";
    //    toUpper2(s);
    toUpper2(ws);
    //    cout << "s =  " << s << endl;
    wcout << "ws = " << ws << endl;
    return 0;
}
//Case-Insensitive Compare
inline bool caseInsCharCompareN(char a, char b)
{
    return (toupper(a) == toupper(b));
}

bool caseInsCompare(const string &s1, const string &s2)
{
    return ((s1.size() == s2.size()) &&
            std::equal(s1.begin(), s1.end(), s2.begin(), caseInsCharCompareN));
}

int main_caseInsCompare()
{
    string s1 = "In the BEGINNING...";
    string s2 = "In the beginning...";
    if (caseInsCompare(s1, s2))
        cout << "Equal!\n";
    return 0;
}

// Doing a Case-Insensitive String Search

string::const_iterator caseInsFind(string &s, const string &p)
{
    string tmp;
    std::transform(p.begin(), p.end(), back_inserter(tmp), toupper);
    return (std::search(s.begin(), s.end(), tmp.begin(), tmp.end(), caseInsCharCompareN));
}

// Make the pattern upper-case
// Return the iterator returned by search

int main_caseInsSearch()
{
    string s = "row, row, row, your boat";
    string p = "YOUR";
    string::const_iterator it = caseInsFind(s, p);
    if (it != s.end())
    {
        cout << "Found it!\n";
    }
    return 0;
}

int main()
{
    main_JoinStrings();
    main_joinStrings2();
    main_caseInsSearch();
    main_uniqueStr();
    main_findInString();
    main_caseInsCompare();
    main_toUpperCase();
    main_removeSubstrs();
    main_nthSubString();
    main_countUnique();
    return 0;
}