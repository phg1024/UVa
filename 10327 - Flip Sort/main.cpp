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

/// @note just count the number of inversions

static const int MAXN = 1024;

int merge_and_count(int l, int m, int r, int nums[])
{
	int count = 0;
	int A[MAXN] = {0}, B[MAXN] = {0};
	// copy into A and B
	int idx = 0;
	for(int i=l;i<=m;i++)
		A[idx++] = nums[i];
	idx = 0;
	for(int i=m+1;i<=r;i++)
		B[idx++] = nums[i];

	int i = 0, j = 0;
	int pos = l; 
	while( i <= (m - l) && j <= (r - m - 1) )
	{
		if( A[i] <= B[j] )
		{
			nums[pos++] = A[i++];
		}
		else
		{
			nums[pos++] = B[j++];
			count += (m - l + 1 - i);
		}
	}

	// copy the rest of either A or B back to the string
	while( i <= (m - l) )
		nums[pos++] = A[i++];

	while( j <= (r - m - 1) )
		nums[pos++] = B[j++];

	return count;
}

int sort_and_count(int l, int r, int nums[])
{
	if( l >= r )
		return 0;
	else
	{
		int m = (l+r)/2; 
		int rl = sort_and_count(l, m, nums);
		int rr = sort_and_count(m+1, r, nums);
		int rm = merge_and_count(l, m, r, nums);
		return rl + rr + rm;
	}
}


int main()
{
	int n;
	while( scanf("%d", &n) != EOF )
	{
		int nums[MAXN];
		for(int i=0;i<n;i++)
			scanf("%d", &nums[i]);

		printf("Minimum exchange operations : %d\n", sort_and_count(0, n-1, nums));
	}
	return 0;
}
