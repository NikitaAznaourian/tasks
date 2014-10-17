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

/* Condition:
    RLE encoding - encode the string
 
   Solution:
    Complexity: O(n) - пройтись по строке
    Additional memory: O(1)
*/

void RLEEncoding(const string& s, string& res) {
    res.clear();

    if (s.size() == 0)
        return;
    
    size_t counter = 1, pos = 1;
    char lastChar = s[0];
    
    while (pos < s.size()) {
        if (s[pos] == lastChar) {
            counter++;
        } else {
            res.append(to_string(counter)).push_back(lastChar);
            counter = 1;
            lastChar = s[pos];
        }
        pos++;
    }
    
    res.append(to_string(counter)).push_back(lastChar);
    return;
}

int main(int argc, const char * argv[])
{
    try {
        string s = "";
        string res;

        RLEEncoding(s, res);
        if (res != "")
            throw "1 test failed";
        
        s = "a";
        res.clear();
        RLEEncoding(s, res);
        if (res != "1a")
            throw "2 test failed";
        
        s = "aaaa";
        res.clear();
        RLEEncoding(s, res);
        if (res != "4a")
            throw "3 test failed";

        s = "aabbbbbcdd";
        res.clear();
        RLEEncoding(s, res);
        if (res != "2a5b1c2d")
            throw "4 test failed";
        
        cout << "All tests successed" << endl;
    
    } catch (char const* err) {
        cout << err << endl;
    }

    return 0;
}

