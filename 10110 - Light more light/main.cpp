#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <bitset>
#include <map>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

int main()
{
	unsigned int n;
	while( scanf("%u", &n) )
	{
		if( n == 0 ) break;
		double r = sqrt(n);
		unsigned int s = r;
		
		// note that the return value is false if any of the factors of n have odd counts
		// otherwise the return value is true, i.e. all the factors have even counts
	
		// the only possibility that all the factors of n have even counts is that n itself
		// is a perfect squre
		
		printf("%s\n", (s == r)?"yes":"no" );
	}
    return 0;
}
