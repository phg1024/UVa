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
    int caseid = 1;
    while( n-- > 0 )
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        int v = a;
        if( b > v && c > v )
            v = min(b, c);
        else if( b < v && c < v )
            v = max(b, c);

        printf("Case %d: %d\n", caseid++, v);
    }
    return 0;
}
