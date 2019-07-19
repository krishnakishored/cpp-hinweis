//http://cppquiz.org/quiz/question/25
// #pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<future>
#include<string>
#include<map>

using namespace std;
/*	Q27:o/p?
hint: What is the dynamic type of a
This is a way to get polymorphic behaviour for operator <<.
*/
struct A {
	virtual std::ostream &put(std::ostream &o) const {
		return o << 'A';
	}
};

struct B : A {
	virtual std::ostream &put(std::ostream &o) const {
		return o << 'B';
	}
};

std::ostream &operator<<(std::ostream &o, const A &a) {
	return a.put(o);
}

void mainQ27() {
	B b;
	std::cout << b;
}
//****************************************
/*	Q140:o/p?
In get_size_1 and get_size_2, the parameter is a pointer, therefore the sizeof operator returns the size of the pointer.
Although the parameter of get_size_2 is an array, it is adjusted into a pointer
In get_size_3, the parameter is a reference to an array of size 10, therefore the sizeof operator returns the size of the array in terms of bytes
*/
size_t get_size_1(int* arr)
{
	return sizeof arr;
}

size_t get_size_2(int arr[])
{
	return sizeof arr;
}

size_t get_size_3(int(&arr)[10])
{
	return sizeof arr;
}

int mainQ140()
{
	int array[10];
	cout << (sizeof(array) == get_size_1(array));
	cout << (sizeof(array) == get_size_2(array));
	cout << (sizeof(array) == get_size_3(array));
	return 0;
}
//****************************************
/*
Q116:????
Hint:The T&& in the the templated functions do not necessarily denote an rvalue reference, it depends on the type that is used to instantiate the template.
If instantiated with an lvalue, it collapses to an lvalue reference,if instantiated with an rvalue, it collapses to an rvalue reference.
Scott Meyers's advice that use std::forward for universal references, and std::move for rvalue references.
*/

/*
In this example, all three functions are called once with an lvalue and once with an rvalue.
In all cases, calling with an lvalue (i) collapses T&& x to T& x (an lvalue reference), and calling with an rvalue (20) collapses T&& x to T&& x (an rvalue reference).
Inside the functions, x itself is always an lvalue, no matter if its type is an rvalue reference or an lvalue reference.
-For the first example, y(int&) is called for both cases. Output: 11.
-For the second example, move(x) obtains an rvalue reference, and y(int&&)is called for both cases. Output: 22.
-For the third example, forward<T>(x) obtains an lvalue reference when x is an lvalue reference, and an rvalue reference when x is an rvalue reference,
resulting in first a call to y(int&)and then a call to y(int&&). Output: 12.
*/

/* ???Error???
int y(int &) { return 1; }
int y(int &&) { return 2; }

template <class T> int f(T &&x) { return y(x); }
template <class T> int g(T &&x) { return y(std::move(x)); }
template <class T> int h(T &&x) { return y(std::forward<T>(x)); }

int mainQ116() {
int i = 10;
std::cout << f(i) << f(20);
std::cout << g(i) << g(20);
std::cout << h(i) << h(20);
return 0;
}

*/
//****************************************
/*
Q48?????
Hint: When we don't call get() on a future returned from async(), when is the asynchronous task guaranteed to complete?

o/p: z

Explanation:
The destructor of a future returned from async is required to block until the async task has finished (see elaboration below).
Since we don't assign the futures that are returned from async() to anything, they are destroyed at the end of the full expression (at the end of the line in this case). §12.2¶3 in the standard:
"Temporary objects are destroyed as the last step in evaluating the full-expression (1.9) that (lexically) contains the point where they were created."
This means that the first async call is guaranteed to finish execution before async() is called the second time, so, while the assignments themselves may happen in different threads, they are synchronized.

Elaboration on synchronization:
According to § 30.6.8¶5 of the standard:
Synchronization:[...]
If the implementation chooses the launch::async policy,
— the associated thread completion synchronizes with (1.10) the return from the first function that successfully detects the ready status of the shared state
or with the return from the last function that releases the shared state, whichever happens first.
In this case, the destructor of std::future<> returned by the async() call is "the last function that releases the shared state", therefore it synchronizes with (waits for) the thread completion.
Scott Meyers writes more about this http://scottmeyers.blogspot.com/2013/03/stdfutures-from-stdasync-arent-special.html
*/
void main48() {
	std::string x = "x";

	std::async(std::launch::async, [&x]() {
		x = "y";
	});
	std::async(std::launch::async, [&x]() {
		x = "z";
	});

	std::cout << x;//#include<string>
}
//*********************************************
/*
Q122:
hint:"Since signed, unsigned, long, and short by default imply int, a type-name appearing after one of those speciﬁers is treated as the name being (re)declared."
*/
typedef long long ll;

void foo(unsigned ll) {
	std::cout << "1";
}

void foo(unsigned long long) {
	std::cout << "2";
}

void mainQ122() {
	foo(2ull);
}

//*********************************************
/*Q3
Hint: What are the ranks of the conversions "double => int" and "double => unsigned int"?
Both conversions are of type "floating-integral conversion", which has rank "conversion" - same rank so compilation error
*/
void f(int) { std::cout << 1; }
void f(unsigned) { std::cout << 2; }

void mainQ3() {
	//f(-2.5);//Error: 'f': ambiguous call to overloaded function	

}
//*********************************************
/*Q37
Hint:The type denoted by decltype(e) is deﬁned as follows:— if e is an unparenthesized id-expression [...], decltype(e) is the type of the entity named by e."
*/
void mainQ37() {
	int a = 0;
	decltype(a) b = a;
	b++;
	std::cout << a << b;
}

