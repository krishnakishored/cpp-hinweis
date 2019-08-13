## Modern C++  
----
#### Deducing Types
1. ___template type deduction___
    ~~~cpp
    template<typename T>
    void f(ParamType param); 

    f(expr); 
    //In the call to f, compilers use expr to deduce types for T and ParamType.
    ~~~
    Three cases of Template type deduction based on the characteristics of ParamType, the type specifier for param in the general function template.
    1. The type specifier is a pointer or reference, but not a universal reference.
    2. The type specifier is a universal reference.
    3. The type specifier is neither a pointer nor a reference

    - During template type deduction, arguments that are references are treated as non-references, i.e., their reference-ness is ignored.
    - When deducing types for universal reference parameters, lvalue arguments get special treatment.
    - When deducing types for by-value parameters, const and/or volatile arguments are treated as non-const and non-volatile.
    - During template type deduction, arguments that are array or function names decay to pointers, unless they’re used to initialize references.

2. ___auto type deduction___
    ~~~cpp
    auto x1 = 27; // type is int, value is 27 
    auto x2(27); // ditto
    auto x3 = { 27 }; // type is std::initializer_list<int> & value is { 27 }
    auto x4{ 27 }; // ditto
    ~~~
    * auto type deduction is usually the same as template type deduction, but auto type deduction assumes that 
      a braced initializer represents a std::initializer_list, and template type deduction doesn’t.
    * auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.
    * auto variables must be initialized, are generally immune to type mismatches that can lead to portability or efficiency problems, 
      can ease the process of refactoring, and typically require less typing than variables with explicitly specified types.
    * When `auto` may not be used: 'Invisible' proxy types can cause auto to deduce the "wrong" type for an initializing expression. 
      The explicitly typed initializer idiom forces auto to deduce the type you want it to have.

3. ___`decltype`___
    * decltype almost always yields the type of a variable or expression without any modifications.
    * For lvalue expressions of type T other than names, decltype always reports a type of T&.
    * C++14 supports decltype(auto), which, like auto, deduces a type from its initializer, but it performs the type deduction using the decltype rules.

4. ___how to view deduced types___
    * opertor `typeid` takes an expression or a type and returns a reference to an object of `type_info` or a subclass of it 
    (which is implementation defined) This is because typeid returns a reference to a static object, 
    so if you call it on two objects that are the same type, you will get two references to the same thing, which is why the equality test returns true.
    * std::type_info::name 
    * to find the type : use of "`./bin/executable | c++filt -t`"

----
### New features 
1. ___uniform initialization___ ,  () vs {}
    * Braced initialization is the most widely usable initialization syntax, it prevents narrowing conversions, and it’s immune to C++’s most vexing parse.
    ~~~cpp
    Widget w2(); // most vexing parse! declares a function  named w2 that returns a Widget!
    Widget w3{}; // calls Widget ctor with no args
    //the most vexing parse most frequently afflicts developers when they want to default-construct an object, but inadvertently end up declaring a function instead

    class Fctor{
        public:
            void operator()(){
                for(){..}
            }
    };

    Fctor fct;
    std::thread t1(fct); //ok 

    std::thread t2(Fctor()); // most vexing parse
    std::thread t2((Fctor())); // with extra pair of () .. this works as expected.

    ~~~
    * During constructor overload resolution, braced initializers are matched to std::initializer_list parameters if at all possible, even if other constructors offer seemingly better matches.
    * An example of where the choice between parentheses and braces can make a significant difference is creating a std::vector<numeric type> with two arguments.
    * Choosing between parentheses and braces for object creation inside templates can be challenging.

2. ___Prefer nullptr to 0 and NULL___
   * Avoid overloading on integral and pointer types.
   * There is some uncertainty in the details in NULL’s case, because implementations are allowed to give NULL an integral type other than int (e.g., long). 
    ~~~cpp
    void f(int); // three overloads of f
    void f(bool);
    void f(void*);

    f(0); // calls f(int), not f(void*)
    f(NULL); // might not compile, but typically calls f(int). Never calls f(void*)
    f(nullptr);         // calls f(void*) overload

    ~~~

3. ___Prefer alias declarations to typedefs___
    ~~~cpp
    //alias
    template<typename T> // MyAllocList<T> 
    using MyAllocList = std::list<T, MyAlloc<T>>; // is synonym for std::list<T, MyAlloc<T>>
    MyAllocList<Widget> lw; // client code

    //typedef
    template<typename T> // MyAllocList<T>::type 
    // is synonym for std::list<T, MyAlloc<T>>
    struct MyAllocList { 
    typedef std::list<T, MyAlloc<T>> type; 
    }; 
    MyAllocList<Widget>::type lw; // client code 
    ~~~
    * typedefs don’t support templatization, but alias declarations do.
    * Alias templates avoid the “::type” suffix and, in templates, the “typename” prefix often required to refer to typedefs.

4. ___Prefer Scoped enums (`enum class`) to unscoped enums___
    * Enumerators of scoped enums are visible only within the enum. They convert to other types only with a cast.
    * Both scoped and unscoped enums support specification of the underlying type. 
      The default underlying type for scoped enums is int. Unscoped enums have no default underlying type.
    * Scoped enums may always be forward-declared. 
      Unscoped enums may be forward-declared only if their declaration specifies an underlying type.

5. ___Prefer deleted functions to private undefined ones___
    
    ~~~cpp
    /*
    *Declaring these functions private prevents clients from calling them. Deliberately failing to define them means that if code that still has access to them 
    (i.e., member functions or friends of the class) uses them, 'linking` will fail due to missing function definitions.
    */
    ...
    private:
        basic_ios(const basic_ios& );            // not defined
        basic_ios& operator=(const basic_ios&);  // not defined
    };

    ----
    /*
    Deleted functions may not be used in any way, so even code that’s in member and friend functions will fail to compile if it tries to copy basic_ios objects. 
    That’s an improvement over the C++98 behavior, where such improper usage wouldn’t be diagnosed until link-time.
    */
    public:
    ...
    basic_ios(const basic_ios& ) = delete; 
    basic_ios& operator=(const basic_ios&) = delete; 
    ...
    ~~~
    * Any function may be deleted, including non-member functions and template instantiations.

6. ___Declare overriding functions override___
    * Member function reference qualifiers make it possible to treat lvalue and rvalue objects (*this) differently.
    * Applying `final` to a virtual function prevents the function from being overridden in derived classes. `final` may also be applied to a class, in which case the class is prohibited from being used as a base class.
    * For overriding to occur, several requirements must be met:
        - The base class function must be virtual.
        - The base and derived function names must be identical (except in the case of destructors).
        - The parameter types of the base and derived functions must be identical. The constness of the base and derived functions must be identical.
        - The return types and exception specifications of the base and derived functions must be compatible.
        - The functions reference qualifiers must be identical

