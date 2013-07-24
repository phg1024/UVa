#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    while( true )
    {
		int64_t v;
		scanf("%lld", &v);
		if( v < 0 ) break;
		
		int64_t x = v;
        printf("%lld\n", (x * (x+1) / 2 + 1));
    }
    return 0;
}