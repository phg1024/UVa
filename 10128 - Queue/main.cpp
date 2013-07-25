#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <stdint.h>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

// DP: c(n, p, r) = c(n-1, p, r) * (n-2) + c(n-1, p-1, r) + c(n-1, p, r-1)
// c(1, 1, 1) = 1

static const int MAXN = 14;
uint32_t c[MAXN][MAXN][MAXN];

void init()
{
    c[1][1][1] = 1;
    c[1][0][1] = 0;
    c[1][1][0] = 0;
    for(int n=2;n<MAXN;n++)
    {
        for(int p=1;p<MAXN;p++)
            for(int r=1;r<MAXN;r++)
            {
                c[n][p][r] = c[n-1][p][r] * (n-2)
                    + c[n-1][p-1][r] + c[n-1][p][r-1];
            }

    }
}

int main()
{
    init();

    int ncases;
    scanf("%d", &ncases);
    while( ncases -- > 0 )
    {
        int n, p, r;
        scanf("%d %d %d", &n, &p, &r);
        printf("%u\n", c[n][p][r]);
    }
    return 0;
}
