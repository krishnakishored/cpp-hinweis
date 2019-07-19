

#ifndef UTILS_H
#define UTILS_H
#include "utils.h"
#endif

using std::list;
using std::string;

static const int ARRAY_SIZE = 5;

template <typename T, typename FwdIter>
FwdIter fixOutliersUBound(FwdIter p1,
						  FwdIter p2,
						  const T &oldVal,
						  const T &newVal)
{
	for (; p1 != p2; ++p1)
	{
		if (std::greater<T>(*p1, oldVal))
		{
			*p1 = newVal;
		}
	}
}
// Using iterators with containers
int main_iteratorTypes()
{
	list<string> lstStr;
	lstStr.push_back("Please");
	lstStr.push_back("leave");
	lstStr.push_back("a");
	lstStr.push_back("message");
	// Create an iterator for stepping through the list
	for (list<string>::iterator p = lstStr.begin();
		 p != lstStr.end(); ++p)
	{
		cout << *p << " ";
	}
	cout << endl;
	//reverse
	for (list<string>::reverse_iterator p = lstStr.rbegin();
		 p != lstStr.rend(); ++p)
	{
		cout << *p << " ";
	}
	cout << endl;
	// Iterating through a range
	string arrStr[ARRAY_SIZE] = {"My", "cup", "cup", "runneth", "over"};
	for (string *p = &arrStr[0];
		 p != &arrStr[ARRAY_SIZE]; ++p)
	{
		cout << *p << " ";
	}
	cout << endl;

	// Using standard algorithms with a standard sequence
	list<string> lstStrDest;
	unique_copy(&arrStr[0], &arrStr[ARRAY_SIZE], back_inserter(lstStrDest));

	return 0;
}

// Removing Objects from a Container
int main_RemovingObjFromAContainer()
{
	list<string> lstStr;
	lstStr.push_back("On");
	lstStr.push_back("a");
	lstStr.push_back("cloudy");
	lstStr.push_back("cloudy");
	lstStr.push_back("day");
	list<string>::iterator p;

	// Find what you want with find
	p = find(lstStr.begin(), lstStr.end(), "day");
	p = lstStr.erase(p); // Now p points to the last element
	// Or, to erase all occurrences of something, use remove
	lstStr.erase(remove(lstStr.begin(), lstStr.end(), "cloudy"), lstStr.end());
	printContainer(lstStr);

	std::string str = "Text with some   spaces";
	std::cout << "before: " << str << "\n";

	std::cout << "after:  ";
	std::remove_copy(str.begin(), str.end(),
					 std::ostream_iterator<char>(std::cout), ' ');
	std::cout << '\n';
	return 0;
}

struct RanNumGenFtor
{
	size_t operator()(size_t n) const
	{
		return (rand() % n);
	}
} rnd;

//Shuffling a sequence at random
int main_shufflingRandom()
{
	vector<int> v;
	std::back_insert_iterator<vector<int>> p = back_inserter(v);
	//back_inserter returns an output iterator that calls push_back on its container whenever you increment the iterator
	for (int i = 0; i < 10; ++i)
		*p = i;
	printContainer(v, true);
	random_shuffle(v.begin(), v.end());
	printContainer(v, true);
	random_shuffle(v.begin(), v.end(), rnd); //void random_shuffle(RndIter first, RndIter last, RandFunc& rand);
	printContainer(v, true);

	return 0;
}

int main_CompareSequences()
{
	vector<string> vec1, vec2;
	vec1.push_back("Charles");
	vec1.push_back("in");
	vec1.push_back("Charge");
	vec2.push_back("Charles");
	vec2.push_back("in");
	vec2.push_back("charge"); // Note the small "c"
	if (equal(vec1.begin(), vec1.end(), vec2.begin()))
	{
		cout << "The two ranges are equal!" << endl;
	}
	else
	{
		cout << "The two ranges are NOT equal!" << endl;
	}
	string s1 = "abcde";
	string s2 = "abcdf";
	string s3 = "abc";
	// Show bools as "true" or "false"
	cout << std::boolalpha << lexicographical_compare(s1.begin(), s1.end(), s1.begin(), s1.end()) << endl; //abcde < abcde (false)
	cout << lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()) << endl;
	cout << lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end()) << endl;
	cout << lexicographical_compare(s1.begin(), s1.end(), s3.begin(), s3.end()) << endl;
	cout << lexicographical_compare(s3.begin(), s3.end(), s1.begin(), s1.end()) << endl;
	std::pair<string::iterator, string::iterator> iters = mismatch(s1.begin(), s1.end(), s2.begin());
	cout << "first mismatch  = " << *(iters.first) << endl;
	cout << "second mismatch = " << *(iters.second) << endl;

	return 0;
}

//Merging two sorted sequences

int main_MergeTwoSortedSeq()
{
	vector<string> v1, v2, v3;
	v1.push_back("a");
	v1.push_back("c");
	v1.push_back("e");
	v2.push_back("b");
	v2.push_back("d");
	v2.push_back("f");
	v3.reserve(v1.size() + v2.size() + 1);
	// Use a back_inserter from iterator to avoid having to put a bunch of default objects in the container.
	//But this doesn't // mean you don't have to use reserve!
	merge(v1.begin(), v1.end(),
		  v2.begin(), v2.end(), std::back_inserter<vector<string>>(v3));
	printContainer(v3);

	// Now make a mess
	random_shuffle(v3.begin(), v3.end());
	sort(v3.begin(), v3.begin() + v3.size() / 2); //sorted halves
	sort(v3.begin() + v3.size() / 2, v3.end());
	printContainer(v3);

	inplace_merge(v3.begin(), v3.begin() + 3, v3.end());
	printContainer(v3);
	// If you are using two lists, though, use list::merge instead.
	list<string> lstStr1, lstStr2;
	lstStr1.push_back("Frank");
	lstStr1.push_back("Rizzo");
	lstStr1.push_back("Bill");
	lstStr1.push_back("Cheetoh");
	lstStr2.push_back("Allie");
	lstStr2.push_back("McBeal");
	lstStr2.push_back("Slick");
	lstStr2.push_back("Willie");
	lstStr1.sort();			// Sort these or merge makes garbage! lstStr2.sort( );
	lstStr1.merge(lstStr2); // Note that this only works with other lists of the same type
	printContainer(lstStr1);
	return 0;
}

