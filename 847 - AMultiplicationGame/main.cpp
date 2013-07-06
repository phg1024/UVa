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
    unsigned int n;
    while( scanf("%u", &n) != EOF )
    {
        unsigned int p = 1;
        unsigned int round = 0;

        while( p < n )
        {
            round++;
            if( round & 0x1 )
            {
                p *= 9;
            }
            else
            {
                p *= 2;
            }
        }
        if( round & 0x1 )
            printf("Stan wins.\n");
        else
            printf("Ollie wins.\n");
    }
    return 0;
}

