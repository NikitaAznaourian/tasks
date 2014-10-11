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

/* 
    Condition: Longest palindrome substring, линейное время.
        Самая длинная подстрока данной строки, которая является палиндромом.
        Сначала за час напиши как получится, потом думай, как сделать за линейное время.
 
    Solution:
        Complexity: Сделал со сложность O(n^2). Как сделать за O(n) - не придумал, нужна подсказка.
            Похоже нужен какой-то препроцессинг. Что-то типа алгоритма Кнута-Морриса-Пратта или Рабина-Карпа
 
        Additional memory: O(1)
*/

void PolHelper(const string& s, string& p, int& posSt, int& posEnd) {
    
    if (posSt >= posEnd || posSt < 0 || posEnd >= (int) s.size()) {
        posSt++; posEnd--;
        return;
    }
    
    while (posSt >= 0 && posEnd < s.size() && s[posSt] == s[posEnd]) {
        posSt--; posEnd++;
    }
    
    posSt++;
    posEnd--;

    return;
}

void checkPolindrom(const string& s, string& p) {
    if (s.size() == 0)
        return;
    
    int pos = 0;
    int posSt, posEnd;
    while (pos < s.size()-1) {
        if (s[pos] == s[pos+1]) {
            posSt = pos-1;
            posEnd = pos+2;
            PolHelper(s, p, posSt, posEnd);
            
            if (posEnd - posSt +1 > p.size())
                p = s.substr(posSt, posEnd-posSt+1);
        }
        
        if (pos+2 < s.size() && s[pos] == s[pos+2]) {
            posSt = pos-1;
            posEnd = pos+3;
            PolHelper(s,p,posSt,posEnd);
        
            if (posEnd - posSt +1 > p.size())
                p = s.substr(posSt, posEnd-posSt+1);
        }
        
        pos++;
    }
    
    if (p.size() == 0) {
        p.append(1,s[0]);
    }
    return;
}

int main(int argc, const char * argv[])
{
    try {
        // test 1
        
        string s = "a";
        string res;
        checkPolindrom(s, res);
        if (res != "a")
            throw "1 test failed";
        
        // test 2
        s = "";
        res.clear();
        checkPolindrom(s, res);
        if (res != "")
            throw "2 test failed";

        // test 3
        s = "abcd";
        res.clear();
        checkPolindrom(s, res);
        if (res != "a")
            throw "3 test failed";

        // test 4
        s = "abcc";
        res.clear();
        checkPolindrom(s, res);
        if (res != "cc")
            throw "4 test failed";

        // test 5
        s = "cdcab";
        res.clear();
        checkPolindrom(s, res);
        if (res != "cdc")
            throw "5 test failed";

        // test 5
        s = "cccaccc";
        res.clear();
        checkPolindrom(s, res);
        if (res != "cccaccc")
            throw "6 test failed";

        cout << "All tests successed" << endl;

    } catch (char const* err) {
        cout << err << endl;
    }

    return 0;
}

