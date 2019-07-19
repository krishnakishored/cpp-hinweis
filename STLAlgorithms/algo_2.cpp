#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#ifndef ALOGORITHM
#define ALOGORITHM
#include <algorithm>
#endif


#ifndef ITERATOR
#define ITERATOR
#include<iterator>
#endif


/*
 *  comparator, sort, unique
 *  
 */


//Using std::unique algorithm removes consecutive duplicate element from a given range.
//Therefore before executing std::unique we should first the sort the given range

/*
std::unique will not decrease the actual size of given range
i.e. it will only overwrite the duplicate elements and returns the new virtual end of range.
For example, after running std::unique 
1,2,3,3,3,4,4,5,5  becomes  1,2,3,4,5,4,4,5,5
*/


/*std::unique uses the == operator to compare the elements in given range. 
So to remove duplicate elements from vector of class objects we should override == operator in that class.*/
class Person {
public:
	std::string m_name;
	int m_id;
	//Person() :m_name(nullptr), m_id(0) {}
	Person(std::string name, int id) :m_name(name), m_id(id) {}
	bool operator ==(const Person & obj) const {//==overloaded for unique
		if (m_id == obj.m_id)
			return true;
		else
			return false;
	}

	bool operator <(const Person & obj) const { // <overloaded for sort
		if (m_id < obj.m_id)
			return true;
		else
			return false;
	}
};



//using lambda
int main_uniqueWithLambda()
{

	std::vector<Person> vecOfPersons = { Person("aaa", 7), Person("kkk", 3),
		Person("aaa", 10), Person("kkk", 2) };

	std::sort(vecOfPersons.begin(), vecOfPersons.end(), [](const Person & first, const Person & sec) {
		if (first.m_name < sec.m_name)
			return true;
		else
			return false;
	});

	std::vector<Person>::iterator newEnd;
	newEnd = std::unique(vecOfPersons.begin(), vecOfPersons.end(), [](const Person & first, const Person & sec) {
		if (first.m_name == sec.m_name)
			return true;
		else
			return false;
	});

	vecOfPersons.erase(newEnd, vecOfPersons.end());

	std::cout << "After removing duplicate Persons List based on Name\n";
	std::for_each(vecOfPersons.begin(), vecOfPersons.end(), [](Person & obj) {
		std::cout << obj.m_id << " :: " << obj.m_name << std::endl;
	});

	return 0;
}



//comparator
struct PersonEqualityCompartor
{
	bool operator()(const Person & first, const Person & sec) {
		if (first.m_name == sec.m_name)
			return true;
		else
			return false;
	}
};

struct PersonCompartor {
	bool operator()(const Person & first, const Person & sec) {
		if (first.m_name < sec.m_name)
			return true;
		else
			return false;
	}
};



int main_Unique_UserClass() {
	std::vector<Person> vecOfPersons = { Person("aaa", 7), Person("kkk", 3),
		Person("aaa", 10), Person("kkk", 7) };
	/*std::vector<Person> vecOfPersons;
	vecOfPersons.push_back(Person("aaa", 7));
	vecOfPersons.push_back(Person("KKK",3));
	vecOfPersons.push_back(Person("aaa", 10));
	vecOfPersons.push_back(Person("KKK", 3));*/
		
	/* Error
				---------------------------
			Microsoft Visual C++ Runtime Library
		---------------------------
		Debug Assertion Failed!

		Program: D:\OneDriveCodeTemp\STL_Algorithms\Debug\STL_Algorithms.exe
		File: c:\program files (x86)\microsoft visual studio 14.0\vc\include\xmemory0
		Line: 106

		Expression: "(_Ptr_user & (_BIG_ALLOCATION_ALIGNMENT - 1)) == 0" && 0

		For information on how your program can cause an assertion
		failure, see the Visual C++ documentation on asserts.

		(Press Retry to debug the application)

		---------------------------
		Abort   Retry   Ignore   
		---------------------------

	*/

	std::sort(vecOfPersons.begin(), vecOfPersons.end());
	vecOfPersons.erase(std::unique(vecOfPersons.begin(), vecOfPersons.end()), vecOfPersons.end());
	std::cout << "After removing duplicate Persons List based on ID\n";
	std::for_each(vecOfPersons.begin(), vecOfPersons.end(),
		[](Person & obj)
	{
		std::cout << obj.m_id << " :: " << obj.m_name << std::endl;
	});

	std::sort(vecOfPersons.begin(), vecOfPersons.end(), PersonCompartor());

	std::vector<Person>::iterator newEnd;
	newEnd = std::unique(vecOfPersons.begin(), vecOfPersons.end(), PersonEqualityCompartor());


	std::for_each(vecOfPersons.begin(), vecOfPersons.end(), 
	[](Person & obj) 
	{
		std::cout << obj.m_id << " :: " << obj.m_name << std::endl;
	});
	return 0;
}



