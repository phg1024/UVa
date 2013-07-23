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

unsigned int c[4][7490];
void init()
{
    int s[5] = {5, 10, 25, 50};
    for(int j=0;j<7490;j++)
        c[0][j] = j / 5 + 1;
 
    for(int i=1;i<4;i++)
    {
        int v = s[i];
        for(int j=0;j<7490;j++)
        {
            int m = j / v;
            c[i][j] = 0;
            for(int k=0, r=j;k<=m;k++, r-=v)
            {
                c[i][j] += c[i-1][r];
            }
        }
    }
}

int main()
{
    init();
    int n;
    while( scanf("%d", &n) != EOF )
    {
        printf("%u\n", c[3][n]);
    }
    return 0;
}
