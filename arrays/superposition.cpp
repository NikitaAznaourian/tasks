//
//  main.cpp
//  tmp
//
//  Created by Nikita Aznauryan on 10.07.14.
//  Copyright (c) 2014 Nikita Aznauryan. All rights reserved.
//

/*
 Conditions: We have an array of segments. Write a function that returns a max number of nested segments.
 Complexity:
 O(n^2) with additional memory of O(n) size.
 */

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

struct classcomp {
    bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs) const {
        if (lhs.first != rhs.first)
            return lhs.first < rhs.first;

        auto same_first = lhs.first;
        return (same_first+rhs.second) < (same_first+lhs.second);
    }
};

int maxCover(const vector<pair<int,int>>& v) {
    
    multimap<pair<int, int>, int, classcomp> points; // second param is cover level
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i].first > v[i].second)
            throw "bad input";
        points.insert({{v[i].first, v[i].second-v[i].first}, 1}); // initialize cover level with 1
    }
    
    int maxCover = 0;
    
    for (auto it = points.begin(); it != points.end(); it++) {
        int pointCover = it->second;
        if (pointCover > maxCover)
            maxCover = pointCover;
        
        auto it2 = it;
        it2++;
        
        while (it2 != points.end() && (it2->first.first <= it->first.first+it->first.second) ) {
            if (it2->first.first+it2->first.second <= it->first.first+it->first.second) {
                it2->second += 1;
            }
            it2++;
        }
        
    }
    
    return maxCover;
}

int main(int argc, const char * argv[])
{
    try {

        // 1 test
        vector<pair<int,int>> v {{100,1000}, {1,3}, {2,4}};
        int res = maxCover(v);
        if (res != 1)
            throw "First test failed";

        // 2 test
        v = {{1,7}, {3,4}};
        res = maxCover(v);
        if (res != 2)
            throw "Second test failed";

        // 3 test
        v = {{0,0}};
        res = maxCover(v);
        if (res != 1)
            throw "Third test failed";

        // 4 test
        v = {{-1,-1}, {-1,-1}};
        res = maxCover(v);
        if (res != 2 )
            throw "Fourth test failed";

        // 5 test
        v = {{-2,2}, {-1,-1}, {-1,2}, {-2, -1}};
        res = maxCover(v);
        if (res != 4)
            throw "Fifth test failed";

        // 6 test
        v = {{1, 10}, {2, 3}, {4, 7}, {5, 6}};
        res = maxCover(v);
        if (res != 3)
            throw "Sixth test failed";

        cout << "All tests passed" << endl;
        
    } catch(char const* err) {
        cout << err << endl;
    }
    
    return 0;
}

