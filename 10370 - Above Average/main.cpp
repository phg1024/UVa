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

        int s[1000];

        int sum = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%d", &(s[i]));
            sum += s[i];
        }

        double ave = sum / (double) n;
        int count = 0;
        for(int i=0;i<n;i++)
        {
            if( s[i] > ave ) count++;
        }

        printf("%.3f%%\n", count / (double) n * 100.0 );

    }
    return 0;
}
