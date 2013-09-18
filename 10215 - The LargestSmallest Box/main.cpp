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

double clamp(double v, double low, double up)
{
	return max(min(v, up), low);
}

int main()
{
	double W, L;
	while( scanf("%lf %lf", &W, &L) != EOF )
	{
		double delta = W*W + L*L - W*L;
		double x1 = ((W+L) - sqrt(delta)) / 6.0;
		double x2 = ((W+L) + sqrt(delta)) / 6.0;
		double E = min(W, L);

		double V1 = (W - 2*x1)*(L - 2*x1)*x1;
		double V2 = (W - 2*x2)*(L - 2*x2)*x2;
		double ans = (V1>V2)?x1:x2;
				
		// used to control precision
		const double eps = 1e-7;
		printf("%.3lf %.3lf %.3lf\n", ans+eps, 0.0, E/2.0+eps);
	}
    return 0;
}
