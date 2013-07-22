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

	bool empty()
	{
		for(int i=0;i<h;i++)
			if( lines[i] != 0 ) return false;
		return true;
	}
	
	int64_t lines[h];
};

int64_t mask[] = 
{
	0x1, 0x2, 0x4, 0x8,
	0x10, 0x20, 0x40, 0x80,
	0x100, 0x200, 0x400, 0x800,
	0x1000, 0x2000, 0x4000, 0x8000,
	0x10000, 0x20000, 0x40000, 0x80000,
	0x100000, 0x200000, 0x400000, 0x800000,
	0x1000000, 0x2000000, 0x4000000, 0x8000000,
	0x10000000, 0x20000000, 0x40000000, 0x80000000,	
	0x100000000, 0x200000000, 0x400000000, 0x800000000,	
	0x1000000000, 0x2000000000, 0x4000000000, 0x8000000000,	
	0x10000000000, 0x20000000000, 0x40000000000, 0x80000000000,	
};

int64_t buf2line(char buf[])
{
	int64_t v = 0x0;
	for(int i=0;i<w;i++)
	{
		if( buf[i] == '*' )
			v |= mask[i];
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
