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

int primes[6543];
int primeCount;

typedef map<unsigned int, unsigned int> factor_t;

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

factor_t factorize(unsigned int n)
{
	factor_t facs;
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
			facs[p] = count;
		}		
	}
	
	if( n != 1 )
		facs[n] = 1;
	return facs;
}

void printFacs(unsigned int n, factor_t& facs)
{
	cout << "n = " << n << endl;
	for(factor_t::iterator it=facs.begin();
		it!=facs.end();
		it++)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
}

bool solve(unsigned int n, unsigned int m)
{
	if( m == 0 ) return false;
	if( m == 1 ) return true;
	if( n >= m ) return true;

	factor_t facs = factorize( m );
	//printFacs(m, facs);
	
	for(factor_t::iterator it=facs.begin();
		it!=facs.end();
		it++)
	{
		int p = (*it).first;
		int k = (*it).second;
		
		//cout << p << " ^ " << k << endl;
		
		/// see if there is enough factor in n!
		unsigned int v = p;
		while( k > 0 )
		{
			if( v > n ) break;
			
			unsigned int v0 = v;
			//cout << "v0 = " << v0 << endl;
			while( v0 % p == 0 )
			{
				v0 /= p;
				k--;
			}
			v += p;
		}
		//cout  <<  k  << endl;
			
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

