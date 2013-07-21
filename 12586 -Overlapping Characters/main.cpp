#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int w = 64;
static const int h = 16;
static const int MAXN = 36;

struct Line
{
	Line(){}
	Line(char buf[])
	{
		memcpy(data, buf, sizeof(char)*w);
	}
	
	Line(const Line& l)
	{
		memcpy(data, l.data, sizeof(char)*w);
	}
	
	Line& operator=(const Line& l)
	{
		if( this != &l )
		{
			memcpy(data, l.data, sizeof(char)*w);
		}
		return (*this);
	}
	
	// remove overlap region
	Line operator-(const Line& l)
	{
		Line res = (*this);
		for(int i=0;i<w;i++)
		{
			res.data[i] = (l.data[i] == '*')?'.':res.data[i];
		}
		return res;
	}
		
	friend ostream& operator<<(ostream& os, const Line& l);
	
	bool empty()
	{
		for(int i=0;i<w;i++)
			if( data[i] == '*' ) return false;
		return true;
	}

	char data[w];
};

ostream& operator<<(ostream& os, const Line& l)
{
	os << l.data;
	return os; 
}

struct Grid
{
	Grid(){}
	Grid(const Grid& g)
	{
		for(int i=0;i<h;i++)
			lines[i] = g.lines[i];
	}
	
	Grid& operator=(const Grid& g)
	{
		if( this != &g )
		{
			for(int i=0;i<h;i++)
				lines[i] = g.lines[i];
		}
		return (*this);
	}
	
	bool empty()
	{
		for(int i=0;i<h;i++)
		{
			if( !lines[i].empty() ) return false;
		}
		return true;
	}
	
	Grid operator-(const Grid& g)
	{
		Grid res = (*this);
		for(int i=0;i<h;i++)
			res.lines[i] = lines[i] - g.lines[i];
		
		return res;
	}
	
	friend ostream& operator<<(ostream& os, const Grid& g);
	
	Line lines[h];
};

ostream& operator<<(ostream& os, const Grid& g)
{
	for(int i=0;i<h;i++)
		cout << g.lines[i] << endl;;
	return os;
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
            grid[i].lines[j] = Line(buf);
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
			testgrid[j] = grid[cmap[buf[j]]];
		
		for(int j=0;j<m;j++)
		{			
			for(int k=0;k<m;k++)
			{
				if( j == k ) continue;
				
				testgrid[j] = testgrid[j] - grid[cmap[buf[k]]];
			}
			//cout << testgrid[j];
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