//*********************************************
/*Q152: Plain char, signed char, and unsigned char are three distinct types*/
void mainQ152() {
	if (std::is_signed<char>::value) {
		std::cout << std::is_same<char, signed char>::value;
	}
	else {
		std::cout << std::is_same<char, unsigned char>::value;
	}
}

//*********************************************

/*Q9:
Hint:Aliasing
Explanation:
When f() is called with a as both parameters, both arguments refer to the same variable. This is known as aliasing. First, a is set to 3, then a is set to 4, then 4+4 is returned.
b is never modified.
*/

int f(int &a, int &b) {
	a = 3;
	b = 4;
	return a + b;
}

void mainQ9() {
	int a = 1;
	int b = 2;
	int c = f(a, a);
	std::cout << a << b << c;
}
//*********************************************
/*
//hint:decltype((a))is not the same as decltype(a).
"The type denoted by decltype(e) is deﬁned as follows:
— if e is an unparenthesized id-expression or an unparenthesized class member access (5.2.5), decltype(e) is the type of the entity named by e.
If there is no such entity, or if e names a set of overloaded functions, the program is ill-formed;
— otherwise, if e is an xvalue, decltype(e) is T&&, where T is the type of e;
— otherwise, if e is an lvalue, decltype(e) is T&, where T is the type of e;
— otherwise, decltype(e) is the type of e."
Because a is encapsulated in parentheses, it doesn't qualify for the first case, it is treated as an lvalue, therefore b's type is int&, not int.

*/

void mainQ38() {
	int a = 0;
	decltype((a)) b = a;
	b++;
	std::cout << a << b;
}

//*********************************************
/*Q131
hint:How well does explicit constructors and copy-initialization play along?
An explicit constructor constructs objects just like non-explicit constructors,
but does so only where the direct-initialization syntax (8.5) or where casts (5.2.9, 5.4) are explicitly used."

Explanation:
The first form, C c1(7), is called direct-initialization, the second, C c2 = 7, is called copy-initialization
So the int constructor is not even considered for initialization in the second case. Instead, a standard conversion sequence is used to convert the integer literal to a double, and the double constructor (the only candidate) is used.

*/
class C {
public:
	explicit C(int) {
		std::cout << "i";
	};
	C(double) {
		std::cout << "d";
	};
};

void mainQ131() {
	C c1(7);//direct initialization
	C c2 = 7;//copy initialization
}
//*********************************************
/*Q126
Using the class scope to specify the static member x changes the initial lookup-path for foo().
The scope at which x exists (that is, the enclosing namepsace where x was declared) is first searched before considering the surrounding namespaces.
*/

int foo()
{
	return 10;
}

struct foobar
{
	static int x;
	static int foo()
	{
		return 11;
	}
};

int foobar::x = foo();

void mainQ126()
{
	std::cout << foobar::x;
}
//*********************************************
/*Q5
What determines the order of member variable initialization?
Explanation
The initialization order of member variables is determined by their order of declaration,
not their order in the initialization list.

*/

struct A1 {
	A1() { std::cout << "A"; }
};
struct B1 {
	B1() { std::cout << "B"; }
};

class C1 {
public:
	C1() : a(), b() {}

private:
	B1 b;
	A1 a;

	/*
	A1 a;
	B1 b;
	*/
};

void mainQ5()
{
	C1();
}

//*********************************************
/*Q125
Each function template specialization instantiated from a template has its own copy of any static variable.
This means we get two instantiations of f, one for T=int, and one for T=double. Thus, i is shared between the two int calls, but not with the double call.
*/
template <class T> void f(T) {
	static int i = 0;
	cout << ++i;
}

void mainQ125() {
	f(1);
	f(1.0);
	f(1);
}
//*********************************************
/*Q24
Unsigned integers have well defined behaviour when they overflow. When you go one above the largest representable unsigned int, you end up back at zero.
According to §3.9.1.4 in the C++ standard: "Unsigned integers, declared unsigned, shall obey the laws of arithmetic modulo 2^n
where n is the number of bits in the value representation of that particular size of integer."
*/
void mainQ24() {
	unsigned int i = std::numeric_limits<unsigned int>::max();
	std::cout << ++i;
}


//*********************************************
/*Q25
What does the standard have to say about signed integer overflow?
Does it differ from unsigned integer overflow?

This question The program is undefined.
*/
void mainQ25() {
	int i = std::numeric_limits<int>::max();
	std::cout << ++i;
}
//*********************************************
/*Q44
arr is an array of X, not of pointers to X. When an object of type Y is stored in it, it is converted to X, and we lose the "Y part" of the object.
This is commonly known as "slicing".
*/
struct X {
	virtual void f() const { std::cout << "X"; }
};

struct Y : public X {
	void f() const { std::cout << "Y"; }
};

void print(const X &x) { x.f(); }

void mainQ44() {
	X arr[1];
	Y y1;
	arr[0] = y1;
	print(y1);
	print(arr[0]);
}

//*********************************************
/*Q31
Have you heard about the "most vexing parse"? Does it apply here?
The compilation error is on the line y.f(), but the source of the problem is Y y(X());

This could be interpreted as a a variable definition (which was the intention of the programmer in this example), or as a definition of a function y, returning an object of type Y,
taking a function (with no arguments, returning an object of type X) as its argument.
The compiler is required by the standard to choose the second interpretation, which means that y.f() does not compile (since y is now a function, not an object of type Y).

Wikipedia has a concise explanation: http://en.wikipedia.org/wiki/Most_vexing_parse, and the standard has more in §6.8.
To fix the problem, change Y y(X()) to either Y y{X{}} (modern C++) or Y y((X())) (pre-C++11)

*/

