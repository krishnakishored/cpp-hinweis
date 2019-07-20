## STLContainers

## Concurrency
1. hardware_concurrency
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



## Chrono



##
-----
#### STL - Containers, Algo, Iter
> create a table form for insert, delete operations for all the containers
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

    - iteration & display using copy + ostream


- set:
    - change the default sorting, compartor
    

- map


- deque

- vector
    - storing custom datatype 
    - storing pointers
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

#### OOAD

- Effects of making ctor & dtor as private
- this pointer 
- vtables & vptr
- usage of ' =default' & ' =delete' 
- deep copy & shallow copy
- disallowing copy ctor
- copy ctor & assignment overload functions with rvalue references
- move semantics
- override, final keywords usage
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

- opertor typeid takes an expression or a type and returns a reference to an object of type_info or a subclass of it (which is implementation defined). 

    This is because typeid returns a reference to a static object, so if you call it on two objects that are the same type, you will get two references to the same thing, which is why the equality test returns true.

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

#### Strings
 - A generic version that suits wstring & string using basic_string<T> template
 - Padding, trimming
 - to print a vector<string>
 - differentiate vector<char> vs string
 - tokenize a string, strtok implementation
 - locale, use_facet
 - unicode 
 - handle localization of strings


#### Streams
- copy(first,last,ostream_iterator<int> (cout," "));
- adding ostream, operator<< as a friend class
- sstream,fstream



#### File Handling


#### Parsing - JSON, XML, text, csv

#### Pointers Vs References - use cases & syntaxes
    - Const pointer, pointer to a const
    - function pointers
    - void pointer
    - “C++’s most vexing parse

#### Smart pointers
    - unique_ptr.swap
    - shared_ptr
    - write your own shared ptr, unique_ptr

#### Error Handling & Exceptions

#### Concurrency
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
    - `this_thread::get_id()` prints thread IDs provided either by the thread object or inside a thread

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
 
- std::ref
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

#### DesignPattern
- Singleton(threadSafe)
- Command Pattern
- Factories
- 

#### Numerical Methods
- `std::default_random_engine`
- `std::uniform_int_distribution`

#### Modern C++
- using static_cast to fix narrowing conversion
- uniform initialization
- Initializing Objects with Initializer Lists - std::initializer_list
- type deduction - auto keyword, typeid()
- to find the type : use of "./bin/executable | c++filt -t"
- decltype keyword  
- T (auto return type)
- constexpr - usage to limit the size of array
- lambda
- using - used for declaration
- auto&& 
- closure 
- reference capture, capture by value
- mutable keyword
- C++11 Vs C++14 (list of new features)
- namespace chrono
- namespace literals
- duration_cast, difference between start & end time
- std::noshowbase, dec, showbase
- lvalue & rvalue
- move ctor
- reinterpret_cast

##### Exception Handling
- You can throw or catch any C++ type that lives up to some simple requirements, namely that it has a valid copy constructor and destructor.
(“trying” something, “throwing” an exception, and subsequently “catching” it)
- throw `domain_error`,  `std::runtime_error`

- Use try and catch in the constructor to clean up properly if an exception is thrown during construction.
- The ellipsis in the catch handler means that anything that is thrown will be caught. 


##### C vs C++
- size of an array is decided at compile time in C & at runtime in C++


##### general questions
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
- most vexing syntax
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



##### Util functions
- tokenizing - convert a string to vector<string>
- 2-D matix class & it's methods to fill
- Matrix -  Multiplication, Addition, Transpose, Inverse, Identity.
- Given the product the matrix - find the missing elements in the input matrices
- 



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
//lambda expressions
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

##### Tips to run this Project on windows using CodeBlocks
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


~~~cpp

int main(){
	
	return 0;
}


~~~