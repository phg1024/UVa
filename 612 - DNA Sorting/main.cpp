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

static const int MAXL = 64;
static const int MAXN = 128;

struct DNA
{
    bool operator<(const DNA& d) const
    {
        return inversions < d.inversions;
    }

    void countInversions()
    {
        inversions = 0;
        for(int i=0;i<L;i++)
        {
            for(int j=i+1;j<L;j++)
            {
                if( str[i] > str[j] )
                    inversions++;
            }
        }
    }

    int L;
    char str[MAXL];
    int inversions;
};

int main()
{
    int ncases;
    scanf("%d", &ncases);
    while( ncases-- > 0 )
    {
        int n, m;
        scanf("%d %d", &n, &m);

        DNA dna[MAXN];
        for(int i=0;i<m;i++)
        {
            dna[i].L = n;
            scanf("%s\n", dna[i].str);
            dna[i].countInversions();
        }

        std::stable_sort(dna, dna+m, std::less<DNA>());

        for(int i=0;i<m;i++)
            printf("%s\n", dna[i].str);

        if( ncases ) printf("\n");
    }
    return 0;
}
