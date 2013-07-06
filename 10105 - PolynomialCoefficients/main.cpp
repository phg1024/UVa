#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int combinations[][13] = 
{
    {1,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},
    {1,    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},
    {1,    2,    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},
    {1,    3,    3,    1,    0,    0,    0,    0,    0,    0,    0,    0,    0},
    {1,    4,    6,    4,    1,    0,    0,    0,    0,    0,    0,    0,    0},
    {1,    5,   10,   10,    5,    1,    0,    0,    0,    0,    0,    0,    0},
    {1,    6,   15,   20,   15,    6,    1,    0,    0,    0,    0,    0,    0},
    {1,    7,   21,   35,   35,   21,    7,    1,    0,    0,    0,    0,    0},
    {1,    8,   28,   56,   70,   56,   28,    8,    1,    0,    0,    0,    0},
    {1,    9,   36,   84,  126,  126,   84,   36,    9,    1,    0,    0,    0},
    {1,   10,   45,  120,  210,  252,  210,  120,   45,   10,    1,    0,    0},
    {1,   11,   55,  165,  330,  462,  462,  330,  165,   55,   11,    1,    0},
    {1,   12,   66,  220,  495,  792,  924,  792,  495,  220,   66,   12,    1},
};

int computeCoeffs_fast(int n, int k, int *exponent)
{
	int val = 1;
	for(int i=0;i<k;i++)
	{
		val *= combinations[n][exponent[i]];
		n -= exponent[i];
	}
	return val;
}

int main()
{
    int n, k;
    while( scanf("%d %d", &n, &k) != EOF )
    {
        int exponent[12];
        for(int i=0;i<k;i++)
        {
            scanf("%d", &exponent[i]);
        }

		int coeff2 = computeCoeffs_fast(n, k, exponent);

        printf("%d\n", coeff2);
    }
    return 0;
}
