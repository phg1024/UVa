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

int extended_gcd(int a, int b, int& x, int &y)
{
    if( b == 0 )
    {
        x = 1, y = 0;
        return a;
    }
    else
    {
        int d = extended_gcd(b, a%b, x, y);

        int nx = y;
        int ny = x - (a/b) * y;

        x = nx;
        y = ny;
        return d;
    }
}

int main(){
    int a, b;
    while( scanf("%d %d", &a, &b) != EOF )
    {
        int x, y;
        if( a <= b )
        {
            int d = extended_gcd(a, b, x, y);
            printf("%d %d %d\n", x, y, d);
        }
        else
        {
            int d = extended_gcd(b, a, y, x);
            printf("%d %d %d\n", x, y, d);
        }
    }
    return 0;
}

