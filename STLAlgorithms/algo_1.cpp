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

/*
 *  remove-erase, std::bind, std::placeholders, functional adapter
 *  std::copy, lambda expression, auto, callbacks
 */
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

int main_EraseRemove()
{
	int arr[10] = { 1,2,5,4,5,1,5,7,8,9 };

	std::vector<int> vec(arr, arr + 10);
	displayVector(vec);
	removeAllMatchingElements_nonEfficient(vec, 5);
	displayVector(vec);

	std::vector<int> vec2(arr, arr + 10);
	removeAllMatchingElements_Efficient(vec2, 5);
	displayVector(vec2);

	return 0;
}



using namespace std::placeholders;

/*std::bind is a Functional Adaptor i.e. it takes a function as input and returns a new function Object as an output 
with with one or more of the arguments of passed function bound or rearranged.*/

int add(int first, int second)
{
	return first + second;
}

bool divisible(int num, int den)
{
	if (num % den == 0)
		return true;
	return false;
}

int approach_1()
{
	int arr[10] = { 1,20,13,4,5,6,10,28,19,15 };
	int count = 0;
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		if (divisible(arr[i], 5))
			count++;
	}
	return count;
}

int approach_2()
{
	int arr[10] = { 1,20,13,4,5,6,10,28,19,15 };
	return static_cast<int>(std::count_if(arr, arr + sizeof(arr) / sizeof(int), std::bind(&divisible, _1, 5)));
}

int main_bind()
{
	int x = add(4, 5);
	// Will return 9

	// What if we want to fix 12 as the first argument
	auto new_add_func = std::bind(&add, 12, _1);

	x = new_add_func(5);
	// Will return 17

	std::cout << x << std::endl;

	auto mod_add_func = std::bind(&add, _2, _1);//change the order 

	x = mod_add_func(12, 15);
	// Will return 27
	std::cout << x << std::endl;

	/*std::bind returns a function object.
	In above examples we have either save this new function object in auto variable or used it directly.
	But we can also store them using std::function Function object */
	std::function<int(int) > mod_add_funcObj = std::bind(&add, 20, _1);
	x = mod_add_funcObj(15);
	// Will return 35

	std::cout << x << std::endl;
	std::cout << approach_1() << std::endl;
	std::cout << approach_2() << std::endl;//count_if (), takes a unary predicate - returns bool using bind

	return 0;
}



//http://thispointer.com/c11-auto-tutorial-and-examples/

//Cannot change the type of already initialized auto variable
//auto x = 1;
//compile time error:  x = "dummy";

//Can not declare auto variable without initialization 
//because its type is based on initiazing value.  //auto a;



auto sum(int x, int y) -> int
{
	return x + y;
}

int main_auto()
{

	// Storing a int inside a auto variable
	auto var_1 = 5;

	// Storing a character inside a auto variable
	auto var_2 = 'C';

	std::cout << var_1 << std::endl;
	std::cout << var_2 << std::endl;

	// Storing Lambda function inside a auto variable
	auto fun_sum = [](int a, int b)
	{
		return a + b;
	};

	std::cout << fun_sum(4, 5) << std::endl;

	std::map<std::string, std::string> mapOfStrs;

	// Insert data in Map
	mapOfStrs.insert(std::pair<std::string, std::string>("first", "1"));
	mapOfStrs.insert(std::pair<std::string, std::string>("sec", "2"));
	mapOfStrs.insert(std::pair<std::string, std::string>("thirs", "3"));

	// Iterate over the map and display all data;
	// Create an iterator
	std::map<std::string, std::string>::iterator it = mapOfStrs.begin();
	while (it != mapOfStrs.end())
	{
		std::cout << it->first << "::" << it->second << std::endl;
		it++;
	}

	// Iterate using auto
	auto itr = mapOfStrs.begin();
	while (itr != mapOfStrs.end())
	{
		std::cout << itr->first << "::" << itr->second << std::endl;
		itr++;
	}

	// auto x = 1;
	// Cannot change the type of already initialized auto variable
	// Error will occur at compile time
	// x = "dummy";

	// Can not declare auto variable without initialization
	// because its type is based on initiazing value.
	//auto a;

	auto value = sum(3, 5);

	std::cout << value << std::endl;
	return 0;
}






//http://thispointer.com/designing-callbacks-in-c-part-3-c11-lambda-functions/

//Lambda functions are a kind of anonymous functions in C++.
//These are mainly used as callbacks in C++.
//You can pass arguments to it & It can return the result like a normal function.

int main_LambdaFn() {
	int arr[] = { 1, 2, 3, 4, 5 };
	std::copy(arr, arr + (sizeof(arr) / sizeof(int)),std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	int mul = 5;

	std::for_each(arr, arr + sizeof(arr) / sizeof(int), [&](int x) {
		x = x * 2;
		std::cout << x << " ";
		// Can modify the mul inside this lambda function because all outer scope elements has write access here.
		
	});
	
	std::cout << std::endl;
	std::for_each(arr, arr + sizeof(arr) / sizeof(int), [=](int &x) {//got modified????
		x = x*mul;
		std::cout << x << " ";
		// Can not modify the mul inside this lambda function because
		// all outer scope elements has read only access here.
		// mul = 9;

	});
	std::cout << std::endl;

	std::copy(arr, arr + (sizeof(arr) / sizeof(int)), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	

	std::for_each(arr, arr + sizeof(arr) / sizeof(int), [](int x) {

		// No access to mul inside this lambda function because no outer scope elements are not visible here.
	
		//	std::cout<<mul<<" ";

	/*Error (active)	an enclosing-function local variable cannot be referenced in a lambda body
	unless it is in the capture list	STL_Algorithms*/

	});
	std::cout << std::endl;

	return 0;
}



//Callback is a function that we pass to another APIs as argument while calling them
//http://thispointer.com/designing-callbacks-in-c-part-1-function-pointers/

/*
Callbacks in C++ can be of 3 types,

1.) Function Pointer
2.) Function Objects / Functors
3.) Lambda functions
*/



class Encryptor {
	bool m_isIncremental;
	int m_count;
public:
	Encryptor() {
		m_isIncremental = 0;
		m_count = 1;
	}
	Encryptor(bool isInc, int count) {
		m_isIncremental = isInc;
		m_count = count;
	}
	std::string operator()(std::string data) {
		for (int i = 0; i < data.size(); i++)
			if ((data[i] >= 'a' && data[i] <= 'z')
				|| (data[i] >= 'A' && data[i] <= 'Z'))
				{
					if (m_isIncremental){
					data[i] = data[i] + m_count;
				}
					
				else{
					data[i] = data[i] - m_count;
				}
				

				}
					
		return data;
	}
};

std::string buildCompleteMessage(std::string rawData, Encryptor encyptorFuncObj) {
	// Add some header and footer to data to make it complete message
	rawData = "[HEADER]" + rawData + "[FooTER]";
	// Call the callBack provided i.e. function pointer to encrypt the
	rawData = encyptorFuncObj(rawData);
	return rawData;
}

int main_Callbacks() 
{
	std::string msg = buildCompleteMessage("SampleString", Encryptor(true, 1));
	std::cout << msg << std::endl;

	msg = buildCompleteMessage("SampleString", Encryptor(true, 2));
	std::cout << msg << std::endl;

	msg = buildCompleteMessage("SampleString", Encryptor(false, 1));
	std::cout << msg << std::endl;

	return 0;
}


int main()
{
	main_bind();
	main_EraseRemove();
	main_auto();
	main_Callbacks();
	main_LambdaFn();

	return 0;
}