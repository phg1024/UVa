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
    int ncases;
    scanf("%d", &ncases);
    for(int i=1;i<=ncases;i++)
    {
        int a, b;
        scanf("%d", &a);
        scanf("%d", &b);

        if( !(a & 0x1) ) 
            a++;
        if( !(b & 0x1) )
            b--;

        int sum = (a + b) * ((b-a)/2+1) / 2;

        printf("Case %d: %d\n", i, sum);
    }
    return 0;
}
