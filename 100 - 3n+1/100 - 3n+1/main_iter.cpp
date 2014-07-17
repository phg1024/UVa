#include "stdio.h"
#include <stack>
using namespace std;

#define min(a, b) ((a) <= (b) ? (a) : (b))  
#define max(a, b) ((a) >= (b) ? (a) : (b)) 

#define SIZE 131072
int count[SIZE];
stack<unsigned int> S;

int length(unsigned int n) {
	int res;
	while( true ) {
		if( n < SIZE && count[n] > 0 ) {
			// update the numbers in the stack
			int L = count[n];
			while( !S.empty() ) {
				unsigned int idx = S.top();
				S.pop();
				if( idx < SIZE && count[idx] == 0 ) count[idx] = ++L;
				else ++L;
			}
			return L;
		}
		else {
			S.push(n);
			if( (n & 0x1) == 0 ) n >>= 1;
			else n += (n << 1) + 1;
		}
	}
}

int main()
{
	count[1] = 1;
	int a, b, start, end, i;
	int L, maxL;
	while( scanf("%d %d", &a, &b) == 2 ){
		start = min(a, b);
		end = max(a, b);
		maxL = 0;
		for(i=start;i<=end;i++){
			L = length( i );
			maxL = max(maxL, L);
		}
		printf("%d %d %d\n", a, b, maxL);
	}
	return 0;
}
