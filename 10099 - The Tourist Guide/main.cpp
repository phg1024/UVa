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

static const int MAXN = 101;

int solve(int n, int m[][MAXN], int from, int to, int num)
{
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                m[i][j] = max( m[i][j], min(m[i][k], m[k][j]) );
            }
        }
    }

    int minW = m[from][to] - 1;

    return (num / minW) + ((num % minW == 0)?0:1);
}

int main()
{
    int idx = 0;
    while( true )
    {
        int n, r;
        scanf("%d %d", &n, &r);
        if( !(n | r) ) break;

        int m[MAXN][MAXN] = {0};
        for(int i=0;i<r;i++)
        {
            int f, t, w;
            scanf("%d %d %d", &f, &t, &w);
            m[f][t] = m[t][f] = w;
        }

        int from, to, num;
        scanf("%d %d %d", &from, &to, &num);

        printf("Scenario #%d\n", ++idx);
        printf("Minimum Number of Trips = %d\n", solve( n, m, from, to, num ));
        printf("\n");
    }

    return 0;
}
