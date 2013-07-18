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

bool isCarmichael(int n)
{
    if( isPrime[n] == 0 )
        return false;

	int m2 = modulo(1, n, n);
	
    for(int i=2, j=4;i<n/2;i++, j=i*2)
    {
		int mi = modulo(i, n, n);
		// (i + j)^n mod n = (i^n + j^n) mod n
		int mj = (mi + mi) % n;
        if( (mi != i) || (mj != j) )
        {
            return false;
        }
    }
	
	if( !(n & 0x1) ) if( modulo(n-1, n, n) != n-1 ) return false;

    return true;
}

int main(){
	init();
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

