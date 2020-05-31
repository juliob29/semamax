#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;

class Semaphore {
    public:
        Semaphore(int max): max(max), value(0) {};
        Semaphore(int val, int max): max(max), value(val) {};

        void signal() {
            lock_guard<mutex> lg(value_lock);
            //* Wait until the value is less than max!
            cv.wait(value_lock, [this] () {return value < max;});
            value++;
            if (value == 1) cv.notify_all();
        }

        void wait() {
            lock_guard<mutex> lg(value_lock);
            //* Get the lock first
            cv.wait(value_lock, [this] () {return value > 0;});
            value--;
            if (value == max - 1) cv.notify_all(); //* Finally less than max? Signal could've been waiting!
        } 
        
    private:
        int max;
        int value;
        mutex value_lock;
        condition_variable_any cv;
}; 



int main(int argc, char** argv) {
    Semaphore sem(5); //* This has a maximum of 5, but sem value is 0. 
    return 0;
}