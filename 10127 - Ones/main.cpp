#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

void add(char* a, char* b, int &L)
{
}

void int2BinaryString(int num, char* str, int &L)
{
}

bool allOnes(char* str, int L)
{
}

int main()
{
    int num;
    while( scanf("%d", &num) != EOF )
    {
        char a[1024] = {0};
        int L = 0;
        int2BinaryString(num, a);

        char b[1024];
        strcpy(b, a);
        int count = 0;
        while( !allOnes( a, L ) )
        {
            add( a, b, L );
            count ++;
        }

        printf("%d\n", count);
    }
    return 0;
}
