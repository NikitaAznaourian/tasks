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

pair<int,int> maxIntersection(const vector<pair<int,int>>& v) {
    
    multiset<pair<int, bool>> points; // false - open, true - closing
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i].first > v[i].second)
            throw "bad input";
        points.insert({v[i].first, false});
        points.insert({v[i].second, true});
    }
    
    int maxInt = 0, maxPoint = 0;
    int curInt = 0;
    
    for (auto it = points.cbegin(); it != points.cend(); it++) {
        if (!it->second) {
            if (++curInt > maxInt) {
                maxInt = curInt;
                maxPoint = it->first;
            }
        } else {
            curInt--;
        }
    }
    
    return {maxInt, maxPoint};
}

int main(int argc, const char * argv[])
{
    try {
    
        // 1 test
        vector<pair<int,int>> v {{1,3}, {2,4}};
        auto res = maxIntersection(v);
        if (res != make_pair(2, 2))
            throw "First test failed";
        
        // 2 test
        v = {{5,7}, {3,4}};
        res = maxIntersection(v);
        if (res != make_pair(1, 3))
            throw "Second test failed";
        
        // 3 test
        v = {{-1,-1}, {-3,-3}, {100, 1000}, {50, 120}, {0,0}};
        res = maxIntersection(v);
        if (res != make_pair(2, 100))
            throw "Third test failed";

        // 4 test
        v = {{-1,-1}, {-1,-1}};
        res = maxIntersection(v);
        if (res != make_pair(2, -1))
            throw "Fourth test failed";

        // 5 test
        v = {{-2,-1}, {-1,0}};
        res = maxIntersection(v);
        if (res != make_pair(2, -1))
            throw "Fifth test failed";

        cout << "All tests passed" << endl;
    
    } catch(char const* err) {
        cout << err << endl;
    }
    
    return 0;
}

