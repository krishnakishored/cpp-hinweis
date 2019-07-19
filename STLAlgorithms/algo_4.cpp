#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif


#ifndef STRING
#define STRING
#include <string>
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
//Recipe 8 - 1. Using an iterator to Define a Sequence within a Container
//using an iterator with vector
int main_Iterators_for_each()
{
	using IntVector = std::vector<int32_t>; //type alias
	using IntVectorIterator = IntVector::iterator;
	using ConstIntVectorIterator = IntVector::const_iterator;
	using ReverseIntVectorIterator = IntVector::reverse_iterator;
	using ConstReverseIntVectorIterator = IntVector::const_reverse_iterator;
	
	IntVector myVector = { 0,1,2,3,4 };
	std::cout << "The values in myVector" << std::endl;
	for (IntVectorIterator iter = myVector.begin(); iter != myVector.end(); iter++) {
		std::cout << "The value is: " << *iter << std::endl;
	}

	//Using non-const iterators
	IntVector myVector2(5, 0);//5 copies of value 0
	int32_t value{ 0 };
	for (IntVectorIterator iter = myVector2.begin(); iter != myVector2.end(); iter++) {
		*iter = value++;// possible due to non-const iterator	
	}

	std::cout<<std::endl << "The values in myVector2(using non-const_iterator)" << std::endl;
	for (IntVectorIterator iter = myVector2.begin(); iter != myVector2.end(); iter++) {
	std::cout << "The value is: " << *iter << std::endl;
	}

	IntVector myVector3(5, 0);
	int32_t value3{ 0 };
	for (ReverseIntVectorIterator iter = myVector3.rbegin(); iter != myVector3.rend(); iter++) {
		*iter = value3++;
	}
	std::cout << std::endl << "The values in myVector3(const reverse iterator)" << std::endl;
	for (ConstReverseIntVectorIterator iter = myVector3.crbegin(); iter != myVector3.crend(); iter++) {
		std::cout << "The value is: " << *iter << std::endl;
	}
	std::cout << std::endl << "The values in myVector3(const iterator)" << std::endl;
	for (ConstIntVectorIterator iter = myVector3.cbegin(); iter != myVector3.cend(); iter++) {
		std::cout << "The value is: " << *iter << std::endl;
	}

	//using for_each : Recipe 8-2. Calling a Function on Every Element in a Container
	std::vector<int> myVector4 = { 11,22,33,44,55 };
	std::cout << std::endl << "The values in myVector4(for_each & lambda function)" << std::endl;
	for_each(myVector4.begin(), myVector4.end(), [](int value) {std::cout << "the value is: " << value << std::endl; });
	return 0;
}


//Recipe 8 - 4. Counting Instances of a Value in a Sequence
//Listing 8 - 12.  Using character predicates with count
int main_countif() 
{
	std::string myString = { "The Bruce Sutherland!" };
	
	//auto nCapitals = count_if(myString.begin(), myString.end(), [](int character) {return static_cast<bool>(isupper(character)); });
	auto nCapitals = count_if(myString.begin(), myString.end(), [](auto&& character) {return static_cast<bool>(isupper(character)); });//rvalue reference
	std::cout << "No.of Capitals: " << nCapitals << std::endl;
	
	auto nLowerCase = count_if(myString.begin(), myString.end(), [](auto&& character) {return static_cast<bool>(islower(character)); });//rvalue reference
	std::cout << "No.of Lowercase: " << nLowerCase << std::endl;

	auto nAlphaNum = count_if(myString.begin(), myString.end(), [](auto&& character) {return static_cast<bool>(isalpha(character)); });//rvalue reference
	std::cout << "No.of AlphaNumerics: " << nAlphaNum << std::endl;

	auto nPunctuationMarks = count_if(myString.begin(), myString.end(), [](auto&& character) {return static_cast<bool>(ispunct(character)); });//rvalue reference
	std::cout << "No.of PunctuationMarks: " << nPunctuationMarks << std::endl;

	auto nWhiteSpace = count_if(myString.begin(), myString.end(), [](auto&& character) {return static_cast<bool>(isspace(character)); });//rvalue reference
	std::cout << "No.of White Spaces: " << nWhiteSpace << std::endl;

	return 0;
}

