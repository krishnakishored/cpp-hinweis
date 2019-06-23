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

  

## Chrono


## References 
1. https://www.youtube.com/watch?v=O7gUNNYjmsM
1. https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/