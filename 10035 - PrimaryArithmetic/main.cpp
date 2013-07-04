#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

int add(char a[], char b[])
{
    int L1 = strlen(a);
    int L2 = strlen(b);
    std::reverse(a, a+L1);
    std::reverse(b, b+L2);

    for(int i=0;i<L1;i++)
        a[i] -= '0';

    for(int i=0;i<L2;i++)
        b[i] -= '0';

    int L = max(L1, L2);

    char c[12] = {0};
    memcpy(c, a, sizeof(char)*L1);
    int carry = 0;
    for(int i=0;i<L;i++)
    {
        int val = b[i] + c[i];
        if( val >= 10 )
        {
            carry++;
            c[i+1]++;
        }
    }

    return carry;
}

int main(){
    while( true )
    {
        char a[11] = {0}, b[11] = {0};
        scanf("%s %s\n", a, b);

        if( a[0] == '0' && b[0] == '0' )
            break;
        else
        {
            int carry = add(a, b);

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

