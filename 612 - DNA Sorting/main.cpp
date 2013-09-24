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
        //inversions = bruteforce_count();
        strcpy(str, istr);
        inversions = sort_and_count(0, L-1);
    }

    int bruteforce_count()
    {
        int ref = 0;
        for(int i=0;i<L;i++)
        {
            for(int j=i+1;j<L;j++)
            {
                if( istr[i] > istr[j] )
                    ref++;
            }
        }
        return ref;
    }

    int merge_and_count(int l, int m, int r)
    {
        int count = 0;
        char A[MAXL] = {0}, B[MAXL] = {0};
        // copy into A and B
        int idx = 0;
        for(int i=l;i<=m;i++)
            A[idx++] = str[i];
        idx = 0;
        for(int i=m+1;i<=r;i++)
            B[idx++] = str[i];

        int i = 0, j = 0;
        int pos = l; 
        while( i <= (m - l) && j <= (r - m - 1) )
        {
            if( A[i] <= B[j] )
            {
                str[pos++] = A[i++];
            }
            else
            {
                str[pos++] = B[j++];
                count += (m - l + 1 - i);
            }
        }

        // copy the rest of either A or B back to the string
        while( i <= (m - l) )
            str[pos++] = A[i++];

        while( j <= (r - m - 1) )
            str[pos++] = B[j++];

        return count;
    }

    int sort_and_count(int l, int r)
    {
        if( l >= r )
            return 0;
        else
        {
           int m = (l+r)/2; 
           int rl = sort_and_count(l, m);
           int rr = sort_and_count(m+1, r);
           int rm = merge_and_count(l, m, r);
           return rl + rr + rm;
        }
    }

    int L;
    char istr[MAXL];
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
            scanf("%s\n", dna[i].istr);
            dna[i].countInversions();
        }

        std::stable_sort(dna, dna+m, std::less<DNA>());

        for(int i=0;i<m;i++)
            printf("%s\n", dna[i].istr);

        if( ncases ) printf("\n");
    }
    return 0;
}
