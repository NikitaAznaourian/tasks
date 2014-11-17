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

        return rhs.second < lhs.second;
    }
};

int maxCover(const vector<pair<int,int>>& v) {
    
    vector<pair<int, int>> segments(v);
    sort(segments.begin(), segments.end(), classcomp());

    vector<int> cover_level(segments.size(), 1);

    for (size_t outer_idx = 0; outer_idx < v.size(); outer_idx++) {
        if (segments[outer_idx].first > segments[outer_idx].second)
            throw "bad input";

        for (size_t inner_idx = outer_idx + 1; inner_idx < v.size() && (segments[inner_idx].first <= segments[outer_idx].second); inner_idx++) {
            if (segments[inner_idx].second <= segments[outer_idx].second) {
                cover_level[inner_idx]++;
            }
        }
    }

    return *max_element(cover_level.begin(), cover_level.end());
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

