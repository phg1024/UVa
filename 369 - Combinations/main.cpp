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

// algorithm: factorize the number, then compute the result
// alternative: dynamic programming, C(n, k) = C(n-1, k-1) + C(n-1, k)

/*
#include <cstdio>
using namespace std;

long long a[101][101];

int main() {
	int n, m;
	a[1][1] = 1;
	a[1][0] = 1;

	for (int i = 2; i <= 100; i++) {
		a[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
		}
	}

	while (scanf("%d%d", &n, &m), n || m) {
		printf("%d things taken %d at a time is %lld exactly.\n", n, m,
				a[n][m]);
	}

	return 0;
}
*/


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