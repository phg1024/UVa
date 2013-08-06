#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <set>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

struct state_t
{
    state_t():key(0),depth(0){}

    bool operator==(const state_t& s) const
    {
        return key == s.key;
    }

    int key;
    int depth;
};

state_t getState()
{
    state_t s;
    for(int i=0;i<4;i++)
    {
        s.key *= 10;
        int val;
        scanf("%d", &val);
        s.key += val;
    }
    return s;
}

inline int value( char str[] )
{
    return str[0] * 1000 + str[1] * 100 + str[2] * 10 + str[3];
}

void getCandidates(state_t state, state_t v[])
{
    char str[5];
    str[0] = state.key / 1000;
    state.key %= 1000;
    str[1] = state.key / 100;
    state.key %= 100; 
    str[2] = state.key / 10;
    state.key %= 10;
    str[3] = state.key;

    char buf[4];
    buf[0] = str[0]; buf[1] = str[1]; buf[2] = str[2]; buf[3] = str[3];

    for(int i=0, j=4;i<4;i++, j++)
    {
        v[i] = v[j] = state;

        buf[i] = str[i] - 1;
        if( buf[i] < 0 ) buf[i] = 9;
        v[i].depth = state.depth + 1;
        v[i].key = value( buf ) ;

        buf[i] = str[i] + 1;
        if( buf[i] > 9 ) buf[i] = 0;
        v[j].depth = state.depth + 1;
        v[j].key = value( buf ) ;

        buf[i] = str[i];
    }
}

int solve(state_t state, state_t target, char visited[]) 
{
    state_t children[8];

    int front = 0, back = 1;
    static const int QSIZE = 6000;
    state_t Q[QSIZE];

    Q[0] = state ;

    while( front != back )
    {
        state_t& cur = Q[front++];
        if( front >= QSIZE ) front = 0;

        if( visited[ cur.key ] == 2 ) continue;

        if( cur == target )
        {
            return cur.depth;
        }

        if( visited[cur.key] == 0 )
        {
            visited[cur.key] = 1; 
            getCandidates( cur, children );
            for(int i=0;i<8;i++)
            {
                if( visited[ children[i].key ] ) continue;
                Q[back++] = children[i];
                if( back >= QSIZE ) back = 0;
            }
        }
    }

    return -1;
}

int main()
{
    int ncases;
    scanf("%d", &ncases);

    while( ncases-- > 0 )
    {
        state_t state = getState();
        state_t target = getState();

        char visited[10000] = {0};
        int nforbids;
        scanf("%d", &nforbids);
        for(int i=0;i<nforbids;i++)
        {
            state_t fs = getState();
            visited[ fs.key ] = 2;
        }

        printf("%d\n", solve(state, target, visited));
    }
    return 0;
}
