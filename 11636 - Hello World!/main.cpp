#include <cstdio>
#include <cmath>

int main()
{
	int n;
	int idx = 0;
	while( true )
	{
		scanf("%d", &n);
		if( n < 0 ) break;
		printf("Case %d: %d\n", ++idx, (int)ceil(log2(n)));
	}
	return 0;
}
