#include <iostream>

using namespace std;

double module(double x) {
    if (x >= 0)
        return x;

    return -x;
}

double sqrtH(double x, double min, double max, double acc) {
    double cur = (min+max) / 2;
    double curSqr = cur*cur;
    if (module(curSqr-x) <= acc) {
        return cur;
    }

    if ( curSqr > x) {
        return sqrtH(x, min, cur, acc);
    } else {
        return sqrtH(x, cur, max, acc);
    }
}

double sqrt(double x, double acc) {
    if (x < 0)
        throw "Negative value";

    if (x == 0)
        return 0;
    if (x == 1)
        return 1;

    if (x > 1) {
        return sqrtH(x, 1, x, acc);
    } else {
        return sqrtH(x, 0.0, 1.0, acc);
    }
}

int main() {
    try {
        double res = sqrt(100, 0.1);
        if (res > 10.1 || res < 9.9)
            throw "1 test failed";

        if (sqrt(900, 0) != 30)
            throw "2 test failed";

        res = sqrt(10, 0.1);
        if (res > 3.3 || res < 3)
            throw "3 test failed";

        res = sqrt(0.01, 0.0000001);
        if (res > 0.100001 || res < 0.09999)
            throw "4 test failed";


    } catch(char const * err) {
        cout << err << endl;
    }

    return 0;
}
