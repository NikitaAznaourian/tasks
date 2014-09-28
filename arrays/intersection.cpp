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
#include <map>
#include <string>
#include <algorithm>

using namespace std;

pair<int,int> maxIntersection(vector<pair<int,int>>& v) {
    
    multimap<int, bool> points; // true - open, false - closing
    for (int i = 0; i < v.size(); i++) {
        if (v[i].first > v[i].second)
            throw "bad input";
        points.insert(make_pair(v[i].first, true));
        points.insert(make_pair(v[i].second, false));
    }
    
    int maxInt = 0, maxPoint = 0;
    int curInt = 0;
    
    for (multimap<int,bool>::const_iterator it = points.begin(); it != points.end(); it++) {
        if (it->second) {
            if (++curInt > maxInt) {
                maxInt = curInt;
                maxPoint = it->first;
            }
        } else {
            curInt--;
        }
    }
    
    return make_pair(maxInt, maxPoint);
}

int main(int argc, const char * argv[])
{
    try {
    
        // 1 test
        vector<pair<int,int>> v {make_pair(1,3), make_pair(2,4)};
        pair<int,int> res = maxIntersection(v);
        if (res.first != 2 || res.second != 2)
            throw "First test failed";
        
        // 2 test
        v.clear();
        v = {make_pair(5,7), make_pair(3,4)};
        res = maxIntersection(v);
        if (res.first != 1 || res.second != 3)
            throw "Second test failed";
        
        // 3 test
        v.clear();
        v = {make_pair(-1,-1), make_pair(-3,-3), make_pair(100, 1000), make_pair(50, 120), make_pair(0,0)};
        res = maxIntersection(v);
        if (res.first != 2 || res.second != 100)
            throw "Third test failed";

        // 4 test
        v.clear();
        v = {make_pair(-1,-1), make_pair(-1,-1)};
        res = maxIntersection(v);
        if (res.first != 2 || res.second != -1)
            throw "Fourth test failed";

        // 5 test
        v.clear();
        v = {make_pair(-2,-1), make_pair(-1,0)};
        res = maxIntersection(v);
        if (res.first != 2 || res.second != -1)
            throw "Fifth test failed";

        cout << "All tests passed" << endl;
    
    } catch(string err) {
        cout << err.c_str() << endl;
    }
    
    return 0;
}

