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
    int M[101][101];

    int n;
    scanf("%d", &n);

    for(int r=1;r<=n;r++)
        for(int c=1;c<=n;c++)
            scanf("%d", &(M[r][c]));

    int V[101][101] = {0};
    for(int r=1;r<=n;r++)
        for(int c=1;c<=n;c++)
        {
            for(int y=1;y<=r;y++)
                for(int x=1;x<=c;x++)
                {
                    V[r][c] += M[y][x];
                }
        }

    int m = V[0][0];

    for(int r=1;r<=n;r++)
        for(int c=1;c<=n;c++)
        {
            for(int y=r;y<=n;y++)
                for(int x=c;x<=n;x++)
                {
                    int v = V[y][x] - V[y][c-1] - V[r-1][x] + V[r-1][c-1];
                    m = (v > m)?v:m;
                }
        }

    printf("%d\n", m);

    return 0;
}
