#include <iostream>
#include <math.h>

// double func(double x) {
//     return x * x;
// }

double integral(double f(double), double a, double b, double eps) {
    long long n = 2;
    double prv = (b - a) * (f(a) + f(b)) / 2;
    double curr = prv / 2 + ((b - a) / 2) * f((a + b) / 2);
    for (int i = 0; i < 5; i++) {
        n *= 2;
        curr = prv / 2;
        double add = 0;
        for (long long c = 1; c < n; c += 2) {
            add += f(a + c * (b - a) / n);
        }
        add *= (b - a) / n;
        prv = curr;
        curr += add;
    }

    while (std::abs(curr - prv) > eps) {
        // std::cout << curr << " " << prv << "\n";
        n *= 2;
        double tmp = curr;
        curr = curr / 2;
        double add = 0;
        for (long long c = 1; c < n; c += 2) {
            add += f(a + c * (b - a) / n);
        }
        add *= (b - a) / n;
        curr += add;
        prv = tmp;
    }
    return curr;
}