struct X1 {
	X1() { std::cout << "X"; }
};

struct Y1 {
	Y1(const X1 &x) { std::cout << "Y"; }
	void f() { std::cout << "f"; }
};

void mainQ31() {
	//Y1 y(X1());
	//y.f();//error: left of '.f' must have class/struct/union
}
//*********************************************

/*Q7
Explanation????
The "trick" here is that B::f() is called even though it is private.
As §11.5.2 in the standard puts it: "Access is checked at the call point using the type of the expression used to denote the object for which the member function is called". The call point here being a.f(), and the type of the expression is A&.

*/
class A2 {
public:
	virtual void f() { std::cout << "A"; }
};

class B2 : public A2 {
private:
	void f() { std::cout << "B"; }
};

void g(A2 &a) { a.f(); }

void mainQ7() {
	B2 b;
	g(b);
}
//*********************************************
/*Q118
(a) Because 0 is a null pointer constant[1], it can be converted implicitly into any pointer type with a single conversion.
(b) Because 0 is of type int, it can be converted implicitly to a short with a single conversion too.
In our case, both are standard conversion sequences with a single conversion of "conversion rank". Since no function is better than the other, the call is ill-formed.
*/
//*********************************************
void print1(char const *str) { std::cout << str; }
void print1(short num) { std::cout << num; }

void mainQ118() {
	print1("abc");
	//	print1(0);//ambiguous call to overloaded function - nullptr and int
	print1('A');
}

//*********************************************
/*
Q151
This question The program is unspecified / implementation defined.
Explanation: It is implementation - defined whether a char object can hold negative values.
*/
void main151()
{
	std::cout << std::is_signed<char>::value;
}

//*********************************************
/*
Q135

Explanation
std::map stores values based on a unique key.
The keys for mb are boolean, and 1, 3 and 5 all evaluate to the same key, true.
"A map is an associative container that supports unique keys (contains at most one of each key value)."
*/
void main135()
{
	map<bool, int> mb = { { 1,2 },{ 3,4 },{ 5,0 } };
	cout << mb.size();
	map<int, int> mi = { { 1,2 },{ 3,4 },{ 5,0 } };
	cout << mi.size();
}

//*********************************************
/*Q145
Hint: Return Value optimization
In f(), an E object is constructed, and 1 is printed. This object is then returned to main, and one could expect the copy constructor to be called, printing 2.
However, §6.6.3¶2 in the standard says "Note: A copy or move operation associated with a return statement may be elided", meaning that the implementation is free to skip the copy constructor.
This is optional, and unspecified behaviour.Most implementations will elide the copy constructor and output 13, but may be urged not to so with the -fno-elide-constructors option and output 1233.

*/
struct E
{
	E() { std::cout << "1"; }
	E(const E&) { std::cout << "2"; }
	~E() { std::cout << "3"; }
};

E f()
{
	return E();
}

void mainQ145()
{
	f();
}


//*********************************************
/*
Q144 ?????

Hint: What will be the type of the integer literal?

Explanation:
As the else part of the branch is obvious, we concentrate on the if part and make the assumptions present in the condition.
§2.14.2 in the standard: "The type of an integer literal is the first of the corresponding list in Table 6." [Table 6: int, unsigned int, long int, unsigned long int … for hexadecimal literals --end Table] in which its value can be represented."
Since the literal 0xffffffff needs 32 digits, it can be represented as an unsigned int but not as a signed int, and is of type unsigned int. But what happens with the negative of an unsigned integer?
§5.3.1 in the standard: "The negative of an unsigned quantity is computed by subtracting its value from 2^n , where n is the number of bits in the promoted operand." Here n is 32, and we get:
2^32 - 0xffffffff = 4294967296 - 4294967295 = 1
So i is initialised to 1, and N[1] is the only element accessed in the loop. (The second time around the loop, i is 0, which evaluates to false, and the loop terminates.)

o/p: 010
*/

void mainQ144()
{
	int N[] = { 0,0,0 };

	if (std::numeric_limits<long int>::digits == 63 &&
		std::numeric_limits<int>::digits == 31 &&
		std::numeric_limits<unsigned int>::digits == 32)
	{
		for (long int i = 0xffffffff; i; --i)
		{
			N[i] = 1;
		}
	}
	else
	{
		N[1] = 1;
	}

	std::cout << N[0] << N[1] << N[2];
}

//*********************************************
/*Q29
Explanation:
Even though foo() is virtual, it is not considered to be so during the execution of constructors and destructors.
Rationale:
If an object of type B is being constructed, first the constructor of A is called, then the constructor of B.
Thus, during A's constructor, the "B part" of the object has not been constructed yet, and should not be used.
One could easily imagine that B::foo() would use the "B part" of the object,
so it would be dangerous for A's constructor to call it.When the object is destroyed, B's destructor is called first, then A's destructor, leading to the same problem.
*/
struct A3 {
	A3() { foo(); }
	virtual ~A3() { foo(); }
	virtual void foo() { std::cout << "1"; }
	void bar() { foo(); }
};

struct B3 : public A3 {
	void foo() { std::cout << "2"; }
};

void mainQ29() {
	B3 b;
	b.bar();
}

//*********************************************
/*Q109
The compiler tries to deduce T for every parameter and checks if the deduced types match.
Because a lambda is of completely different type, it cannot be matched against std::function<void(T)> and the deduction process fails.
This problem can be fixed by turning the first parameter into a so-called nondeduced context.
*/
template <typename T>
void call_with(std::function<void(T)> f, T val)
{
	f(val);
}

