//#############################################################
// const
//   - A compile time constraint that an object can not be modified
//

/*
  Why use const
		a.) Guard against inadvertent write to the variable.
		b.) Self documenting
		c.) Enable compiler to do more optimiztion, making code tighter.
		d.) const usually means the variable is put in ROM. 
*/

#include<iostream>
#include<string>
#include<vector>


using std::string;
using std::vector;
using std::endl;
using std::cout;

int main_const_basics()
{
   int i = 1;

   const int *p1 = &i; // data is const, pointer is not

   int *const p2 = &i; // pointer is const, data is not

   // compilation error: uninitialized const 'p3'
   // const int *const p3; // data and pointer are both const

   // Triky one
   int const *p4 = &i; // data is const, pointer is not

   // If const is on the left  of *, data is const
   // If const is on the right of *, pointer is const

   //--------------------------------------------------------------------------
   /*casting*/
   const int i2 = 10;
   const_cast<int &> (i2) = 6; // removes the const

   // int j;
   //add the const
   //static_cast<const int&> (j) = 7; // compilation error-    assignment of read-only location 'j'

   return 0;
}



class Dog {
   int age;
   string name;
public:
   Dog() { age = 3; name = "dummy"; }
   
   // const parameters
   void setAge(const int& a) { age = a; }
   void setAge(int& a) { age = a; }

   // void setAge(const int a) {} //  const is useless here as it's a pass-by-value
   
   // Const return value
   const string& getName() {return name;}
   // const string getName() {return name;} // const is useles here, as return value is temporary
   
   // const function
   void printDogName() const { cout << name << "const" << endl; }
   void printDogName() { cout << getName() << " non-const" << endl; }
};


//const` used with functions - as args, return value, const functions(that don't modify members). 
//const functions can only call other const functions within them.

int main_const_used_with_functions(){
   Dog d;
   d.printDogName();
   
   const Dog d2;
   d2.printDogName();

   /*casting*/
   // const Dog d2(8);
   // d2.f();  // const f()
   // const_cast<Dog&>(d2).f() // non-const f()

   // Dog d(9);
   // d.f(); // invoke non-const f()
   // static_cast<const Dog&>(d).f(); // invoke const f()
   
   return 0;
}

class BigArray {
   vector<int> v; // huge vector
   mutable int accessCounter;
   
   int* v2; // another int array

public:
   int getItem(int index) const {
      accessCounter++;
      //use of mutable  is similar to - const_cast<BigArray*>(this)->accessCounter++;
      return v[index];
   }
   
   //  void setV2Item(int index, int x)  const {
   void setV2Item(int index, int x) {
      *(v2+index) = x;
   }
    
   // // Quiz:
   // const int*const fun(const int*const& p)const;
};

int main()
{
   // main_const_basics();
   // main_const_used_with_functions();
   BigArray b;
   return 0;
}

