#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
int main() {
    long double eps = 1e-7;
    long double x1, y1, x2, y2, x3, y3, r1, r2, r3, x, y;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> r1 >> r2 >> r3;
    x = ((y2 - y1) * (r2 * r2 - r3 * r3 - y2 * y2 + y3 * y3 - x2 * x2 + x3 * x3) - (y3 - y2) * (r1 * r1 - r2 * r2 - y1 * y1 + y2 * y2 - x1 * x1 + x2 * x2)) / (2 * ((y3 - y2) * (x1 - x2)  - (y2 - y1) * (x2 - x3)));
    y = ((x2 - x1) * (r2 * r2 - r3 * r3 - x2 * x2 + x3 * x3 - y2 * y2 + y3 * y3) - (x3 - x2) * (r1 * r1 - r2 * r2 - x1 * x1 + x2 * x2 - y1 * y1 + y2 * y2)) / (2 * ((x3 - x2) * (y1 - y2)  - (x2 - x1) * (y2 - y3)));
    ((abs((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) - r1 * r1) < eps) && (cout << fixed << setprecision (10) << x << " " << y << endl)) || ((abs((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) - r1 * r1) >= eps) && (cout << "Impossible" << endl)); 
    return 0;
}