#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXDIM = 10;
static const int MAXBOXES = 30;

struct Box
{
    Box():ndim(0){}
    Box(int n):ndim(n){}
    Box(const Box& b):idx(b.idx), ndim(b.ndim)
    {
        memcpy(dim, b.dim, sizeof(int)*b.ndim);
    }

    void setDim(int i, int val)
    {
        dim[i] = val;
    }

    void rearrange()
    {
        std::sort(dim, dim+ndim, std::less<int>());
    }

    bool operator<(const Box& b) const
    {
        for(int i=0;i<ndim;i++)
            if( dim[i] >= b.dim[i] )
                return false;
        return true;
    }

    int idx;
    int ndim;
    int dim[MAXDIM];
};

void printMap(char m[][MAXBOXES], int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout << (int)(m[i][j]) << ' ';
		}
		cout << endl;
	}
}

void topsort(char m[][MAXBOXES], int n, int order[])
{
	set<int> nodes;
    int idx = 0;
    // 0 in-degree nodes
    while( idx < n )
    {
        for(int i=0;i<n;i++)
        {
            bool flag = true;
            for(int j=0;j<n;j++)
                if( m[i][j] != 0 )
                {
                    flag = false;
                }

            if( flag && nodes.find(i) == nodes.end() )
            {
				nodes.insert(i);
                order[idx++] = i;
				
	            // cancel out going link
	            for(int k=0;k<n;k++)
	                m[k][i] = 0;
				break;
            }
        }
    }
}

void printPath(int idx, int prev[])
{
	if( prev[idx] != -1 )
	{
		printPath(prev[idx], prev);
		cout << ' ' << idx + 1;
	}
	else
	{
		cout << idx + 1;
	}
}

int main()
{
    int k, d;
    while( scanf("%d %d", &k, &d) != EOF )
    {
        Box b[MAXBOXES];
        for(int i=0;i<k;i++)
        {
            b[i].idx = i+1;
            b[i].ndim = d;
            for(int j=0;j<d;j++)
            {
                int v;
                scanf("%d", &(b[i].dim[j]));
            }
            b[i].rearrange();
        }

        // build a map
        char boxMap[MAXBOXES][MAXBOXES];
        for(int i=0;i<k;i++)
            for(int j=0;j<k;j++)
            {
				boxMap[i][j] = 0;
                if( b[j] < b[i] )
				{
					// incoming link
                    boxMap[i][j] = 1;
				}
            }

        // topological sort the nodes
        int order[MAXBOXES];
        topsort(boxMap, k, order);
		
		// restore the map
        for(int i=0;i<k;i++)
            for(int j=0;j<k;j++)
            {
				boxMap[i][j] = 0;
                if( b[i] < b[j] )
				{
					// outgoing link
                    boxMap[i][j] = 1;
				}
            }
		
		// reverse index
		int index[MAXBOXES];
		for(int i=0;i<k;i++)
			index[order[i]] = i;
			
        // find the longest path
		int pathLength[MAXBOXES];
		int prev[MAXBOXES];
		int maxIdx = 0;
		int maxLength = 0;
		
		for(int i=0;i<k;i++)
		{
			prev[i] = -1;
			pathLength[i] = 0;
		}
		
        for(int i=0;i<k;i++)
        {
			int s = order[i];
			// for all forward link
			for(int j=0;j<k;j++)
				if( boxMap[s][j] )
				{
					int L = pathLength[s] + 1;
					if( L > pathLength[j] )
					{
						prev[j] = s;
						pathLength[j] = L;
					}
				}
        }
		
		for(int i=0;i<k;i++)
		{
			if( pathLength[i] > maxLength )
			{
				maxLength = pathLength[i];
				maxIdx = i;
			}
		}
		cout << maxLength + 1 << endl;
		// print the path
		printPath(maxIdx, prev);
		cout << endl;
    }

    return 0;
}
