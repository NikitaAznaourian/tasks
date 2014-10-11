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
#include <queue>

using namespace std;

/* Condition:
    Дана нуль-терминированная строка char*, состоящая только из букв a,b,c,d.
    Надо преобразовать её в строку, где все вхождения "a" удалены, а все
    вхождения "b" заменены на "cc".
    "abba" -> "cccc", "cdb" -> "cdcc".
    Сделать это надо in place, в предположении, что памяти аллоцировано
    достаточно, чтобы поместилась результирующая строка (и ноль в конце,
    конечно, тоже).
 
   Solution:
    Complexity: O(n) - пройтись по строке
    Additional memory: O(n) в худшем случае, если вся строка s состоит из символов 'b'
*/

void RemoveAndAdd(char* s) {
    if (s == NULL)
        return;
    
    size_t pos1 = 0, pos2 = 0;
    queue<char> buff;
    while (s[pos1] != '\0') {
        if (s[pos1] == 'a') {
            pos1++;
        } else {
            if (s[pos1] == 'b') {
                buff.push('c');
                buff.push('c');
            } else {
                buff.push(s[pos1]);
            }
            pos1++;
            
            while (!buff.empty() && pos2 < pos1) {
                char a = buff.front();
                s[pos2] = a;//buff.front();
                buff.pop();
                pos2++;
            }
        }
    }
    
    while (! buff.empty()) {
        s[pos2] = buff.front();
        buff.pop(); pos2++;
    }
    s[pos2] = '\0';
    return;
}

int main(int argc, const char * argv[])
{
    try {
        char s[32] = "abcd";
        RemoveAndAdd(s);
        if ( strcmp(s, "cccd") ) {
            throw "1 test failed";
        }
        
        char s2[32] = "";
        RemoveAndAdd(s2);
        if ( strcmp(s2, "") ) {
            throw "2 test failed";
        }
        
        char s3[32] = "aaaaaa";
        RemoveAndAdd(s3);
        if ( strcmp(s3, "") ) {
            throw "3 test failed";
        }

        char s4[32] = "aacabbb";
        RemoveAndAdd(s4);
        if ( strcmp(s4, "ccccccc") ) {
            throw "4 test failed";
        }
        
        cout << "All tests successed" << endl;

    } catch (char const* err) {
        cout << err << endl;
    }

    return 0;
}

