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

unsigned int primes[180];
int primeCount;
// only a small set of primes, may not work for very large range
static const unsigned int MAXPRIMES = 1024;
bitset<MAXPRIMES> flag(0);

bool isPrime(unsigned int n)
{	
	if( n < MAXPRIMES ) return 1-flag[n];
	else
	{
		for(int i=0;i<primeCount;i++)
			if( n % primes[i] == 0 ) return false;
		return true;
	}
}

void init()
{
	unsigned int MAXR = (sqrt(MAXPRIMES) + 0.5);
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
		{
			primes[primeCount++] = i;
		}
		
		i++;
		while( flag[i] == 1 && i < MAXPRIMES ) i++;
	}
}

void findPrimes(unsigned int n)
{
        for(int i=0;i<primeCount;i++)
        {
			unsigned int pi = primes[i];
            for(int j=0;j<primeCount;j++)
            {
				unsigned int sumj = primes[j] + pi;
			    for(int k=0;k<primeCount;k++)
                {
					unsigned int sumk = sumj + primes[k];
					if( sumk > n )
					{
						break;
					}
					else
					{
                    	unsigned int pl = n - sumk;

						if( isPrime(pl) )
						{
							printf("%d %d %d %d\n", primes[i], primes[j], primes[k], pl);
							return;
						}
					}
                }
            }
        }
		
		// not found
		printf("Impossible.\n");
}

int main()
{
	init();
    unsigned int n;
    while( scanf("%u", &n) != EOF )
    {
        findPrimes(n);
    }
    return 0;
}
