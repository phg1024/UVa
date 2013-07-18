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
    int64_t a, b;
    while( scanf("%lld %lld", &a, &b) != EOF )
    {
        if( a >= b ) printf("%lld\n", a-b);
        else printf("%lld\n", b-a);
    }
    return 0;
}

