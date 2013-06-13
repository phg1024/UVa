#include "stdio.h"
#define max(a, b) ((a)>(b))?(a):(b)
#define min(a, b) ((a)<(b))?(a):(b)

double costs[1000];

double exchangedAmount(double* costs, int n)
{
	int i;
	double average = 0.0;
	double diff[2] = {0, 0};
	int count[2] = {0, 0};
	double amount = 0.0;
	
	for (i = 0; i < n; i++)  
        average += costs[i];  
  
    average /= n;  
    average = (long) (average * 100 + 0.5) / 100.00; 

	for (i = 0; i < n; i++)  
    {  
        if (costs[i] > average)  
		{
			count[0] ++;
            diff[0] += (costs[i] - average);  
		}
        else  
		{
			count[1] ++;
            diff[1] += (average - costs[i]);  
		}
    }  

	if( diff[0] > 0 && diff[1] > 0 )
		return min(diff[0], diff[1]);
	else
	{
		if( diff[0] == 0 && diff[1] == 0 ) return 0.0;
		else{
			if( diff[1] == 0 ){
				return diff[0] - 0.1 * count[0];
			}
			else
			{
				return diff[1] - 0.1 * count[1];
			}
		}
	}
}

int main()
{
	int i, n;
	while( scanf("%d", &n) == 1 ){
		if( n==0 ) break;

		for(i=0;i<n;i++) scanf("%lf", costs+i);

		printf("$%.2f\n", exchangedAmount(costs, n));
	}
	return 0;
}