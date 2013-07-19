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
    int n;
    scanf("%d", &n);
    while( n-- > 0 )
    {
        int m;
        scanf("%d", &m);

        int sum = 0;

        for(int i=0;i<m;i++)
        {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            sum += a * c;
        }
        
        printf("%d\n", sum);
    }
    return 0;
}