7. ___Prefer const_iterators to iterators___
    * const_iterators are the STL equivalent of pointers-to-const. 
    * In maximally generic code, prefer non-member versions of begin, end, rbegin, etc., over their member function counterparts.
    ~~~cpp
    template <class C>
    auto cbegin(const C& container)->decltype(std::begin(container))
    { 
        return std::begin(container);  
    }
    ~~~

8. ___Declare functions `noexcept` if they won’t emit exceptions___
    * noexcept is part of a function’s interface, and that means that callers may depend on it.
    * noexcept functions are more optimizable than non-noexcept functions.
    * noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.
    * Most functions are exception-neutral rather than noexcept.

9. ___Use `constexpr` whenever possible___
    * constexpr objects are const and are initialized with values known during compilation.
      constexpr - usage to limit the size of array
    * constexpr functions can produce compile-time results when called with arguments whose values are known during compilation.
      Declaring a function `constexpr` makes its result available during compilation.
    * constexpr is part of an object’s or function’s interface.
    * const doesn’t offer the same guarantee as constexpr, because `const` objects need not be initialized with values known during compilation

10. ___Make `const` member functions thread safe___ 
    * unless you’re certain they’ll never be used in a concurrent context.
    * For a single variable or memory location requiring synchronization, use of a `std::atomic` is adequate, but once you get to two or more variables or memory locations that require manipulation as a unit, you should reach for a `mutex`

11. ___Understand special member function generation___    
    * Rules governing member functions:
        - Default constructor: Generated only if the class contains no user-declared constructors.
        - Destructor: _destructors are noexcept_ by default. 
                      virtual only if a base class destructor is virtual.
        - Copy constructor: memberwise copy construction of non-static data members. 
                            Generated only if the class lacks a user- declared copy constructor. 
                            Deleted if the class declares a move operation. 
                            Generation of this function in a class with a user-declared copy assignment operator or destructor is deprecated.
        - Copy assignment operator: memberwise copy assignment of non-static data members. 
                                    Generated only if the class lacks a user-declared copy assignment operator. 
                                    Deleted if the class declares a move operation. 
                                    Generation of this function in a class with a user-declared copy constructor or destructor is deprecated.
        - Move constructor and move assignment operator: Each performs memberwise moving of non-static data members. 
                                                         Generated only if the class contains no user-declared copy operations, move operations, or destructor.

    * Member function templates never suppress generation of special member functions.
----
### Lambda expression
1. ___Avoid default capture modes___
* Beyond the Standard Library, lambdas facilitate the on-the-fly specification of callback functions, interface adaption functions, and context-specific functions for one-off calls. 
* A `closure` is the runtime object created by a lambda. Depending on the capture mode, closures hold copies of or references to the captured data. 
* Default by-reference capture can lead to dangling references.
* Default by-value capture is susceptible to dangling pointers (especially this), and it misleadingly suggests that lambdas are self-contained.
* Captures apply only to non-static local variables (including parameters) visible in the scope where the lambda is created. 

2. ___Use (c++14) init capture to move objects into closures___
* Like lambda expressions, std::bind produces function objects(say bind object).
* A bind object contains copies of all the arguments passed to std::bind. For each lvalue argument, the corresponding object in the bind object is copy constructed. For each rvalue, it’s move constructed
* Using an init capture makes it possible for you to specify
    - the name of a data member in the closure class generated from the lambda and
    - an expression initializing that data member.
* In C++11, emulate init capture via hand-written classes or std::bind.

3. ___Use decltype on auto&& parameters to std::forward them___
* C++14 generic lambdas—lambdas that use auto in their parameter specifications

    ~~~cpp
        auto f = [](auto x){ return func(normalize(x)); };    // The implementation of this feature is straight‐ forward: operator() in the lambda’s closure class is a template.
        
        //the closure class’s function call operator looks like this:
        class SomeCompilerGeneratedClassName 
        { 
        public:
            template<typename T>
            auto operator()(T x) const
            { return func(normalize(x)); }
            ... };

        //perfect forwarding lambda   
        auto f = [](auto&& param)
        {
            return func(normalize(std::forward<decltype(param)>(param)));
        };

    ~~~

4. ___Prefer lambdas to std::bind___
* std::bind always copies its arguments, but callers can achieve the effect of having an argument stored by reference by applying std::ref to it. 
* Lambdas are more readable, more expressive, and may be more efficient than using std::bind.
    ~~~cpp
    //The result of this is that compressRateB acts as if it holds a reference to w, rather than a copy.
    auto compressRateB = std::bind(compress, std::ref(w), _1);
    ~~~
----
### Smart Pointers

1. ___Use std::unique_ptr for exclusive-ownership resource management___
* A common use for std::unique_ptr is as a factory function return type for objects in a hierarchy.
* std::unique_ptr is even more popular as a mechanism for implementing the Pimpl Idiom.
* std::unique_ptr is a small, fast, move-only smart pointer for managing resources with exclusive-ownership semantics.
* By default, resource destruction takes place via delete, but custom deleters can be specified. Stateful deleters and function pointers as deleters increase the size of std::unique_ptr objects.

2. ___Use std::shared_ptr for shared-ownership resource management___
* std::shared_ptrs offer convenience approaching that of garbage collection for the shared lifetime management of arbitrary resources.
* Compared to std::unique_ptr, std::shared_ptr objects are typically twice as big, incur overhead for control blocks, and require atomic reference count manipulations.
* Memory for the reference count must be dynamically allocated
* Increments and decrements of the reference count must be atomic,
* Default resource destruction is via delete, but custom deleters are supported. The type of the deleter has no effect on the type of the std::shared_ptr. For std::unique_ptr, the type of the deleter is part of the type of the smart pointer. For std::shared_ptr, it’s not
* Avoid creating std::shared_ptrs from variables of raw pointer type.
* std::shared_ptr offers no operator[]. std::shared_ptr has an API that’s designed only for pointers to single objects. std::shared_ptrs can't work with arrays.

3. ___Use std::weak_ptr for std::shared_ptr- like pointers that can dangle___
* std::weak_ptrs can’t be dereferenced, nor can they be tested for nullness. That’s because std::weak_ptr isn’t a standalone smart pointer. It’s an augmentation of std::shared_ptr.
* Potential use cases for std::weak_ptr include caching, observer lists, and the prevention of std::shared_ptr cycles.
* In observer design pattern: A reasonable design is for each subject to hold a container of std::weak_ptrs to its observers, thus making it possible for the subject to determine whether a pointer dangles before using it.

4. ___Prefer std::make_unique and std::make_shared to direct use of new___
* std::make_unique and std::make_shared are two of the three make functions: functions that take an arbitrary set of arguments, perfect-forward them to the con‐ structor for a dynamically allocated object, and return a smart pointer to that object. The third make function is std::allocate_shared. It acts just like std::make_shared, except its first argument is an allocator object to be used for the dynamic memory allocation.

