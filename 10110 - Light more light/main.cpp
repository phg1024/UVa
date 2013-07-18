#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int primes[6543];
int primeCount;

void init()
{
	char flag[65539] = {0};
	
	for(int i=2;i<258;i++)
	{
		for(int j=i+i;j<65539;j+=i)
			flag[j] = 1;
	}

	primeCount = 0;	
	for(int i=2;i<65539;i++)
	{
		if( flag[i] == 0 )
			primes[primeCount++] = i;
	}
}

int divisibleCount(unsigned int n)
{		
	char facs[16] = {0};
	int facCount = 0;
	
	for(int i=0;i<primeCount;i++)
	{
		int p = primes[i];
		if( p * p > n ) break;
		
		if( n % p == 0 )
		{
			while( n % p == 0 )
			{
				facs[facCount]++;
				n /= p;
			}
			
			// hack, return value would be even if facs[facCount] is odd
			if( facs[facCount] & 0x1 ) return 0;
			facCount++;
		}		
	}
	
	if( n != 1 )
	{
		// hack, return value would be even if facs[facCount] is odd
		return 0;
		//facs[facCount++] = 1;
	}
	
	// hack, in this case, the return value must be odd
	return 1;
	
	// number of possible factor combinations
	unsigned int count = 1;
	for(int i=0;i<facCount;i++)
	{
		count *= (facs[i] + 1);
	}	

	return count;
}

int main()
{
	init();

	unsigned int n = 2;
	while( scanf("%u", &n) )
	{
		if( n == 0 ) break;
		printf("%s\n", ((divisibleCount(n) & 0x1)?"yes":"no") );
	}
    return 0;
}
