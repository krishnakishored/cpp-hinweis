#include<iostream>
#include<string>
#include<vector>

using namespace std;

//1. What is wrong with this code ? how to fix it ???
string& getName(int idx) {
	string name = (idx < 0) ? "Not Found" : "Found";
	return name; //Warning c4172 - returning address of local variable or temporary:name
}

/*
2.Given a class A.
What do these mean - 1.A a; A b(a);   ---- 2. A a; A g();
*/
class A
{
public:
	int m_x;
	A() : m_x(0) {}
	int getx() {
		cout << "getx" << endl;
		return m_x;
	}
	int* putx(int x) {

		cout << x << endl;
		return &x;
	}
	//~A(); // this will throw compilation error
	//virtual ~A()=0; //Q5
};



typedef int* (A::*fptr) (int);


/*
3a)Using the class def. above write a typedef for a pointer to member fun with no args and returns an int(e.g. like A's getx())
3b)write typedefs to a fun that takes a single int & returns a pointer to the arguments
*/

/*
Q4 What happens  when ptr goes out of scope
auto_ptr<T> ptr(new T[n]);//assume T: some known type; n: unsigned int
*/

/*
Q5 Suppose we have to add a public section of the class defined in Q2.
vituaal ~A()=0;
select all that apply
a)We should provide a default implementation for A's destructor
b)Since ~A() declared as pure virtual; only the derived classes need to implement this
c)We can no longer instantiate objects of class A
d) You can't declare a destructor as virtual

Answer : both B and C;
*/


/*
Q6 Using the def of A in Q2; Tabulate the likely values of a.size() and a.capacity() after each line
*/

/*
Q7 Select all that apply

a)Both a and s are constructed and a.m_cx==0 and s.mx==0
b)Both a and s are constructed but a.m_cx cannot be changed (SnippetA won't compile)
c)Only s is constructed and s.m_cx ==0 and snippetA will not compile
d) a.m_cx and s.m_cx are public
e) struct cannot have methods or constructors, hence snippet S will cause error

*/

/*
Q8A)Given map<int k,int V> m . write a piece of code to print sum of all values
map contains:(1,-3),(2,-2),(3,-1) , the o/p should be -6\

Q8B) Extra credit
write a map<int,int, ?>	such that it arranges in descending order of key values - (3,-1),(2,-2),(1,-3)
*/

/*
Q9) We have two threads A & B. a, b are shared values
in A: if(a%2==0){b = a+1;}
in B: if(a%2==0){a+=1;}

Identify the issues and the fix

*/

/*
Q10)Design exception guard class that will catch all uncaught exceptions
{
Guard g(args); // pass in the args that should be released gracefully in c
// do some stuff that could potentially throw
}

//assume availability of function void releaseResources(void *args);
*/


/*
Q11)Given a sorted array A of N distinct integers. write a method to test if there's an index i
A[i]= i;  (Note: runs from 0 to N-1). can this done in O(logN). How does your method compare
*/

/*
Q12) Consider a binary tree made up of nodes of the form

typedef struct Node
{
struct node *left,*right;
A *pa;//Assume Ais some known user-defined type
}Node;

You are given a fn:size_t freeNode(Node* n); //this fn takes O(1) and ...

write a method of the form:size_t freeTree(Node* root); that will
a)Release the .. associated with binary tree rooted at root and
b) return the total no.of nodes
if there are N nodes in the tree . what is the time complexity of freeTree
*/



