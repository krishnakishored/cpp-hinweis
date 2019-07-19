#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef UNORDERED_SET
#define UNORDERED_SET
#include<unordered_set>
#endif


#ifndef UNORDERED_MAP
#define UNORDERED_MAP
#include<unordered_map>
#endif



#ifndef STRING
#define STRING
#include <string>
#endif

//Recipe 7-5. Storing Unsorted Elements in a Container for Very Fast Lookups
class SetObject;

namespace std
{
	template <>
	class hash<SetObject>
	{
	public:
		template <typename... Args>
		size_t operator()(Args&&... setObject) const
		{
			return hash<string>()((forward<Args...>(setObject...)).GetName());//perfect forwarding??
		}
	};
}

class SetObject
{
private:
	std::string m_Name;
	size_t m_Hash{};
public:
	SetObject(const std::string& name): m_Name{ name }, m_Hash{ std::hash<SetObject>()(*this) }{}

	const std::string& GetName() const{return m_Name;}

	const size_t& GetHash() const {return m_Hash;}

	bool operator==(const SetObject& other) const {return m_Hash == other.m_Hash;}
};

class MapObject
{
private:
	std::string m_Name;
public:
	MapObject(const std::string& name): m_Name{ name }{}
	const std::string& GetName() const { return m_Name;}
};

int main_unordered_Set_Map() 
{
	std::unordered_set<SetObject> mySet;
	mySet.emplace("Five");
	mySet.emplace("Three");
	mySet.emplace("Four");
	mySet.emplace("One");
	mySet.emplace("Two");
	std::cout << std::showbase << std::hex;

	for (auto&& number : mySet)
	{
		std::cout << number.GetName() << " - " << number.GetHash() << std::endl;
	}

	auto iter = mySet.find({ "Three" });
	if (iter != mySet.end())
	{
		std::cout << "Found: " << iter->GetName() << " with hash: " << iter->GetHash() << std::endl;
	}

	std::unordered_map<int32_t, MapObject> myMap;
	myMap.emplace(std::pair<int32_t, MapObject>(5, MapObject("Five")));
	myMap.emplace(std::pair<int32_t, MapObject>(3, MapObject("Three")));
	myMap.emplace(std::pair<int32_t, MapObject>(4, MapObject("Four")));
	myMap.emplace(std::pair<int32_t, MapObject>(1, MapObject("One")));
	myMap.emplace(std::pair<int32_t, MapObject>(2, MapObject("Two")));

	std::cout << std::showbase << std::hex;

	for (auto&& number : myMap)
	{
		std::cout << number.second.GetName() << std::endl;
	}

	auto iter2 = myMap.find(3);
	if (iter2 != myMap.end())
	{
		std::cout << "Found: " << iter2->second.GetName() << std::endl;
	}

	return 0;
}

int main()
{
	main_unordered_Set_Map();
	return 0;
}