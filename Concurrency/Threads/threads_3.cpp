// ---------- C++ TUTORIAL 16 ----------

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>

// ---------- CALCULATE PRIMES WITHOUT THREADS -----------

void FindPrimes_withoutThreads(unsigned int start, 
        unsigned int end,
        std::vector<unsigned int>& vect){
    
    // Cycle through numbers while ignoring evens
    for(unsigned int x = start; x <= end; x += 2){
        for(unsigned int y = 2; y < x; y++){
            if((x % y) == 0){
                break;
            } else if((y + 1) == x){
                vect.push_back(x);
            }
        }
    }
}

int main_withoutThreads()
{
    std::vector<unsigned int> primeVect;
    
    // Get time before code starts executing
    int startTime = clock();
    
    FindPrimes_withoutThreads(1, 100000, primeVect);
    for(auto i: primeVect)
        std::cout << i << "\n";
  
    // Get time after execution
    int endTime = clock();
    
    // Print out the number of seconds by taking the difference
    // and dividing by the clock ticks per second
    std::cout << "Execution Time : " << 
            (endTime - startTime)/double(CLOCKS_PER_SEC) 
            << std::endl;
    
    return 0;
}

// ---------- END CALCULATE PRIMES WITHOUT THREADS -----------

// ---------- CALCULATE PRIMES WITH THREADS -----------

// Used to protect writing to the vector
std::mutex vectLock;
std::vector<unsigned int> primeVect;

void FindPrimes(unsigned int start, 
        unsigned int end){
    
    // Cycle through numbers while ignoring evens
    for(unsigned int x = start; x <= end; x += 2){
    
    	// If a modulus is 0 we know it isn't prime
        for(unsigned int y = 2; y < x; y++){
            if((x % y) == 0){
                break;
            } else if((y + 1) == x){
                vectLock.lock();
                primeVect.push_back(x);
                vectLock.unlock();
            }
        }
    }
}

void FindPrimesWithThreads(unsigned int start, 
        unsigned int end,
        unsigned int numThreads){
    
    std::vector<std::thread> threadVect;
    
    // Divide up the calculation so each thread
    // operates on different primes
    unsigned int threadSpread = end / numThreads;
    unsigned int newEnd = start + threadSpread - 1;
    
    // Create prime list for each thread
    for(unsigned int x = 0; x < numThreads; x++){
        threadVect.emplace_back(FindPrimes, start, newEnd);
        start += threadSpread;
        newEnd += threadSpread;
    }
    
    for(auto& t : threadVect){
        t.join();
    }

}

int main_withThreads()
{
    // Get time before code starts executing
    int startTime = clock();
    
    FindPrimesWithThreads(1, 100000, 4);
    
    // Get time after execution
    int endTime = clock();
    
    for(auto i: primeVect)
        std::cout << i << "\n";

    // Print out the number of seconds
    std::cout << "Execution Time : " << 
            (endTime - startTime)/double(CLOCKS_PER_SEC) 
            << std::endl;
    
    return 0;
}


int main(){
    main_withoutThreads();
    // main_withThreads();
}

// ---------- END CALCULATE PRIMES WITH THREADS -----------
