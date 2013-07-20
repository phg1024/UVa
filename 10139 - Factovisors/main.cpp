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

// primes in [1, 65536]
int primes[6543];
int primeCount;

typedef pair<unsigned int, unsigned int> factor_t;

void init()
{
	bitset<65536> flag(0);
	for(int i=2;i<257;)
	{
		for(int j=i+i;j<65536;j+=i)
			flag[j] = 1;
		
		i++;
		while( flag[i] == 1 && i < 257 ) i++;
	}
	
	primeCount = 0;	
	for(int i=2;i<65536;)
	{
		if( flag[i] == 0 )
			primes[primeCount++] = i;
		
		i++;
		while( flag[i] == 1 && i < 65536 ) i++;
	}
}

void factorize(unsigned int n, factor_t facs[], int& nfacs)
{
	nfacs = 0;
	for(int i=0;i<primeCount;i++)
	{
		int p = primes[i];
		if( p > n ) break;
		
		if( n % p == 0 )
		{		
			int count = 0;
			while( n % p == 0 )
			{
				count++;
				n /= p;
			}
			facs[nfacs++] = make_pair(p, count);
		}		
	}
	
	if( n != 1 )
	{
		facs[nfacs++] = make_pair(n, 1);
	}
}

bool solve(unsigned int n, unsigned int m)
{
	if( m == 0 ) return false;
	if( m == 1 ) return true;
	if( n >= m ) return true;

    // there are no more than 64 factors for any unsigned int
	factor_t facs[64];
	int nfacs;
	
	factorize( m, facs, nfacs );
	
	for(int i=0;i<nfacs;i++)
	{
		int p = facs[i].first;
		int k = facs[i].second;
				
		/// see if there is enough factor in n!
		unsigned int v = p;
		while( k > 0 )
		{
			if( v > n ) break;
			
			unsigned int v0 = v;
			while( v0 % p == 0 )
			{
				v0 /= p;
				k--;
			}
			v += p;
		}
			
		if( k > 0 ) return false;
	}
	
	return true;
}

int main(){
	init();
	
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

