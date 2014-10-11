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
    Condition: Дан маппинг кнопок в буквы. Напечатать все буквенные комбинации, которые соответствуют этому
        номеру в данном маппинге.
 
    Solution:
        Complexity: Здесь были проблемы с определение сложости. Рассуждения такие:
        f(n) = k * f(n-1), где k - число символов для каждой кнопки
        Получается сложность O(k)
 
        Additional memory: k^9, где 9 - число кнопок (если сохраняем результаты , а не выводим на печать), иначе O(1)
*/

void phoneNumbersHelper(const map<int, vector<char>>& s, const string& phone, vector<string>& results, size_t pos, string& curStr) {

    if (pos >= phone.size()) {
        results.push_back(curStr);
        return;
    }
    
    
    int curNum = (int) phone[pos] - (int)'0';
    if (s.count(curNum) == 0)
        throw "Unknown button";
    
    const vector<char> chars = s.at(curNum);
    if (chars.size() == 0)
        throw "Button without digits";
    
    for (auto it = chars.cbegin(); it != chars.cend(); it++) {
        curStr.append(1, *it);
        phoneNumbersHelper(s, phone, results, pos+1, curStr);
        curStr.pop_back();
    }
    
}

void phoneNumbers(const map<int, vector<char>>& s, const string& phone, vector<string>& results) {
    string curStr;
    phoneNumbersHelper(s, phone, results, 0, curStr);
}

int main(int argc, const char * argv[])
{
    try {
        
        // test 1
        vector<string> results;
        vector<string> expected = {"ac", "ad", "bc", "bd"};
        map<int, vector<char>> map;
        map[0] = {'a', 'b'};
        map[1] = {'c', 'd'};
        string phone = "01";
        
        phoneNumbers(map, phone, results);
        
        if (results != expected)
            throw "1 test failed";
        
        
        // test 2
        map.clear();
        results.clear();
        
        expected = {"aa", "ab", "ba", "bb"};
        phone = "11";
        map[1] = {'a', 'b'};
        
        phoneNumbers(map, phone, results);
        
        if (results != expected)
            throw "2 test failed";
        
        cout << "All tests successed" << endl;

    } catch (char const* err) {
        cout << err << endl;
    }

    return 0;
}

