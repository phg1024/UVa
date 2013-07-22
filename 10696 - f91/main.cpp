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

    while( true )
    {
        scanf("%d", &n);
        if( n == 0 ) break;
        if( n >= 101 ) printf("f91(%d) = %d\n", n, n-10);
        else printf("f91(%d) = 91\n", n);
    }
    return 0;
}
