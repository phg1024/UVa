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

// the steps must be the following pattern
//
// 1, 2, ..., k-1, k, ..., k, k-1, ..., x+1, x, x, x-1, ..., 2, 1 
// 
// there are at least one k in the sequence, and the x can be 1 to k-1
// compute the sum of the sequence leads to the answer

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

