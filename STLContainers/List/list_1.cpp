#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif


#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional>
#endif

using std::cout;
using std::endl;
using std::list;
using std::cout;
using std::endl;
using std::cerr;
using std::string;


#include<forward_list>

//ToDo

/* ?????
http://thispointer.com/different-ways-to-initialize-a-list-in-c/
http://thispointer.com/how-to-erase-elements-from-a-list-in-c-using-iterators/
http://thispointer.com/how-to-remove-elements-from-a-list-while-iterating/
http://thispointer.com/how-to-remove-elements-from-a-list-based-on-value/
*/


//http://thispointer.com/stdlist-tutorial-and-usage-details/
int main_list_thispointer()
{
	list<int> listOfNumbers;

	//Inserting elements at end in list
	listOfNumbers.push_back(5);
	listOfNumbers.push_back(6);

	//Inserting elements at front in list
	listOfNumbers.push_front(2);
	listOfNumbers.push_front(1);
	cout<<"list of Numbers:"<<endl;
	// Iterating over list elements and display them
	list<int>::iterator it = listOfNumbers.begin();
	while (it != listOfNumbers.end())
	{
		cout << (*it) << "  ";
		it++;
	}
	cout << endl;


	//Inserting elements in between insert(pos,elem) member function. 	
	it = listOfNumbers.begin();
	it++;
	it++;
	// Iterator 'it' is at 3rd position.
	listOfNumbers.insert(it, 4);


	// Iterating over list elements and display them
	it = listOfNumbers.begin();
	while (it != listOfNumbers.end())
	{
		cout << (*it) << "  ";
		it++;
	}
	cout << endl;


	//Erasing elements in between the list using erase(position) member function. 
	// Let's iterate to 3rd position
	it = listOfNumbers.begin();
	it++;
	it++;
	// Iterator 'it' is at 3rd position. Now erase this element.
	listOfNumbers.erase(it);

	// Iterating over list elements and display them
	it = listOfNumbers.begin();
	while (it != listOfNumbers.end())
	{
		cout << (*it) << "  ";
		it++;
	}
	cout << endl; //Lets remove all elements with value greater than 3. 
	listOfNumbers.remove_if([](int elem) 
	{ if (elem > 3)
		return true;
	else
		return false;
	});

	it = listOfNumbers.begin();
	while (it != listOfNumbers.end())
	{
		std::cout << (*it) << "  ";
		it++;
	}
	cout << endl;

	return 0;
}


//Recipe 7-3. Storing a Set of Elements that Is Constantly Altered

//Listing 7 - 11.  Using a forward_list
/*
A forward_list does not contain the methods emplace or emplace_back. It does contain emplace_front and also emplace_after
which allow you to add elements to the beginning of the forward_list or after a specific position in the forward_list.
*/

int main_ForwardList()
{
	std::forward_list<int32_t> myList{ 1, 2, 3, 4, 5 };

	myList.emplace_front(6);

	auto forwardIter = myList.begin();
	++forwardIter;
	++forwardIter;
	myList.emplace_after(forwardIter, 9);

	for (auto&& number : myList)
	{
		std::cout << number << " ";
	}

	return 0;
}
//Listing 7 - 10.  Using a list
int main_ListEmplace() 
{
	std::list<int32_t> myList{ 1, 2, 3, 4, 5 };

	myList.emplace_front(6);
	myList.emplace_back(7);

	auto forwardIter = myList.begin();
	++forwardIter;//there's no + offset Index for list
	++forwardIter;
	myList.emplace(forwardIter, 9);

	auto reverseIter = myList.end();
	--reverseIter;
	--reverseIter;
	--reverseIter;
	myList.emplace(reverseIter, 8);

	for (auto&& number : myList)
	{
		std::cout << number << " ";
	}

	return 0;
}

//from C++ cookbook

//6.5 Storing Objects in a list
// A simple functor for printing
template<typename T>
struct printer {
	void operator( )(const T& s) {
		cout << s << ' ';
	}
};

bool inline even(int n) {
	return(n % 2 == 0);
}

printer<string> strPrinter;
printer<int>    intPrinter;

void main_list_merge_splice() {
	
	list<string> lstOne;
	list<string> lstTwo;
	list<string> lstThree;
	list<string> lstFour;
	lstOne.push_back("Red");
	lstOne.push_back("Green");
	lstOne.push_back("Blue");
	lstTwo.push_front("Orange");
	lstTwo.push_front("Yellow");
	lstTwo.push_front("Fuschia");
	
	lstFour.push_back("Red2");
	lstFour.push_back("Green2");
	lstFour.push_back("Blue2");

	lstThree.push_front("Orange2");
	lstThree.push_front("Yellow2");
	lstThree.push_front("Fuschia2");

	for_each(lstOne.begin(), lstOne.end(), strPrinter);
	cout << endl;
	for_each(lstTwo.begin(), lstTwo.end(), strPrinter);
	// Print each element in the list with a custom functor, 
	cout << endl;
	
	// Find somewhere to insert the other list
	list<string>::iterator p = std::find(lstFour.begin(), lstFour.end(), "Green2");
	//splices two lists together
	lstFour.splice(p, lstThree);   // Insert lstTwo right before "Green"		
	
	for_each(lstFour.begin(), lstFour.end(), strPrinter);
	cout << endl;
	for_each(lstThree.begin(), lstThree.end(), strPrinter);
	cout << endl;


	lstOne.sort();           // list has a member for sorting
	lstTwo.sort();
	lstOne.merge(lstTwo);    // Merge the two lists and print
	for_each(lstOne.begin(), lstOne.end(), strPrinter); 
	// the results (the lists must be sorted before merging)
	cout << endl;
	list<int> intLst;
	intLst.push_back(0);
	intLst.push_back(1);
	intLst.push_back(2);
	intLst.push_back(3);
	intLst.push_back(4);
	for_each(intLst.begin(), intLst.end(), intPrinter);
	cout << endl;
	// Remove all values greater than 2
	intLst.remove_if(std::bind2nd(std::greater<int>(), 2));
	for_each(intLst.begin(),intLst.end(),intPrinter);
	//or remove all even values
	intLst.remove_if(even);
	cout << endl;
	for_each(intLst.begin(), intLst.end(), intPrinter);


	//list<string> strLst, myOtherStrLst;
	//list<string>::iterator p;
	//// ...
	//string s = "Scion";
	//p = find(strLst.begin(), strLst.end(), "Toyota"); // std::find from <algorithm>
	//strLst.insert(p, s);       // Insert s right before p
	//strLst.insert(p, 16, s);   // Insert 16 copies of s right before p
	//strLst.insert(p, myOtherStrLst.begin(), myOtherStrLst.end()); // Insert everything in myOtherStrLst before p

}

int main(){
	// main_ListEmplace();
	// main_ForwardList();
	// main_list_thispointer();
	main_list_merge_splice();
	return 0;
}