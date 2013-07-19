#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int main() {
    double n, p;

    while (scanf("%lf%lf", &n, &p) != EOF) {
        printf("%.lf\n", pow(p, 1/n));
    }

    return 0;
}

