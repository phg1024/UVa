#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

struct point_t
{
    int x, y;
};

struct tri_t
{
    point_t p[3];
};

int solve(tri_t tris[])
{

}

int main(){

    int ncases;
    scanf("%d", &ncases);

    char str[][4] = {"yes", "no"};
    for(int i=1;i<=ncases;i++)
    {
        tri_t tris[2]; 

        for(int i=0;i<2;i++)
            for(int j=0;j<3;j++)
                scanf("%d %d", tri[i].p[j].x, tri[i].p[j].y);

        printf("pair %d: %s", i, str[ solve(tris) ]);
    }
    return 0;
}

