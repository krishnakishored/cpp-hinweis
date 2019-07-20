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

#include <functional>

/*
 *  generator, for_each, find_if
 *
 */

//http://thispointer.com/stdgenerate-tutorial-and-example/
/*std::generate is a STL algorithm useful in generating data for a sequential container by calling passed function object continuously */


struct Task
{
	int m_id;
	std::string m_name;
	Task(int id, std::string name) :
		m_id(id), m_name(name)
	{}
};

class TaskFactory
{
	static int m_counter;
public:
	Task * getTask()
	{
		m_counter++;
		Task * taskPtr = new Task(m_counter, "Task_" + std::to_string(m_counter));
		return taskPtr;
	}
	Task * operator ()()
	{
		return getTask();
	}

};
int TaskFactory::m_counter = 0;

void approach_1(std::vector<Task *> & vecList)
{
	TaskFactory factory;
	for (int i = 0; i < 10; i++)
	{
		Task * ptr = factory.getTask();
		vecList[i] = ptr;
	}
}

void approach_3(std::vector<Task *> & vecList)
{
	TaskFactory factory;
	std::generate(vecList.begin(), vecList.end(), std::bind(std::mem_fun(&TaskFactory::getTask), &factory));
}
void approach_2(std::vector<Task *> & vecList)
{
	// TaskFactory factory;
	std::generate(vecList.begin(), vecList.end(), TaskFactory());
}

void displayTasks(std::vector<Task *> & vecList)
{
	std::for_each(vecList.begin(), vecList.end(), [](const Task * taskPtr) {
		std::cout << taskPtr->m_id << " :: " << taskPtr->m_name << std::endl;
	});
}

void generate_n_example(std::vector<Task *> & vecList)
{
	std::generate_n(vecList.begin(), 5, TaskFactory());
}
int main_generate()
{

	std::vector<Task *> vecList(10);

	approach_1(vecList);
	displayTasks(vecList);

	approach_2(vecList);
	displayTasks(vecList);

	approach_3(vecList);
	displayTasks(vecList);

	std::vector<Task *> vecList_2(10);
	generate_n_example(vecList_2);
	std::for_each(vecList_2.begin(), vecList_2.begin() + 5, [](const Task * taskPtr) {
		std::cout << taskPtr->m_id << " :: " << taskPtr->m_name << std::endl;
	});

	return 0;

}



//The std::for_each() algorithm allows us to iterate over a given range of elements and perform operations over them.
//http://thispointer.com/iterating-over-a-range-of-user-defined-objects-and-calling-member-function-using-stdfor_each/


/*how to iterate over a container of user defined objects and call a member function on each of the iterating element.*/
class Employee
{
	int m_id;
	std::string m_name;
public:
	Employee(int id, std::string name)
	{
		m_id = id;
		m_name = name;
	}
	void displayEmployeeInfo()
	{
		std::cout << "Employee ID :: " << m_id << "  , Name :: " << m_name << std::endl;
	}
};

void getEmployeeList(std::vector<Employee *> & vecOfEmployees)
{
	vecOfEmployees.push_back(new Employee(1, "Varun"));
	vecOfEmployees.push_back(new Employee(1, "John"));
	vecOfEmployees.push_back(new Employee(1, "Ritu"));
	vecOfEmployees.push_back(new Employee(1, "Jack"));
}

int main_for_each_memberFunction()
{
	std::vector<Employee *> vecOfEmployees;
	getEmployeeList(vecOfEmployees);
	std::for_each(vecOfEmployees.begin(), vecOfEmployees.end(), std::bind(std::mem_fun(&Employee::displayEmployeeInfo), std::placeholders::_1));
	std::for_each(vecOfEmployees.begin(), vecOfEmployees.end(), [](Employee * emp) {
		delete emp;
	});
	return 0;
}




//http://thispointer.com/stdfor_each-tutorial-usage-details-with-examples/


void addNames(std::vector<std::string> & vecNames)
{
	vecNames.push_back("Varun");
	vecNames.push_back("Ajay");
	vecNames.push_back("John");
	vecNames.push_back("Rita");
}
void printName(std::string name)
{
	std::cout << name << std::endl;
}

class NameChecker
{
	std::string m_biggerName;
	int m_nameCount;
public:
	NameChecker() : m_biggerName(""), m_nameCount(0)
	{}
	void operator()(std::string name)
	{
		if (m_biggerName.size() < name.size())
			m_biggerName = name;
		m_nameCount++;
	}

	const std::string& getBiggerName() const {
		return m_biggerName;
	}

	int getNameCount() const {
		return m_nameCount;
	}
};

void example_1(std::vector<std::string> & vecNames)
{
	// Display Each name in vector using std::for_each and global function
	std::for_each(vecNames.begin(), vecNames.end(), printName);
}

