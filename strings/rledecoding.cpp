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
#include <locale>

using namespace std;

/* Condition:
    RLE decoding - decode the string
 
   Solution:
    Complexity: O(n) - пройтись по строке
    Additional memory: O(1)
*/

void RLEDecoding(const string& s, string& res) {
    locale loc;
    bool count_found = false;
    size_t count = 0;
    
    for (char c : s) {
        if (isdigit(c, loc)) {
            count *= 10;
            count += c - '0';
            count_found = true;
        } else  {
            if (count_found) {
                res.append(count, c);
                count_found = false;
                count = 0;
            } else {
                throw "Digit expected";
            }
        }
    }
    
    if (count_found)
        throw "Digit without a letter at the end";
    return;
}


int main(int argc, const char * argv[])
{
    try {
        
        bool isExeption = false;
        string s = "";
        string res;

        // 1 test
        RLEDecoding(s, res);
        if (res != "")
            throw "1 test failed";
        
        // 2 test
        s = "a1";
        res.clear();
        isExeption = false;

        try {
            RLEDecoding(s, res);
        } catch(char const* err) {
            isExeption = true;
        }

        if (!isExeption)
            throw "2 test failed";

        // 3 test
        s = "2a3";
        res.clear();
        isExeption = false;
        
        try {
            RLEDecoding(s, res);
        } catch(char const* err) {
            isExeption = true;
        }
        
        if (!isExeption)
            throw "3 test failed";

        // 4 test
        s = "2a3ss";
        res.clear();
        isExeption = false;
        
        try {
            RLEDecoding(s, res);
        } catch(char const* err) {
            isExeption = true;
        }
        
        if (!isExeption)
            throw "4 test failed";

        // 5 test
        s = "2a3s1d";
        res.clear();
        isExeption = false;

        RLEDecoding(s, res);
        if (res != "aasssd")
            throw "5 test failed";

        // 6 test
        s = "12a1d";
        res.clear();
        isExeption = false;
        
        RLEDecoding(s, res);
        if (res != "aaaaaaaaaaaad")
            throw "6 test failed";

        cout << "All tests successed" << endl;
 
    } catch (char const* err) {
        cout << err << endl;
    }

    return 0;
}

