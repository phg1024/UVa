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

const double pi=3.141592653589793;  
int main()  
{  
	double r;
	double pid3 = pi / 3.0;
	double sqrt3 = sqrt(3.0);
    while (scanf("%lf",&r)!=EOF)  
    {  
		double r2 = r*r;
        printf("%.3lf %.3lf %.3lf\n",r2*(1+pid3-sqrt3),r2*(pid3+2*sqrt3-4),r2*(-2*pid3+4-sqrt3));  
    }  
    return 0;  
}  