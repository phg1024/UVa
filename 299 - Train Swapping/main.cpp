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

int main()
{
    int ncases;
    scanf("%d", &ncases);

    while( ncases-- > 0 )
    {
        int n;
        scanf("%d", &n);

        int idx[50];
        for(int i=0;i<n;i++)
            scanf("%d", &(idx[i]));

        int count = 0;
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
                if( idx[j] < idx[i] )
                    count++;
        }

        printf("Optimal train swapping takes %d swaps.\n", count);
    }
    return 0;
}
