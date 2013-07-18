#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

int extended_gcd(int a, int b, int& x, int &y, int &d)
{
	x = 0, y = 1;
	int lastx = 1, lasty = 0;
	int q, r;
	
	while( b != 0 )
	{
		q = a / b;
		r = a % b;
		a = b;
		b = r;
		
		int nx = lastx - q * x;
		lastx = x;
		x = nx;
		
		int ny = lasty - q * y;
		lasty = y;
		y = ny;
	}
	
	x = lastx;
	y = lasty;
	d = a;
}

int main(){
    int a, b;
    while( scanf("%d %d", &a, &b) != EOF )
    {
        int x, y, d;
		extended_gcd(a, b, x, y, d);
        printf("%d %d %d\n", x, y, d);
    }
    return 0;
}

