#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <limits>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXN = 8;

int fac(int n)
{
	if( n == 1 ) return 1;
	else return n * fac(n-1);
}

double computeWidth( double r[], int order[], int n )
{
	// compute the width of the box
	
	double x[MAXN];
	x[0] = r[order[0]];
	
	for(int i=1;i<n;i++)
	{
		int cur = order[i];
        x[i] = x[i-1];
		
		for(int j=0;j<=i-1;j++)
		{
			int prev = order[j];
			// test if it hits the previous circle
			double rdiff = fabs(r[cur] - r[prev]);
			double rsum = r[cur] + r[prev];
			double xcoord = x[j] + sqrt( rsum * rsum - rdiff * rdiff );
			
			if( xcoord > x[i] )
            {
                x[i] = xcoord;
            }
		}
	}
	
	double lbound = numeric_limits<double>::max();
	double rbound = 0.0;

	for(int i=0;i<n;i++)
	{
		double xl = x[i] - r[order[i]];
		double xr = x[i] + r[order[i]];
		
		if( xl < lbound ) lbound = xl;
		if( xr > rbound ) rbound = xr;
	}
		
	return rbound - lbound;
}

double solve( double r[], int n )
{
	int order[MAXN];
	for(int i=0;i<n;i++)
		order[i] = i;
	
	int count = 0;
	int L = fac(n);
	
	double res = numeric_limits<double>::max();
	
	while( count++ < L )
	{
		double s = computeWidth( r, order, n );
		if( s < res )
		{
			res = s;
		}
		std::next_permutation(order, order+n);
	}
	return res;
}

int main()
{
    int ncases;
    scanf("%d", &ncases);

    while( ncases -- > 0 )
    {
        int n;
        scanf("%d", &n);

        double r[MAXN];
        for(int i=0;i<n;i++)
            scanf("%lf", &r[i]);

        printf("%.3f\n", solve( r, n ) );
    }
    return 0;
}
