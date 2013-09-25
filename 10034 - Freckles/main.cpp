#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <limits>
#include <cfloat>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 100;

struct point_t
{
    double distance(const point_t& p) const
    {
        double dx = x - p.x;
        double dy = y - p.y;
        return dx*dx + dy*dy; 
    }
    double x, y;
};

int main(){
    int ncases;
    scanf("%d", &ncases);

    while( ncases )
    {
        int n;
        scanf("%d", &n);
        point_t pts[MAXN];

        for(int i=0;i<n;i++)
        {
            scanf("%lf %lf", &pts[i].x, &pts[i].y);
        }

        set<int> left, right;
            left.insert(0);

        for(int i=1;i<n;i++)
            right.insert(i);

        double length = 0;

        while( !right.empty() )
        {
            set<int>::iterator it=left.begin();

            set<int>::iterator rit;
            double minDist = FLT_MAX;
            while( it!=left.end() )
            {
                const point_t& p = pts[(*it)];
                for(set<int>::iterator it2=right.begin();
                    it2!=right.end();
                    it2++)
                {
                    double dist = p.distance(pts[(*it2)]);
                    if( dist < minDist )
                    {
                        rit = it2;
                        minDist = dist;
                    }
                }
                it++;
            }

            right.erase(rit);
            left.insert(*rit);

            length += sqrt(minDist);
        }

        printf("%.2lf\n", length);

        if( --ncases ) putchar('\n');
    }
    return 0;
}

