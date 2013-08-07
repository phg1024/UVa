#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXFACS = 32;
static const int nprimes = 25;
int primes[] = {
    2,  3,  5,  7,  11, 
    13, 17, 19, 23, 29, 
    31, 37, 41, 43, 47, 
    53, 59, 61, 67, 71, 
    73, 79, 83, 89, 97
};

int primemap[98];

void factorize( int n, int facs[] )
{
    for(int i=2;i<=n;i++)
    {
        int m = i;
        for(int j=0;j<nprimes;j++)
        {
            int p = primes[j];
            if( p > m ) break;
            while( m % p == 0 )
            {
                facs[ primemap[p] ]++;
                m /= p;
            }
        }
    }
}

int main()
{
    // initialize prime map
    for(int i=0;i<nprimes;i++)
        primemap[ primes[i] ] = i;

    int n;
    while( true )
    {
        scanf("%d", &n);
        if( n == 0 ) break;
        
        int facs[MAXFACS] = {0};
        factorize( n, facs );

        printf("%3d! =", n);
        bool newline = false;
        for(int i=0, c=1;i<MAXFACS;i++, c++)
        {
            if( facs[i] != 0 )
            {
                if( newline ){
                    printf("\n      "); 
                    newline = false;
                }
                printf("%3d", facs[i]);
                if( c % 15 == 0 ) newline = true;
            }
        }
        putchar('\n');
    }
    return 0;
}