void example_2(std::vector<std::string> & vecNames)
{
	// Now Display Each name in vector using std::for_each and Lambda function
	std::for_each(vecNames.begin(), vecNames.end(), [](std::string name)
	{
		std::cout << name << std::endl;
	});
}
void example_3(std::vector<std::string> & vecNames)
{
	// Now count the number of names and in end print the biggest name
	// Let's do this with std::for_each and a function object.

	NameChecker nameCheckerObj = std::for_each(vecNames.begin(), vecNames.end(), NameChecker());

	std::cout << std::endl << "Biggest Name = " << nameCheckerObj.getBiggerName() << std::endl;
	std::cout << std::endl << "Total Names = " << nameCheckerObj.getNameCount() << std::endl;

}
int main_for_each()
{
	std::vector<std::string> vecNames;
	addNames(vecNames);
	example_1(vecNames);
	std::cout << std::endl;
	example_2(vecNames);
	std::cout << std::endl;
	example_3(vecNames);

	return 0;

}


class Item
{
private:
	std::string  m_ItemId;
	int m_Price;
	int m_Count;
public:
	Item(std::string id, int price, int count) :
		m_ItemId(id),  m_Price(price), m_Count(count)
	{}
	int getCount() const {
		return m_Count;
	}
	std::string getItemId() const {
		return m_ItemId;
	}
	int getPrice() const {
		return m_Price;
	}
	bool operator==(const Item & obj2) const
	{
		if (this->getItemId().compare(obj2.getItemId()) == 0)
			return true;
		else
			return false;
	}
};


std::vector<Item> getItemList()
{
	std::vector<Item> vecOfItems;
	vecOfItems.push_back(Item("D121", 100, 2));
	vecOfItems.push_back(Item("D122", 12, 5));
	vecOfItems.push_back(Item("D123", 28, 6));
	vecOfItems.push_back(Item("D124", 8, 10));
	vecOfItems.push_back(Item("D125", 99, 3));
	return vecOfItems;
}

bool priceComparision(Item & obj, int y)
{
	if (obj.getPrice() == y)
		return true;
	else
		return false;
}


template <typename T>
struct GenericComparator
{
	typedef  int (T::*GETTER)() const;
	GETTER m_getterFunc;
	int m_data;
	GenericComparator(GETTER getterFunc, int data)
	{
		m_getterFunc = getterFunc;
		m_data = data;
	}
	bool operator()(const Item  & obj)
	{
		if ((obj.*m_getterFunc)() == m_data)
			return true;
		else
			return false;
	}
};


bool IsLesser10(int i) {
	return (i < 10);
}

int main_find_if()
{

	std::vector<int> vecData{ 1,2,3,4,5 };

	std::vector<int>::iterator it1;
	it1 = std::find(vecData.begin(), vecData.end(), 2);
	if (it1 != vecData.end())
		std::cout << *it1 << std::endl;
	it1 = std::find_if(vecData.begin(), vecData.end(), IsLesser10);
	if (it1 != vecData.end())
		std::cout << *it1 << std::endl;


	std::vector<Item> vecOfItems = getItemList();
	std::vector<Item>::iterator it = std::find(vecOfItems.begin(), vecOfItems.end(), Item("D126", 99, 0));

	if (it != vecOfItems.end())
		std::cout << "Found with ID :: " << it->getItemId() << " Price ::" << it->getPrice() << " Count :: " << it->getCount() << std::endl;
	else
		std::cout << "Item with ID :: D126 not Found" << std::endl;

	it = std::find(vecOfItems.begin(), vecOfItems.end(), Item("D124", 99, 0));
	if (it != vecOfItems.end())
		std::cout << "Found with ID :: " << it->getItemId() << " Price ::" << it->getPrice() << " Count :: " << it->getCount() << std::endl;
	else
		std::cout << "Item with ID :: D124 not Found" << std::endl;



	it = std::find_if(vecOfItems.begin(), vecOfItems.end(), [](Item const& obj) {
		return obj.getPrice() == 28;
	});

	if (it != vecOfItems.end())
		std::cout << "Found with ID :: " << it->getItemId() << " Price ::" << it->getPrice() << " Count :: " << it->getCount() << std::endl;
	else
		std::cout << "Item not Found" << std::endl;


	//using bind(), std::placeholders::_1
	it = std::find_if(vecOfItems.begin(), vecOfItems.end(), std::bind(priceComparision, std::placeholders::_1, 28));
	if (it != vecOfItems.end())
		std::cout << "Found with ID :: " << it->getItemId() << " Price ::" << it->getPrice() << " Count :: " << it->getCount() << std::endl;
	else
		std::cout << "Item not Found" << std::endl;



	it = std::find_if(vecOfItems.begin(), vecOfItems.end(), GenericComparator<Item>(&Item::getPrice, 99));
	if (it != vecOfItems.end())
		std::cout << "Found with ID :: " << it->getItemId() << " Price ::" << it->getPrice() << " Count :: " << it->getCount() << std::endl;
	else
		std::cout << "Item not Found" << std::endl;


	return 0;
}


int main(){

	main_find_if();
	main_for_each();
	main_for_each_memberFunction();
	main_generate();

	return 0;
}