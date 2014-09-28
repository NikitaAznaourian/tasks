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

struct classcomp {
    bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs) const {
        if (lhs.first != rhs.first)
            return lhs.first < rhs.first;

        return rhs.second < lhs.second;
    }
};

int maxCover(vector<pair<int,int>>& v) {
    
    multiset<pair<int, int>, classcomp> points; // true - open, false - closing
    for (int i = 0; i < v.size(); i++) {
        if (v[i].first > v[i].second)
            throw "bad input";
        points.insert(make_pair(v[i].first, v[i].second-v[i].first));
    }
    
    int maxCover = 0;
    
    for (multiset<pair<int,int>, classcomp>::const_iterator it = points.begin(); it != points.end(); it++) {
        int pointCover = 1;
        
        multiset<pair<int,int>, classcomp>::const_iterator it2 = it;
        it2++;
        
        while (it2 != points.end() && (it2->first <= it->first+it->second) ) {
            if (it2->first+it2->second <= it->first+it->second) {
                pointCover++;
            }
            it2++;
        }
        
        if (pointCover > maxCover) {
            maxCover = pointCover;
        }
        
    }
    
    return maxCover;
}

int main(int argc, const char * argv[])
{
    try {
    
        // 1 test
        vector<pair<int,int>> v {make_pair(100,1000), make_pair(1,3), make_pair(2,4)};
        int res = maxCover(v);
        if (res != 1)
            throw "First test failed";
        
        // 2 test
        v.clear();
        v = {make_pair(1,7), make_pair(3,4)};
        res = maxCover(v);
        if (res != 2)
            throw "Second test failed";
        
        // 3 test
        v.clear();
        v = {make_pair(0,0)};
        res = maxCover(v);
        if (res != 1)
            throw "Third test failed";

        // 4 test
        v.clear();
        v = {make_pair(-1,-1), make_pair(-1,-1)};
        res = maxCover(v);
        if (res != 2 )
            throw "Fourth test failed";

        // 5 test
        v.clear();
        v = {make_pair(-2,2), make_pair(-1,-1), make_pair(-1,2), make_pair(-2, -1)};
        res = maxCover(v);
        if (res != 4)
            throw "Fifth test failed";

        cout << "All tests passed" << endl;
    
    } catch(string err) {
        cout << err.c_str() << endl;
    }

    return 0;
}

