#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int main()
{
    int ncases;
    scanf("%d\n", &ncases);

    int idx = 0;
    while( (++idx) <= ncases )
    {
        string buf;
        getline(cin, buf);
        stringstream ss;
        ss.str(buf);

        int v;
        int k = 0;
        while( ss >> v )
        {
            if ( v > k )  k = v;
        }

        printf("Case %d: %d\n", idx, k);
    }
    return 0;
}
