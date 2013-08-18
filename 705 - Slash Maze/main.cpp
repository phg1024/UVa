#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <limits>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

static const int MAXSIZE = 150;

char dirs[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

bool valid( int w, int h, int x, int y )
{
    return x >= 0 && x < w && y >= 0 && y < h;
}

void flood_fill(char m[MAXSIZE][MAXSIZE], int w, int h, int x, int y, int& length)
{
    length++;
    m[y][x] = 3;

    for(int i=0;i<8;i++)
    {
	int nx = x + dirs[i][0];
	int ny = y + dirs[i][1];

	if( valid(w, h, nx, ny) && m[ny][nx] == 0 )
	{
	    switch( i )
	    {
		case 0:
		    {
			if( m[y][x-1] != 2 )
			{
			    flood_fill(m, w, h, nx, ny, length);
			}
		        break;
		    }
		case 7:
		    {
			if( m[y][x+1] != 2 )
			    flood_fill(m, w, h, nx, ny, length);
		        break;
		    }
		case 2:
		    {
			if( m[y][x+1] != 1 )
			    flood_fill(m, w, h, nx, ny, length);
		        break;
		    }
		case 5:
		    {
			if( m[y][x-1] != 1 )
			{
			    flood_fill(m, w, h, nx, ny, length);
			}
		        break;
		    }
		default:
		    {
		        flood_fill(m, w, h, nx, ny, length);
		        break;
		    }
	    }
	}
    }
}

void printMap(char m[MAXSIZE][MAXSIZE], int w, int h)
{
	for(int i=0;i<h;i++)
	{
	    for(int j=0;j<w;j++)
	    {
		cout << (int)m[i][j];
	    }
	    cout << endl;
	}
	cout << endl;
}

void solve(char m[MAXSIZE][MAXSIZE], int w, int h, int& n, int &l)
{
    int dummy = 0;
    // preprocess, fill the boundary positions with 1s'
    for(int i=0;i<h;i++)
    {
	if( m[i][0] == 0 )
	    flood_fill(m, w, h, 0, i, dummy);

	if( m[i][w-1] == 0 )
	    flood_fill(m, w, h, w-1, i, dummy);
    }

    for(int j=0;j<w;j++)
    {
	if( m[0][j] == 0 )
	    flood_fill(m, w, h, j, 0, dummy);

	if( m[h-1][j] == 0 )
	    flood_fill(m, w, h, j, h-1, dummy);
    }

    n = 0, l = 0;
    for(int i=1;i<h-1;i++)
	for(int j=1;j<w-1;j++)
	{
	    if( m[i][j] == 0 )
	    {
		n++;

		int cl = 0;
		flood_fill(m, w, h, j, i, cl);
		
		if( cl > l )
		    l = cl;
	    }
	}
}

int main()
{
    int w, h;

    char m[MAXSIZE][MAXSIZE];
    char buf[MAXSIZE];

    int idx = 1;
    while( true )
    {
	scanf("%d %d", &w, &h);

	if( !(w | h) ) break;

	for(int y=0, r=0;y<h;y++, r+=2)
	{
	    scanf("%s", buf);

	    for(int x=0, c=0;x<w;x++, c+=2)
	    {
		if( buf[x] == '\\' )
		{
		    m[r][c] = 1;
		    m[r][c+1] = 0;
		    m[r+1][c] = 0;
		    m[r+1][c+1] = 1;
		}
		else
		{
		    m[r][c] = 0;
		    m[r][c+1] = 2;
		    m[r+1][c] = 2;
		    m[r+1][c+1] = 0;
		}
	    }
	}

	int n, l;
	solve( m, w*2, h*2, n, l );

	printf("Maze #%d:\n", idx++);
	if( n > 0 )
	{
	    printf("%d Cycles; the longest has length %d.\n", n, l);
	}
	else
	{
	    printf("There are no cycles.\n");
	}
	printf("\n");
    }

    return 0;
}
