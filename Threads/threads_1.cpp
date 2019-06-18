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

int GetRandom(int max){
    srand(time(NULL));
    return rand() % max;
}

// ----- SIMPLE THREAD EXAMPLE -----
void ExecuteThread(int id){
    // Get current time
    auto nowTime = std::chrono::system_clock::now(); 
    
    // Converts time_point to a time we can output
    std::time_t sleepTime = 
            std::chrono::system_clock::to_time_t(nowTime);
    
    // Convert to current time zone
    tm myLocalTime = *localtime(&sleepTime);
    
    // Print full time information
    std::cout << "Thread " << id << 
            " Sleep Time : " <<
            std::ctime(&sleepTime) << "\n";
    
    // Get separate pieces
    std::cout << "Month : " <<
            myLocalTime.tm_mon << "\n";
    std::cout << "Day : " <<
            myLocalTime.tm_mday << "\n";
    std::cout << "Year : " <<
            myLocalTime.tm_year + 1900 << "\n";
    std::cout << "Hours : " <<
            myLocalTime.tm_hour << "\n";
    std::cout << "Minutes : " <<
            myLocalTime.tm_min << "\n";
    std::cout << "Seconds : " <<
            myLocalTime.tm_sec << "\n\n";
    
    // Put the thread to sleep for up to 3 seconds
    std::this_thread::sleep_for (std::chrono::seconds(GetRandom(3)));
    nowTime = std::chrono::system_clock::now();
    sleepTime = 
            std::chrono::system_clock::to_time_t(nowTime);
    std::cout << "Thread " << id << 
            " Awake Time : " <<
            std::ctime(&sleepTime) << "\n";
    
}
// ----- END SIMPLE THREAD EXAMPLE ----- 


int main()
{
    // ----- SIMPLE THREAD EXAMPLE -----
    // Create a thread and pass a parameter to the function
    std::thread th1 (ExecuteThread, 1);
    
    // Join the thread to the main thread meaning main waits for this thread to
    // stop executing before continuing execution of code in main
    th1.join();
    
    std::thread th2 (ExecuteThread, 2);
    th2.join();
    // ----- END SIMPLE THREAD EXAMPLE ----- 
        
    return 0;
}