void mainQ109()
{
	auto print = [](int x) { std::cout << x; };
	//call_with(print, 42);//Compiler error
	call_with<int>(print, 42);//works when the template arg is explicitly specified
}

//*********************************************
/*Q30
This program has no output.
X x(); is a function prototype, not a variable definition.
Remove the parentheses(or since C++11, replace them with{}), and the program will output X.

*/
struct X2 {
	X2() { std::cout << "X"; }
};

void mainQ30() {
	//X2 x(); //no o/p;
	X2 x{};//outputs X;

}
//*********************************************
/*Q49
When are temporaries destroyed? What happens if you bind a const reference to it?
explanation:
§12.2¶3 in the standard: "Temporary objects are destroyed as the last step in evaluating the full-expression (...) that (lexically) contains the point where they were created." This means that normally the temporaries returned from C(1) and C(2) should be destroyed at the end of the line.
However: §12.2¶5 states: "(...)when a reference is bound to a temporary. The temporary to which the reference is bound (...) persists for the lifetime of the reference", so the lifetime of the temporary returned by C(1) is extended to the end of main. The temporary returned by C(2) is still destroyed at the end of the line,
so it gets destroyed before the one returned by C(1).
*/

class C2 {
public:
	C2(int i) : i(i) { std::cout << i; }
	~C2() { std::cout << i + 5; }

private:
	int i;
};

void main49() {
	const C2 &c = C2(1);
	//C2(1);
	C2(2);
	C2 *pC = new C2(3);
	delete pC;

}

//*********************************************
/*Q112????
//Hint: When members are not mentioned in the member initializer list, when is it initialized ?
First, b1 is default initialized. All members are initialized before the body of the constructor, so b1.a is default initialized first, and we get the output 14.

§12.6.2¶8 in the standard: "In a non-delegating constructor, if a given non-static data member or base class is not designated by a mem-initializer-id (...)
then if the entity is a non-static data member that has a brace-or-equal-initializer, the entity is initialized as specified in §8.5 (...) otherwise, the entity is default-initialized."

Then, b2 is initialized with the move construcor (since std::move(b1)converts the reference to b1 to an xvalue, allowing it to be moved from.)
In B's move constructor, a is initialized in the initializer list. Even though a is an rvalue reference (and bound to an rvalue),
a itself is an lvalue, and cannot be moved from. b2.a is then copy initialized, printing 2, and finally the body of B's move constructor prints 6.

o/p: 1426*/
struct A4
{
	A4() { std::cout << "1"; }
	A4(const A&) { std::cout << "2"; }
	A4(A&&) { std::cout << "3"; }
};

struct B4
{
	A4 a;
	B4() { std::cout << "4"; }
	B4(const B4& b) : a(b.a) { std::cout << "5"; }
	B4(B4&& b) : a(b.a) { std::cout << "6"; }
};

void mainQ112()
{
	B4 b1;
	B4 b2 = std::move(b1);
}

//*********************************************
/*Q111
The continue statement (...) causes control to pass to the loop-continuation portion of the smallest enclosing iteration-statement,
that is, to the end of the loop." (Not to the beginning.)
*/
int main111() {
	int i = 1;
	do {
		std::cout << i;
		i++;
		if (i < 3) continue;
	} while (false);
	return 0;
}
//*********************************************
/*Q14
//Hint: When are non - local static variables, local static variables and local automatic variables initialized and destroyed ? Does it matter if we put static in front of A a ?

It is implementation-defined whether the dynamic initialization of a non-local variable with static storage duration is done before the first statement of main.
If the initialization is deferred to some point in time after the first statement of main, it shall occur before the first odr-use (3.2) of any function or variable defined in the same translation unit as the variable to be initialized."

Since A() is not const expr, the initialization of a is dynamic. There are two possibilities:
- a is initialized before main is called, i.e. before b is initialized.
- a is not initialized before main. It is however guaranteed to be initialized before the the use of any function defined in the same translation unit, i.e. before the constructor of b is called.

When execution reaches B b, it is initialized as normal. Static local variables are initialized the first time control passes through their declaration, so c is initialized next.
As main is exited,its local variable b goes out of scope, and is destroyed.
Finally, all static variables are destroyed in reverse order of their initialization, first c, then a.

*/
class A5 {
public:
	A5() { std::cout << "a"; }
	~A5() { std::cout << "A"; }
};

class B5 {
public:
	B5() { std::cout << "b"; }
	~B5() { std::cout << "B"; }
};

class C5 {
public:
	C5() { std::cout << "c"; }
	~C5() { std::cout << "C"; }
};

//A5 a;
//static A5 a;//no difference

void foo1() { static C5 c; }
void mainQ14() {
	B5 b;
	foo1();
}
//*********************************************
/*Q2
hint:What is the type of a string literal?
Does the compiler prefer standard or user defined conversions?

Explanation:
A string literal is not a std::string, but a const char[] .
If the compiler was to choose f(const std::string&), it would have to go through a user defined conversion and create a temporary std::string.
Instead, it prefers f(const void*), which requires no user defined conversion.

*/
void f2(const std::string &) { std::cout << 1; }

void f2(const void *) { std::cout << 2; }

void mainQ2() {
	f2("foo");
	const char *bar = "bar";
	f2(bar);
}

