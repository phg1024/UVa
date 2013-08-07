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

bitset<1000010> notprime(0);
int ndp;
int dp[32768];
int dpcount[1000001];

int digitsum(int n)
{
    int v = 0;
    while( n )
    {
        v += n % 10;
        n /= 10;
    }
    return v;
}

void digitprimes()
{
    int x=2;
    while( x <= 1000009 )
    {
        for(int i=x+x;i<=1000009;i+=x)
            notprime[i] = 1;

        while( notprime[++x] == 1 )
        {
            if( x > 1000009 ) break;
        }
    }

    ndp = 0;
    for(int i=2;i<=1000009;i++)
    {
        if( !notprime[i] ){
            int v = digitsum( i );
            if( !notprime[v] )
                dp[ndp++] = i;
        }
        dpcount[i] = ndp;
    }
}

int main()
{
    digitprimes();

    int n;
    scanf("%d", &n);

    while( n-- > 0 )
    {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%d\n", dpcount[b] - dpcount[a-1]);
    }

    return 0;
}
