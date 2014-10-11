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
    Condition: Для заданного списка слов напишите алгоритм поиска самого длинного слова,
        образованного другими словами, входящими в список.
 
        Например:
            cat, banana, dog, nana, walk, walker, dogwalker
            => dogwalker
 
    Solution:
        Complexity: Не очень понимаю, как здесь можно оценить сложность задачи.
            Кажется, что внутри CanBuildWords сложность можно вычислитсь по формуле
            f(l) = f(l-1)+f(l-2) +... = 2f(l-1)
            => O(k^l) , но не очень понятно, откуда брать основние и вообще насколько это правильно.
*/

struct compare {
    bool operator()(const string& first, const string& second) {
        return first.size() < second.size();
    }
};

bool canBuildWords(string& str, bool isOriginalWord, map<string, bool>& map) {
    if (map.count(str) > 0 && !isOriginalWord) {
        return map[str];
    }
    
    for (int i = 1; i < str.length(); i++) {
        string left = str.substr(0, i);
        string right = str.substr(i);
        
        if (map.count(left) > 0 && map[left] && canBuildWords(right, false, map))
            return true;
    }
    map[str] = false;
    return false;
}

string Word (vector<string>& arr) {
    map<string, bool> map;
    for (auto it = arr.cbegin(); it != arr.cend(); it++) {
        map.insert({*it, true});
    }
    
    compare c;
    sort(arr.begin(), arr.end(), c);
    
    for (auto it = arr.cbegin(); it != arr.cend(); it++) {
        string curStr = *it;
        if (canBuildWords(curStr, true, map)) {
            return curStr;
        }
    }
    
    return "";
}


int main(int argc, const char * argv[])
{
    try {
        vector<string> v {"dog", "walk", "dogwalk"};
        cout << Word(v);

        cout << "All tests successed" << endl;

    } catch (char const* err) {
        cout << err << endl;
    }

    return 0;
}

