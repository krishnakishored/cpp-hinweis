#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef UNORDERED_SET
#define UNORDERED_SET
#include<unordered_set>
#endif

#ifndef SET
#define SET
#include <set>
#endif

#ifndef MAP
#define MAP
#include<map>
#endif



#ifndef UNORDERED_MAP
#define UNORDERED_MAP
#include<unordered_map>
#endif



#ifndef STRING
#define STRING
#include <string>
#endif


using std::cout;
using std::endl;

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

//From C++ CookBook

//6.9 Storing Containers in Containers
//Example 6 - 12. Storing set pointers in a map
using std::set;
using std::string;
using std::map;

typedef set<string> SetStr;
typedef map<string, SetStr*> MapStrSetStr;

//Dummy database class
class DBConn {
public:
	void beginTxn() {}
	void endTxn() {}
	void execSql(string& sql) {}
};
/*
 a simple transaction log class that stores its data as a map of string-set pointer pairs.
 Imagine that you need to store a series of SQL statements in batches, 
 to be executed against a relational database all at once sometime in the future. 
 That’s what SimpleTxnLog does
 */
class SimpleTxnLog 
{
public:
	SimpleTxnLog() {}
	~SimpleTxnLog() { purge(); }
	// Add an SQL statement to the list
	void addTxn(const string& id,
		const string& sql) {
		SetStr* pSet = log_[id];      // This creates the entry for this id if it isn't there
		if (pSet == NULL) 
		{            
			pSet = new SetStr();
			log_[id] = pSet;
		}
		pSet->insert(sql);
	}
// Apply the SQL statements to the database, one transaction at a time
	void apply() {
		for (MapStrSetStr::iterator p = log_.begin();
		p != log_.end(); ++p) {
			conn_->beginTxn();
			// Remember that a map iterator actually refers to an object of pair<Key,Val>.
			// The set pointer is stored in p->second.
			for (SetStr::iterator pSql = p->second->begin();pSql != p->second->end(); ++pSql) 
			{
				string s = *pSql;
				conn_->execSql(s);
				cout << "Executing SQL: " << s << endl;
			}
			conn_->endTxn();
			delete p->second;
		}
		log_.clear();
	}

	void purge() {
		for (MapStrSetStr::iterator p = log_.begin();
		p != log_.end(); ++p)
			delete p->second;
		log_.clear();
	}
	// ...
private:
	MapStrSetStr log_;
	DBConn* conn_;
};

int main()
{
	main_unordered_Set_Map();
	return 0;
}