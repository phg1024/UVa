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

int main(){
	int ncases;
	scanf("%d", &ncases);
	
	while( ncases-- > 0 )
	{
		unsigned int x, y;
		scanf("%d %d", &x, &y);
		
		unsigned int delta = y - x;
		
		if( delta == 0 )
		{
			printf("0\n");
			continue;
		}
		
		int k = floor(sqrt(delta));
		int r = delta % k;
		int p = delta / k;
		
		// p + (k-1) + (r==0?1:0)
		printf("%d\n", p + k + (r==0?-1:0) );
	}
	
    return 0;
}

