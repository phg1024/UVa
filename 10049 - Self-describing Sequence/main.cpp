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
#include <cassert>
using namespace std;

// long enough sequence of n to generate a 2000000000 length sequence
const static unsigned int L = 673368;
const static int MAXN = 4807;

int fn[L] = {0};

// sn(k) = sum_{i=1}{k} fn(i)
// sn(k) is the length of the sequence ending with k
unsigned int sn[L] = {0};
	
void init()
{
	sn[0] = 0;
	fn[1] = 1, fn[2] = 2;
	unsigned int pos = 2;

	for(int i=2;i<MAXN;i++)
	{
		for(int j=0;j<fn[i];j++)
		{
			fn[pos] = i;
			pos++;
		}
	}

	for(int i=1;i<L;i++)
	{
		sn[i] = sn[i-1] + fn[i];
	}
}

// binary search to find the containing interval
int findFn(unsigned int n)
{
	int high = L - 1, low = 1;
	int mid = (high + low) / 2;
	
	while( high > low )
	{
		if( sn[mid] == n )
			return mid;
		if( sn[mid] < n )
			low = mid + 1;
		else
			high = mid;
		mid = (high + low) / 2;
	}

	return mid;
}

int main(){
	init();
	
	unsigned int n;
	while( true )
	{
		scanf("%u", &n);
		if( n == 0 ) break;
		printf("%d\n", findFn(n));
	}

    return 0;
}

