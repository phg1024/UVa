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

unsigned int primes[173];
int primeCount;
// only a small set of primes, may not work for very large range
static const unsigned int MAXPRIMES = 1024;
static const unsigned int MAXR = 33;
bitset<MAXPRIMES> flag(0);

bool isPrime(unsigned int n)
{	
	if( n < MAXPRIMES ) return 1-flag[n];
	else
	{
		for(int i=0;i<primeCount;i++)
		{
			if( n % primes[i] == 0 ) return false;
		}
		return true;
	}
}

void init()
{
	flag[0] = 1, flag[1] = 1;
	for(unsigned int i=2;i<MAXR;)
	{
		for(unsigned int j=i+i;j<MAXPRIMES;j+=i)
			flag[j] = 1;
		
		i++;
		while( flag[i] == 1 && i < MAXR ) i++;
	}
	
	primeCount = 0;	
	for(unsigned int i=2;i<MAXPRIMES;)
	{
		if( flag[i] == 0 )
			primes[primeCount++] = i;
		
		i++;
		while( flag[i] == 1 && i < MAXPRIMES ) i++;
	}
}

int main()
{
	init();
    unsigned int n;
    while( scanf("%u", &n) != EOF )
    {
		// use Goldbach's conjecture
		if( n <= 7 )
			printf("Impossible.\n");
		else
		{
			int r = n & 0x1;
			unsigned int np = n - 4 - r;
		    for(int i=0;i<primeCount;i++)
		    {
				unsigned int pj = np - primes[i];
				if( isPrime(pj) )
				{
					printf("2 %d %d %d\n", 2+r, primes[i], pj);
					break;
				}
			}
		}
    }
    return 0;
}