* Compared to direct use of new, make functions eliminate source code duplication, improve exception safety, and, for std::make_shared and std::allo cate_shared, generate code that’s smaller and faster.
* Situations where use of make functions is inappropriate include the need to specify custom deleters and a desire to pass braced initializers.
* For std::shared_ptrs, additional situations where make functions may be ill-advised include (1) classes with custom memory management and (2) systems with memory concerns, very large objects, and std::weak_ptrs that outlive the corresponding std::shared_ptrs.

5. ___When using the Pimpl Idiom, define special member functions in the implementation file___
* That’s the technique whereby you replace the data members of a class with a pointer to an implementation class (or struct), put the data members that used to be in the primary class into the implementation class, and access those data members indirectly through the pointer. 
* The Pimpl Idiom decreases build times by reducing compilation dependencies between class clients and class implementations.
* For std::unique_ptr pImpl pointers, declare special member functions in the class header, but implement them in the implementation file. Do this even if the default function implementations are acceptable.
* The above advice applies to std::unique_ptr, but not to std::shared_ptr.
----
### Misc

1. ___Consider pass by value for copyable parameters that are cheap to move and always copied___
* For copyable, cheap-to-move parameters that are always copied, pass by value may be nearly as efficient as pass by reference, it’s easier to implement, and it can generate less object code.
* Copying parameters via construction may be significantly more expensive than copying them via assignment.
* Pass by value is subject to the slicing problem, so it’s typically inappropriate for base class parameter types.

2. ___Consider emplacement instead of insertion___
* In principle, emplacement functions should sometimes be more efficient than their insertion counterparts, and they should never be less efficient.
* In practice, they’re most likely to be faster when (1) the value being added is constructed into the container, not assigned; (2) the argument type(s) passed differ from the type held by the container; and (3) the container won’t reject the value being added due to it being a duplicate.
* Emplacement functions may perform type conversions that would be rejected by insertion functions.

----

### Rvalue References, Move Semantics, and Perfect Forwarding
* Move semantics makes it possible for compilers to replace expensive copying operations with less expensive moves. 
  Move semantics also enables the creation of move-only types, such as std::unique_ptr, std::future, and std::thread.

* Perfect forwarding makes it possible to write function templates that take arbitrary arguments and forward them to other functions such that the target functions receive exactly the same arguments as were passed to the forwarding functions.
 
* Rvalue references are the glue that ties these two rather disparate features together. They’re the underlying language mechanism that makes both move semantics and perfect forwarding possible.
* A parameter is always an lvalue, even if its type is an rvalue reference
~~~cpp
void f(Widget&& w); 
//the parameter w is an lvalue, even though its type is rvalue-reference-to-Widget. 
~~~
1. ___Understand std::move and std::forward___
* std::move doesn’t move anything. std::forward doesn’t forward anything. 
  At runtime, neither does anything at all. They generate no executable code. Not a single byte.
* std::move and std::forward are merely functions (actually function templates) that perform casts. 
   - std::move unconditionally casts its argument to an rvalue, while
   ~~~cpp
   template<typename T> decltype(auto) move(T&& param) {
     using ReturnType = remove_reference_t<T>&&;
     return static_cast<ReturnType>(param);
   }
   ~~~
   - std::forward performs this cast only if a particular condition is fulfilled.

2. ___Distinguish universal references from rvalue references___
* If a function template parameter has type T&& for a deduced type T, or if an object is declared using auto&&, the parameter or object is a universal reference.
* If the form of the type declaration isn’t precisely type&&, or if type deduction does not occur, type&& denotes an rvalue reference.
* Universal references correspond to rvalue references if they’re initialized with rvalues. 
  They correspond to lvalue references if they’re initialized with lvalues.

3. ___Use std::move on rvalue references, std::forward on universal references___
* Apply std::move to rvalue references and std::forward to universal references the last time each is used.
* Do the same thing for rvalue references and universal references being returned from functions that return by value.
* Never apply std::move or std::forward to local objects if they would other‐ wise be eligible for the return value optimization.

4. ___Avoid overloading on universal references___
* Overloading on universal references almost always leads to the universal refer‐ ence overload being called more frequently than expected.
* Perfect-forwarding constructors are especially problematic, because they’re typically better matches than copy constructors for non-const lvalues, and they can hijack derived class calls to base class copy and move constructors.

5. ___Familiarize yourself with alternatives to overloading on universal references___
* Alternatives to the combination of universal references and overloading include the use of distinct function names, passing parameters by lvalue- reference-to-const, passing parameters by value, and using tag dispatch.
- Constraining templates via std::enable_if permits the use of universal ref‐ erences and overloading together, but it controls the conditions under which compilers may use the universal reference overloads.
- Universal reference parameters often have efficiency advantages, but they typ‐ ically have usability disadvantages.

6. ___Understand reference collapsing___
* Reference collapsing occurs in four contexts: template instantiation, auto type generation, creation and use of typedefs and alias declarations, and decltype.
* When compilers generate a reference to a reference in a reference collapsing context, the result becomes a single reference. 
  If either of the original references is an lvalue reference, the result is an lvalue reference. Otherwise it’s an rvalue reference.
* Universal references are rvalue references in contexts where type deduction distinguishes lvalues from rvalues and where reference collapsing occurs.

7. ___Assume that move operations are not present, not cheap, and not used___
* In code with known types or support for move semantics, there is no need for assumptions.

8. ___Familiarize yourself with perfect forwarding failure cases___
* Perfect forwarding fails when template type deduction fails or when it deduces the wrong type.
* The kinds of arguments that lead to perfect forwarding failure are braced ini‐ tializers, null pointers expressed as 0 or NULL, declaration-only integral const static data members, template and overloaded function names, and bitfields.

----
### Concurrency API

1. ___Prefer task-based programming to thread- based___
    * The std::thread API offers no direct way to get return values from asynchronously run functions, and if those functions throw, the program is terminated.
    * Task-based programming via std::async with the default launch policy handles most of these issues for you - manual management of thread exhaustion, oversubscription, load balancing, and adaptation to new platforms
    * But there are _some situations where using threads directly may be appropriate_: 
        - _You need access to the API of the underlying threading implementation_ - 
        `std::thread` objects typically offer the `native_handle` member function. There is no counterpart to this functionality for std::futures (i.e., for what std::async returns). C++ threads has no notion of thread priority & affinity
        - _You need to implement threading technology beyond the C++ concurrency API_ - e.g. thread pools

2. ___Specify std::launch::async if asynchronicity is essential___

    * The `std::launch::async` launch policy means that f must be run asynchronously, i.e., on a different thread.
      The `std::launch::deferred` launch policy means that f may run only when get or wait is called on the future returned by std::async
    * The default launch policy for std::async permits both asynchronous and synchronous task execution. 
      This flexibility leads to uncertainty when accessing `thread_locals`, implies that the task may never execute, and affects program logic for timeout-based wait calls.
 
3. ___Make std::threads `unjoinable` on all paths___
    * join-on-destruction can lead to difficult-to-debug performance anomalies. 
    * detach-on-destruction can lead to difficult-to-debug undefined behavior. 
    * Declare std::thread objects last in lists of data membe

