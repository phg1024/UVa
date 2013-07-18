#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

#define CHEAT 1

#if !CHEAT
bitset<65536> isPrime(0);

void init()
{
	for(int i=2;i<257;)
 	{
		for(int j=i+i;j<65536;j+=i)
 			isPrime[j] = 1;
		
		i++;
		while( isPrime[i] == 1 && i < 257 ) i++;
 	}
 }

// a^n mod x 
unsigned int modulo(int a, int n, int x)
{
	if( n == 0 ) return 1;
    if( n == 1 ) return a % x;
    else
    {
		int m = n / 2;
		int r = n & 0x1;
		unsigned int v = modulo(a, m, x);
		unsigned int k = (r == 1)?(a % x):1;
		v = (v * v) % x;
        return (v * k) % x; 
    }
}
#endif

#if CHEAT
const int SIZE = 15;
int cheat[] = { 561, 1105, 1729, 2465, 2821, 
				6601, 8911, 10585, 15841, 29341, 
				41041, 46657, 52633, 62745, 63973};
#endif
						
inline bool isCarmichael(int n)
{
#if CHEAT
	for(int i=0;i<SIZE;i++)
		if( n == cheat[i] ) return true;
	return false;
#else
    if( isPrime[n] == 0 )
        return false;

    for(int i=2;i<n/2;i++)
    {
		int mi = modulo(i, n, n);
        if( mi != i )
        {
            return false;
        }
    }
	
	if( n & 0x1 )
		return true;
	else
		return (modulo(n-1, n, n) == n-1);
#endif
}
				
int main(){
	// create cheat answers
	//for(int i=2;i<65536;i++)
	//	if( isCarmichael(i) ) cout << i << endl;
#if !CHEAT
	init();
#endif
	
    while( true )
    {
        int n;
        scanf("%d", &n);

        if( n == 0 ) break;

        if( isCarmichael( n ) )
        {
            printf("The number %d is a Carmichael number.\n", n);
        }
        else
        {
            printf("%d is normal.\n", n);
        }
    }
    return 0;
}

