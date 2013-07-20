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

// primes in [1, 32768]
int primes[3600];
int primeCount;
static const unsigned int MAXPRIMES = 32768;
bitset<MAXPRIMES> flag(0);

typedef pair<unsigned int, unsigned int> factor_t;

bool isPrime(unsigned int n)
{
	if( n < MAXPRIMES )
		return 1 - flag[n];
	else
	{
		for(int i=0;i<primeCount;i++)
			if( n % primes[i] == 0 ) return false;
		return true;
	}
}

void init()
{
	unsigned int MAXR = sqrt(MAXPRIMES) + 0.5;
	for(int i=2;i<MAXR;)
	{
		for(int j=i+i;j<MAXPRIMES;j+=i)
			flag[j] = 1;
		
		i++;
		while( flag[i] == 1 && i < MAXR ) i++;
	}
	
	primeCount = 0;	
	for(int i=2;i<MAXPRIMES;)
	{
		if( flag[i] == 0 )
			primes[primeCount++] = i;
		
		i++;
		while( flag[i] == 1 && i < MAXPRIMES ) i++;
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

unsigned int sumOfDigits(unsigned int n)
{
	unsigned int sum = 0;
	
	while( n )
	{
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

bool isSmithNumber(unsigned int n)
{
	factor_t facs[32];
	int nfacs;
	
	if( isPrime(n) ) return false;
	factorize(n, facs, nfacs);
	
	unsigned int s1 = sumOfDigits(n);
	unsigned int s2 = 0;
	for(int j=0;j<nfacs;j++)
	{
		s2 += sumOfDigits(facs[j].first) * facs[j].second;
	}
	
	return s1 == s2;
}

int main()
{
	init();
	
	int ncases;
	scanf("%d", &ncases);
	while( ncases-- > 0 )
	{
		unsigned int n;
		scanf("%u", &n);
		
		while( true )
		{
			n++;
			if( isSmithNumber(n) )
			{
				printf("%u\n", n);
				break;
			}
		}
	}
	
    return 0;
}
