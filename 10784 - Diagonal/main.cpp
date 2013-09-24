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
    // n-gon has n(n-3)/2 diagonals

    int caseidx = 1;
    while( true )
    {
        int64_t N;
        scanf("%lld", &N);
        if( !N ) break;

        // n(n-3)/2 > N
        // n^2 - 3*n - 2N > 0

        int n = ceil( (3 + sqrt(9 + 8 * N)) / 2 );
        
        printf("Case %d: %d\n", caseidx++, n);
    }
    return 0;
}
