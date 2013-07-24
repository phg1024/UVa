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

struct fact_t
{
    fact_t(){}
    fact_t(int v):v(v),count(0){}

    int v;
    int count;
};

void factorize(int n, fact_t facs[], int& nfacs)
{
    nfacs = 0;
    for(int i=2;i<=10;i++)
    {
        if( n % i == 0 )
        {
            fact_t f(i);
            while( n % i == 0 )
            {
                n /= i;
                f.count++;
            }
            facs[nfacs++] = f;
        }
    }


    if( n != 1 )
    {
        fact_t f(n);
        f.count = 1;
        facs[nfacs++] = f;
    }

}

unsigned int combinations(int n, int k)
{
    unsigned int v = 1;
    map<int, int> up, down;

    fact_t facs[16];
    int nfacs;

    int m = n - k;
    m = (m>k?k:m);

    // n * (n-1) * ... * (n-m+1)
    for(int i=n-m+1;i<=n;i++)
    {
        factorize(i, facs, nfacs);
        for(int j=0;j<nfacs;j++)
        {
            if( up.find(facs[j].v) == up.end() )
                up[facs[j].v] = 0;
            up[facs[j].v] += facs[j].count;
        }
    }
    
    // m * (m-1) * ... * 1
    for(int i=2;i<=m;i++)
    {
        factorize(i, facs, nfacs);
        for(int j=0;j<nfacs;j++)
        {
            if( down.find(facs[j].v) == down.end() )
                down[facs[j].v] = 0;

            down[facs[j].v] += facs[j].count;
        }
    }

    for(map<int,int>::iterator it=up.begin();
        it!=up.end();
        ++it)
    {
        map<int, int>::iterator dit = down.find( (*it).first );
        if( dit  != down.end() )
        {
            (*it).second -= (*dit).second;
        }


        v *= (unsigned int)powf((*it).first, (*it).second);
    }

    return v;
}

int main()
{
    while( true )
    {
        int n, k;
        scanf("%d %d", &n, &k);
        if( n == 0 && k == 0 ) break;

        printf("%d things taken %d at a time is %u exactly.\n", n, k, combinations(n, k));
    }
    return 0;
}
