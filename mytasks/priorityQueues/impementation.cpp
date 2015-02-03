//
//  main.cpp
//  tmp
//

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <list>
#include <limits>

using namespace std;

class PriorityQueue {
public:
    PriorityQueue() {data.resize(1);};
    bool empty() { return N==0; };
    size_t size() { return N; };
    
    void insert(int i) {
        N++;
        data.push_back(i);
        swim(N);
    };
    
    void removeMax() {
        if (empty())
            return;
        data[1] = data[N--];
        data.pop_back();
        sink(1);
    }
    
    int max() {
        if (empty())
            throw "empty queue";
        
        return data[1];
    };
    
private:
    void swap(size_t i, size_t j) {
        if (i > N || j > N)
            return;
        
        int tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
    
    void swim(size_t i) {
        while (i > 1 && i <= N) {
            if (data[i] <= data[i/2])
                return;
            
            swap(i, i/2);
            i = i/2;
        }
    }
    
    void sink(size_t i) {
        if (i == 0)
            return;
        
        while (i <= N/2) {
            size_t j = 2*i;
            
            if (j+1 <= N && data[j] < data[j+1]) {
                j++;
            }
            
            if (data[i] < data[j]) swap(i,j);
            i = j;
        }
    }

    vector<int> data;
    size_t N = 0;
};

int main() {
    
    try {
        
        PriorityQueue* q = new PriorityQueue();
        
        // 1 test
        if (!q->empty())
            throw "1 test failed";
        
        // 2 test
        q->insert(100);
        if (q->size() != 1 || q->max() != 100)
            throw "2 test failed";
        
        // 3 test
        q->insert(12);
        q->insert(0);
        q->insert(23);
        
        if (q->size() != 4 || q->max() != 100)
            throw "3 test failed";
        
        // 4 test
        q->insert(120);
        if (q->max() != 120)
            throw "4 test failed";
        
        // 5 test
        q->removeMax();
        q->removeMax();
        
        if (q->max() != 23 || q->size() != 3)
            throw "5 test failed";
        
        // 6 test
        q->insert(24);
        if (q->max() != 24)
            throw "6 test failed";
        
        // 7 test
        q->removeMax();
        q->removeMax();
        q->removeMax();
        q->removeMax();
        
        if (!q->empty())
            throw "7 test failed";
        
        // 8 test
        q->insert(1);
        if (q->size() != 1 || q->max() != 1)
            throw "8 test failed";
        
        
        cout << "All tests successfull\n";
    } catch (const char* err) {
        cout << err << endl;
    }
    
    return 0;
}

