#include <mutex>
#include <atomic>
#include <iostream>
using namespace std;

class AddOnlySet { 
private: 
atomic_int end_index;
atomic_int *elements;
 
public: 
  AddOnlySet(int s) { 
    end_index = 0; 
    elements = new atomic_int[s]; 
    for (int i = 0; i < s; i++) { 
      elements[i] = -1; 
    } 
  } 
 
  bool contains(int check) { 
    for (int i = 0; i < end_index; i++) {
 
      if (elements[i] == check) { 
        return true; 
      } 
    } 
    return false; 
  } 

  void display() {
      cout << '{';
      for (int i = 0; i < 10; i++) {
          cout << elements[i] << ", "; 
      }
      cout << '}' << endl;
  }
 
  void add(int to_add) { 
    int t = end_index.load();
    if (contains(to_add)) { 
      return; 
    } 
    else { 
      if (atomic_compare_exchange_strong(&end_index, &t, t) == true) {
      elements[end_index] = to_add; 
      end_index++; 
      }
    }
  } 
}; 