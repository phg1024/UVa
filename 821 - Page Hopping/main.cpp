#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;

static const int MAXN = 101;

typedef pair<int, int> edge_t;

float solve(int m[][MAXN], int n)
{
    for(int i=0;i<n;i++)
    {
        m[i][i] = 0;
    }

    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                int v = m[i][k] + m[k][j];
                if( v < m[i][j] )
                    m[i][j] = v;
            }
        }
    }

    float res = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            res += m[i][j];
        }
    }

    return res / (n * (n-1));
}

int main(){
    int idx = 0;
    while( true )
    {
        int from, to;
        int NE = 0;
        set<int> nodes;
        vector<edge_t> edges;
        while( true )
        {
            scanf("%d %d", &from, &to);
            if( !(from | to) ) break;
            nodes.insert(from);
            nodes.insert(to);
            edges.push_back(make_pair(from, to));
            NE++;
        }

        if( NE == 0 ) return 0;

        // renumber nodes
        int N = nodes.size();
        int index[MAXN];
        set<int>::iterator it = nodes.begin();
        for(int i=0;i<N;i++)
        {
            index[(*it)] = i;
            ++it;
        }

        int m[MAXN][MAXN];
        // initialize the map
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                m[i][j] = MAXN;
            }
        }

        for(int i=0;i<edges.size();i++)
        {
            edge_t& e = edges[i];
            m[ index[e.first] ] [ index[e.second] ] = 1;
        }

        float res = solve( m, N );

        printf("Case %d: average length between pages = %.3f clicks\n", ++idx, res);
    }
}

