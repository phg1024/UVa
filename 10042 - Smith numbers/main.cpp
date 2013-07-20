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

// primes in [1, 65536]
int primes[6543];
int primeCount;
bitset<65536> flag(0);

typedef pair<unsigned int, unsigned int> factor_t;

bool isPrime(unsigned int n)
{
	if( n < 65536 )
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
