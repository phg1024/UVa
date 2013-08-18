#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <queue>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

static const int MAXN = 10000;
#define BURTE_FORCE 0

#if BRUTE_FORCE

int main()
{
    int x;
    int mid;
    int v[MAXN];
    int L = 0;
    while( scanf("%d", &x) != EOF )
    {
	v[L++] = x;
	std::sort(v, v+L);

	if( L & 0x1 )
	{
	    mid = v[L/2];
	}
	else
	{
	    mid = (v[L/2] + v[L/2-1]) / 2;
	}

	printf("%d\n", mid);
    }
}
#else

int main()
{
    int x, mid;
    int v[MAXN];
    int L = 0;

    while( scanf("%d", &x) != EOF )
    {
	v[L++] = x;

	int idx = L-1;
	int tmp;
	for(int k=L-1;k>0;k--)
	{
	    if( v[k] < v[k-1] )
	    {
	    tmp = v[k];
	    v[k] = v[k-1];
	    v[k-1] = tmp;
	    }
	    else break;
	}
     
	int pos = L>>1;
	if( L & 0x1 )
	    printf("%d\n", v[pos]);
	else
	    printf("%d\n", (v[pos] + v[pos-1]) >> 1);
    }

    return 0;

}
#endif
