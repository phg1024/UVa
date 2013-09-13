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

int64_t judge(int64_t val)
{
    // 1 is deficient
    if( val == 1 ) return -1;

    int64_t sum = 1;
    int bound = floor(sqrt(val));

    for(int i=2;i<=bound;i++)
    {
        if( val % i == 0 )
        {
            int64_t q = val / i;
			if( q != i )
				sum += (i+q);
			else
				sum += i;
        }
    }
    return sum - val;
}

int main()
{
    int64_t numbers[100];
    int n=0;
    while( true )
    {
        int64_t val;
        scanf("%lld", &val);
        if( val == 0 ) break;
        numbers[n++] = val;
    }

    char *str[3] = {"PERFECT", "DEFICIENT", "ABUNDANT"};

    printf("PERFECTION OUTPUT\n");
    for(int i=0;i<n;i++)
    {
        int cat = judge(numbers[i]);
        if( cat > 0 ) cat = 2;
        if( cat < 0 ) cat = 1;
        printf("%5lld  %s\n", numbers[i], str[cat]);
    }
    printf("END OF OUTPUT\n");
    return 0;
}
