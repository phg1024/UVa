#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <bitset>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

static const int MAXN = 1000001;
char notprime[MAXN];
int nprimes;
int primes[80000];

void init()
{
    int x=2;
    notprime[0] = notprime[1] = 1;
    while( x < MAXN )
    {
        for(int i = x+x;i<MAXN;i+=x)
        {
            notprime[i] = 1;
        }

        while( notprime[++x] == 1 ){
            if( x >= MAXN ) break;
        } 
    }

    nprimes = 0;
    for(int i=2;i<MAXN;i++)
    {
        if( !notprime[i] )
        {
            primes[nprimes++] = i;
        }
    }
}

void split( int n, int& p, int& m )
{
    for(int i=0;i<nprimes;i++)
    {
        p = primes[i];
        m = n - primes[i];
        if( !notprime[m] ) 
        {
            return;
        }
    }
}

int main(){
    init();

    while( true )
    {
        int n;
        scanf("%d", &n);
        if( n == 0 ) break;

        int p, m;
        split( n, p, m );

        printf("%d = %d + %d\n", n, p, m);
    }
    return 0;
}

