#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef SET
#define SET
#include <set>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

using std::cout;
using std::endl;
using std::set;
using std::string;

class SetObject
{
  private:
	string m_Name;
	int32_t m_Key{};

  public:
	SetObject(int32_t key, const string &name) : m_Name{name}, m_Key{key}{}
	SetObject(int32_t key) : SetObject(key, ""){}
	const string& GetName() const
	{
		return m_Name;
	}
	int32_t GetKey() const
	{
		return m_Key;
	}
	bool operator<(const SetObject &other) const
	{
		return m_Key < other.m_Key;
	}
	bool operator>(const SetObject &other) const
	{
		return m_Key > other.m_Key;
	}
};

int main_Set_reordering(int argv, char *argc[])
{
	set<SetObject> mySet{{6, "Six"},{3, "Three"},{4, "Four"},{1, "One"}, {2, "Two"}};
	// Ordering elements in a set from highest to lowest
	set<SetObject,std::greater<SetObject> > mySet_2{{6, "Six"},{3, "Three"},{4, "Four"},{1, "One"}, {2, "Two"}};
	for (auto &&number : mySet)
	{
		cout << number.GetName() << " ";
	}
	cout<<endl;
	for (auto &&number : mySet_2)
	{
		cout << number.GetName() << " ";
	}
	cout<<endl;

	auto iter = mySet.find(3);
	if (iter != mySet.end())
	{
		cout << "Found: " << iter->GetName() << " " ;
	}
	cout<<endl;
	// Adding elements to a set
	mySet.emplace(SetObject( 5, "Five" ));

	for (auto &&number : mySet)
	{
		cout << number.GetName() << " ";
	}
	cout<<endl;

	return 0;
}

//from C++ cookbook

//Example 6-11. Storing pointers in a set
// Class for comparing strings given two string pointers
struct strPtrLess {
	bool operator( )(const string* p1,
		const string* p2) {
		assert(p1 && p2);
		return(*p1 < *p2);
	}
};
//**********************************************************************************

void main_set_pointers() {
	set<string*, strPtrLess> setStrPtr;  // Give it my special less-than functor
	string s1 = "Tom";
	string s2 = "Dick";
	string s3 = "Harry";
	setStrPtr.insert(&s1);
	setStrPtr.insert(&s2);
	setStrPtr.insert(&s3);
	for (set<string*, strPtrLess>::const_iterator p =
		setStrPtr.begin(); p != setStrPtr.end(); ++p)
		cout << **p << endl;  // Dereference the iterator and what it points to
}


//6.8 Storing Objects in Sorted Order
void main_set_Strings() {
	set<string> setStr;
	string s = "Bill";
	setStr.insert(s);
	s = "Steve";
	setStr.insert(s);
	s = "Randy";
	setStr.insert(s);
	s = "Howard";
	setStr.insert(s);
	for (set<string>::const_iterator p = setStr.begin();
	p != setStr.end(); ++p)
		cout << *p << endl;
}

int main()
{
	// main_set_pointers();
	main_set_Strings();
	return 0;
}