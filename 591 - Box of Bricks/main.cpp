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
    int idx = 0;
    while( true )
    {
        int n;
        scanf("%d", &n);
        if( n == 0 ) break;

        int h[50];

        int sum = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%d", &(h[i]));
            sum += h[i];
        }

        int hbar = sum / n;

        int count = 0;
        for(int i=0;i<n;i++)
        {
            if( h[i] > hbar )
            count += (h[i] - hbar);
        }

        printf("Set #%d\n", ++idx);
        printf("The minimum number of moves is %d.\n", count);
        putchar('\n');
    } 
    return 0;
}