4.  ___Be aware of varying thread handle destructor behavior___
    * Hardware threads are the threads that actually perform computation. 
      Software threads (also known as OS threads or system threads) are the threads that the operating system1 manages across all processes and schedules for execution on hardware threads. Both `std::thread` objects and `future` objects can be thought of as handles to system threads

    * std::threads and futures have different behaviors in their destructors.     destruction of a joinable std::thread terminates your program, Yet the destructor for a future sometimes behaves as if it did an implicit join, sometimes as if it did an implicit detach, and sometimes neither.
    
    * Future destructors normally just destroy the future’s data members.
    
    * The final future referring to a shared state for a non-deferred task launched via std::async blocks until the task completes.

5. ___Consider void futures for one-shot event communication___
    * a communications channel whose transmitting end is a std::promise and whose receiving end is a future can be used for more than just callee-caller communication. Such a communications channel can be used in any situation where you need to transmit information from one place in your program to another
    *  For simple event communication, condvar-based designs require a superflu‐ ous mutex, impose constraints on the relative progress of detecting and react‐ ing tasks, and require reacting tasks to verify that the event has taken place.
    * Designs employing a flag avoid those problems, but are based on polling, not blocking.
    * A condvar and flag can be used together, but the resulting communications mechanism is somewhat stilted.
    * Using std::promises and futures dodges these issues, but the approach uses heap memory for shared states, and it’s limited to one-shot communication.


6. ___Use std::atomic for concurrency, volatile for special memory___    
    * std::atomic is for data accessed from multiple threads without using mutexes. It’s a tool for writing concurrent software.
    * `volatile` is for memory where reads and writes should not be optimized away. It’s a tool for working with special memory.

----
### Concurrency - BoQian

#### Process vs Thread
* Two Programming models for concurrent programming
    1. Multiprocessing
        - Talk to each other through `inter process communication`: Files, Pipes, Message Queues ..
        
    2. Multithreading
        - pros: 
            - Fast to start
            - Low overhead
            - Communicating through `shared memory`
        - Cons         
            - Difficult to implement
            - can't run on distributed system

#### Creating Threads
* By default the parameter to a thread are always _passed by value_
  - To pass a parameter reference :  `std::ref(param)` // this might create data race problem as mem is shared between threads
  - `std::move(s)` // safe and efficient

* A thread object cannot be copied . But it can be moved.  Like fstream, unique_ptr, etc.
~~~cpp
    //Case 1:
    std::thread t1(call_from_thread);
    std::thread t2 = move(t1);  // t2 become the owner of the thread
    t2.join();

    //Case 2:
    thread f() 
    {
        // ...
        return std::thread(call_from_thread);   // move semantics 
    }

    //Case 3:
    void f(std::thread t);
    int main() 
    {
        f(std::thread(call_from_thread));  // move semantics
        //...
    }
~~~

* a thread can only be moved but not copied
  ~~~cpp
    std::thread t2 = t1; // error
    std::thread t2 = std::move(t1); // it works
  ~~~

* `this_thread::get_id()` or `t1.get_id()` prints thread IDs provided either by the thread object or inside a thread

* Oversubscription - when there are more threads running than the available cpu cores, it creates a lot contact switching & in turn degrades the performance use `std::thread::hardware_concurrency` to find out

#### Date Race & Mutex




------
### Exceptions & Safety
* You can throw or catch any C++ type that lives up to some simple requirements, namely that it has a valid copy constructor and destructor. 
* C++ supports exceptions with three keywords: `try`, `catch`, and `throw`.
    ~~~cpp
    try {
       // Something that may call "throw", e.g.
       throw(Exception("Uh-oh"));
    }
    catch(Exception& e) {
       // Do something useful with e
    }
    ~~~
------
1. 
2. hyperthreading
3. maximum number of threads
    Computation intensive 
        - #thread << #core 
    IO intensive 
                          #core
        #thread <<   -----------------
                     1 - blocking factor   
        blocking factor is amount of time a task is gonna spend time being blocked

4. thread of excution Vs thread object
    - The thread object may die long before the thread of execution is finished
    - The thread of execution may finish long before the thread object dies

5. What if an exception occurs during join()  - use RAII thread class
6. Shared mutability is pure evil - source of many concurrency issues
7. A concurrent code should not break any invariants from the point of view of observing threads
8. livelock - wait forever an event that never ever will happen
9. lock_guard is RAII applied on locking. Using mutex lock & unlock is bad programming
10. Not only should methods of an object encapsulate it, it should also not allow data to escape. Anywhere a pointer or reference is returned from a method or passed to another method is a source of potential trouble. 
11. Deadlock - can happen if we lock multiple mutex one at a time. 
    std::lock comes to help - it acquires properly in order internally

12. Never acquire lock more than once in your execution sequence
    Never acquire multiple locks one at a time
    Always ask for them in one shot
    Never lock on an already acquired mutex
    Avoid nested locks

13. unique_lock 
    - unlike lock_guard, these are movable (but not copyable)
    - they can be locked later - in deferred mode if desired
    - you can unlock and lock again on this one as needed
    - When to use unique_lock & When to use lock_guard

14. Condition_variable
    - When wait is called, it checks the condition for 'true' and then proceeds
    - if the condition is false, it will release the lock and wait.
    - Once notified, it will acquire the lock, checks the condition. If condition is satisfied, moves forward. Otherwise releases the lock and waits.
15. Anytime you call a function that will wait for some thread or task to complete, always specify a timeout.  Look for variations of wait that take a timeout - duration & until a particular time

16. Future
    - A future is useful of one-off event & it may accompany some data with it.
    - async launch options
        * std::launch::async
        * std::launch::deferred
        * std::launch::deferred | std::launch::async 
    - Future is thread safe for access by worker  thread & calling thread. 
        But it is __not__ thread safe for multiple threads to access the same instance


17. packaged_task
     - A connector between a function and a future of the result of that function
     - useful to schedule a set of functions for exection on a thread pool

//////////////////////////////////////////////
- *High-Level Interface: async()*
    - `async()` provides an interface to let a piece of functionality, a callable object run in the background as a separate thread, if possible.  
    - Class `future<>` allows you to wait for the thread to be finished and provides access to its outcome: return value or exception, if any. 
    - Class `std::shared_future<>` allows you to wait for and process the outcome of a thread at multiple places.

   - *modify the program so that it might benefit from parallelization, if the underlying platform supports it, but still works as before on single-threaded environments*
        - #include <future>
        - Pass some functionality that could run on its own in parallel as a callable object to std::async()
        - Assign the result to a future<ReturnType> object
        - Call get() for the future<> object when you need the result or want to ensure that the functionality that was started has finished

   - Using Launch Policies
     - You can force async() to not defer the passed functionality, by explicitly passing a launch policy - `std::launch::async`,  `std::launch:deferred`

   - get() for futures also handles exceptions. When get() is called and the background operation was or gets terminated by an exception, which was/is not handled inside the thread, this exception gets propagated again. 

    - You can call get() for a future<> only once. After get(), the future is in an invalid state.Futures also provide an interface to wait for a background operation to finish without processing its outcome -  calling `wait()` forces the start of a thread a future represents and waits for the termination of the background operation

    - `wait_for()`,`wait_until()` `std::this_thread::yield()`
    - passing args

