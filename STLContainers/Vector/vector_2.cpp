
#include <iostream>
#include <vector>

//****************************************************************************

//http://thispointer.com/be-careful-of-hidden-cost-while-using-stdvector-with-user-defined-objects/
//***************************************************************************************

//to create a vector of 10000 Item objects.
class Item {
public:
	static int m_ConstructorCalledCount;
	static int m_DestCalledCount;
	static int m_CopyConstructorCalledCount;
	Item() {
		m_ConstructorCalledCount++;
	}
	~Item() {
		m_DestCalledCount++;
	}
	Item(const Item& obj) {
		m_CopyConstructorCalledCount++;
	}
};
int Item::m_ConstructorCalledCount = 0;
int Item::m_CopyConstructorCalledCount = 0;
int Item::m_DestCalledCount = 0;

//A factory class to create Item objs
class ItemFactory
{
public:
	//Culprit in this case : 

	/*
	- Inside the for loop we created 10000 objects, so constructor is called 10000 times.
	- Then after creating every object we inserted the newly created object in vector 10000 times, therefore copy constructor is called 10000 times and destructor of old 10000 Item object is called.
	- In last line of function, we returned the vector and all its content was copied to vecOfItems vector, so again 10000 times copy constructor is called and destructor of old 10000 Item object is called.
	
	*/
	static std::vector<Item> getItemObjects(int count)
	{
		std::vector<Item> vecOfItems;
		vecOfItems.reserve(count);
		for (int var = 0; var < count; ++var) {
			vecOfItems.push_back(Item());
		}
		return vecOfItems;
	}
};

class ItemFactoryImproved
{
public:
	static void getItemObjects_1(std::vector<Item> & vecItems, int count)
	{
		vecItems.assign(count, Item());
	}
	static std::vector<Item> getItemObjects_2(int count)
	{
		std::vector<Item> vecOfItems;
		vecOfItems.assign(count, Item());
		return vecOfItems;
	}
};

int main_Vector_HiddenCosts()
{

	int count = 10000;

	std::vector<Item> vecOfItems;
	vecOfItems = ItemFactory::getItemObjects(count);//this could create 30000 Objs

	std::cout << "Total Item Objects constructed = " << (Item::m_ConstructorCalledCount + Item::m_CopyConstructorCalledCount) << std::endl;
	std::cout << "Constructor called  " << Item::m_ConstructorCalledCount << " times" << std::endl;
	std::cout << "Copy Constructor called  " << Item::m_CopyConstructorCalledCount << " times" << std::endl;
	std::cout << "Total Item Objects destructed = " << Item::m_DestCalledCount << std::endl << std::endl;

	Item::m_ConstructorCalledCount = 0;
	Item::m_CopyConstructorCalledCount = 0;
	Item::m_DestCalledCount = 0;
	//With this, instead of copying 10000 objects, all objects will be moved to new vector
	std::vector<Item> vecOfItems_2 = ItemFactory::getItemObjects(count);
	std::cout << "Total Item Objects constructed = " << (Item::m_ConstructorCalledCount + Item::m_CopyConstructorCalledCount) << std::endl;
	std::cout << "Constructor called  " << Item::m_ConstructorCalledCount << " times" << std::endl;
	std::cout << "Copy Constructor called  " << Item::m_CopyConstructorCalledCount << " times" << std::endl;
	std::cout << "Total Item Objects destructed = " << Item::m_DestCalledCount << std::endl << std::endl;

	Item::m_ConstructorCalledCount = 0;
	Item::m_CopyConstructorCalledCount = 0;
	Item::m_DestCalledCount = 0;
	std::vector<Item> vecOfItems_3 = ItemFactoryImproved::getItemObjects_2(count);
	std::cout << "Total Item Objects constructed = " << (Item::m_ConstructorCalledCount + Item::m_CopyConstructorCalledCount) << std::endl;
	std::cout << "Constructor called  " << Item::m_ConstructorCalledCount << " times" << std::endl;
	std::cout << "Copy Constructor called  " << Item::m_CopyConstructorCalledCount << " times" << std::endl;
	std::cout << "Total Item Objects destructed = " << Item::m_DestCalledCount << std::endl << std::endl;

	Item::m_ConstructorCalledCount = 0;
	Item::m_CopyConstructorCalledCount = 0;
	Item::m_DestCalledCount = 0;
	std::vector<Item> vecOfItems_4;
	ItemFactoryImproved::getItemObjects_1(vecOfItems_4, count);
	std::cout << "Total Item Objects constructed = " << (Item::m_ConstructorCalledCount + Item::m_CopyConstructorCalledCount) << std::endl;
	std::cout << "Constructor called  " << Item::m_ConstructorCalledCount << " times" << std::endl;
	std::cout << "Copy Constructor called  " << Item::m_CopyConstructorCalledCount << " times" << std::endl;
	std::cout << "Total Item Objects destructed = " << Item::m_DestCalledCount << std::endl << std::endl;
	
	return 0;
}