//*********************************************
/*Q124????

Explanation:
"A template-parameter of a template template-parameter is permitted to have a default template-argument.
When such default arguments are specified, they apply to the template template-parameter in the scope of
the template template-parameter."
In this case, the template template-parameter is C, and the scope of C is the function g(),
so the default arguments of C (i.e. T = B) are applied and C<B>::f() is called inside g().

o/p: 2
*/
struct A6 {};
struct B6 {};

template<typename T = A6>
struct X6;

template<>
struct X6<A6> {
	static void f() { cout << 1 << endl; }
};

template<>
struct X6<B6> {
	static void f() { cout << 2 << endl; }
};

template< template<typename T = B6> class C6>
void g() {
	C6<>::f();
}

void mainQ124() {
	g<X6>();
}
//*********************************************
/*Q148
Accessing volatiles counts as a side effect.

explanation:
The issue here is not the missing initializer of the variable a - it will implicitly be initialized to 0 here.

But the issue is the access to a twice without sequencing between the accesses.
According to §1.9¶12, accesses of volatile glvalues are side-effects and
according to §1.9¶15 these two unsequenced side-effects on the same scalar object result in undefined behavior.
*/
volatile int a1;
void mainQ148() {
	std::cout << (a1 + a1);
}
//*********************************************
/*Q153
"A narrow string literal has type “array of n const char”"
An array of n const char converts to a pointer to const char. According to §4.4¶1:
"A prvalue of type “pointer to cv1 T” can be converted to a prvalue of type “pointer to cv2 T” if “cv2 T” is more cv-qualified than “cv1 T”."
In this case however, char* is less cv-qualified than const char *, and the conversion is not allowed.
Note: While most compilers still allow char const[] to char* conversion with just a warning, this is not a legal conversion in C++11.
*/
void main153() {
	char* str = "X";
	std::cout << str;
}
//*********************************************
/*Q105
Hint:Control passes through A a; twice. Does it make more sense to construct a both times, or just the first?
Should the destructor be called the same number of times as the constructor?
§6.6¶2 Transfer [...] back past an initialized variable with automatic storage duration involves
the destruction of variables with automatic storage duration that are in scope at the point transferred from but not at the point transferred to.

*/

class A8 {
public:
	A8() { cout << "a"; }
	~A8() { cout << "A"; }
};

int i8 = 1;

void mainQ105() {
label8:
	A8 a8;
	if (i8--)
		goto label8;
}
//*********************************************
/*Q114 ?????
How does const-ness of an object affect members?
Is an object pointed to by a const pointer, itself const?
What is the const-ness of an object returned by a const vector::operator[]?

According to §8.3.1.1 in the C++ Standard, "The cv-qualifiers [e.g., const] apply to the pointer and not to the object pointed to."

That is, const-ness is shallow with regards to raw pointers and references (and standard types that seek to emulate them,
like std::unique_ptr) but not with regard to standard containers such as std::vector.

In the code above, the object s is non-const, and so its members all retain their default const-ness and all calls through them invoke the non-const version of C::foo().

However, r refers to its object as a const instance of S. That const-ness changes the behavior of its member v, an std::vector
which is "const-correct" in the sense that its operator[] returns const C& (see §23.2.3.16) and therefore invokes the const version of C::foo().

The const-ness of r's referent is also propagated to its members u and p (meaning one could not perform a mutating operation on u, e.g., calling r.u.reset()),
but this has no effect on the instance of C that they both point *to*. That is, the pointers themselves become const, but the pointed-to objects remain non-const.
Hence, they both still call the non-const version of C::foo().

The const-ness of the member S::p is the same for both s and r. Because it is declared as a const pointer, it does not change const-ness to follow the const-ness of its instance of S
but remains a const pointer to a non-const object.
*/
class C8 {
public:
	void foo() { std::cout << "A"; }
	void foo() const { std::cout << "B"; }
};

struct S8 {
	std::vector<C8> v;
	std::unique_ptr<C8> u;
	C8 *const p;

	S8()
		: v(1)
		, u(new C8())
		, p(u.get())
	{}
};

void mainQ114() {
	S8 s;
	const S8 &r = s;

	s.v[0].foo();
	s.u->foo();
	s.p->foo();

	r.v[0].foo();
	r.u->foo();
	r.p->foo();
}

//*********************************************
/*Q32
Hint:What is the difference between direct initialization and copy initialization? Do they in any way relate to the copy constructor and copy assignment operator?
o/p:abbc
*/
struct X8 {
	X8() { std::cout << "a"; }
	X8(const X8 &x8) { std::cout << "b"; }
	const X8 &operator=(const X8 &x8) {
		std::cout << "c";
		return *this;
	}
};

void mainQ32() {
	X8 x8;
	X8 y8(x8);
	X8 z8 = y8;
	z8 = x8;
}
//*********************************************
/*Q107
The goal of this question is to demonstrate that the evaluation order of elements in an initializer list is specified (as opposed to the arguments to a function call).

§8.5.4¶4: Within the initializer-list of a braced-init-list, the initializer-clauses,
including any that result from pack expansions (§14.5.3), are evaluated in the order in which they appear.

If h took two ints instead of a vector<int>, and was called like this: h(f(), g());
the program would be unspecified, and could either print fg or gf.
*/
int f8() { std::cout << "f"; return 0; }
int g8() { std::cout << "g"; return 0; }

//void h7(int,int){} ???
void h8(std::vector<int> v) {}

