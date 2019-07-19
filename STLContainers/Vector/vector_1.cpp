#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif


//****************************************************************************
//http://thispointer.com/stdvector-and-iterator-invalidation/
int main_iterator_invalidation()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> vecArr(arr, arr + sizeof(arr) / sizeof(int));

	auto it = vecArr.begin();
	for (; it != vecArr.end(); it++)
		std::cout << (*it) << "  ";

	std::cout << std::endl;

	it = vecArr.begin();

	// Insert an element in position 2,Now old iterator it has become invalidated
	// SO, using it as it is can result in undefined behavior
	vecArr.insert(it + 2, 1, 200);

	// Reinitialize the invalidated iterator to the begining.
	it = vecArr.begin();

	for (; it != vecArr.end(); it++)   // Undefined Behavior if old iterator is not updated
		std::cout << (*it) << "  ";

	return 0;
}

int main_itrInvalidate_eraseElement()
{
	/*std::vector<int> vecArr;*/
	/*for (int i = 1; i <= 10; i++)
		vecArr.push_back(i);*/
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> vecArr(arr, arr + sizeof(arr) / sizeof(int));
	
	for (auto it = vecArr.begin(); it != vecArr.end(); it++)
		std::cout << (*it) << "  ";

	std::cout << "size of vector: "<<vecArr.size()<<std::endl;

	// Erase and element with value 5.
	/*auto it = std::find(vecArr.begin(), vecArr.end(), 5);
	if (it != vecArr.end())
		vecArr.erase(it);
	*/
	// Now iterator 'it' is invalidated because it still points to old location, which has been deleted.
	//	So, if you will try to use the same iterator then it can show undefined behavior.
		
	//Solution: After calling the erase function update the value of iterator �it� i.e.
	/*As, erase() function returns an iterator pointing to the new location of the element that followed the last element erased by the same function.
		Also, if the element deleted was the last element of the container then it returns the end of the container.*/

	// Erase and element with value 5.
	auto it = std::find(vecArr.begin(), vecArr.end(), 5);
	if (it != vecArr.end())
		it = vecArr.erase(it);
	std::cout << "size of vector: " << vecArr.size() << std::endl;

	for (; it != vecArr.end(); it++)   // Unpredicted Behavior if iterator not updated
		std::cout << (*it) << "  ";          

	return 0;
}
//****************************************************************************
//http://thispointer.com/importance-of-constructors-while-using-user-defined-objects-with-stdvector/
class NewSample
{
public:
	
	NewSample()	{}// Remove these comments to make it compilable
	NewSample(const NewSample & obj)
	{}
	NewSample& operator=(const NewSample & obj){return *this;} //-W: reaches end of non-void function
};

int main_Vector_UserDefinedObj()
{

	std::vector<NewSample> vecOfNewSample(2);
	// It will create 2 Objects using default constructor and insert them in vector.

	std::cout << "vecOfNewSample Size = " << vecOfNewSample.size() << std::endl;
	std::cout << "vecOfNewSample Capacity = " << vecOfNewSample.capacity() << std::endl;

	std::vector<NewSample> vecOfNewSample_2;
	vecOfNewSample_2.reserve(2);
	// It will make the capacity of vector to contain 2 objects.
	// ALthough size will remain 0.

	std::cout << "vecOfNewSample_2 Size = " << vecOfNewSample_2.size() << std::endl;
	std::cout << "vecOfNewSample_2 Capacity = " << vecOfNewSample_2.capacity() << std::endl;

	return 0;
}


//http://thispointer.com/how-stdvector-works-internally/
/*
When std::vector�s internal memory completely finishes then it increases the size of its memory. To do that it performs following steps,
1.) It will allocate a bigger chunk of memory on heap i.e. almost double the size of previously allocated.
2.) Then it copies all the elements from old memory location to new one. Yes it copies them, so in case our elements are user defined objects
then their copy constructor will be called. Which makes this step quite heavy in terms of speed.
3.) Then after successful copying it deletes the old memory.
*/

struct Sample
{
	Sample() {}
	Sample(const Sample & obj)
	{
		std::cout << "Sample copy constructor" << std::endl;
	}
};
int main_capacity_size()
{
	std::vector<Sample> vecOfInts;

	std::cout << "Capacity :: " << vecOfInts.capacity() << std::endl;
	std::cout << "Size :: " << vecOfInts.size() << std::endl;
	int capcity = vecOfInts.capacity();
	for (int i = 0; i < capcity + 1; i++)
		vecOfInts.push_back(Sample());

	std::cout << "Capacity :: " << vecOfInts.capacity() << std::endl;
	std::cout << "Size :: " << vecOfInts.size() << std::endl;

	for (int i = 0; i < capcity + 1; i++)
		vecOfInts.push_back(Sample());

	std::cout << "Capacity :: " << vecOfInts.capacity() << std::endl;
	std::cout << "Size :: " << vecOfInts.size() << std::endl;

	return 0;
}
//****************************************************************************


void example1() {
	// Initialize vector with 5 integers Default value of all 5 ints will be 0.
	std::vector<int> vecOfInts(5);

	for (int x : vecOfInts)
		std::cout << x << " ";
	std::cout << std::endl;
}

void example2() {
	// Initialize vector to 5 string objects with value "Hi"
	std::vector<std::string> vecOfStr(5, "Hi");
	
	for (std::string str : vecOfStr)
		std::cout << str << " ";
	std::cout << std::endl;

}

void example3() {
	// Create an array of string objects
	std::string arr[] = { "first", "sec", "third", "fourth" };

	// Initialize vector with a string array
	std::vector<std::string> vecOfStr(arr, arr + sizeof(arr) / sizeof(std::string));
	for (std::string str : vecOfStr)
		std::cout << str << " ";
	std::cout << std::endl;
}

void example4() {
	// Create an std::list of 5 string objects
	std::list<std::string> listOfStr;
	listOfStr.push_back("first");
	listOfStr.push_back("sec");
	listOfStr.push_back("third");
	listOfStr.push_back("fourth");

	// Initialize a vector with std::list
	std::vector<std::string> vecOfStr(listOfStr.begin(), listOfStr.end());
	
	for (std::string str : vecOfStr)
		std::cout << str << " ";
	std::cout << std::endl;
	// Initialize a vector with other string object(vector)
	std::vector<std::string> vecOfStr3(vecOfStr);

	for (std::string str : vecOfStr3)
		std::cout << str << " ";
	std::cout << std::endl;

}

int main_initializingVector() 
{

	example1();
	example2();
	example3();
	example4();
	return 0;
}


int main(){
	main_initializingVector();
	main_iterator_invalidation();
	main_itrInvalidate_eraseElement();
	main_Vector_UserDefinedObj();
	main_capacity_size();
	return 0;
}