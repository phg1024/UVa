#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// compare 2^(2^x) with n!
// boils down to compare 2^x with sum_{i=1}^n log_2(i)

int main()
{
    double logsum = 0;
    // all the benchmark scores
    vector<int> pos(23);
    int i=1, w=2, cutoff_w = 4;
    while( true ) {
        logsum += log2(double(i));
        if( logsum >= cutoff_w ){ pos[w] = i+1; ++w; cutoff_w *= 2; }
        if( w>22 ) break;
        ++i;
    };
    
    int year;
    while( true ) {
        scanf("%d", &year);
        if( year == 0 ) break;
        year -= 1960;
        year /= 10;
        // the power
        int p = year + 2;
        printf("%d\n", pos[p]-2);
    }
    return 0;
}
