#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <bitset>
#include <map>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
#define FAST 1	

#if !FAST
int primes[6543];
int primeCount;

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
#endif

bool divisibleCount(unsigned int n)
{
#if FAST
	// note that the return value is false if any of the factors of n have odd counts
	// otherwise the return value is true, i.e. all the factors have even counts
	
	// the only possibility that all the factors of n have even counts is that n itself
	// is a perfect squre
	unsigned int s = sqrt(n);
	return (s * s == n);
#else
	for(int i=0;i<primeCount;i++)
	{
		int p = primes[i];
		if( p * p > n ) break;
		
		if( n % p == 0 )
		{		
			int count = 0;
			while( n % p == 0 )
			{
				count++;
				n /= p;
			}
			
			if( count & 0x1 ) return false;
		}		
	}
	
	if( n != 1 )
		return false;
	
	return true;
#endif
}

int main()
{
#if !FAST
	init();
#endif
	unsigned int n;
	while( scanf("%u", &n) )
	{
		if( n == 0 ) break;
		printf("%s\n", ((divisibleCount(n))?"yes":"no") );
	}
    return 0;
}
