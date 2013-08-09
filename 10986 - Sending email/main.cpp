#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <queue>
#include <limits>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXN = 20001;

typedef pair<int, int> PII;

int solve( vector<PII> e[], int n, int s, int t )
{
    // Q is the list of edges with their ends in the S of undiscovered nodes
    priority_queue<PII, vector<PII>, greater<PII> > Q;

    vector<unsigned int> dist(n, numeric_limits<int>::max());
    vector<int> prev(n, -1);

    dist[s] = 0;
    Q.push( make_pair(0, s) );

    while( !Q.empty() )
    {
        PII p = Q.top();
        Q.pop();

        int v = p.second;
        if( v == t ) break;

        for(vector<PII>::iterator it=e[v].begin();
            it!=e[v].end();
            it++)
        {
            if(dist[it->second] > dist[v] + it->first)
            { 
                dist[it->second] = dist[v] + it->first;
                prev[it->second] = v;
                Q.push(make_pair(dist[it->second], it->second));
            }
        }
    }

    return dist[t];
}

int main()
{
    int ncases;
    scanf("%d", &ncases);

    for(int i=1;i<=ncases;i++)
    {
        int n, m, s, t;
        scanf("%d %d %d %d", &n, &m, &s, &t);

        vector<PII> e[MAXN];

        for(int j=0;j<m;j++)
        {
            int v1, v2, w;
            scanf("%d %d %d", &v1, &v2, &w);
            e[v1].push_back(make_pair(w, v2));
            e[v2].push_back(make_pair(w, v1));
        }

        int d = solve(e, n, s, t);
        if( d == numeric_limits<int>::max() )
        {
            printf("Case #%d: unreachable\n", i);
        }
        else
        {
            printf("Case #%d: %d\n", i, d );
        }
    }

    return 0;
}
