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
    int denom[11] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

    int64_t count[30001] = {0};
    count[0] = 1;
    for(int i=0;i<11;i++)
    {
        for(int j=denom[i];j<30001;j++)
        {
            count[j] += count[j-denom[i]];
        }
    }

    int v1, v2;
    while( scanf("%d.%d", &v1, &v2) != EOF )
    {
        int v = v1 * 100 + v2;
        if( v == 0 ) break;
        if( v2 < 10 )
            printf("%3d.0%d%17lld\n", v1, v2, count[v]);
        else
            printf("%3d.%2d%17lld\n", v1, v2, count[v]);
    }
    return 0;
}

