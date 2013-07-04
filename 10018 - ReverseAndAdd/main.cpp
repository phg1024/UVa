#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

void add(char *a, char *b, int& L)
{
    for(int i=0;i<L;i++)
    {
        int val = a[i] + b[i];

        if( val >= 10 )
        {
            a[i] = val - 10;
            a[i+1]++;
        }
        else
            a[i] = val;
    } 
    // carry over
    if( a[L] != 0 )
        L++;
}

void revert(char *a, char *b, int L)
{
    for(int i=0, j=L-1;i<L;i++, j--)
        b[j] = a[i];
}

bool isPalindrome(char *str, int L)
{
    int left = 0, right = L-1;
    while( left <= right )
    {
        if( str[left] != str[right] )
            return false;

        left++;
        right--;
    }

    return true;
}

int main(){
    int ncases;
    scanf("%d", &ncases);

    while( ncases-- > 0 )
    {
        char a[16]={0};
        scanf("%s", a);
        int L = strlen(a);
        for(int i=0;i<L;i++)
            a[i] -= '0';

        char b[16]={0};
        int count = 0;
        while( !isPalindrome( a, L ) )
        {
            revert( a, b, L );
            add( a, b, L );
            count++;
        }

        printf("%d ", count);
        for(int i=0;i<L;i++)
            printf("%d", a[i]);
        putchar('\n');
    }
    return 0;
}