//Sorting a Range
int main_sorting_partitioning()
{
	// cout << "Enter a series of strings: ";
	// istream_iterator<string> start(cin);
	// istream_iterator<string> end; // This creates a "marker"
	// vector<string> v(start, end);

	vector<string> v = {"a", "z", "c", "v", "t", "g", "q", "o"};
	// The sort standard algorithm will sort elements in a range. It // requires a random-access iterator, so it works for a vector.
	sort(v.begin(), v.end());
	printContainer(v);
	random_shuffle(v.begin(), v.end());
	string *arr = new string[v.size()];
	// Copy the elements into the array
	copy(v.begin(), v.end(), &arr[0]);
	// Sort works on any kind of range, so long as its arguments are random-access iterators.
	sort(&arr[0], &arr[v.size()]);
	printRange(&arr[0], &arr[v.size()]);
	// Create a list with the same elements
	list<string> lst(v.begin(), v.end());
	lst.sort(); // The standalone version of sort won't work; you have to use list::sort. Note, consequently, that you
				// can't sort only parts of a list.
	printContainer(lst);

	//partioning a range
	// Rearrange the elements in v so that those that are less
	// than "foo" occur before the rest.
	vector<string> v2 = {"a", "d", "f", "j", "k", "l"};
	vector<string>::iterator p =
		partition(v2.begin(), v2.end(), bind2nd(std::less<string>(), "foo"));
	printContainer(v2);
	cout << "*p = " << *p << endl;
	return 0;
}

//Performing Set Operations on Sequences

int main_SetOperations()
{
	// cout << "Enter some strings: ";
	// istream_iterator<string> start(cin);
	// istream_iterator<string> end;
	// set<string> s1(start, end);
	// cin.clear();
	set<string> s1={"a","b","c","d"};

	// cout << "Enter some more strings: ";
	// set<string> s2(++start, end);

	set<string> s2={"d","e","f","g"};
	set<string> setUnion;
	set<string> setInter;
	set<string> setDiff;
	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
			  inserter(setUnion, setUnion.begin()));

	set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),
				   inserter(setDiff, setDiff.begin()));
	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
					 inserter(setInter, setInter.begin()));

	cout << "Union: ";
	printContainer(setUnion);
	cout << "Difference: ";
	printContainer(setDiff);
	cout << "Intersection: ";
	printContainer(setInter);

	return 0;
}


// Transforming Elements in a Sequence

// Convert a string to upper case
string strToUpper(const string &s)
{
	string tmp;
	for (string::const_iterator p = s.begin(); p != s.end(); ++p)
		tmp += toupper(*p);
	return (tmp);
}
void strToUpperInPlace(string &s)
{
	for (string::iterator p = s.begin(); p != s.end(); ++p)
		*p = std::toupper(*p);
}

string strAppend(const string &s1, const string &s2)
{
	return (s1 + s2);
}

int main_transform_foreach()
{
	list<string> lst = {"a", "z", "c", "v", "t", "g", "q", "o"}, out;

	// Use transform with an unary function...
	transform(lst.begin(), lst.end(),
			  back_inserter(out),
			  strToUpper);
	printContainer(out);
	list<string> lst1 = {"a", "z", "c", "v", "t", "g", "q", "o"}, lst2;
	transform(lst1.begin(), lst1.end(), lst2.begin(),
             back_inserter(out),
             strAppend);
	printContainer(out);

	printContainer(lst);
	std::for_each(lst.begin(), lst.end(), strToUpperInPlace);
	printContainer(lst);
	return 0;
}


//Writing Your Own Algorithm
template <typename In, typename Out, typename UnPred>
Out copyIf(In first, In last, Out result, UnPred pred)
{
	for (; first != last; ++first)
		if (pred(*first))
			*result++ = *first;
	return (result);
}

int main_bind2nd()
{
	vector<string> v = {"a", "z", "c", "v", "t", "g", "q", "o"};
	list<string> lst;
	copyIf(v.begin(), v.end(), std::back_inserter<list<string>>(lst), std::bind2nd(std::less<string>(), "tookie"));
	//only copies values less than “tookie” into the destination range.

	printContainer(lst);


	//Printing a range to a stream
	//Treat the output stream as a container by using an output_iterator. It constructs an output iterator where writing to each element is equivalent to writing it to the stream. 
	copy(v.begin(), v.end(), std::ostream_iterator<string>(cout, " + "));
	cout<<endl;
	printRange(v.begin(), v.end(), ';', cout);

	return 0;
}

int main(){
	main_bind2nd();
	main_CompareSequences();
	main_iteratorTypes();
	main_MergeTwoSortedSeq();
	main_RemovingObjFromAContainer();
	main_SetOperations();
	main_shufflingRandom();
	main_sorting_partitioning();
	main_transform_foreach();
	
	return 0;
}