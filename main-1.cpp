//  A bunch of examples that illustrate C++ 11 features
//
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

int simpleFunction(int a) {
    return a + 1;
}

void functionPointerDemo() {
    cout << "funcionPointerDemo()" << endl;
    // NOTE: Strongly typed nullptr!
    int (*f1)(int) = nullptr;
    if (f1 == nullptr) {
        cout << "Null" << endl;
    }
    // Assign to a function pointer
    f1 = simpleFunction;
    cout << "Test " << f1(5) << endl;
}

void rangeDemo() {
    // -----------------------------------------------------------------------
    // Showing range iteration of an std::vector
    std::vector<float> v;
    v.push_back(1.0);
    v.push_back(3.0);
    v.push_back(2.0);
    cout << "Simple iteration" << endl;
    for (float n : v) {
        cout << n << endl;
    }
}

void lambdaDemo() {

    // -----------------------------------------------------------------------
    // Iterating across an array
    char s[] = "Hello Izzy!";
    // In this case the lambda gets each member of the array
    for_each(s,s+sizeof(s),[](char c) {
        cout << "Hit " << c << endl;
    });

    // -----------------------------------------------------------------------
    // Iterating across an array with access to a variable
    int count = 0;
    // What is shown inside of the [] is called the "capture."  What is passed
    // into the lambda from the enclosing scope.
    for_each(s,s+sizeof(s),[&count](char c) {
        cout << "Hit " << c << endl;
        count++;
    });
    cout << "Count " << count << endl;

    // -----------------------------------------------------------------------
    // Showing sort of an array
    float numbers[] = { 1, 2, 4, 3 };
    std::sort(numbers,numbers+4,  
        // Lambda expression begins  
        [](float a, float b) -> bool {  
            return (a < b);  
        } // end of lambda expression  
    );  
    cout << "After sort:" << endl;
    for_each(numbers,numbers + 4,[](float n) {
        cout << n << endl;
    });

    // -----------------------------------------------------------------------
    // Showing sort of an std::vector
    //
    // IMPORTANT: Notice the new initialization syntax (no push_backs())!
    std::vector<float> v = { 1.0, 3.0, 2.0 };
    std::sort(v.begin(),v.end(),  
        // Lambda expression begins  
        [](float a, float b) -> bool {  
            return (a < b);  
        } // end of lambda expression  
    );  
    cout << "After sort:" << endl;
    for_each(v.begin(),v.end(),[](float n) {
        cout << n << endl;
    });
}

int dummy() {
    return 6;
}

void autoDemo() {
    cout << "autoDemo" << endl;
    auto f = 10.5;
    cout << f << endl;
    auto i = dummy();
    cout << i << endl;
}

static std::mutex m;
static std::string data;

void doWork() {
    // Acquires the mutex for the lifetime of this function
    std::lock_guard<std::mutex> lk(m);
    cout << "Hello on different thread" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout << "Finished sleeping" << endl;
}

void threadDemo() {

    std::thread t1(doWork);
    t1.join();
    cout << "Joined and done!" << endl;

    std::thread t2(doWork);
    t2.detach();
    cout << "Detached and done!" << endl;

    // Wait for a few seconds to see the detached thread finish
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main(int argc,const char** argv) {
    cout << "Hello world" << endl;
    rangeDemo();
    lambdaDemo();
    autoDemo();
    functionPointerDemo();
    threadDemo();
    return 0;
}