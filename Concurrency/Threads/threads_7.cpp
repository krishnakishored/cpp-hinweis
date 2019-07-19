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

#include<future>


using namespace std::chrono_literals; // for operator""s
using std::cout;
using std::string;


// - Condition_variable
int product;
std::mutex product_mutex;
std::condition_variable signal1;

void producer(){
    while(true){
        std::lock_guard<std::mutex> guard(product_mutex);
        // std::unique_lock<std::mutex> guard(product_mutex);
        product++;        
        
        // signal1.notify_one();
        signal1.notify_all();
        
        std::this_thread::sleep_for(1s);
        cout<<"prod "<< product<<"\n";
        
    }
    std::this_thread::sleep_for(300ms);
}

void consumer(string name){
    while(true){
        std::unique_lock<std::mutex> guard(product_mutex);
        signal1.wait(guard,[](){return product>0;});
        cout<< name <<" "<<product<<"\n";
        product--;
    }
    std::this_thread::sleep_for(1s);
}

int main_conditionvariable()
{

    std::thread th1(producer);
    std::thread th2(consumer,"con1");
    // std::thread th3(consumer,"con2");

    th1.join();
    th2.join();
    // th3.join();

    return 0;
}

// Using Future

long fib(int position){
    if(position<0)
        throw string("invalid position");

    if(position < 2)
        return 1;
    else
        return fib(position-1)+fib(position-2);
}

void printResult(std::future<long> result)
{
    cout<<result.get()<<"\n";
}

int main_simplefuture()
{
    std::thread print(printResult, std::async(fib,10));
    print.join();
    return 0;
}


long compute(int position){
    cout<<"computing in thread.. "<< std::this_thread::get_id()<<"\n";
    return fib(position);
}

int main_launchdeferred(){

    cout << "in main.."<< std::this_thread::get_id()<<"\n";
    auto result = std::async(std::launch::deferred, compute, 5);
    cout<<result.get()<<"\n";
    return 0;
}

int main_launchasync(){

    cout << "in main.."<< std::this_thread::get_id()<<"\n";
    auto result = std::async(std::launch::async, compute, 5);
    cout<<result.get()<<"\n";
    return 0;
}


void print1(std::shared_future<long> future){
    cout<< future.get()<<std::endl;
}


void print2(std::shared_future<long> future){
    cout<< std::boolalpha << (future.get() > 1) << "\n";
}

int main_sharedFuture(){
    auto future = std::async(fib,10);
    std::shared_future<long> sharedFuture(std::move(future));
    std::thread thread1(print1, sharedFuture);
    std::thread thread2(print2, sharedFuture);

    thread1.join();
    thread2.join();

    return 0;
}

int main_packagedtask(){
    std::packaged_task<long(int)> task(compute);
    auto result = task.get_future();
    cout << "in main.."<< std::this_thread::get_id()<< "\n";
    std::thread thread(std::move(task),10);
    thread.detach();

    cout << "wait for the result\n ";
    cout << result.get()<< "\n";


    return 0;
}


long compute_withpromise(int position, std::promise<long> resultPromise)
{
    cout<<"computing in thread.. "<< std::this_thread::get_id()<<"\n";
    try{
        long result = fib(position);
        resultPromise.set_value(result);
    }
    catch(...){
        resultPromise.set_exception(std::current_exception());
    }

    return 0;
}

int main_promise()
{
    std::vector<int> positions = {10,20, 4};

    for(auto position:positions){
        try{
            std::promise<long> resultPromise;
            auto result = resultPromise.get_future();
            std::thread thread(compute_withpromise,position,std::move(resultPromise));
           //  // std::thread thread(compute,position,resultPromise);

            thread.detach();
            cout<<result.get() << "\n";
        }
        catch(const string& ex){
            cout << ex << std::endl;
        }
    }
return 0;
}

int main(){
    // main_simplefuture();
    // main_launchdeferred();
    // main_launchasync();
    // main_sharedFuture();
    // main_packagedtask();
    // main_promise();
    main_conditionvariable();

    return 0;
}