#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <map>
#include <iomanip>
#include <algorithm>
#include <functional>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

unsigned int modulo(unsigned int n, unsigned int m)
{
	if( n == 0 ) return m;
	if( n == 1 ) return 1;
	else
	{
		unsigned int r = 2 % m;
		unsigned int j = 3;
		while( j <= n )
		{
			unsigned int v = j % m;
			r = (v * r) % m;
			j++;
		}
		return r;
	}
}

bool solve(unsigned int n, unsigned int m)
{
	if( m == 0 ) return false;
	if( m == 1 ) return true;
	if( n >= m ) return true;
	
	return (modulo(n, m) == 0);
}

int main(){
	unsigned int n, m;
	while(scanf("%u %u", &n, &m) != EOF)
	{
		if( solve(n, m) )
			printf("%u divides %u!\n", m, n);
		else
			printf("%u does not divide %u!\n", m, n);
	}
    return 0;
}

