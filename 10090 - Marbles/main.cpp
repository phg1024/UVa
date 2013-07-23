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

typedef long long int lint;

lint extended_gcd(lint a, lint b, lint& x, lint &y)
{
	x = 0, y = 1;
	lint lastx = 1, lasty = 0;
	lint q, r;
	
	while( b != 0 )
	{
		q = a / b;
		r = a % b;
		a = b;
		b = r;
		
		lint nx = lastx - q * x;
		lastx = x;
		x = nx;
		
		lint ny = lasty - q * y;
		lasty = y;
		y = ny;
	}
	
	x = lastx;
	y = lasty;
	return a;
}

int main()
{
    lint n;
    while( true )
    {
        scanf("%lld", &n);
        if( n == 0 ) break;

        lint c1, c2;
        lint n1, n2;
        scanf("%lld %lld %lld %lld", &c1, &n1, &c2, &n2);

		lint x, y;
        lint g = extended_gcd(n1, n2, x, y);
		
		if( n % g != 0 )
		{
			printf("failed\n");
			continue;
		}
		
		lint lowk = ceil(-n*x/(double)n2);
		lint upk = floor(n*y/(double)n1);
		
		if( lowk > upk )
		{
			printf("failed\n");
			continue;
		}
		
		if( c1 * n2 <= c2 * n1 )
		{
			x = n2 / g * upk + n / g * x;
			y = n / g * y - n1 / g * upk;
		}
		else
		{
			x = n2 / g * lowk + n / g * x;
			y = n / g * y - n1 / g * lowk;
		}
		printf("%lld %lld\n", x, y);
    }
    return 0;
}
