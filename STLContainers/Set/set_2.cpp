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

// int main_Set_reordering(int argv, char *argc[])
int main()
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