//Erase Duplicate Elements from a Vector using std::unique
int main_unique_int()
{
	std::vector<int> vecOfInts = { 5,3,1,6,7,6,7,6,9,0,2,3,5 };

	// First Sort the given range to bring duplicate
	// elements at consecutive positions
	std::sort(vecOfInts.begin(), vecOfInts.end());
	copy(vecOfInts.begin(), vecOfInts.end(), std::ostream_iterator<int>(std::cout, ","));	
	std::cout << std::endl;
	std::vector<int>::iterator newEnd;
	// Override duplicate elements
	newEnd = std::unique(vecOfInts.begin(), vecOfInts.end());
	vecOfInts.erase(newEnd, vecOfInts.end());
	std::for_each(vecOfInts.begin(), vecOfInts.end(),
		[](int a) {
		//a++; mutating
		std::cout << a << " , ";
	});

	return 0;
}





int main_sort() 
{
	/*
			---------------------------
		Microsoft Visual C++ Runtime Library
		---------------------------
		Debug Assertion Failed!

		Program: D:\OneDriveCodeTemp\STL_Algorithms\Debug\STL_Algorithms.exe
		File: c:\program files (x86)\microsoft visual studio 14.0\vc\include\xmemory0
		Line: 106

		Expression: "(_Ptr_user & (_BIG_ALLOCATION_ALIGNMENT - 1)) == 0" && 0

		For information on how your program can cause an assertion
		failure, see the Visual C++ documentation on asserts.

		(Press Retry to debug the application)

		---------------------------
		Abort   Retry   Ignore   
		---------------------------

	*/


	int arr[] = { 1, 3, 2, 8, 6, 7, 5 };
	int len = sizeof(arr) / sizeof(int);

	std::sort(arr, arr + len);

	for (int i = 0; i < len; i++)
		std::cout << arr[i] << " , ";
	std::cout << std::endl;

	std::vector<std::string> vecOfStrings;

	vecOfStrings.push_back("bbb");
	vecOfStrings.push_back("fff");
	vecOfStrings.push_back("aaa");
	vecOfStrings.push_back("ccc");
	vecOfStrings.push_back("abc");

	std::sort(vecOfStrings.begin(), vecOfStrings.end());

	std::for_each(vecOfStrings.begin(), vecOfStrings.end(),
		[](std::string str) {
		std::cout << str << " , ";
	});

	std::cout << std::endl;

	std::vector<Person> vecOfPersons = { Person("aaa", 7), Person("kkk", 3),
		Person("ddd", 5), Person("abc", 2) };

	std::sort(vecOfPersons.begin(), vecOfPersons.end());

	std::cout << "Sorted Persons List based on ID\n";
	std::for_each(vecOfPersons.begin(), vecOfPersons.end(), [](Person & obj) {
		std::cout << obj.m_id << " :: " << obj.m_name << std::endl;
	});

	std::sort(vecOfPersons.begin(), vecOfPersons.end(), PersonCompartor());

	std::cout << "Sorted Persons List based on Name using Func Object\n";
	std::for_each(vecOfPersons.begin(), vecOfPersons.end(), [](Person & obj) {
		std::cout << obj.m_id << " :: " << obj.m_name << std::endl;
	});

	std::cout << "Sorted Persons List based on Name using Lamba\n";
	std::sort(vecOfPersons.begin(), vecOfPersons.end(), [](const Person & first, const Person & sec) {
		if (first.m_name < sec.m_name)
			return true;
		else
			return false;
	});

	std::cout << "Sorted Persons List based on Name\n";
	std::for_each(vecOfPersons.begin(), vecOfPersons.end(), [](Person & obj) {
		std::cout << obj.m_id << " :: " << obj.m_name << std::endl;
	});

	return 0;
}

int main()
{
	main_uniqueWithLambda();
	main_Unique_UserClass();
	main_unique_int();
	main_sort();
	return 0;
}