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

// int main_MapObject() 
int main()
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