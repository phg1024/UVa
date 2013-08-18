#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <limits>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

int solve(int n, int k)
{
    int total = 0;
    while( n >= k )
    {
	int r = n % k;
	int q = n / k;
	total += (n - r);
	n = r + q;
    }

    total += n;

    return total;
}

int main()
{
    int n, k;
    while( scanf("%d %d", &n, &k) != EOF )
    {
	printf("%d\n", solve(n, k));
    }

    return 0;

}
