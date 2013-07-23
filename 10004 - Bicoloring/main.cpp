#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXNODES = 200;

int main()
{
    while( true )
    {
        int n, ne;
        scanf("%d", &n);
        if( n == 0 ) break;

        scanf("%d", &ne);
        vector<int> E[MAXNODES];
        char color[MAXNODES];
        memset(color, 0, sizeof(char)*MAXNODES);

        for(int i=0;i<ne;i++)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            E[a].push_back(b);
            E[b].push_back(a);
        }

        queue<int> Q;
        Q.push(0);
        color[0] = 'b';

        bool flag = true;

        while(!Q.empty())
        {
            int cur = Q.front();
            Q.pop();

            char c = (color[cur] == 'b')?'w':'b';

            for(int i=0;i<E[cur].size();i++)
            {
                int idx = E[cur][i];
                if( color[idx] == 0 )
                {
                    // push into queue
                    color[idx] = c;
                    Q.push(idx);
                }
                else
                {
                    if( color[idx] == color[cur] )
                    {
                        flag = false;
                        break;
                    } 
                }
            }
        }

        if( flag ) cout << "BICOLORABLE." << endl;
        else cout << "NOT BICOLORABLE." << endl;
    }
    return 0;
}
