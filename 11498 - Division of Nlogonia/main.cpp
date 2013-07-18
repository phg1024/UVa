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
    while( true )
    {
        int q;
        int n, m;

        scanf("%d", &q);
        if( q == 0 ) break;

        scanf("%d %d", &n, &m);

        for(int i=0;i<q;i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);

            int dx = x - n;
            int dy = y - m;

            if( dx == 0 || dy == 0 )
                printf("divisa\n");
            else
            {
                putchar( (dy > 0)?'N':'S' );
                putchar( (dx > 0)?'E':'O' );
                putchar('\n');
            }
        }

    }
    return 0;
}
