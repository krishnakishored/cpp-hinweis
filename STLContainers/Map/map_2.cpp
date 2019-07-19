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

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional> //for greater in set<SetObject,greater<SetObject>> mySet2{}
#endif




#ifndef ALOGORITHM
#define ALOGORITHM
#include <algorithm>
#endif

using std::make_pair;
using std::pair;
using std::ifstream;
using std::string;

//http://www.bogotobogo.com/cplusplus/stl2_map.php

/*
//map class template looks like this: 
//STP map implementations are more like a balanced binary search trees (BST). To be more specific, they are red-black trees.

std::map<Key, Data, Compare, Alloc>

namespace std {
template <class Key, class T,
	class Compare = less<Key>,
	class Allocator = allocator<pair<const Key, T> > >
	class map;
*/

//ToDo
//Multimap example - Anagrams from a dictionary
//Maps for Word Count



//read in the data to a map
int read_words(std::vector<std::string> & words, std::ifstream & in) {
	int i = 0;
	while (!in.eof()) {
		in >> words[i++];
	}
	/*return i- 1;*/
	return i;
}

int main_ReadFromIfStream() 
{
	std::ifstream ifp("names.txt");
	std::vector<std::string> w(500);
	int number_of_words = read_words(w, ifp);
	w.resize(number_of_words);

	for (auto it : w)
		std::cout << it << " ";
	std::cout << std::endl;

	std::map<std::string, std::string> wMap;

	for (int i = 0; i < number_of_words;) {
		wMap.insert(std::pair<std::string, std::string>(w[i], w[i + 1]));
		i += 2;
	}

	std::cout << "\nwMap.size()=" << wMap.size() << std::endl;
	std::cout << std::endl;
	for (auto it = wMap.begin(); it != wMap.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;

	return 0;

}


int main_MapInitialization() 
{
	typedef std::map<std::string, int> mapType;
	mapType populationMap;

	populationMap.insert(pair<std::string, int>("China", 1939));
	populationMap.insert(pair<std::string, int>("India", 1187));
	
	//To avoid implicit type conversion, pass the correct type explicitly by using value_type
	populationMap.insert(mapType::value_type("US", 310));	
	populationMap.insert(mapType::value_type("Indonesia", 234));
	
	populationMap.insert(make_pair("Brasil", 193));
	populationMap.insert(make_pair("Pakistan", 170));

	// Erase the end element using the erase function
	// Because it's ordered map (by key), map elements are not in the order of the entry 
	mapType::iterator iter = --populationMap.end();
	populationMap.erase(iter);// In this map it's US since it's ordered alphabetically (default??)

	// output the size of the map
	std::cout << "Size of populationMap: " << populationMap.size() << '\n';

	for (iter = populationMap.begin(); iter != populationMap.end(); ++iter) {
		std::cout << iter->first << ": "
			<< iter->second << " million\n";
	}

	// find will return an iterator to the matching element if it is found
	// or to the end of the map if the key is not found
	std::string country("Indonesia");
	iter = populationMap.find(country);
	
	if (iter != populationMap.end())
		std::cout << country << "'s populations is " << iter->second << " million\n";
	else
		std::cout << "Key is not in populationMap" << '\n';

	//insert and update[] in a map - using map::insert for adding and map::operator[] for updates is recommended.
	populationMap["Indonesia"] = 244;//update
	std::cout << country << "'s populations is " << populationMap["Indonesia"] << " million after update[]\n";

	// clear the entries in the map
	populationMap.clear();


	return 0;
}


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
		std::cout << number.second.GetName() << std::endl;
	}
	
	myMap.emplace(pair<int32_t, MapObject>(5, MapObject("Five")));
	for (auto&& number : myMap)
	{
		std::cout << number.second.GetName() << std::endl;
	}
	

	auto iter = myMap.find(3);
	if (iter != myMap.end())
	{
		std::cout << "Found: " << iter->second.GetName() << std::endl;
	}
	return 0;
}

int main()
{
	main_MapObject();
	main_MapInitialization();
	main_ReadFromIfStream();
	return 0;
}