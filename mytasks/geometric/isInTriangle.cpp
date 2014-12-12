//
//  main.cpp
//  tmp
//

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <climits>
#include <locale>
    
using namespace std;

std::locale loc;

/* 
 - Считаем площадь изначального треугольника
 - Вычисляем площади треугольников с проверяемо точкой
 - Если сумма трех треугольников с проверяемой точкой равна сумме изначального треугольника, 
 значит толька пренадлежит этому треугольнику
 
 Площадь треугольника вычисляется как 1/2 * | SUM(i = 1..n) (Xi*(Yi+1-Yi-1))|
*/

float trArea(int x1, int y1, int x2, int y2, int x3, int y3) {
    return abs(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2;
}

bool inTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int ax, int ay) {
    float ABC = trArea(x1, y1, x2, y2, x3, y3);
    
    float ABP = trArea(ax, ay, x1, y1, x2, y2);
    float ACP = trArea(ax, ay, x1, y1, x3, y3);
    float BCP = trArea(ax, ay, x2, y2, x3, y3);
    
    return (ABC == ABP+ACP+BCP);
}

int main() {
    try {
        
        int x1 = -8, y1 = -4, x2 = 2, y2 = -2, x3 = 1, y3 = 5;
        
        if (!inTriangle(x1, y1, x2, y2, x3, y3, 0, 0))
            throw "1 test failed";
        
        if (!inTriangle(x1, y1, x2, y2, x3, y3, -4, 0))
            throw "2 test failed";
        
        if (inTriangle(x1, y1, x2, y2, x3, y3, -5, 1))
            throw "3 test failed";
        
        cout << "All test successfull\n";
        
    } catch(char const * err) {
        cout << err << endl;
    }
    
    return 0;
}










