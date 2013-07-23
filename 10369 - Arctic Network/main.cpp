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
        float dist[MAXP][MAXP]; 

        for(int i=0;i<P;i++)
        {
            scanf("%d %d", &(pos[i][0]), &(pos[i][1]));
        }

        for(int i=0;i<P;i++)
            for(int j=i+1;j<P;j++)
            {
                float d = distance(pos[i], pos[j]);
                dist[i][j] = dist[j][i] = d;
            }


        // minimum spanning tree

        // start with the first node
        int VL[MAXP], VR[MAXP];
        int sizeL = 1, sizeR = P - 1;
        float W[MAXP];
        int sizeW = 0;

        VL[0] = 0;

        for(int i=1;i<P;i++)
            VR[i-1] = i;

        while( sizeR > 0 )
        {
            float w = numeric_limits<float>::max();
            int idxR;
            pair<int, int> e;
            for(int i=0;i<sizeR;i++)
            {
                int nr = VR[i];
                for(int j=0;j<sizeL;j++)
                {
                    int nl = VL[j];

                    if( dist[nl][nr] < w )
                    {
                        e.first = nl;
                        e.second = nr;
                        w = dist[nl][nr];
                        idxR = i;
                    }
                }
            }

            VL[sizeL++] = e.second;
            VR[idxR] = VR[sizeR-1];
            sizeR--;
            W[sizeW++] = w;
        }

        std::sort(W, W+sizeW, std::greater<float>());

        /*
        for(int i=0;i<sizeW;i++)
            cout << W[i] << endl;
            */
        

        cout << std::fixed << setprecision(2) << sqrt(W[S-1]) << endl;
    }
    return 0;
}