void mainQ107() {
	h8({ f8(), g8() });

}
//*********************************************
/*Q6
Whether you post-increment or pre-increment i,
its value does not change until after the loop body has executed.
*/
void mainQ6() {
	for (int i = 0; i < 3; i++)
		std::cout << i;
	for (int i = 0; i < 3; ++i)
		std::cout << i;
}
//*********************************************
/*Q132
Is foo called both times or just once? The C++11 standard says this in §8.3.6¶9:
"Default arguments are evaluated each time the function is called."
Thus, foo is called twice.


*/
int foo9() {
	cout << 1;
	return 1;
}

void bar9(int i = foo9()) {}

void mainQ132() {
	bar9();
	bar9();
}

//*********************************************
/*Q35
Hint: Which constructors are invoked for v1 and v2? How is a vector constructed from an initializer list?

To answer this we need to look at overload resolution of vector's constructors:
§23.3.6.2¶3 says (somewhat redacted): vector(size_type n, const T& value); Effects: Constructs a vector with n copies of value. So v1 contains one "2".

§13.3.1.7 says (in summary) that when non-aggregate classes (such as vector) are list-initialized† and have an initializer list constructor (again, like vector),
that constructor is chosen, and the argument list consists of the initializer list as a single argument.
(†: 8.5.4¶1: List-initialization is initialization of an object or reference from a braced-init-list.)

So v2 is initialized from the elements (aka initializer-clauses) in the braced-init-list, and contains the elements "1" and "2".
*/
void mainQ35() {
	std::vector<int> v1(1, 2);
	std::vector<int> v2{ 1, 2 };
	std::cout << v1.size() << v2.size();
}
//*********************************************
/*Q16
Hint:When are member variables initialized and destroyed?
Member variables are initialized before the constructor is called. The destructor is called before member variables are destroyed.
*/
class A10 {
public:
	A10() { std::cout << 'a'; }
	~A10() { std::cout << 'A'; }
};

class B10 {
public:
	B10() { std::cout << 'b'; }
	~B10() { std::cout << 'B'; }
	A10 a;
};

void mainQ16() { B10 b; }

//*********************************************
/*Q52
There is a compilation error when attempting to declare A::createB() a friend of B.
To declare A::createB() a friend of B, the compiler needs to know that function exists.
Since it has only seen the declaration of A so far, not the full definition, it cannot know this.
*/

/*Compilation error

class A7;
class B7 {
B7() { std::cout << "B"; }

public:
friend B7 A7::createB();
};

class A7 {
public:
A7() { std::cout << "A"; }

B7 createB() { return B7(); }
};

void mainQ52() {
A7 a;
B7 b = a.createB();
}

*/
//*********************************************
/*Q121
Hint: What effect does parentheses have on operator precedence? What is the value of an expression involving the comma operator?

The comma operator is applied on two expressions: a and b.
According to §5.18¶10 in the standard: "A pair of expressions separated by a comma is evaluated left-to-right;
the left expression is a discarded-value expression (...) The type and value of the result are the type and value of the right operand"
The right operand here being b, with the value 20. This is then the resulting value of the expression (a, b), and 20 is assigned to x.
*/

void mainQ121() {
	int a = 10;
	int b = 20;
	int x;
	x = (a, b);
	std::cout << x;
}


//*********************************************
/*Q33
Hint: Pass by Value - Pass by Reference
We throw a SpecialException. It is derived from GeneralException, but is caught by value, so e will have the dynamic type GeneralException, not SpecialException. This is known as slicing.
Instead, we should have caught it by reference catch (GeneralException& e), then its dynamic type would be SpecialException, and the program would output S.

*/

struct GeneralException {
	virtual void print() { std::cout << "G"; }
};

struct SpecialException : public GeneralException {
	void print() override { std::cout << "S"; }
};

void f11() { throw SpecialException(); }

void mainQ33() {
	try {
		f11();
	}
	catch (GeneralException e) {
		e.print();
	} //o/p: G
	  /*catch (GeneralException& e1) {
	  e1.print();
	  }*/ //o/p: S
}

//*********************************************
/*Q129
Explanation:?????
Here we are trying to initialize a vector<char> using two string literals, not two chars.
The initializer-list constructor for template <class T>vector is defined as vector(initializer_list<T>) by §23.3.6.1 in the standard. In our case, vector(initializer_list<char>).

The type of a string literal is "array of n const char" (§2.14.5¶8), so clearly the initializer-list constructor is not a match.

This problem does however not result in a compiler error, since the compiler is able to find another constructor that matches!
template <class InputIterator> vector(InputIterator first, InputIterator last)
Note that the type of InputIterator has no link to the type of T in the vector<T>. So even if we are initializing a vector<char>, the two arguments can be of arbitrary type.
The only requirement is that they confirm to the concept of InputIterator, which const char[] happens to do.
Now the constructor believes it has been passed two iterators to the same sequence, but it has actually been passed iterators to two completely different sequences, "," and ";". §24.2.5¶2 says:
"The domain of == for forward iterators is that of iterators over the same underlying sequence.". So the result of this program is undefined.

§13.3.1.7¶1 explains the rules very clearly:
"When objects of non-aggregate class type T are list-initialized, overload resolution selects the constructor in two phases:
— Initially, the candidate functions are the initializer-list constructors of the class T and the argument list consists of the initializer list as a single argument [which we have seen didn't match].
— If no viable initializer-list constructor is found, overload resolution is performed again, where the candidate functions are all the constructors of the class T and the argument list consists of the elements of the initializer list [in our case, the two string literals "," and ";" ]".

*/
void mainQ129() {
	std::vector<char> delimiters = { ",", ";" };
	//std::vector<const char> delimiters = { ",", ";" };//Error	C2338	The C++ Standard forbids containers of const elements because allocator<const T> is ill - formed.

	cout << delimiters[0];
}
//*********************************************
/*Q120:
Hint:Operator precedence

The comma operator has the lowest precedence of all C++ operators (specifically lower than =).
In this example it separates the two expressions x = a and b.

First x = a is evaluated, setting x to 10.Then, b is evaluated, which does nothing.
*/
void mainQ120() {
	int a = 10;
	int b = 20;
	int x, y;
	x = a, b;
	y = (a, b);
	std::cout << x << " " << y;
}

