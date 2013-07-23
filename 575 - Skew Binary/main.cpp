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

unsigned int base[] = 
{
    0x1, 0x2, 0x4, 0x8,
    0x10, 0x20, 0x40, 0x80,
    0x100, 0x200, 0x400, 0x800,
    0x1000, 0x2000, 0x4000, 0x8000,
    0x10000, 0x20000, 0x40000, 0x80000,
    0x100000, 0x200000, 0x400000, 0x800000,
    0x1000000, 0x2000000, 0x4000000, 0x8000000,
    0x10000000, 0x20000000, 0x40000000, 0x80000000,
};

int skewBinary(char digit[], int L)
{
    unsigned int sum = 0;
    for(int i=L-1, j=0;i>=0;i--, j++)
    {
        while( digit[i] == '0' )
        {
            i--, j++;
        }
        sum += (digit[i] - '0') * (base[j+1]-1);
    }
    return sum;
}

int main()
{
    while( true )
    {
        char buf[64];
        scanf("%s", buf);

        int L = strlen(buf); 
        if( L == 1 && buf[0] == '0' ) break;

        printf("%u\n", skewBinary(buf, L));
    }
    return 0;
}
