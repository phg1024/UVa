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

int main()
{
    int n;
    scanf("%d", &n);
    while( n-- > 0 )
    {
        int a, b;
        scanf("%d %d", &a, &b);

        if( a > b ){ printf(">\n"); continue; }
        if( a < b ){ printf("<\n"); continue; }
        if( a == b ){ printf("=\n"); continue; }
    }

    return 0;
}