//*********************************************
/*Q119

Hint: At which point in the program is the name p declared?

As defined in §3.3.2¶1, the point of name declaration is after its complete declarator and before its initialisation.
This means that line 4 is valid C++, because it's possible to initialise the variable p with the address of an existing
variable, even if it is its own address.

The value of p is unknown, but can not be a null pointer value. The cast must thus evaluate to 1 and initialise the temporary bool as true.
*/
void mainQ119() {

	void * p = &p;
	std::cout << bool(p);//address type cast to bool - '1'
}
//*********************************************
/*Q28
Hint : When are array elements initialized? What is the difference between auto and auto&?

When the array is initialized, the default constructor is called once for each of the two objects in it.

Then we iterate over the array using auto, which in our case is deduced to be A.
This means the copy constructor will be called before f() for each iteration, printing BCBC. (Just as if we had written for (A x: a).

If we want to avoid the copy constructor, we can write for (auto& x : a) instead. Then the loop would print CC. (Just as if we had written for (A& x: a).

*/
struct A15 {
	A15() { std::cout << "A"; }
	A15(const A15 &a) { std::cout << "B"; }
	virtual void f() { std::cout << "C"; }
};

void mainQ28() {
	A15 a[2];
	for (auto x : a) {
		x.f();
	}

	for (auto& y : a) {//without copy constructor - o/p: only CC
		y.f();
	}
}
//*********************************************
/*Q8
Hint: What is the dynamic type of a in void g(A a) ?
g(A a) takes an object of type A by value, not by reference or pointer.
This means that A's copy constructor is called on the object passed to g() (no matter if the object we passed was of type B),
and we get a brand new object of type A inside g(). This is commonly referred to as slicing.
*/
class A13 {
public:
	virtual void f() { std::cout << "A"; }
};

class B13 : public A13 {
public:
	void f() { std::cout << "B"; }
};

void g(A13 a) { a.f(); }

void h(A13& a) { a.f(); }

void mainQ8() {
	B13 b;
	g(b);
	h(b);
}
//*********************************************
/*Q133 ????
Hint: Virtual inheritance is a technique used to avoid multiple copies of the same indirect base class in an object.
The call order of base constructors is well defined.

Explanation:

On the first line of main, d1 is initialized, in the order A, B, C, D. That order is defined by §12.6.2¶10:
"
— First, and only for the constructor of the most derived class (1.8), virtual base classes are initialized in the order they appear on a depth-first left-to-right traversal of
the directed acyclic graph of base classes, where “left-to-right” is the order of appearance of the base classes in the derived class base-specifier-list.
— Then, direct base classes are initialized in declaration order as they appear in the base-specifier-list(...)
— Finally, the compound-statement of the constructor body is executed.
"

So the output is ABCD.

On the second line, d2 is initialized. But why are the constructors (as opposed to the copy constructors) for the base classes, called? Why do we see ABCd instead of abcd?
As it turns out, an implicitly-defined copy constructor would have called the copy constructor of its bases (§12.8¶.15:
"The implicitly-defined copy/move constructor for a non-union class X performs a memberwise copy/move of its bases and members.").
But when you provide a user-defined copy constructor, this is something you have to do explicitly.

final o/p: 'ABCDABCd'

*/
class A16
{
public:
	A16() { cout << "A"; }
	A16(const A16 &) { cout << "a"; }
};

class B16 : virtual A16
{
public:
	B16() { cout << "B"; }
	B16(const B16 &) { cout << "b"; }
};

class C16 : virtual A16
{
public:
	C16() { cout << "C"; }
	C16(const C16 &) { cout << "c"; }
};

class D16 :B16, C16
{
public:
	D16() { cout << "D"; }
	D16(const D16 &) { cout << "d"; }
};

void mainQ133()
{
	/*D16 d1;
	D16 d2(d1);*/
}

//*********************************************
/*Q42
Hint:How greedy are initializer-list constructors?

a1 is default initialized, as described in §8.5.0.11
a2 doesn't actually use the initializer_list constructor with a list of zero elements,
a3's and a4's constructor is chosen in overload resolution

Initializer list constructors are greedy, so even though A(int) constructor is available, the standard mandates that initializer_list<int> is prioritized,
and if - and only if - it's not available, the compiler is allowed to look for other constructors.
(This is why it is not recommended to provide a constructor that ambiguously overloads with an initializer_list constructor.
*/

struct A17 {
	A17() { std::cout << "1"; }

	A17(int) { std::cout << "2"; }

	A17(std::initializer_list<int>) { std::cout << "3"; }
};

void mainQ42(int argc, char *argv[]) {
	A17 a1;
	A17 a2{};
	A17 a3{ 1 };
	A17 a4{ 1, 2 };
}
//*********************************************

/*Q15
Hint: When are static local variables initialized? If an exception is thrown in a constructor, is the object considered constructed? Will the destructor be called?

Explantion:
Static local variables are initialized the first time control passes through their declaration.
The first time foo() is called, b is attempted initialized. Its constructor is called, which first constructs all member variables.
This means A::A() is called, printing a. A::A() then throws an exception, the constructor is aborted, and neither b or B::a are actually considered constructed.
In the catch-block, c is printed, and then foo() is called again. Since b was never initialized the first time, it tries again, this time succeeding, printing ab.
When main exits, the static variable b is destroyed, first calling the destructor printing B, and then destroying member variables, printing A.

*/
int x18 = 0;

