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
    Check if s2 is a rotation of s1
 
   Solution:
    Complexity: O(n), n - length of s1 and s2
    Additional memmory: 2n
*/

bool isRotation(const string& s1, const string& s2) {
    if (s1.size() != s2.size())
        return false;
    
    string doubled = s1 + s1;
    return doubled.find(s2) != string::npos;
}

int main(int argc, const char * argv[])
{
    try {
        string s1 = "test";
        string s2 = "test";
        
        if (!isRotation(s1, s2))
            throw "1 test failed";
        
        s1 = "abc";
        s2 = "ab";
        if (isRotation(s1, s2))
            throw "2 test failed";
        
        s1 = "test";
        s2 = "tset";
        if (isRotation(s1, s2))
            throw "3 test failed";
        
        s1 = "abcd";
        s2 = "dabc";
        if (!isRotation(s1, s2))
            throw "4 test failed";
        
        cout << "All tests successed" << endl;
    } catch (char const* err) {
        cout << err << endl;
    }

    return 0;
}

