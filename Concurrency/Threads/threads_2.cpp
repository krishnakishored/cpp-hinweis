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

std::string GetTime(){
    auto nowTime = std::chrono::system_clock::now();
    std::time_t sleepTime = 
            std::chrono::system_clock::to_time_t(nowTime);
    return std::ctime(&sleepTime);
}

double acctBalance = 100;

// Protects shared data from being accessed at the same time
std::mutex acctLock;

void GetMoney(int id, double withdrawal)
{ 
    // The exception safe way to protect access to code within its scope. 
    // The lock is released after execution leaves this scope
    std::lock_guard<std::mutex> lock(acctLock);
    
    // Blocks access between lock and unlock until execution completes
    //acctLock.lock();  // This isn't good to use however, if an error occurs between lock and unlock 
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    std::cout << id << 
            " tries to withdrawal $" <<
            withdrawal << " on " <<
            GetTime() << "\n";
            
    if((acctBalance - withdrawal) >= 0){
        acctBalance -= withdrawal;
        std::cout << "New Account Balance is $" << acctBalance << "\n";
    } else {
        std::cout << "Not Enough Money in Account\n";
        std::cout << "Current Balance is $" << acctBalance << "\n";
    }
    // acctLock.unlock();
}

int main()
{
    // We will create a pool of threads that will access a bank account in no particular order
    std::thread threads[10];

    
    for(int i = 0; i < 10; ++i){
        threads[i] = std::thread(GetMoney, i, 15);
    }
    
    for(int i = 0; i < 10; ++i)
    {
        threads[i].join();
    }
    
    return 0;
}
