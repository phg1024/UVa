#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <limits>
#include <set>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXP = 500;

float distance(int p1[], int p2[])
{
    float dx = p1[0] - p2[0];
    float dy = p1[1] - p2[1];
    return dx*dx + dy*dy;
}

int main()
{
    int ncases;
    scanf("%d", &ncases);
    while( ncases-->0 )
    {
        int S, P;
        scanf("%d %d", &S, &P);

        int pos[MAXP][2];

        for(int i=0;i<P;i++)
        {
            scanf("%d %d", &(pos[i][0]), &(pos[i][1]));
        }

        float dist[MAXP][MAXP]; 
        for(int i=0;i<P;i++)
            for(int j=i+1;j<P;j++)
            {
                dist[i][j] = dist[j][i] = distance(pos[i], pos[j]);
            }


        // minimum spanning tree

        // start with the first node
        float cost[MAXP], W[MAXP]; 
        int cov[MAXP], adj[MAXP];

        cost[0] = 0; adj[0] = 0; cov[0] = 1;
        for(int i=1;i<P;i++)
        {
            cost[i] = dist[0][i];
            adj[i] = 1;
            cov[i] = 0;
        }

        for(int i=0;i<P;i++)
        {
            float minW = numeric_limits<float>::max();
            int k;
            for(int j=1;j<P;j++)
            {
                if( !cov[j] && cost[j]<minW )
                {
                    minW = cost[j];
                    k = j;
                }
            }

            W[i] = minW;
            cov[k] = 1;

            // update closest neighbors
            for(int j=1;j<P;j++)
            {
                if( !cov[j] && cost[j] > dist[k][j] )
                {
                    cost[j] = dist[k][j];
                    adj[j] = k;
                }
            }
        }

        std::sort(W, W+P-1, std::greater<float>());

        printf("%.2f\n", sqrt(W[S-1]));
    }
    return 0;
}
