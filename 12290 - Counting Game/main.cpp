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

bool clap(int val)
{
    if( val % 7 == 0 ) return true;
    while( val )
    {
        if( val % 10 == 7 ) return true;
        val /= 10;
    }

    return false;
}

int main()
{
    int n, m, k;
    while( true )
    {
        scanf("%d %d %d", &n, &m, &k);

        if( !( n | m | k) ) break;

        int cycle = (n-1)*2;

        // m appears at positions:
        // m, 2*n-m, m+cycle, 2*n-m+cycle, ...
        
        int pos1 = m;
        int pos2 = (2*n-m);
        if( pos2 > cycle) pos2 %= cycle;

        if( (n == m) || (pos1 == pos2))
        {
            int val;
            while( k )
            {
                if( clap(pos1) )
                {
                    val = pos1;
                    k--;
                }

                pos1 += cycle;
            }
            printf("%d\n", val);
        }
        else
        {
            int val;
            while( true )
            {
                if( clap(pos1) )
                {
                    val = pos1;
                    k--;
                }

                if( k == 0 ) break;

                if( clap(pos2) )
                {
                    val = pos2;
                    k--;
                }

                if( k == 0 ) break;

                pos1 += cycle;
                pos2 += cycle;
            }
            printf("%d\n", val);
        }
    }
    return 0;
}