int mainBOA() {

	/*
	Q1
	//string name = (idx < 0) ? "Not Found" : "Found"; // this works??
	string name = getName(2);
	cout << name;
	*/



	/*
	Q2
	A a; //calls the ctor
	A b(a);//calls the copy ctor provided by the compiler
	A g(); //??? functor (not defined)??? what happens now?
	*/

	/*
	Q4 What happens  when ptr goes out of scope
	int n = 10;
	template<typename T>
	auto_ptr<T> ptr(new T[n]);
	*/


	//Q3
	//A a;
	//fptr xyz = &A::putx;
	//(a.*xyz)(10);

	//Q6
	//vector<int> a(100000); //line 1: size? capacity?
	//a.clear();//line2
	//a.reserve(100);//line 3
	//vector<int>().swap(a);//line 4
	//a.reserve(100); //line 5


	//vector<string> S(100000); //line 1: size? capacity?
	//S.clear();//line2
	//S.reserve(100);//line 3
	//vector<string>().swap(S);//line 4
	//S.reserve(100); //line 5


	/*
	A a;
	int (A::*fpGetX)()= &A::getx;
	(a.*fpGetX)();
	*/


	/*
	Q6

	vector<A> a(100000); //line 1: size? capacity?
	a.clear();//line2
	a.reserve(100);//line 3
	vector<A>().swap(a);//line 4
	a.reserve(100); //line 5

	*/


	/*
	Q7

	class A {
	int m_cx = 0;
	A() : m_cx(-1) {}
	int getCx() const { return m_cx; }
	};

	A a;
	a.m_cx = 0;


	struct S {
	int m_cx = 0;
	S() : m_cx(-1) {}
	int getCx() const { return m_cx; }
	};

	S s;
	s.m_cx = 0;


	*/




	return 0;
}



/*


*/


/*
RAM BOA

2nd round
  Implement a Cache which has 3 positions .
  Input will be integer variables
   

   1st Round Interview
   -Balanced binary tree
   -Sorting techniques and its efficiency
   -mirror of  binary tree
    
	class Base2
	{
	public:
	void print()
	{
	cout<<"I am from base2 normal print function"<<endl;
	}
	 
	 void virtual vprint()
	 {
	 cout<<"I am from base2 normal print function"<<endl;
	 }
	 };
	  
	  class Derived2:public Base2
	  {
	  private://also try with public:
	  void print()
	  {
	  cout<<"I am from Derived1 normal print function"<<endl;
	  }
	   
	   void virtual vprint()
	   {
	   cout<<"I am from Derived1 vprint print function"<<endl;
	   }
	   };
	    
		Derived2 d;
		//d.vprint();
		 
		 Base2* bp;
		 bp=&d;
		 bp->vprint();
		  
		  Hash table and its complexity,min and max
		  Map should be ordered base on some ci
		  -implement a functor which takes two class objects


		  */

		  //Suresh BOA

		  /*
		  1. Two stacks - one Queue
		  2. Vector<int>v(100); -remove even numbers
		  3. Mirror a binary tree
		  4. Strings
		  5. Synchronization

		  */

// Name: 
// a) an in-place sorting algorithm
// b) a stable sorting algorithm
 

// The number of nodes in a balanced binary tree of height H is:
// [a] O(H) [b] O(log(H)) [c] exponential in H [d] None of these
 

// If a hash function takes an O(N) (i.e. “big-Oh-of-N”) time to hash a key in a hash table of size N:
// a) The hash function is a good choice
// b) The hash function is a poor choice
// c) It does not matter, the lookup time will be O(1) in a hash table
 

// What is the time complexity to reverse a sequence of N characters?
 

// Can you find both the maximum and minimum of a given sequence of integers in just one sweep over the sequence? Yes/No
 

// Given a public class method:
// const int X2() const { cout << “X2” << endl; }
// If aobj is an object of class A, what happens when you compile and run: aobj.getX2();

 

 

// Comment on the following snippet:
// int x = 10; int *px = &x;
// *px = 20;
// delete px;
 

 

// Given the following snippet:
// int *px = new int;
// px = 0;
// delete px;

// What will happen when the last line is executed? Explain in one sentence.

 

 

// Answers

// In-place algorithms - Selection sort, Bubble sort
// Stable Algorithms - Merge sort, Insertion Sort.

// O(log(H))
// Option C -  The lookup time will be O(1)
// O(N).
// Yes. It's possible to find min and max in one sweep.
// This will throw an compilation error.
// The function definition of X2() doesn't return anything.

//  (guess aobj.getX2() is a typo)

// Runtime error - Using delete on a stack variable results in a undefined behavior.
// Will result in a memory leak.
// There might be a compiler optimization but the program will execute fine.         