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

static const int MAXW = 32;
static const int MAXL = MAXW*MAXW + 3*MAXW - 2;
int main()
{
    int n;
    scanf("%d", &n);
    while( n )
    {
        int w, f;
        scanf("%d %d", &w, &f);

		char buf[MAXL] = {0};
		
		// fill the buffer
		int m = w * 2;
		int diff = 1;
		int pos = 0;
		char* pbuf=&(buf[0]);
        for(int j=1, wj=1;j<m;j++)
        {
			std::fill(pbuf, pbuf+wj, '0'+wj);
			pbuf[wj] = '\n';
			pbuf += (wj+1);
			if( wj == w ) diff = -1;
			wj += diff;
        }

        while( f )
        {
			printf("%s", buf);
			if( --f ) putchar('\n');
			else break;
        }
        if( --n > 0 ) putchar('\n');
    }
    return 0;
}
