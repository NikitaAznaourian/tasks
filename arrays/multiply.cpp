//
//  main.cpp
//  tmp
//
//  Created by Nikita Aznauryan on 10.07.14.
//  Copyright (c) 2014 Nikita Aznauryan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <set>
#include <map>
#include <string>
#include <algorithm>

using namespace std;



vector<int> multiply(vector<int>& v) {
    vector<int> b(v.size());
    int cur = 1;
    
    for (int i = 0; i < v.size(); i++) {
        cur *= v[i]; b[i] = cur;
    }
    
    cur = 1;
    vector<int> c(v.size());
    for (int i = (int)v.size()-1; i>= 0; i--) {
        cur *= v[i];
        c[i] = cur;
    }
    
    vector<int> res(v.size());
    
    if (v.size() == 0)
        return res;
    
    if (v.size() == 1) {
        res[0] = 0;
        return res;
    }
    
    res[0] = c[1];
    res[v.size()-1] = b[v.size()-2];
    for (int i = 1; i < v.size()-1; i++) {
        res[i] = b[i-1]*c[i+1];
    }
    return res;
}

int main(int argc, const char * argv[])
{
    try {
    
        // 1 test
        vector<int> v {1,2,3,4};
        vector<int> res = multiply(v);
        if (res != vector<int>{24, 12, 8, 6})
            throw "First test failed";
        
        // 2 test
        v.clear();
        res = multiply(v);
        if (res != vector<int>{})
            throw "Second test failed";
        
        // 3 test
        v = {2};
        res = multiply(v);
        if (res != vector<int>{0})
            throw "Third test failed";

        // 4 test
        v = {-1, -10, 10};
        res = multiply(v);
        if (res != vector<int>{-100, -10, 10})
            throw "Fourth test failed";

        // 5 test
        v = {100, 2, -3, 0};
        res = multiply(v);
        if (res != vector<int>{0, 0, 0, -600})
            throw "Fifth test failed";

        cout << "All tests passed" << endl;
    
    } catch(char const* err) {
        cout << err << endl;
    }

    return 0;
}

