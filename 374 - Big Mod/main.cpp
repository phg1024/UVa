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

int solve( int B, int P, int M )
{
    if( P == 0 ) return 1;
    if( P == 1 ) return B % M;

    if( P & 0x1 )
    {
        int r = solve( B, P/2, M );
        return ((r * r) % M * (B % M)) % M;
    }
    else
    {
        int r = solve( B, P/2, M );
        return (r * r) % M; 
    }
}

int main(){

    int B, P, M;

    while( scanf("%d %d %d", &B, &P, &M) != EOF )
    {
        printf("%d\n", solve( B, P, M ));
    }

    return 0;
}

