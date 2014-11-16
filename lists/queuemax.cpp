#include <stack>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

/*
5) Реализовать очередь с операцией "максимум" в двух вариантах — на двух стеках и без.

Как сделать без стеков - не догадался
*/


class Queue {
private:
    stack<pair<int,int> > second;
    stack<int> first;
    int fMax = INT_MIN;

public:
    void push(int n);
    int pop();
    int max();
    bool empty();
};

void Queue::push(int n) {
    fMax = ::max(fMax, n);
    first.push(n);
}

int Queue::pop() {
    if (empty())
        throw "Cannot pop from empyt queue";
    
    if (second.empty()) {
        int curEl;
        while (!first.empty()) {
            curEl = first.top();
            if (!second.empty()) {
                second.push( {curEl, ::max(curEl, second.top().second)} );
            } else {
                second.push({curEl, curEl});
            }
            first.pop();
        }
        fMax = INT_MIN;
    }
    
    pair<int,int> curEl = second.top();
    second.pop();
    return curEl.first;
}

bool Queue::empty() {
    if (first.empty() && second.empty())
        return true;
    return false;
}

int Queue::max() {
    if (empty())
        throw "Cannot call max on empty queue";
    
    if (first.empty())
        return second.top().second;
    
    if (second.empty())
        return fMax;
    
    return ::max(fMax, second.top().second);
}

int main() {

    try {
        Queue q;
        bool exc = false;
        
        // test 1
        try {
            q.pop();
        } catch(...) {
            exc= true;
        }
        
        if (!exc)
            throw "1 test failed";
        exc = false;
        
        // test 2
        if (!q.empty())
            throw "2 test failed";
        
        // test 3
        q.push(3);
        if (q.max() != 3)
            throw "3 test failed";
        
        // test 4
        q.push(4);
        if (q.max() != 4)
            throw "4 test failed";
        
        q.pop();
        if (q.max() != 4)
            throw "5 test failed";
        
        q.push(1);
        if (q.max() != 4)
            throw "6 test failed";
        
        q.pop(); q.pop();
        if (!q.empty())
            throw "7 test failed";
        
        cout <<  "all test successed" << endl;
        
    } catch(char const * err) {
        cout << err << endl;
    }
    return 0;
}
