#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

static const int MAXSIZE = 10000;

int comp(char* a, int La, char* b, int Lb)
{
    if( La < Lb ) return -1;
    if( La == Lb )
    {
        for(int i=0;i<La;i++)
            if( a[i] != b[i] )
            {
                if( a[i] > b[i] ) return 1;
                else return -1;
            }

        return 0;
    }
    else
        // a > b
        return 1;
}

void print(char* str, int L)
{
    for(int i=0;i<L;i++)
        putchar('0' + str[i]);
    putchar('\n');
}

// a div b
int division(char* a, int La, char* b, int Lb)
{
    /*
    printf("division:\n");
    print(a, La);
    print(b, Lb);    
    */
    int type = comp(a, La, b, Lb);
    switch( type )
    {
        case -1:
            {
                return -1;
            }
        case 0:
            {
                return 0;
            }
        case 1:
            {
                int result;
                // do the division
                if( comp( a, Lb, b, Lb ) > 0 )
                {
                    // the first Lb digits are large enough
                    while( comp( a, Lb, b, Lb ) > 0 )
                    {
                        // subtract b from a
                        for(int i=Lb-1;i>=0;i--)
                        {
                            char val = a[i] - b[i];
                            if( val < 0 )
                            {
                                a[i-1]--;
                                a[i] = val + 10;
                            }
                            else
                            {
                                a[i] = val;
                            }
                        }
                    }

                    if( a[0] == 0 )
                    {
                        result = division( a+1, La-1, b, Lb ); 
                    }
                    else
                    {
                        result = division( a, La, b, Lb ); 
                    }
                }
                else
                {
                    // do the division with the first Lb+1 digits
                    while( a[0] != 0 || comp( a+1, Lb, b, Lb) > 0 )
                    {
                        for(int i=Lb-1, j=Lb;i>=0;i--,j--)
                        {
                            char val = a[j] - b[i];
                            if( val < 0 )
                            {
                                a[j-1]--;
                                a[j] = val + 10;
                            }
                            else
                                a[j] = val;
                        }
                    }

                    if( a[1] == 0 )
                    {
                        result = division( a+2, La-2, b, Lb );
                    }
                    else
                    {
                        result = division( a+1, La-1, b, Lb );
                    }
                }

                return result;
            }
    }
}

void int2str(int num, char* str, int &L)
{
    // num is between 0 and 10000
    // at most 14 bits
    sprintf(str, "%d", num);
    L = strlen(str);
    for(int i=0;i<L;i++)
        str[i] -= '0';
}

void ones(char* str, int L)
{
    for(int i=0;i<L;i++)
        str[i] = 1;
}

int main()
{
    unsigned int num;
    while( scanf("%d", &num) != EOF )
    {
        char a[6] = {0};
        int La = 0;
        int2str(num, a, La);

        char product[MAXSIZE] = {0};
        int L = La + 1; 
        while( L < MAXSIZE )
        {
            ones( product, L );
            int res = division( product, L, a, La ); 

            if( res == 0 )
                break;

            L++;
        }

        printf("%d\n", L);
    }
    return 0;
}
