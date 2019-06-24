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


## References 
1. https://www.youtube.com/watch?v=O7gUNNYjmsM
1. https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/