#include "set.h"
#include <thread>
#include <vector>
using namespace std; 
AddOnlySet s(10);


void settest() {
    for (int i = 0; i < 10; i++) {
        s.add(i);
    }
}

int main() {
    thread *tArr = new thread[2];
    
    for (int i = 0; i < 10; i++) {
        tArr[i] = std::thread(settest);
    }
    for (int i = 0; i < 10; i++) {
        tArr[i].join();
    }
    s.display();
    // int c = 0;
    // for (auto& i : v) {
    //     cout << "thread " << c << " entered " << i << "times" << endl;
    //     c++; 
    // }
        delete[] tArr;

    return 0;
}