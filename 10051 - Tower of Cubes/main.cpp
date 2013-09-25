#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 500;

enum face_t
{
    Front = 0,
    Back,
    Left,
    Right,
    Top,
    Bottom
};

string facename[] = {
    "front",
    "back",
    "left",
    "right",
    "top",
    "bottom"
};

struct cube_t
{
    int idx;
    // front, back, left, right, top, bottom
    int color[6];
};

struct trace_t
{
    trace_t(){}
    trace_t(int l, int f):level(l),face(f){}
    int level;
    int face;
};

void printTrace(int level, int face, trace_t prev[MAXN][6])
{
    trace_t p = prev[level][face];
    if( p.level != -1 && p.face != -1 )
    {
        printTrace( p.level, p.face, prev );
    }
    printf("%d %s\n", level + 1, facename[face].c_str());
}

int main(){
    int caseidx = 0;

    while( true )
    {
        int n;
        scanf("%d", &n);
        if( !n ) break;

        if( caseidx ) putchar('\n');

        cube_t cubes[MAXN];
        for(int i=0;i<n;i++)
        {
            scanf("%d %d %d %d %d %d",
                    &cubes[i].color[Front],
                    &cubes[i].color[Back],
                    &cubes[i].color[Left],
                    &cubes[i].color[Right],
                    &cubes[i].color[Top],
                    &cubes[i].color[Bottom]
                 );
        }

        // the maximum height including the i-th cube
        // when the j-th face is on top
        int h[MAXN][6];
        trace_t prev[MAXN][6];

        for(int j=0;j<6;j++)
        {
            h[0][j] = 1;
            prev[0][j] = trace_t(-1, -1);
        }

        int maxH = 1;
        pair<int, int> maxTower;
        for(int i=1;i<n;i++)
        {
            for(int j=0;j<6;j++)
            {
                h[i][j] = 1;
                prev[i][j] = trace_t(-1, -1);
            }

            for(int k=0;k<i;k++)
            {
                for(int j=0;j<6;j++)
                {
                    int bottomcolor = cubes[k].color[j^0x1];
                    // find the matched color
                    for(int m=0;m<6;m++)
                    {
                        if( cubes[i].color[m] == bottomcolor )
                        {
                            // put the cube in the stack
                            if( h[k][j] + 1 > h[i][m] )
                            {
                                h[i][m] = h[k][j] + 1;
                                prev[i][m] = trace_t(k, j);
                            }
                        }
                    }
                }
            }

            for(int j=0;j<6;j++)
            {
                if( h[i][j] > maxH )
                {
                    maxH = h[i][j];
                    maxTower = make_pair(i, j);
                }
            }
        }

        /*
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<6;j++)
                printf("%d ", h[i][j]);
            printf("\n");
        }
        */

        printf("Case #%d\n", ++caseidx);
        printf("%d\n", maxH);

        // print the trace
        printTrace( maxTower.first, maxTower.second, prev );
    }
    return 0;
}

