#include "sem.h"
#include <thread>
#include <vector>
using namespace std; 
Semaphore s(3);
vector<int> v (8, 0);
void semtest ( int tid) {
    int i = 20;
    

    if (tid == 1) {
        s.resize(2);
        while (i > 0) {
            s.enter(tid);
            s.enter(tid); 
            v[tid]++;
            s.exit(tid);
            s.exit(tid);

            i--;
        }
    }else {
        while (i > 0) {
            s.enter(tid);
            v[tid]++;
            s.exit(tid);
            i--;
        }
    }
    if (tid == 3) {
        s.resize(1);
    }
    if (tid == 4) {
        s.resize(5);
    }
}
int main() {
    thread *tArr = new thread[8];
    for (int i = 0; i < 8; i++) {
        tArr[i] = std::thread(semtest, i);
    }
    for (int i = 0; i < 8; i++) {
        tArr[i].join();
    }
    
    int c = 0;
    for (auto& i : v) {
        cout << "thread " << c << " entered " << i << "times" << endl;
        c++; 
    }
        delete[] tArr;

    return 0;
}
