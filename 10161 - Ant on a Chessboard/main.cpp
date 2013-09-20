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

        int x, y;
        // n = m*m + l
        // if m is even, goes up then left
        // if m is odd, goes right then down
        int m = floor(sqrt(n));
        int l = n - m*m;

        if( m & 0x1 )
        {
           if( l <= m+1 )
           {
               y = (l==0)?m:m+1;
               x = (l==0)?1:l;
           }
           else
           {
               x = m+1;
               y = (m+1)*2 - l;
           } 
        }
        else
        {
            if( l <= m+1 )
            {
                x = (l==0)?m:m+1;
                y = (l==0)?1:l;
            }
            else
            {
                y = m+1;
                x = (m+1)*2 - l;
            }
        }

        printf("%d %d\n", x, y);
    }
    return 0;
}
