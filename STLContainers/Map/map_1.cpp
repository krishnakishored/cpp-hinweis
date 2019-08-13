#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef MAP
#define MAP
#include<map>
#endif


#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional> 
#endif


#ifndef ALOGORITHM
#define ALOGORITHM
#include <algorithm>
#endif

using std::make_pair;
using std::string;
using std::pair;
using std::ifstream;
using std::map;

using std::cout;
using std::endl;


/*The STL provides the set and map containers that can automatically sort their objects and provide very fast 
search characteristics.*/
//Recipe 7-4. Storing Sorted Objects in a Container that Enables Fast Lookups
//Listing 7 - 15.  Creating a map

class MapObject
{
private:
	string m_Name;

public:
	MapObject(const string& name): m_Name{ name } {}
	const string& GetName() const {return m_Name;}
};

int main_MapObject() 
{

	std::map<int32_t, MapObject, std::greater<int32_t>> myMap
	{
		pair<int32_t, MapObject>(6, MapObject("Six")),
		pair<int32_t, MapObject>(3, MapObject("Three")),
		pair<int32_t, MapObject>(4, MapObject("Four")),
		pair<int32_t, MapObject>(1, MapObject("One")),
		make_pair(2, MapObject("Two"))	
	};

	for (auto&& number : myMap)
	{
		std::cout << number.second.GetName() << " ";
	}
	cout<<endl;
	
	myMap.emplace(pair<int32_t, MapObject>(5, MapObject("Five")));
	for (auto&& number : myMap)
	{
		std::cout << number.second.GetName() << " ";
	}
	
	cout<<endl;
	auto iter = myMap.find(3);
	if (iter != myMap.end())
	{
		std::cout << "Found: " << iter->second.GetName() << " ";
	}
	return 0;
}

//From C++ Cookbook
//Example 6-7. Using your own sorting functor
class Person {
	friend class PersonLessThan;
public:
	Person(const string& first, const string& last) :
		lastName_(last), firstName_(first) {}
	// ...
	string getFirstName() const { return(firstName_); }
	string getLastName() const { return(lastName_); }
private:
	string lastName_;
	string firstName_;
};

class PersonLessThan {
public:
	bool operator( )(const Person& per1, const Person& per2) const 
	{
		if (per1.lastName_ < per2.lastName_)          // Compare last
			return(true);                              // names, then
		else if (per1.lastName_ == per2.lastName_)    // first
			return(per1.firstName_ < per2.firstName_);
		else
			return(false);
	}
};

void main_map_ownFunctor() 
{
	map<Person, string, PersonLessThan> personMap;
	Person per1("Billy", "Silly"),
		per2("Johnny", "Goofball"),
		per3("Frank", "Stank"),
		per4("Albert", "Goofball");
	personMap[per1] = "cool";
	personMap[per2] = "not cool";
	personMap[per3] = "not cool";
	personMap[per4] = "cool";
	for (map<Person, string, PersonLessThan>::const_iterator p =
		personMap.begin(); p != personMap.end(); ++p) {
		cout << p->first.getFirstName() << " " << p->first.getLastName()
			<< " is " << p->second << endl;
	}
}
//6.6 Mapping strings to Other Things
void main_Map_lessByDefault() 
{
	map<string, string> strMap;
	strMap["Monday"] = "Montag";
	strMap["Tuesday"] = "Dienstag";
	strMap["Wednesday"] = "Mittwoch";
	strMap["Thursday"] = "Donnerstag";
	// strMap.insert(make_pair("Sunday", "Sonntag"));
	strMap.insert(pair<string, string>("Sunday", "Sonntag"));
	strMap.insert(std::make_pair("Saturday", "Samstag"));
	for (map<string, string>::iterator p = strMap.begin();p != strMap.end(); ++p) 
	
	{
		cout << "English: " << p->first
			<< ", German: " << p->second << endl;
	}
	cout << endl;
	strMap.erase(strMap.find("Tuesday"));
	for (map<string, string>::iterator p = strMap.begin();
	p != strMap.end(); ++p) {
		cout << "English: " << p->first
			<< ", German: " << p->second << endl;
	}
}



int main()
{
	// main_MapObject();
	// main_Map_lessByDefault();
	main_map_ownFunctor();
	return 0;
}