- *Low-Level Interface: threads & promises()*
    - To start a thread, you simply have to declare an object of class std::thread and pass the desired task as initial argument, and then either wait for its end or detach it.
    - If an exception occurs that is not caught inside the thread, the program immediately aborts, call- ing std::terminate(). To pass exceptions to a context outside the thread exception_ptrs have to be used.
    

- *Promises
    - You can pass parameters (and handle exceptions) between threads by simply passing them as arguments. And if you need a result, you can pass return arguments by reference, just as described for async() . Another mechanism to pass result values and exceptions as out- comes of a thread: class std::promise. 


    - A promise object is the counterpart of a future object. Both are able to temporarily hold a shared state, representing a (result) value or an exception.  While the future object allows you to retrieve the data (using get()), the promise object enables you to provide the data (by using one of its set_...() functions).
    - `promise.set_exception(std::current_exception())` - store exception

    - The moment we store a value or an exception in a shared state, it becomes ready. If you want the shared state to become ready when the thread really ends to ensure the cleanup of thread local objects and other stuff before the result gets processed — you have to call `set_value_at_thread_exit()` or `set_exception_at_thread_exit()` instead


    - * class `std::packaged_task<>`, also defined in \<future\>, holds both the functionality to perform and its possible outcome (the so-called shared state of the functionality;
        - create a task, 
        - get its future, 
        - start the task(typically in a separate thread),wait for its end and process result/exception

    - *Layers of Thread Interfaces* 
        - With the low-level interface of class thread, we can start a thread. To return data, we need shared variables (global or static or passed as argument). To return exceptions, we could use the type std::exception_ptr, which is returned by std::current_exception() and can be processed by std::rethrow_exception() 
        - The concept of a shared state allows us to deal with return values or exceptions in a more conve- nient way. With the low-level interface of a promise, we can create such a shared state, which we can process by using a future.
        - At a higher level, with class packaged_task or async(), the shared state is automatically created and set with a return statement or an uncaught exception.
        - With packaged_task, we can create an object with a shared state where we explicitly have to program when to start the thread.
        - With std::async(), we don’t have to care when the thread exactly gets started. The only thing we know is that we have to call get() when we need the outcome.
        -  A shared state is usually implemented as a reference-counted object that gets destroyed when the last object referring to it releases it. 

    ~~~cpp
    //you can also pass arguments that existed before the async() statement. 
    //As usual, you can pass them by value or by reference:
    char c = ’@’;
    // =: can access objects in scope by value // pass copy of c to doSomething()
    auto f = std::async([=]
    {  doSomething(c); });
    
    //By defining the capture as [=], you pass a copy of c and all other visible objects to the lambda, so inside the lambda you can pass this copy of c to doSomething().
    ~~~
    -  If you start to use async(), you should pass all objects necessary to process the passed functionality by value so that async() uses only local copies. If copying is too expensive, ensure that the objects are passed as constant reference and that mutable is not used.

    - class std::future provides the ability to process the future outcome of a concur- rent computation.  However, you can process this outcome only once. 
    For std::shared_future,  multiple get() calls are possible and yield the same result or throw the same exception.




- use of `thread_local`
- mutex vs semafore
    * Don’t pass pointers and references to protected data outside the scope of the lock, whether by returning them from a function, storing them in externally visible memory, or passing them as arguments to user-supplied functions.
- hierarchical_mutex
- reference_wrapper

- threadsafe singleton
- `std::unique_lock` provides a bit more flexibility than std::lock_guard by relaxing the invariants; a std::unique_lock instance doesn’t always own the mutex that it’s associated with. 
First off, just as you can pass std::adopt_lock as a second argument to the constructor to have the lock object manage the lock on a mutex, you can also pass `std::defer_lock` as the second argument to indicate that the mutex should remain unlocked on construction. The lock can then be acquired later by calling lock() on the std::unique_lock object (not the mutex) or by passing the std:: unique_lock object itself to std::lock().
- `std::unique_lock`  vs  `std:lock_guard`
The class `unique_lock` is a general-purpose mutex ownership wrapper allowing deferred locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with condition variables.


    * `std::lock` -  a function that can lock two or more mutexes at once without risk of deadlock. 
    * The `std::adopt_lock` parameter is supplied in addition to the mutex to indicate to the `std::lock_guard` objects that the mutexes are already locked, and they should just adopt the ownership of the existing lock on the mutex rather than attempt to lock the mutex in the constructor.
    * `std::recursive_mutex`. It works just like std::mutex, except that you can acquire multiple locks on a single instance from the same thread. You must release all your locks before the mutex can be locked by another thread, so if you call lock() three times, you must also call unlock() three times. Correct use of std::lock_guard \<std::recursive_mutex\> and std::unique_lock\<std::recursive_mutex\> will handle this for you.
- lock_guard
- Thread-safe lazy initialization of a class member using `std::call_once`
- Guidelines for avoiding deadlock
    - Avoid nested locks
    - Avoid calling user-supplied code while holding a lock
    - Acquire locks in a fixed order
    - use a lock hierarchy

    
- Synchronization of threads
    * C++ Standard Library provides facilities to handle it, in the form of condition variables and futures.
    * `std::condition_variable` & `std::condition_variable_any` both need to work with a mutex in order to provide synchronization
    * waiting for one-off events - `std::future` & `std::shared_future`
    * `std::async`
    * `std::packaged_task`ties a future to a function or callable object. When the std:: packaged_task<> object is invoked, it calls the associated function or callable object and makes the future ready, with the return value stored as the associated data.
    A `std::packaged_task` object prepares a function (or other callable object) for asynchronous execution by wrapping it such that its result is put into a shared state.
    ~~~cpp
    int calcValue(); // func to run
    /* wrap calcValue so that it can run asynchronously */
    std::packaged_task<int()> pt(calcValue); 
    auto fut = pt.get_future(); // get future for pt


    std::thread t(std::move(pt));         
    // run pt on t
    /*
    Once created, the std::packaged_task pt can be run on a thread. (It could be run via a call to std::async, too, but if you want to run a task using std::async, there’s little reason to create a std::packaged_task, because std::async does everything std::packaged_task does before it schedules the task for execution.)

    std::packaged_tasks aren’t copyable, so when pt is passed to the std::thread constructor, it must be cast to an rvalue -    */

    ~~~
    * `std::promise<T>` provides a means of setting a value (of type T), which can later be read through an associated std::future<T> object. 
    * Waiting for a condition variable with a timeout
    * parallel  quicksort implementation
    * A simple implementation of an ATM logic class
    * `std::this_thread::yield()`


- promise-future
     * multi-execution future
     * a communications channel whose transmitting end is a std::promise and whose receiving end is a future can be used for more than just callee-caller communication. Such a communications channel can be used in any sit‐ uation where you need to transmit information from one place in your program to another.


- Future, async, packaged_task, promise 
    * std::async can be seen as a high level interface to std::threads.
    * A future is a way to access a result from an asynchronous operation
    * Async executes a function asynchronously and returns a future. The future can then be used to get the result of executing that function.
    * When fut.get() is called, our code waits for that asynchronous operation to complete.   
    * packaged_task provides a little more control over the execution of a function. Achieves the same thing as async but gives freedom to specify exactly on which thread we want the task to run. 
    * For both async and packaged_task, the returned value of the function being executed was the value we acquired from the future.  Promises give us the freedom to set the promise value whenever and however we need.
    * Instead of the value of the future being set from the return value of the function, the function specifically sets the value using a promise

- Threads, Processes - Intro
    * When a user starts executing a program, the program becomes a process. A process is a set of instructions (the code) and state (memory, registers) that is managed by the operating system. The operating system tells the processor which process it should be running.
    * Processes can create other processes by using Fork. When a process forks, they become independent of each other. They own their own instructions and state.
    * A process can contain multiple threads. Because multiple threads live in the same process, they share their state (memory, address space). Because threads share state, switching between different threads in the same process is faster than switching between different processes.
    * Multiple threads in a single process can be executed in parallel if the hardware allows it (multiple CPU cores). This can make a program significantly faster. Because multiple threads can run simultaneously sharing state, it is important to be aware of problems that can happen when multiple threads access or modify state at the same time.
    * If an exception occurs in a thread, the whole process is aborted.

- critical section
    * lock, trylock, unlock, auto unlock
- wait_until
- packaged_task
- async
- bind
- atomic
- `native_handle`  - a member function of std::thread that can be used for accessing to the platform’s underlying threading API (usually POSIX threads or Windows threads). setting its priority or core affinity
- void futures - use case: creating a suspended thread
- Both `std::thread` objects and `future` objects can be thought of as handles to system threads.
----
## Chrono


----
##
-----
## STL - Containers, Algo, Iter
 - ToDo create a table form for insert, delete operations for all the containers
insertion into containers - multiple ways 
- list :
    - insertion: push_back, push_front, insert
    - deletion : erase,remove, remove_if
        - Remove elements from a container  - use erase() member function of the container

    `remove` doesn’t actually remove anything. __It moves everything that isn’t equal to the value you specify to the beginning of the sequence, and returns an iterator that refers to the first element following them.__ Then, it is up to you to actually call erase on the container to delete the objects between [p, end), where p is the iterator returned by remove.
    

    Use `remove_if` -  if you want to remove elements that satisfy some predicate, and not simply those equal to some value

    Finally, you may want to leave the original sequence alone (maybe it’s const) and copy the results minus some elements into a new sequence.use `remove_copy` and `remove_copy_if`, which work the same way as remove and remove_if, except that there is also an output iterator you pass in where the resulting data is supposed to go.

    ```cpp
    std::remove_copy(str.begin(), str.end(),std::ostream_iterator<char>(std::cout), ' ');
    // removes the blank spaces
    ```
    - If your lists are sorted (list has its own sort member function; std::sort won’t work with a list), and you want to merge them together and preserve their sorted order, use `merge` instead of splice. merge will combine the two lists into one, and if two elements are equivalent, the one from lstOne comes first in the final list. 

    - iteration & display using copy + ostream


- set:
    - change the default sorting, compartor
    

- map


- deque

- vector
    * To be safe, use `at( )` instead of `operator[]`. It throws out_of_range if the index used is > `size()`
    * Instead of inserting, you might want simply to assign the vector to a preexisting sequence from somewhere else, erasing whatever was there before. The assign member function does this. 
	* The biggest difference between calling `reserve` and specifying the size at construction is that reserve doesn’t initialize the slots in the buffer with anything.
    ~~~cpp
    vector<string> vec(100);
    string s = vec[50]; // No problem: s is now an empty string
    vector<string> vec2;
    vec2.reserve(100);
    s = vec2[50];// Undefined
    ~~~
    * Copying a vector
        - Use `assign` or the copy constructor instead of looping yourself.  
        - use `assign` for copying a subset of a sequence
    * Store pointers to your objects in a vector instead of copies of the objects themselves. But if you do, don’t forget to delete the objects that are pointed to, because the vector won’t do it for you. explicitly Purge the contents so no one tries to delete them again (`clear()`)

    - storing custom datatype 
    
    
    - deleting elements
    - emplace_back vs insert
    
- rope 

- STL containers of pointers

- use `empty()` function to test a container for emptiness. Don't compare begin==end or size==0

- `back_inserter` - A back_inserter is a class defined in \<iterator\> that provides a convenient way to create an output iterator that calls push_back on a sequence every time you assign a value to it. 
- `inserter` - is a function template defined in \<iterator\> that takes a container and an iterator and returns an output iterator that calls insert on its first argument when values are assigned to it. 

- `equal` to compare two sequences for equality


- `transform` or `for_each` - used for transforming elements in sequence
- `search`
- `accumulate` - function from the \<numeric\> header to compute the sum, and then divide by the size to get the mean.
-  `merge` - merge merges two sorted sequences and places the result into a third
    Both sequences must be sorted (or the output will be garbage), and neither is modified by merge
- `inplace_merge` - if you have two sequences that are contiguous (i.e., they are parts of the same sequence), and they are sorted, and you want the entire sequence sorted, you can use inplace_merge instead of a sort algorithm. The advantage is that inplace_ merge can run in linear time if there is enough additional memory available. If there isn’t, it runs in n log n, which is the average complexity of sort anyway.
- to know how or where two sequences differ, you can use `lexicographical_compare` or `mismatch`.

- types of sortings
- `sort` - take random-access iterators; vector,deque,string/wstring. for list use `list.sort()`
- `partial_sort` - Takes three random-access iterators: first, middle, and last, and optionally a comparison functor. It has two postconditions: the elements in the range (first, middle) are all less than those in the range (middle, last), and the range (first, middle) is sorted according to operator< or your comparison functor. In other words, __it sorts until the first n elements are sorted.__

 `partial_sort_copy` - It takes the first n elements from the source range and copies them into the desti- nation range in sorted order. If the destination range (n) is shorter than the source range (m), only n items are copied into the destination range

`nth_element` - Takes three random-access iterator arguments: first, nth, and last, and an optional comparison functor __It puts the element referred to by nth at the index where it would be if the entire range were sorted.__ Consequently, __all elements in the range (first, nth) are less than the element at the nth position (those in (nth, last) are not sorted, but are all greater than the ones preceding nth)__. You would use this if you only want one or a few elements sorted in a range, but you don’t want to pay for sorting the entire range if you don’t have to.

- `partition`
- `bind2nd`
- set opertations can be called the set operations on any sequence, not    just sets.`set_union, set_difference, set_intersection, set_symmetric_difference` - If a and b are sets symmetric difference is (a-b) U (b-a) - set of all elements that appear in one set but not the other
- generator functions for filling containers
- nullary functor
- `unique_copy`, `copy` 
```cpp
 copy(v.begin(), v.end(), ostream_iterator<string>(cout, ", "));
```
- write your own copy_if
- `random_shuffle`
- `std::function` - Class template std::function is a general-purpose polymorphic function wrapper. 
   Instances of std::function can store, copy, and invoke any Callable target -- functions, lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members. The stored callable object is called the target of std::function. If a std::function contains no target, it is called empty. Invoking the target of an empty std::function results in std::bad_function_call exception being thrown.
   std::function satisfies the requirements of CopyConstructible and CopyAssignable.

-  types of iterators - 
    * An `input iterator` supports advancing forward with p++ or ++p, and dereferencing with *p. __You get back an rvalue when you dereference though__. Input iterators are used for things like streams, where dereferencing an input iterator means pulling the next element off the stream, __so you can only read a particular element once__.
    
    * An `output iterator` supports advancing forward with p++ or ++p, and dereferenc- ing with *p. It’s different from an input iterator though, in that you can’t read from one, __you can only write to it—and only write to an element once.__ __Also unlike an input iterator, you get back an lvalue and not an rvalue, so you can assign to it but not read from it.__
    
    A `forward iterator` merges the functionality of an input iterator and an output iterator: it supports ++p and p++, and you can treat *p as an rvalue or an lvalue. You can use a forward iterator anywhere you need an input or an output iterator, with the added benefit that __you can read from or write to a dereferenced forward iterator as many times as you see fit.__
    
    As the name implies, a `bidirectional iterator` goes forward and backward. __It is a forward iterator that adds the ability to go backward using --p or p--.__
    
    A `random-access iterator` does everything a bidirectional iterator does, but it also __supports pointer-like operations__. You can use p[n] to access the element that is n positions after p in the sequence, or you can add to or subtract from p with +, +=, -, or -= to move the iterator forward some number of elements in constant time. You can also compare two iterators p1 and p2 with <, >, <=, or >= to determine their relative order (as long as they both point to the same sequence).

    other kinds of iterators are `streamiterators` - A stream iterator is an iterator that is based on a stream instead of a range of elements in some container,and streamiterators allow you to treat streaminput as an input iterator ,`streambufferiterators`,and `rawstorageiterators`
    `const`,`reverse`

- `distance` - count no.of elements when only iterators are given
- `max_element` & `min_element` - return iterators not values
- `valarray` -   can be used as a numerical vector especially those on high-performance machines, can apply specialized vector optimizations to it. 
   valarray provides numerous overloaded operators specifically for working with numerical vectors. 
   These operators provide such functionality as vector addition and scalar multiplication.
   The valarray template can also be used with the standard algorithms like a C-style array.

- `inner_product` - computing the dot product. It can also be used for computing distance between two vectors or compute the norm of a vector
- `std::plus`
- `std::iterator_traits`
-----
### OOAD

- Effects of making ctor & dtor as private
- this pointer 
- vtables & vptr
- usage of ' =default' & ' =delete' 
- deep copy & shallow copy
- disallowing copy ctor
- copy ctor & assignment overload functions with rvalue references
- move semantics
- Virtual Function Pointer Table
    - Whenever a class defines a virtual function a hidden member variable is added to the class which points to an array of pointers to (virtual) functions called the virtual function table(VFT)
    - VFT pointers are used at runtime to invoke the appropriate function implementations. because at compile time it may not yet be known if the base function is to be called or a derived one implemented by a class that inherits from the base class
    - VFT is class-specific - all instances of the class has same VFT
    - VFT carries the Run-Time Type Information(RTTI) of objects
    - Virtual functions introduce 'dynamic dispatch' which compilers implement using v-table(VFT)


- pure virtual methods - Interfaces
- virtual destructor uses, why not virtual ctor
- friend class
- friend operators
- benefits of using an initializer list becomes more apparent when you have class or reference member variables, or when you are trying to deal with exceptions effectively.
    If an object is constructed in the initializer list, and that object throws an exception during construction, the runtime environment destroys all other previ- ously constructed objects in the list, and the exception continues to the caller of the constructor. On the other hand, if you assign the argument in the body of the con- structor, then you have to handle the exception with a try/catch block.

- factory pattern - using a function to create an object

- resource acquisition is initialization (RAII)
- static vs global
    If you declare a member variable static, only one of it will ever be constructed, regardless of the number of objects of that class that are instantiated. Similarly, if you declare a variable static in a function, it is constructed at most once and retains its value from one function call to another. 
    you should not put the definition in the header file. If you do, storage will be allocated in each implementation file that includes the header file, and either you will get a linker error or, worse, there will be several instances of this member variable in memory. This is not what you want if you need a static member variable.


- Use dynamic_cast operator to query the relationship between two types.
    The only requirement is that the object argument is a polymorphic type, which means that it has at least one virtual function.

- Singleton: 
    Create a static member that is a pointer to the current class, restrict the use of con- structors to create the class by making them private, and provide a public static member function that clients can use to access the single, static instance.

    - implement it using pointers and references
    - how to make it thread safe


- Abstract Base Class (ABC) - is a class that can't be instanstiated & acts as an interface.


    Here is a quick list of rules regarding abstract classes and pure virtual functions. A class is abstract if:
    - It declares at least one pure virtual function
    - It inherits, but does not implement, at least one pure virtual function
    abstract class cannot be instantiated. 

    However, with an abstract class you can:
    - Have data members
    - Have nonvirtual member functions
    - Provide implementations for pure virtual functions Do most of the things you can in an ordinary class
    In other words, you can do just about everything you can do with an ordinary class except instantiate it.

- Diamond Problem
- class templates
- calling a specific version of virtual function

-----
## Design

- `SOLID`
    - Avoiding tight coupling is the key!

    - SINGLE RESPONSIBILITY PRINCIPLE (SRP)
        - There should never be more than one reason for a class to change. 
        - *Just because you can, doesn't mean you should. stay away swiss army knife*
        - #PROTIPS
            * Split big classes
            * use layers
            * __Avoid god classes__
            * write straightforward comments

    - OPEN-CLOSED PRINCIPLE(OCP)    
        - Software entities should be open for extension, but closed for modification.
        - *Open chest surgery is not needed when putting on a coat* 
        - #PROTIPS
            * Make all member variables private
            * No global variables, ever
            * __Avoid setters__ (as much as possible)

    - LISKOV SUBSTITUTION PRINCIPLE (LSP)
        - Objects in a program should be replaceable with instances of  their subtypes without altering the correctness of the program. 
        - *If it looks like a duck, quacks like a duck but needs Batteries - You probably have the wrong Abstraction*    

    - INTERFACE SEGREGATION PRINCIPLE (ISP)
        - Many client-specific interfaces are better than one general-purpose interface. 
        - *USB - where do you want to plug this in?*
    
    - DEEPENDENCY INVERSION PRINCIPLE (DIP)
        - High level modules should not depend upon low level modules. Both should depend upon abstractions.
        - Abstractions should not depend upon details. Details should depend upon abstractions. 
        - *Would you solder a lamp directly to the electrical wiring in a wall?*

## DesignPatterns
- Singleton(threadSafe)
- Command Pattern
- Factories
- 

-----
### Strings
 - A generic version that suits wstring & string using basic_string<T> template
 - Padding, trimming
 - to print a vector<string>
 - differentiate vector<char> vs string
 - tokenize a string, strtok implementation
 - locale, use_facet
 - unicode 
 - handle localization of strings

-----

### Streams
- copy(first,last,ostream_iterator<int> (cout," "));
- adding ostream, operator<< as a friend class
- sstream,fstream
-----


### File Handling

-----
### Parsing - JSON, XML, text, csv
-----
### Pointers Vs References - use cases & syntaxes
    - Const pointer, pointer to a const
    - function pointers
    - void pointer

### Smart pointers
    - unique_ptr.swap
    - shared_ptr
    - write your own shared ptr, unique_ptr




### Numerical Methods
- `std::default_random_engine`
- `std::uniform_int_distribution`
----

    
-----
* using static_cast to fix narrowing conversion

* Initializing Objects with Initializer Lists - std::initializer_list


* T (auto return type)

    - 

* using - used for declaration
* auto&& 
* reference capture, capture by value
* mutable keyword
* C++11 Vs C++14 (list of new features)
* namespace chrono
* namespace literals
* duration_cast, difference between start & end time
* std::noshowbase, dec, showbase

* lvalue & rvalue


* move ctor
* reinterpret_cast

#### Exception Handling
- You can throw or catch any C++ type that lives up to some simple requirements, namely that it has a valid copy constructor and destructor.
(“trying” something, “throwing” an exception, and subsequently “catching” it)
- throw `domain_error`,  `std::runtime_error`

- Use try and catch in the constructor to clean up properly if an exception is thrown during construction.
- The ellipsis in the catch handler means that anything that is thrown will be caught. 


#### C vs C++
- size of an array is decided at compile time in C & at runtime in C++


#### general questions
- partial template specialization
- overloading vs templates - pros and cons
- templates with variable no.of arguments
- What are references & classify them
- pointers vs references
- pass by value, reference and pointers - differences?
- using const Vs #define 
- how floating point is stored. 
- Diff between floating point, double, fixed point

- curiously recursive template pattern
- reading xml,json, csv file types
- use of namespaces
- bitwise operations - left shift, right shift,packing, masking, narrowing conversions - use cases
- Overloading new and delete to limit the number of instances
- Memory Management - address space, heap, stack
- static
- handling json
- function objects vs function pointers (both collectively called functors)
    - Function objects refer to instances of classes or structs that overload operator (). A function object is more efficient because most compilers can more easily inline a function object.Also it can have a state. 
    - You can pass values to its constructor, which it stores in its fields for use later on. This gives function objects an expressive equivalency as with the concept of closures found in other programming languages.
    - Finally, function objects can be defined within another function or class. Function pointers have to be declared in a namespace scope.



#### Util functions
- tokenizing - convert a string to vector<string>
- 2-D matix class & it's methods to fill
- Matrix -  Multiplication, Addition, Transpose, Inverse, Identity.
- Given the product the matrix - find the missing elements in the input matrices

### Comparison of sorting algorithms

| Sort  |  key words | Complexity  |   |   |
|---|---|---|---|---|
| Merge  |  Divide, Conquer & Combine |   |   |   |
| Quick   |  Divide, Conquer & Combine, pivot, partition |  in place |   |   |
| Insertion  |   |   |   |   |
| Bubble  |   |   |   |   |



//Date - 22-Feb-2016
/*
1.When is copy constructor invoked? Mention all the scenarios
2.Why there is no virtual Constructor?
3.Can constructor be private()? When do we need private methods

4.Why don't we pass a pointer to copy constructor instead of reference?
5.How to call a CPP dll in C & vice versa

*/

//Date - 22-Feb-2016
/*
1.Deep copy - Shallow copy + Copy constructor
2.Interfaces
3.What is the difference between compiler and interpreter
4.Volatile 
5.Smart pointer - predefined/custom
6.Object Slicing
7.Conversion Constructor
8.Static Constructor & order
9.exception in Constructor - how to handle it ? is destructor called in this case?
10. exception in destructor - can we throw?
11. Can we access virtual functions in constructors

*/


//Date - 22-Feb-2016

/*
1.HashTable vs Dictionary vs Map
2.Keywords - explicit (conversion ctor), volatile, mutable, extern, static,boost, 

3.what happens if copy constructor is private? When should we make copy ctor private?
4.Can I access private member variables/functions outside the class or using instance of the class?
5.What happens if we pass a value in copy constructor? Does compiler allows it
6.Advantages of new and delete over malloc ,calloc and free
7.Can a class be declared as private, protected,public internal(c#)?
8.Typecasting in C++ (dynamic and static)
9.const functions and overloading const functions
10. Abstraction and encapsulation difference

*/

//What is include precompiled headers?
//Why is the reference object a const in constructor 
//Difference between a struct and class in CPP

//Interfaces Vs Abstract Class

//Date - 03-Mar-2016
//function pointers Vs Functors Vs Predicate
//upcast and downcast
//re-interpret cast, static cast
//Run-time Type Identification.
//bits
//Allocators 

//lvalue, rvalue, use of const

//int to char* - char* to int
//string to int - int to string
//string to char* - char* to string


//Simple Programs
1. Swap



➜  clang++ Concurrency/multithread_q/asynchronous_1.cpp -std=c++14  -o ./bin/async     ✭

-----

#### Tips to run this Project on windows using CodeBlocks
1. Install the following 
    - CMake, 
    - MinGW(posix - for std::thread), 
    - CodeBlocks (Create a new Compiler & set the path to MinGW executables (had to rename them)) 
1. add installation location of the binaries to "PATH" environment variable
1. Use CMake GUI ( less error prone) to generate the codeblocks project files 


$ cmake --version   
cmake version 3.15.0

$ mingw32-g++.exe --version
mingw32-g++.exe (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0


* Alternately use cmake from cmd prompt@ project directory
$ cmake -S . -B build -G "CodeBlocks - MinGW Makefiles"
$ cmake --build build

-----

## References 
1. https://www.youtube.com/watch?v=O7gUNNYjmsM
1. https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/
1. Setup CodeBlocks - https://medium.com/@yzhong.cs/code-blocks-compile-64-bit-under-windows-with-mingw-w64-79101f5bbc02 
1. https://www.fluentcpp.com/2018/04/10/maps-vectors-multimap/

~~~cpp

int main(){
	
	return 0;
}

~~~