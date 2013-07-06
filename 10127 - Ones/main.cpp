#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

// suppose:
// k * n + r_L = 10^(L-1) + 10^(L-2) + ... + 10^0
// k * n + r_L = (10^L - 1) / 9
// let:
// r_j = mod[ (10^j - 1) / 9, n ]
// then
// r_(j+1) = mod[ 10 * r_j + 1, n ]
// the first r_i == 0 is the solution 

int main()
{
    int num;
    int rem, L;
    while( scanf("%d", &num) != EOF )
    {
        rem = L = 1;
        // skip the first few modulo operations
        while( rem < num )
        {
            rem = rem * 10 + 1;
            L++;
        }

        while( rem != 0 )
        {
            rem = (10 * rem + 1) % num;
            L++;
        }

        printf("%d\n", L);
    }
    return 0;
}
