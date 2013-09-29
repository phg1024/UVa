#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

const static int N = 51;

// model color as nodes in the graph
// beads are then edges connecting two nodes of color
// the problem is then to find an euler circle in the graph
// note there could be multiple edges between two nodes
// so in the adjacency matrix the edges are marked with their
// multiplicity

void euler(int u, int g[][N]){
    for(int i=1;i<N;i++)
    {
        if( g[u][i] )
        {
            g[u][i]--;
            g[i][u]--;
            euler(i, g);

            printf("%d %d\n", i, u);
        }
    }
}

bool bfs(int g[][N], int deg[])
{
    char visited[N] = {0};
	int root = -1;
	for(int i=1;i<N;i++)
	{
		visited[N] = (deg[i] == 0);
		if( deg[i] && root == -1 )
		{
			root = i;
		}
	}
	
	queue<int> Q;
	Q.push(root);
	
	while( !Q.empty() )
	{
		int cur = Q.front();
		Q.pop();
		for(int i=1;i<N;i++)
		{
			int v = g[i][cur];
			if( !visited[v] )
			{
				Q.push(v);
				visited[v] = 1;
			}
		}
	}
	
	for(int i=1;i<N;i++)
		if( !visited[i] )
			return true;
	return false;
}

int main()
{
    int ncases;
    scanf("%d", &ncases);

    for(int i=1;i<=ncases;i++)
    {
        int n;
        scanf("%d", &n);

        int graph[N][N] = {0};
        int deg[N] = {0};

        for(int j=0;j<n;j++)
        {
            int v1, v2;
            scanf("%d %d", &v1, &v2);
            graph[v1][v2]++;
            graph[v2][v1]++;
            deg[v1]++;
            deg[v2]++;
        }

        bool hasEuler = true;
				
		// check if the graph is connected
		hasEuler = bfs(graph, deg);
		
		// check if the graph has an euler circle
        for(int j=1;j<N;j++)
        {
            if( deg[j] & 0x1 ) {
                hasEuler = false;
                break;
            }
        }

        printf("Case #%d\n", i);
        if( hasEuler )
        {
            for(int j=1;j<N;j++)
                euler(j, graph);
        }
        else
        {
            printf("some beads may be lost\n");
        }

        if( i < ncases ) 
            printf("\n");
        
    }
    return 0;
}
