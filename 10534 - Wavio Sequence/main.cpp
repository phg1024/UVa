#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

int binarySearch(int lis[], int L, int x)
{
    int l, r, m;
    l = 0; r = L;

    do
    {
        m = (l+r)/2;
        if( lis[m] >= x ) r = m;
        else l = m;
    }while( r-l > 1 );

    if( lis[l]>=x ) return l;
    else if( lis[r]>=x ) return r;
    else return -1;
}

int longestWavioSequence(int n, int num[])
{
    int Li[10000] = {0};
    int lis[10000] = {0};

    // longest increasing
    int L = 0;
    for(int i=0;i<n;i++)
    {
        int x = num[i];
        int j = binarySearch(lis, L, x);
        if( j == -1 ) lis[++L] = x;
        else lis[j] = x;
        Li[i] = L;
    }
    
    // longest decreasing
    int Ld[10000] = {0};
    L = 0;
    for(int i=n-1;i>=0;i--)
    {
        int x = num[i];
        int j = binarySearch(lis, L, x);
        if( j == -1 ) lis[++L] = x;
        else lis[j] = x;
        Ld[i] = L;
    }

    // add them up
    int longest = 1;
    for(int i=0;i<n;i++)
    {
        int L = min(Li[i], Ld[i]);
        if( L > longest )
            longest = L;
    }
    return longest * 2 - 1;
}

int main(){
    int n;
    while( scanf("%d", &n) != EOF )
    {
        int num[10000];

        for(int i=0;i<n;i++)
            scanf("%d", &num[i]);

        printf("%d\n", longestWavioSequence( n, num ) );
    }
    return 0;
}

