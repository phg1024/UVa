#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

int findExp_fast(unsigned int num)
{
    const double base = 3.321928094887362181708567732130177319049835205078125;
	double lognum = log2(num);
	double lognum1 = log2(num+1);
	int L = floor(log10(num)) + 1;
	
    int k = L + 1;
    while( true )
    {
        double diff = k * base;
        unsigned int a = floor( lognum + diff ); 
        unsigned int b = floor( lognum1 + diff ); 
        if( b > a )
            return b;
        k++;
    }
}

int main()
{
    unsigned int num;
	while (scanf("%u", &num) != EOF) {
		int idx = findExp_fast(num);
		if (idx) {
			printf("%d\n", idx);
		} else {
			printf("no power of 2\n");
		}
	}
	return 0;
}
