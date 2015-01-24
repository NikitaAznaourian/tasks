//
//  main.cpp
//  tmp
//

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <climits>
#include <locale>
#include <bitset>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <sstream>


/*
 #include <stdio.h>
 int main() { int a, b; scanf("%d %d", &a, &b); printf("%d\n",a+b); return 0; }
*/

using namespace std;

class Queue {
public:
    
    Queue(size_t cap);
    void enqueue(int el);
    int dequeue();
    size_t Size() {return size;};
    size_t Capacity() {return capacity;};
    bool isEmpty() {if (size) return false; return true;}
    ~Queue();

private:
    int* data = nullptr;
    size_t st = 0, end = 0;
    size_t capacity = 0;
    size_t size = 0;
};

Queue::Queue(size_t cap) {
    if (cap < 10)
        cap = 10;
    
    capacity = cap;
    data = new int[capacity+1];
}

Queue::~Queue() {
    delete data;
}

void Queue::enqueue(int val) {
    if (size < capacity) {
        data[end++] = val;
        end = end % (capacity+1);
    } else {
        size_t newCapacity = 1.6 * capacity;
        int* newData = new int[newCapacity+1];
        size_t newSt = 0, newEnd = 0;
        
        // copy all elements
        if (st > end) {
            while (st <= capacity) {
                newData[newEnd++] = data[st++];
            }
            st = 0;
        }
        
        while (st < end) {
            newData[newEnd++] = data[st++];
        }
        
        newData[newEnd++] = val;
        delete data;
        data = newData;
        capacity = newCapacity; st = newSt; end = newEnd;
    }
    
    size++;
}

int Queue::dequeue() {
    if (size == 0)
        throw "Cannot dequeue from emoty queue";
    
    int res = data[st++];
    st = st % (capacity+1);
    size--;
    
    if (size <= capacity/4 && capacity /2 > 10) {
        // allocate new memory and copy
        size_t newCapacity = capacity /2;
        int* newData = new int[newCapacity+1];
        size_t newSt = 0, newEnd = 0;
        
        if (st > end) {
            while (st <= capacity) {
                newData[newEnd++] = data[st++];
            }
            
            st =0;
        }
        
        while (st < end) {
            newData[newEnd++] = data[st++];
        }
        
        delete data;
        data = newData;
        capacity = newCapacity; st = newSt; end = newEnd;
    }
    
    return res;
}

int main() {
    try {
        Queue* q = new Queue(1);
        
        // 1 test
        if (q->Capacity() != 10 || q->Size() || !q->isEmpty())
            throw "1 test failed";
        
        // 2 test
        for (int i =0 ; i < 9; i++)
            q->enqueue(i);
        if (q->Size() != 9 || q->dequeue() != 0 || q->Size() != 8)
            throw "2 test failed";
        
        // 3 test
        for (int i = 0; i < 2; i++)
            q->enqueue(i);
        
        if (q->Size() != 10 || q->Capacity() != 10 || q->dequeue() != 1)
            throw "3 test failed";
        
        // 4 test
        q->enqueue(-1); q->enqueue(-2);
        if (q->Capacity() != 16 || q->Size() != 11 || q->dequeue() != 2)
            throw "4 test failed";
        
        // 5 test
        for (int i = 100; i < 107; i++)
            q->enqueue(i);
        
        if (q->Capacity() != 25 || q->Size() != 17)
            throw "5 test failed";
        
        // 6 test
        for (int i = 0; i < 11; i++)
            q->dequeue();
        
        if (q->Capacity() != 12 || q->Size() != 6)
            throw "6 test failed";
        
        for (int i = 0; i < 6; i++) {
            if (q->dequeue() != 101 + i)
                throw "7 test failed";
        }
        
        // 7 test
        if (q->Size() || q->Capacity() != 12)
            throw "7 test failed";

        cout << "All test successfull\n";
        
    } catch(char const * err) {
        cout << err << endl;
    }
    
    return 0;
}

