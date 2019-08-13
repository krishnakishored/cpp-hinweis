#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#include<array>

#include<exception>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cerr;

//6.4 Storing Pointers in a vector
static const int NUM_OBJECTS = 10;

class MyClass { /*...*/ };
void main_Vector_of_pointers() {
	vector<MyClass*> vec;
	MyClass* p = NULL;
	// Load up the vector with MyClass objects
	for (int i = 0; i < NUM_OBJECTS; i++) {
		p = new MyClass();
		vec.push_back(p);
	}
	// Do something useful with this data, then delete the objects when you're done
	for (vector<MyClass*>::iterator pObj = vec.begin();
	pObj != vec.end(); ++pObj) {
		delete *pObj; // Note that this is deleting what pObj points to, which is a pointer
	}
	/*You should also explicitly empty the vector after you have deleted the pointers for
	the same reason that you should set pointer variables to NULL when you’re done with them.
	This will prevent them from erroneously being deleted again.*/
	vec.clear(); // Purge the contents so no one tries to delete them again
}

//6.3 Copying a vector -
/*There are a couple of ways to do this. You can use a copy constructor
when you create a vector, or you can use the assign member function.*/

// Util function for printing vector contents
template<typename T>
void vecPrint(const vector<T>& vec) {
	cout << "{";
	for (typename vector<T>::const_iterator p = vec.begin();p != vec.end(); ++p) 
	{
		cout << "{" << *p << "} ";
	}
	cout << "}" << endl;
}
void main_Vector_assign() 
{
	vector<string> vec(5);
	string foo[] = { "My", "way", "or", "the", "highway" };
	vec[0] = "Today";
	vec[1] = "is";
	vec[2] = "a";
	vec[3] = "new";
	vec[4] = "day";
	vector<string> vec2(vec);
	vecPrint(vec2);
	vec.at(0) = "Tomorrow";
	vec2.assign(vec.begin(), vec.end()); // Copy each element over with assign
	vecPrint(vec2); //copy ctor    // {{Tomorrow} {is} {a} {new} {day} }                  
	vec2.assign(&foo[0], &foo[5]); // Assign works for anything that behaves like an iterator
	vecPrint(vec2);     // {{My} {way} {or} {the} {highway} }      
	vector<string>::iterator p;
	p = find(vec.begin(), vec.end(), "day");
	vec2.assign(vec.begin(), p); // Copy a subset of the full range of vec
	vecPrint(vec2);      //{{Tomorrow} {is} {a} {new} }        // 
}


//6.1 Using vectors Instead of Arrays
void main_VectorBasic() {

	vector<int>    intVec;
	vector<string> strVec;
	// Add elements to the "back" of the vector with push_back
	intVec.push_back(3);
	intVec.push_back(9);
	intVec.push_back(6);
	string s = "Army";
	strVec.push_back(s);
	s = "Navy";
	strVec.push_back(s);
	s = "Air Force";
	strVec.push_back(s);
	// You can access them with operator[], just like an array
	for (vector<string>::size_type i = 0; i < intVec.size(); ++i) {
		cout << "intVec[" << i << "] = " << intVec[i] << '\n';
	}
	// Or you can use iterators
	for (vector<string>::iterator p = strVec.begin();p != strVec.end(); ++p) 
	{
		cout << *p << '\n';
	}

	string sarr[3] = { "Ernie", "Bert", "Elmo" };
	string t = "Oscar";
	strVec.assign(&sarr[0], &sarr[3]); // Assign this sequence
	
	for (vector<string>::iterator p = strVec.begin();p != strVec.end(); ++p) 
	{
		cout << *p << ' ';
		// Ernie Bert Elmo 
	}

	strVec.assign(5, t);              // Assign 5 copies of t
	for (vector<string>::iterator p = strVec.begin(); p != strVec.end(); ++p)
	{
		cout << *p << ' ';
		//o/p:  Oscar Oscar Oscar Oscar Oscar 
	}

	// If you need to be safe, use at( ) instead of operator[].  
	// It throws out_of_range if the index you use is > size( ).
	try {
		intVec.at(300) = 2;
	}
	catch (std::out_of_range& e) {
		cerr << "\nout_of_range: " << e.what() << endl;
		//o/p: out_of_range: vector
	}

}

//Based on C++ cookbook
int main()
{
	// main_VectorBasic();
	// main_Vector_assign();
	main_Vector_of_pointers();
	return 0;
}