#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <bitset>
#include <set>
#include <map>

#include <stdint.h>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int move[][2] = 
{
	{-1, -1},
	{1, -1},
	{-1, 1},
	{1, 1}
};

int64_t one = 0x1;

struct Board
{
	Board(int n):n(n)
	{
		data = 0x0;
		m = 0x0;
	}
	
	void mask(int x, int y)
	{
		m |= (one << (y * n + x));
	}
	
	void set(int x, int y)
	{
		data |= (one << (y * n + x));
		m |= (one << (y * n + x));
		
		// mask all invalid positions
		for(int i=0;i<4;i++)
		{
			int c = x + move[i][0];
			int r = y + move[i][1];
			
			while( inrange(r, c) )
			{
				m |= (one << (r * n + c));
				c += move[i][0];
				r += move[i][1];
			}
		}
	}
	
	int64_t maskvalue(int x, int y) const
	{
		return (m & (one << (y * n + x)));
	}
	
	int64_t value(int x, int y) const
	{
		return (data & (one << (y * n + x)));
	}
	
	bool inrange(int r, int c)
	{
		if( r >= n || c >= n || r < 0 || c < 0 ) return false;
		return true;
	}
	
	vector<pair<int, int> > getCandidates() const
	{
		vector<pair<int, int> > c;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if( !maskvalue(j, i) )
					c.push_back(pair<int,int>(j, i));
					
			}
		}
		return c;
	}
	
	int n;
	int64_t m;
	int64_t data;
};

map<int64_t, bool> visited;

int64_t solve_backtrack(int n, int k, const Board& b)
{
	if( k == 0 ) return 1;
	
	uint64_t sum = 0;
	//cout << bitset<64>(b.data) << endl;
	
	vector<pair<int, int> > candidates = b.getCandidates();
	//cout << candidates.size() << endl;
	for(int i=0;i<candidates.size();i++)
	{
		pair<int, int>& x = candidates[i];
		Board bb = b;
		bb.set(x.first, x.second);
		//cout << bitset<64>(bb.data) << endl;
		if( visited.find(bb.data) == visited.end() )
		{
			visited[bb.data] = true;
			sum += solve(n, k-1, bb);
		}
	}
	
	return sum;
}

unsigned int values[][17] = {
{1, 1, 0},
{1, 4, 4, 0, 0},
{1, 9, 26, 26, 8, 0, 0},
{1, 16, 92, 232, 260, 112, 16, 0, 0},
{1, 25, 240, 1124, 2728, 3368, 1960, 440, 32, 0, 0},
{1, 36, 520, 3896, 16428, 39680, 53744, 38368, 12944, 1600, 64, 0, 0},
{1, 49, 994, 10894, 70792, 282248, 692320, 1022320, 867328, 389312, 81184, 5792, 128, 0, 0},
{1, 64, 1736, 26192, 242856, 1444928, 5599888, 14082528, 22522960, 22057472, 12448832, 3672448, 
489536, 20224, 256, 0, 0}
};

int main()
{
	int n, k;
	while( scanf("%d %d", &n, &k) != EOF )
	{
		if( n == 0 && k == 0 ) break;
		
		if( k > (n << 1) )
			printf("0\n");
		else
			printf("%u\n", values[n-1][k]);
				
		/*
		for(int n=1;n<=8;n++)
		{
			for(int k=0;k<=n*2-1;k++)
			{
				visited.clear();
		
				Board b(n);
				printf("%lld, ", solve_backtrack(n, k, b));
			}
			putchar('\n');
		}
		*/
	}
	
    return 0;
}