class A18 {
public:
	A18() {
		std::cout << 'a';
		if (x18++ == 0) {
			throw std::exception();
		}
	}
	~A18() { std::cout << 'A'; }
};

class B18 {
public:
	B18() { std::cout << 'b'; }
	~B18() { std::cout << 'B'; }
	A18 a;
};

void foo18() { static B18 b; }

void mainQ15() {
	try {
		foo18();
	}
	catch (std::exception &) {
		std::cout << 'c';
		foo18();
	}
}
//*********************************************
/*Q106:?????
Hint: Is there a difference between the two extern syntaxes? Something to do with declarations and definitions?

According to §7.5¶7 in the standard : A declaration directly contained in a linkage-specification is treated as if it contains
the extern specifier (§7.1.1) for the purpose of determining the linkage of the declared name and whether it is a definition.

extern "C" int x; //is just a declaration
extern "C" { int y; } //is a definition

And according to §3.2¶3:
"Every program shall contain exactly one definition of every non-inline function or variable that is odr-used in that program; no diagnostic required."
The result: x is never defined but it is optional for the compiler to print an error. The behaviour of this program is undefined
*/

/*
extern "C" int x106;
extern "C" { int y106; }

int mainQ106() {

std::cout << x106 << y106;

return 0;
}
*/

//*********************************************
/*Q147
Explanation:
??/ is a trigraph. According to §2.4¶1, this trigraph is translated to \ before any other processing takes place.
Since that \ is followed by a newline, the line x=1 is treated as a continuation of the comment.
Note: Trigraphs will be removed from the standard in C++17.
*/
int mainQ147() {
	int x = 0; //What is wrong here??
	x = 1;
	std::cout << x;
	return 0;
}

//*********************************************
/*Q127 ????
Hint: [=] captures by copy. There's an important difference between decltype(j) and decltype((j)). What is the const-ness of the lambda's operator()?

§5.1.2¶18 says
Every occurrence of decltype((x)) where x is a possibly parenthesized id-expression that names an entity of automatic storage duration is treated as if x were transformed into an access
to a corresponding data member of the closure type that would have been declared if x were an odr-use of the denoted entity.

So additional parentheses, as the in the code snippet above, are ignored.

The member of the closure type corresponding to the as-if-captured j will be not a reference, but will have the referenced type of the reference,
since it is captured by copy (§5.1.2¶14).Since the lambda is not declared mutable, the overloaded operator() of the closure type will be a const member function. 5.1.2¶5:
"The closure type for a lambda-expression has a public inline function call operator (...) This function call operator is declared const if and only if the lambda-expression’s parameter-declaration-clause is not followed by mutable."

Since the expression for decltype is a parenthesized lvalue expression, §7.1.6.2¶4 has this to say:
"The type denoted by decltype(e) is (...) T&, where T is the type of e;" As the expression occurs inside a const member function, the expression is const, and decltype((j)) denotes int const&. See also the example in §5.1.2¶18.

*/
int mainQ127()
{
	int i, &j = i;
	[=]
	{
		cout << is_same<decltype    ((j)), int         >::value
			<< is_same<decltype   (((j))), int      &  >::value
			<< is_same<decltype  ((((j)))), int const&  >::value
			<< is_same<decltype (((((j))))), int      && >::value
			<< is_same<decltype((((((j)))))), int const&& >::value;
	}();

	return 0;
}
//*********************************************
/*Q117 ?????
Hint: Is a template alias a new family of types?
Explanation:
X takes a template template parameter[1], meaning that any template argument for X needs to itself take a template parameter.
For instance, you cannot do X<int>, but you can do X<Y>, since Y itself is a template.There are two definitions of X, first the general template one, then the specialization X<Y>.
Y is a normal template.
Z is a template alias declaration, meaning that Z is now an alias for Y (think of template aliases as a "typedef for templates").

Now let's look at main:
Defining a variable of type X<Y> uses that specialization (printing 2).
But what happens when we use a template alias, as in X<Z>? Is the specialization X<Y> still used, since Z is an alias for Y?

No. According to §14.5.7¶1 in the standard, a template alias declaration resolve to a new family of types.
The specialization cannot be used, and the first template delcaration is used instead, printing 1.

[1]: For a good introduction to template template parameters, see http://www.informit.com/articles/article.aspx?p=376878
*/
template <template <typename> class>
struct X19 {
	X19() { std::cout << "1"; }
};

template <typename>
struct Y19 {};

template <typename T>
using Z19 = Y19<T>;

template <>
struct X19<Y19> {
	X19() { std::cout << "2"; }
};

int mainQ117() {
	X19<Y19> x1;
	X19<Z19> x2;
	return 0;
}

//*********************************************

/*§5.2.8¶1: "The result of a typeid expression is an lvalue of static type const std::type_info",and
§5.3.1¶3: "The result of the unary & operator is a pointer to its operand",so we're comparing two pointers to const std::type_info.
There is no guarantee that the same std::type_info instance will be referred to by all evaluations of the typeid expression on the same type,
although std::type_info::hash_code of those type_info objects would be identical, as would be their std::type_index.*/
struct A157 {};

int mainQ157()
{
	std::cout << (&typeid(A157) == &typeid(A157));
	return 0;
}
//*********************************************


int main(){
	main111();
	return 0;
}