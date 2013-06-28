#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

bool comp(unsigned int a, unsigned int b)
{
    return a < b;
}

unsigned int computeDistance(int s[500], int count, int pos)
{
    unsigned int d = 0;
    for(int i=0;i<count;i++)
    {
        d += abs( s[i] - pos );
    }
    return d;
}

int main()
{
    int ncases;
    int s[500];
    unsigned int dists[30000];
    cin >> ncases;
    for(int i=0;i<ncases;i++)
    {
        int nneighbors;
        cin >> nneighbors;

        int maxS, minS;
        maxS = 0, minS = 30001;
        for(int i=0;i<nneighbors;i++)
        {
            int t;
            cin >> t;
            s[i] = t;
            if( t > maxS ) maxS = t;
            if( t < minS ) minS = t;
        }

        std::sort(s, s+nneighbors, std::greater<int>());

        int pos;
        if( nneighbors % 2 == 1 )
        {
            pos = s[nneighbors/2];
        }
        else
        {
            pos = (int)((s[nneighbors/2-1] + s[nneighbors/2]) * 0.5 + 0.5);
        }

        cout << computeDistance( s, nneighbors, pos ) << endl;
    }
    return 0;
}
