#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

bool solve3(int x[], int a, int b, int c)
{
    int sum = (a + b + c)/2;
    if( sum * 2 != (a + b + c) )
        return false;

    x[0] = sum - c;
    x[1] = sum - b;
    x[2] = sum - a;
    return true;
}

bool solve(int x[], int n, vector<int>& sums)
{
    if( n == 3 ) return solve3(x, sums[0], sums[1], sums[2]);

    for(int i=2;i<n;i++)
    {
        if( solve3(x, sums[0], sums[1], sums[i]) )
        {
            vector<int> s(sums.begin()+2, sums.end());
            s.erase(s.begin() + i - 2);

            bool flag = true;
            int count = 3;
            while( flag && count < n )
            {
                x[count] = s.front() - x[0];

                for(int k=0;k<count;k++)
                {
                    vector<int>::iterator it = std::find( s.begin(), s.end(), x[count] + x[k] );
                    if( it == s.end() )
                    {
                        flag = false;
                        break;
                    }
                    else
                        s.erase( it );
                }
                count++;
            }
            if( flag ) return true;
        }
    }
    return false;
}

int main()
{
    int n;
    while( scanf("%d", &n) != EOF )
    {
        int nSums = n * (n-1) / 2;
        vector<int> sums;
        sums.resize(nSums);
        int x[10];

        for(int i=0;i<nSums;i++)
        {
            scanf("%d", &(sums[i]));
        }

        std::sort(sums.begin(), sums.end(), std::less<int>());

        if( solve( x, n, sums ) )
        {
            for(int i=0;i<n;i++)
            {
                printf("%d", x[i]);
                putchar( ((i==n-1)?'\n':' ') );
            }
        }
        else printf("Impossible\n");
    }
    return 0;
}
