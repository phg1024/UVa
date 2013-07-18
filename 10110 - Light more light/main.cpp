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

int primes[6544];
int primeCount;

bool isPrime(unsigned int n)
{
	for(int i=0;i<primeCount;i++)
	{
		if( n == primes[i] ) return true;
		if( n % primes[i] == 0 ) return false;
	}
	
	return true;
}

void init()
{
	primes[0] = 2;
	primeCount = 1;
	for(int i=3;i<65538;i+=2)
	{
		if( isPrime(i) )
		{
			primes[primeCount++] = i;
		}
	}
}

int divisibleCount(unsigned int n)
{
	unsigned int n0 = n;
	if( n == 1 ) return 1;
	
	if( isPrime(n) ) return 2;
	
	vector<int> facs;
	vector<unsigned int> comps;
	
	for(int i=0;i<primeCount;i++)
	{
		int p = primes[i];
		if( p > n ) break;
		if( n % p == 0 )
		{
			facs.push_back(0);
			comps.push_back(p);
			while( n % p == 0 )
			{
				facs.back()++;
				n /= p;
			}
		}		
	}
	
	if( n != 1 )
	{
		facs.push_back(1);
		comps.push_back(n);
	}
	
	unsigned int count = 1;
	for(size_t i=0;i<facs.size();i++)
	{
		count *= (facs[i] + 1);
	}	
		
	return count;
}

int main()
{
	init();
	unsigned int n;
	while( cin >> n )
	{
		if( n == 0 ) break;
		cout << ((divisibleCount(n) & 0x1)?"yes":"no") << endl;
	}
    return 0;
}
