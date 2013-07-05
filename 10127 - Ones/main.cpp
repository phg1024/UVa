#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

// suppose:
// k * n + r_L = 10^(L-1) + 10^(L-2) + ... + 10^0
// k * n + r_L = (10^L - 1) / 9
// let:
// r_j = mod[ (10^j - 1) / 9, n ]
// then
// r_(j+1) = mod[ 10 * r_j + 1, n ]
// the first r_i == 0 is the solution 

int findMultiple(unsigned int num)
{
    vector<int> rem;

    int val = 1;
    while( val <= num )
    {
        rem.push_back( val % num );
        val = val * 10 + 1;
    }

    int L = rem.size();
    while( rem.back() != 0 )
    {
        rem.push_back( (10 * rem.back() + 1) % num );
    }

    return rem.size();
}

int main()
{
    unsigned int num;
    while( scanf("%d", &num) != EOF )
    {
        printf("%d\n", findMultiple( num ));
    }
    return 0;
}
