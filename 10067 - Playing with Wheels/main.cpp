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

inline int str2key( char str[] )
{
    return str[0] * 1000 + str[1] * 100 + str[2] * 10 + str[3];
}

inline void key2str( int key, char str[] )
{
    str[0] = key / 1000;
    key %= 1000;
    str[1] = key / 100;
    key %= 100; 
    str[2] = key / 10;
    key %= 10;
    str[3] = key;
}

void getCandidates(state_t state, state_t v[])
{
    char str[5];
    key2str(state.key, str);
    char buf[4];
    buf[0] = str[0]; buf[1] = str[1]; buf[2] = str[2]; buf[3] = str[3];

    for(int i=0, j=4;i<4;i++, j++)
    {
        v[i] = v[j] = state;

        buf[i] = str[i] - 1;
        if( buf[i] < 0 ) buf[i] = 9;
        v[i].depth = state.depth + 1;
        v[i].key = str2key( buf ) ;

        buf[i] = str[i] + 1;
        if( buf[i] > 9 ) buf[i] = 0;
        v[j].depth = state.depth + 1;
        v[j].key = str2key( buf ) ;

        buf[i] = str[i];
    }
}

int solve(state_t state, state_t target, char visited[]) 
{
    state_t children[8];

    int front = 0, back = 1;
    // large enough pool
    static const int QSIZE = 6000;
    state_t Q[QSIZE];

    Q[0] = state ;

    // unsafe queue, possible overwrite of data
    while( front != back )
    {
        state_t& cur = Q[front++];
        if( front >= QSIZE ) front = 0;

        if( visited[ cur.key ] == 2 ) continue;

        if( cur.key == target.key )
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
