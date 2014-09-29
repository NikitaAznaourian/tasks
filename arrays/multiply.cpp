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



vector<int> multiply(const vector<int>& v) {
    auto size = v.size();

    if (size == 0)
        return {};

    if (size == 1)
        return {0};

    // size >= 2

    vector<int> b(size);
    b[0] = 1;
    for (size_t i = 1; i < size; i++) {
        b[i] = v[i-1] * b[i-1];
    }
    
    vector<int> c(size);
    c[size-1] = 1;
    for (size_t i = size-1; i > 0; i--) {
        c[i-1] = c[i] * v[i];
    }
    
    vector<int> res(size);
    for (size_t i = 0; i < size; i++) {
        res[i] = b[i] * c[i];
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

