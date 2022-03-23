#pragma once
#include <atomic>
#include <mutex>
#include <iostream>
using namespace std;
// pretend this is passed in as compile time constant
#define NUMTHREADS 8
class Semaphore {                                                                                            
 public: 
  Semaphore (int num_allowed_threads) { 
    allowed = num_allowed_threads;                                                                                                                             
    occupants.store(0);
// array which will denote if thread w/ tid t is in critical section or not
    inSection = new bool[NUMTHREADS];
    for (int i = 0; i < NUMTHREADS; i++) {
        inSection[i] = false;
    }
  } 
  int enter(int tid) { 
    // safety check: cannot call enter if already entered 
    if (inSection[tid] == true) {
        // cout << tid << " illegal entry attempt " << endl;
        return -1;
    }
    //if semaphore at capacity, must wait
    bool acquired = false;
    while (!acquired) {
        // protect incrementing w/ mutex
        m.lock();
        // cout << tid << " wants to enter " << endl;
        // cout << "occupant limit: " << allowed << " occupants allowed " << endl;
        // cout << "currently " << occupants << " in section. " << endl;
        if (occupants.load() < allowed) {
            cout << tid << " entered " << endl;
            atomic_fetch_add(&occupants, 1);
            acquired = true;
            // mark that youve entered
            inSection[tid] = true;
            // cout << " now " << occupants << " occupants in section " << endl;
        }
        m.unlock();
    }                   
    return 0;                                                                              
  } 
  int exit(int tid) { 
    // safety check: cant exit if you havent entered
    if (inSection[tid] == false) {
        // cout << tid << " illegal exit attempt " << endl;
        return -1;
    }
    // threads that exit should make room for more threads to enter. 
    m.lock();
    // cout << tid << " exiting " << endl;
    atomic_fetch_sub(&occupants, 1);
    // mark that youve exited
    inSection[tid] = false;
    // cout << "now " << occupants << " in section " << endl;
    m.unlock();                       
    return 0;                                                                                                                                     
  } 
  void resize(int new_num_allowed_threads) {
    bool acquired = false;
    while (!acquired) {
        if (occupants.load() <= new_num_allowed_threads) {
            m.lock();
            // cout << " about to resize from " << allowed << " to " << new_num_allowed_threads << endl;
            allowed = new_num_allowed_threads;
            acquired = true;
            m.unlock();
        }
    }
    return;
    }

 private:  
    // give me private variables          
    int allowed;
    atomic<int> occupants;
    mutex m;
    // PART C array pointer
    bool *inSection;
}; 