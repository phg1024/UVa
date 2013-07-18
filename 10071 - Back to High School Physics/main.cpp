#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

int main(){
    int v, t;
    while( scanf("%d %d", &v, &t) != EOF )
    {
        // v = a * t
        // d = 0.5 * a * t * t
        // res = 0.5 * a * (2t) * (2t) = 2 * v * t
        printf("%d\n", (v * t) << 1);
    }
    return 0;
}