//using count
int main_count() {
	std::vector<int> myVector{ 3, 2, 3, 7, 3, 8, 9, 3 };
	auto number = count(myVector.begin(), myVector.end(), 3);
	std::cout << "The no.of 3's in myVector: " << number << std::endl;
	return 0;
}


//Recipe 8.3  Finding the Maximum and Minimum Values  in a Container
//Listing 8-8. Using min_element in conjunction with a class that contains a < operator
class MyClass {
private:
	int m_Value;
public:
	MyClass(const int value) :m_Value(value) {}
	int GetValue() const { return m_Value; }
	bool operator<(const MyClass& other) const {
		return m_Value < other.m_Value;
	}
};
bool CompareMyClassesGreater(const MyClass& left, const MyClass& right)
{
	return left.GetValue() < right.GetValue();//both min_element & max_element use '<' in comparator funtion
}


int main_Min_Max_element() 
{
	std::vector<int> myVector = {4,10,6,9,1};
	std::vector<int>::iterator iter_min;
	iter_min = min_element(myVector.begin(), myVector.end());//min_element & max_element both return an iterator
	auto iter_max = max_element(myVector.begin(), myVector.end());
	std::cout << "Minimum Value: " << *iter_min << std::endl;
	std::cout << "Maximum Value: " << *iter_max << std::endl;

	std::vector<MyClass> myVector2 = { 4,10,6,9,1 };
	auto minimum = min_element(myVector2.begin(), myVector2.end());
	if (minimum != myVector2.end()) {
		std::cout << "Minimum Value (using '<' operator of class): " << (*minimum).GetValue() << std::endl;
	}

	auto maximum = max_element(myVector2.begin(), myVector2.end(), CompareMyClassesGreater);
	if (maximum != myVector2.end()) {
		std::cout << "Maximum Value (using comparator): " << (*maximum).GetValue() << std::endl;
	}
	return 0;
}


//predicate for descending order
bool IsGreater(int left, int right) {

	return left > right;
}

//Recipe 8 - 6. Sorting Elements in a Sequence
int main_Sort() {
	std::vector<int> myVector{ 10, 6, 4, 7, 8, 3, 9 };
	sort(myVector.begin(), myVector.end());
	std::vector<int>::const_iterator iter;
	
	std::cout <<std::endl << "using iter:";
	for (iter = myVector.cbegin(); iter != myVector.cend(); iter++) {
		std::cout << *iter << " ";
	}
	std::cout<<std::endl << "using auto:";
	for (auto elem : myVector) { 
		std::cout << elem << " ";
	}
	//using predicate for descending order
	std::cout << std::endl << "using predicate for descending:";
	sort(myVector.begin(), myVector.end(),IsGreater);
	for (auto&& elem : myVector) {//using rvalue reference
		std::cout << elem << " ";
	}


	return 0;
}

//Recipe 8-5. Finding Values in a Sequence
int main_Find() 
{
	std::string myString = { "The Bruce Sutherland!" };
	auto found = find(myString.begin(), myString.end(), 'e');
	
	while (found != myString.end()) {
		std::cout << "Found: " << *found << std::endl;
		found = find(found + 1, myString.end(), 'e');
	}
	std::string::iterator found_iter = find(myString.begin(), myString.end(), 'Z');
	if (found_iter != myString.end()) {
		std::cout << "Found: " << *found_iter << std::endl;
	}
	else {
		std::cout << 'Z' << " - not Found" << std::endl;
	}
	
	return 0;
}

int main()
{
	main_count();
	main_countif();
	main_Find();
	main_Iterators_for_each();
	main_Min_Max_element();
	main_Sort();
	return 0;
}