//***************************************************************************************
//http://thispointer.com/how-to-fill-a-vector-with-random-numbers-in-c/

struct RandomGenerator {
	int maxValue;
	RandomGenerator(int max) :
		maxValue(max) {
	}

	int operator()() {
		return rand() % maxValue;
	}
};

int main_randomNumbers() 
{
	// Initialize a vector with 10 ints of value 0
	std::vector<int> vecOfRandomNums(10);

	// Generate 10 random numbers by lambda func and fill it in vector
	std::generate(vecOfRandomNums.begin(), vecOfRandomNums.end(), []() {
		return rand() % 100;
	});

	std::cout << "Random Number Generated by Lambda Function" << std::endl;
	for (int val : vecOfRandomNums)
		std::cout << val << " ";

	// Generate 10 random numbers by a Functor and fill it in vector
	std::generate(vecOfRandomNums.begin(), vecOfRandomNums.end(),
		RandomGenerator(500));
	std::cout << std::endl;
	std::cout << "Random Number Generated by Functor" << std::endl;
	for (int val : vecOfRandomNums)
		std::cout << val << " ";

	return 0;
}
//***************************************************************************************

//http://thispointer.com/removing-all-occurences-of-an-element-from-vector-in-on-complexity/

//Let�s say vector contain following numbers 1,2,5,4,5,1,5,7,8,9
//so that vector contents should become � 1 2 4 1 7 8 9 .
//Use Remove-Erase idiom

void removeAllMatchingElements_nonEfficient(std::vector<int> & vec, int elem)
{
	std::vector<int>::iterator it = vec.begin();
	while (it != vec.end())
	{
		if (*it == elem)
		{
			it = vec.erase(it);
		}
		else
			it++;
	}
}

void removeAllMatchingElements_Efficient(std::vector<int> & vec, int elem)
{
	vec.erase(std::remove(vec.begin(), vec.end(), elem), vec.end());
}

void displayVector(std::vector<int> & vec)
{
	std::vector<int>::iterator it = vec.begin();
	while (it != vec.end())
		std::cout << (*it++) << " ";
	std::cout << std::endl;
}

int main_erase_remove_idiom()
{
	int arr[10] = { 1,2,5,4,5,1,5,7,8,9 };

	std::vector<int> vec(arr, arr + 10);
	displayVector(vec);
	//removeAllMatchingElements_nonEfficient(vec, 5);
	auto newEnd = std::remove(vec.begin(), vec.end(), 5);
	std::vector<int>::iterator it = vec.begin();
	std::cout << "After remove: ";
	displayVector(vec);
	
	std::cout << "\nusing itr returned from remove:";
	while ( it!= newEnd)
		std::cout << (*it++) << " ";
	std::cout << std::endl;


	std::vector<int> vec2(arr, arr + 10);
	removeAllMatchingElements_Efficient(vec2, 5);
	displayVector(vec2);

	return 0;
}

int main_removeErase()

{    // constructors used in the same order as described above:
    std::vector<int> first;                               // empty vector of ints
    std::vector<int> second(4, 100);                      // four ints with value 100
    std::vector<int> third(second.begin(), second.end()); // iterating through second
    std::vector<int> fourth(third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16, 2, 77, 29, 108, 786, 255, 134};
    std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    int m = 2;
    //erase mth element
    std::vector<int> sixth(fifth);                       // a copy of fifth
    sixth.erase (sixth.begin()+m);

    std::cout << "The contents of sixth are:";
    for (std::vector<int>::iterator it = sixth.begin(); it != sixth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    //erase elements from mth to nth (element n excluded)

    std::vector<int> seventh(fifth);                       // a copy of fifth
    
    int n = 5;
    seventh.erase(seventh.begin()+m, seventh.begin()+n);
     
    std::cout << "The contents of seventh are:";
    for (std::vector<int>::iterator it = seventh.begin(); it != seventh.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}

int main()
{
	main_randomNumbers();
	main_Vector_HiddenCosts();
	main_erase_remove_idiom();
	main_removeErase();
	return 0;
}

