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

unsigned int c[5][7490];
void init()
{
    int s[5] = {1, 5, 10, 25, 50};
    for(int j=0;j<7490;j++)
        c[1][j] = j / 5 + 1;
 
    for(int i=2;i<5;i++)
    {
        int v = s[i];
        for(int j=0;j<7490;j++)
        {
            int m = j / v;
            c[i][j] = 0;
            for(int k=0;k<=m;k++)
            {
                int r = j - k * v;
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
        printf("%u\n", c[4][n]);
    }
    return 0;
}
