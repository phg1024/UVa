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

inline int next(int Z, int I, int M, int L)
{
    return (Z * L + I) % M;
}

int solve(int Z, int I, int M, int L)
{
    char visited[10001] = {0};
    int idx=0;
    int val = L;

    while( true )
    {
        val = next(Z, I, M, val);
        if( visited[val] ) break;
        visited[val] = 1;
        idx++;
    }

    return idx;
}

int main()
{
    int Z, L, I, M;
    int idx = 1;
    while( true )
    {
        scanf("%d %d %d %d", &Z, &I, &M, &L);
        if( !(Z | I | M | L) ) break;

        printf("Case %d: %d\n", idx++, solve(Z, I, M, L));
    }
    return 0;
}
