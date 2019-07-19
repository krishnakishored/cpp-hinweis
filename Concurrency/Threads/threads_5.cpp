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

using namespace std::chrono_literals; // for operator""s


// ---------- race condition -----------
using std::vector;
using std::cout;
using std::string;

int a_count = 0;
void change(int by)  // lead to race condition
{
    int value = a_count;
    a_count = value + by;
}

std::mutex a_count_mutex;

void change_avoidRace(int by)
{
    /* avoid race condition unless there's an exception 
    or a thread misses to unlock the mutex */
    // a_count_mutex.lock();

    std::lock_guard<std::mutex> guard(a_count_mutex); //uses RAII Pattern
    int value = a_count;
    a_count = value+by;
    // a_count_mutex.unlock();
}


int main_racecondition()
{
    vector<std::thread> threads;

    for(auto i=0;i<20000;i++){
        // threads.push_back(std::thread(change,(i%2==0)?1:-1));
        threads.push_back(std::thread(change_avoidRace,(i%2==0)?1:-1));
    }
    for(auto thread = threads.begin();thread!=threads.end();thread++)
    {
        thread->join();
    }
    cout << a_count << "\n"; // should be 0 but result is unpredictable
    return 0;
}

// --- DEADLOCK -----
class Account{
    private:
        int balance;
        std::mutex mutex;
    public:
        Account(int balance): balance(balance){}
        int getBalance()const {return balance;} 
        
        void transferFrom(Account& other, int amount){
            // std::lock_guard<std::mutex> guard1(mutex); // bad idea -  two mutexs - one after other
            std::lock(mutex,other.mutex);
            std::lock_guard<std::mutex> guard1(mutex,std::adopt_lock); // handles only unlocking 
            std::this_thread::sleep_for(2s);//simulate delay;
            cout<< "acquired one.. waiting for the other\n";
            // std::lock_guard<std::mutex> guard2(other.mutex);  // bad idea -  two mutexs - one after other
            std::lock_guard<std::mutex> guard2(other.mutex,std::adopt_lock);
            //assume there's enough fund
            balance +=amount;
            other.balance -= amount;
        }


         void transferFrom_usingUniqueLock(Account& other, int amount){
            
            std::unique_lock<std::mutex> lock1(mutex,std::defer_lock);
            std::this_thread::sleep_for(2s);//simulate delay;
            std::unique_lock<std::mutex> lock2(other.mutex,std::defer_lock);
            cout<< "request lock\n";
            std::lock(lock1,lock2);
            cout<<"one thread working.. \n";
            //assume there's enough fund
            balance +=amount;
            other.balance -= amount;
            cout<<"done working..\n ";
        }
};


int main_uniquelock(){

    // main_racecondition();
    Account a1(100);
    Account a2(200);
    cout<<a1.getBalance()<<"\n";
    // a1.transferFrom(a2,50);
    a1.transferFrom_usingUniqueLock(a2,20);
    cout<<a1.getBalance()<<"\n";

    return 0;
}

// --- Another Race Condition 

class Resource{
    private:
        bool used = false;
        std::mutex mutex;
    
    public:
        bool isAvailable(){
            std::lock_guard<std::mutex> guard(mutex);
            return !used;
        }

        string use(){
            std::lock_guard<std::mutex> guard(mutex);
            if(!used){
                used = true;
                return "It's for you";
            }
            else{
                return "it's gone";
            }
        }
};

void useResource(Resource& resource){
    if(resource.isAvailable()){
        cout << "is available\n " ;
        std::this_thread::sleep_for(2s);
        cout<< resource.use()<<"\n";
    }
}

class Resource2 // using unique_lock
{
    private:
        bool used = false;
        std::mutex external;
        std::mutex mutex;
    
    public:
        auto getlock() {return std::unique_lock<std::mutex> {external};}
        bool isAvailable(){
            std::lock_guard<std::mutex> guard(mutex);
            return !used;
        }

        string use(){
            std::lock_guard<std::mutex> guard(mutex);
            if(!used){
                used = true;
                return "It's for you";
            }
            else{
                return "it's gone";
            }
        }
};

void useResource2(Resource2& resource){
    auto lock = resource.getlock();
    if(resource.isAvailable()){
        cout << "is available!\n";
    }
}


// -- Another approach
class Resource3 // using unique_lock
{
    private:
        bool used = false;
        std::mutex external;
        std::mutex mutex;
    
    public:
        void operateOn(std::function<void(Resource3&)> func){
            std::unique_lock<std::mutex> guard(external);
            func(*this);
        }

        auto getlock() {return std::unique_lock<std::mutex> {external};}
        bool isAvailable(){
            std::lock_guard<std::mutex> guard(mutex);
            return !used;
        }

        string use(){
            std::lock_guard<std::mutex> guard(mutex);
            if(!used){
                used = true;
                return "It's for you";
            }
            else{
                return "it's gone";
            }
        }
};

void useResource3(Resource3& resource){
    resource.operateOn([](Resource3& resource){
        if(resource.isAvailable()){
            cout << "is available!\n";
            std::this_thread::sleep_for(2s);
        }
    });    
}



int main(){

    // Resource resource;
    // std::thread thread1(useResource,std::ref(resource));
    // std::thread thread2(useResource,std::ref(resource));

    // thread1.join();
    // thread2.join();



    Resource2 resource2;
    std::thread thread3(useResource2,std::ref(resource2));
    std::thread thread4(useResource2,std::ref(resource2));

    thread3.join();
    thread4.join();

    // Resource3 resource3;
    // std::thread thread5(useResource3,std::ref(resource3));
    // std::thread thread6(useResource3,std::ref(resource3));

    // thread5.join();
    // thread6.join();

    return 0;
}