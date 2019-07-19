#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

using std::cout;
using std::endl;
using std::list;


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

int main(){
	main_ListEmplace();
	main_ForwardList();
	main_list_thispointer();
	return 0;
}