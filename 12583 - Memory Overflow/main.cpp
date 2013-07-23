#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int main()
{
    int ncases;
    scanf("%d", &ncases);

    for(int c=1;c<=ncases;c++)
    {
        int n, k;
        char p[501];
        scanf("%d %d %s", &n, &k, p);

        int count = 0;
        for(int i=0;i<n;i++)
        {
            for(int j=i-1;j>=max(i-k, 0);j--)
            {
                if( p[i] == p[j] ){
                    count++;
                    break;
                }
            }
        }

        printf("Case %d: %d\n", c, count);
    }
    return 0;
}
