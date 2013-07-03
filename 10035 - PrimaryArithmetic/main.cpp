#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

int add_bignum(char a[], char b[])
{
    int L1 = strlen(a);
    int L2 = strlen(b);
    std::reverse(a, a+L1);
    std::reverse(b, b+L2);

    int L = min(L1, L2);

    char c[12] = {0};
    int carry = 0;
    for(int i=0;i<L;i++)
    {
        int val = (a[i] - '0') + (b[i] - '0') + c[i];
        if( val >= 10 )
        {
            carry++;
            c[i] = val-10;
            c[i+1]++;
        }
        else
            c[i] = val;
    }
    if( L1 > L2 )
    {
        for(int i=L;i<L1;i++)
        {
            int val = (a[i] - '0') + c[i];
            if( val >= 10 )
            {
                carry++;
                c[i] = val - 10;
                c[i+1]++;
            }
            else
                c[i] = val;
        }
    }
    else
    {
        for(int i=L;i<L2;i++)
        {
            int val = (b[i] - '0') + c[i];
            if( val >= 10 )
            {
                carry++;
                c[i] = val - 10;
                c[i+1]++;
            }
            else
                c[i] = val;
        }
    }


    return carry;
}

int main(){
    while( true )
    {
        char a[11], b[11];
        scanf("%s %s\n", a, b);

        if( a[0] == '0' && b[0] == '0' )
            break;
        else
        {
            int carry = add_bignum(a, b);

            switch( carry )
            {
                case 0:
                    {
                    printf("%s\n", "No carry operation.");
                    break;
                    }
                case 1:
                    {
                    printf("%s\n", "1 carry operation.");
                    break;
                    }
                default:
                    {
                    printf("%d %s\n", carry, "carry operations.");
                    break;
                    }
            }
        }
    }
    return 0;
}

