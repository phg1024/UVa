#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <limits>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

static const int MAXN = 65536;

int find_set(int x, int p[])
{
    if( x == p[x] ) return x;
    else return p[x] = find_set(p[x], p);
}

bool union_set(int x, int y, int p[])
{
    int px = find_set(x, p);
    int py = find_set(y, p);

    if( px == py ) return false;
    else p[py] = px;
    return true;
}

int main()
{
    int idx = 1;
    while( true )
    {
	int p[MAXN] = {0};
	int deg[MAXN] = {0};
	set<int> nodes;

	for(int i=0;i<MAXN;i++) p[i] = i;

	bool isTree = true;
	int u, v;
	int nedges = 0;
	while( true )
	{
	    scanf("%d %d", &u, &v);
	    if( u < 0 && v < 0 )
		return 0;

	    if( !(u | v) ) break;
	    if( deg[v]++ > 1 ){ isTree = false; }
	    if( !union_set(u, v, p) ){ isTree = false; }

	    nodes.insert(u);
	    nodes.insert(v);
	    nedges++;
	}

	isTree &= (nodes.size() == nedges+1);
	isTree |= (nedges == 0);

	if( isTree )
	    printf("Case %d is a tree.\n", idx++);
	else
	    printf("Case %d is not a tree.\n", idx++);
    }
    return 0;
}
