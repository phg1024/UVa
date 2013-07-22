#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <bitset>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int w = 44;
static const int h = 16;
static const int MAXN = 36;

struct Grid
{
	Grid(){}
	Grid(const Grid& g)
	{
		memcpy(lines, g.lines, sizeof(int64_t)*h);
	}
	
	Grid& operator=(const Grid& g)
	{
		if( this != &g )
		{
			memcpy(lines, g.lines, sizeof(int64_t)*h);
		}
		return (*this);
	}
	
	bool empty()
	{
		for(int i=0;i<h;i++)
		{
			if( lines[i]  ) return false;
		}
		return true;
	}
		
	int64_t lines[h];
};

int64_t buf2line(char buf[])
{
	int64_t v = 0x0;
	int64_t one = 0x1;
	for(int i=0;i<w;i++)
	{
		if( buf[i] == '*' )
			v |= (one << i);
	}
	return v;
}

void removeOverlap(Grid& g1, const Grid& g2)
{
	for(int i=0;i<h;i++)
	{
		g1.lines[i] &= (~g2.lines[i]);
	}
}

void initgrid(Grid& g1, const Grid& g2)
{
	for(int i=0;i<h;i++)
		memcpy(g1.lines, g2.lines, sizeof(int64_t)*h);
}

int main()
{
    Grid grid[MAXN];
    char c[MAXN+1];
    char buf[w];
    int N, Q;

    scanf("%d %d\n", &N, &Q);
	gets(c);

    int cmap[128];
    for(int i=0;i<N;i++)
        cmap[c[i]] = i;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<h;j++)
        {
            gets(buf);
            grid[i].lines[j] = buf2line(buf);
        }
		gets(buf);
    }
		
    Grid testgrid[MAXN];
    for(int i=1;i<=Q;i++)
    {
		// remove the overlapped region
		gets(buf);
		int m = strlen(buf);
		for(int j=0;j<m;j++)
			initgrid(testgrid[j], grid[cmap[buf[j]]]);
		
		for(int j=0;j<m;j++)
		{			
			for(int k=0;k<m;k++)
			{
				if( j == k ) continue;
				
				removeOverlap(testgrid[j], grid[cmap[buf[k]]]);
			}
		}
		
		printf("Query %d: ", i);
		for(int j=0;j<m;j++)
		{
			if( testgrid[j].empty() ) putchar('N');
			else putchar('Y');
		}
		putchar('\n');
    }
	
    return 0;
}
