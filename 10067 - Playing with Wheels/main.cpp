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
    state_t():key(0),depth(0){
        memset(str, 0, sizeof(char)*4);
    }

    state_t(const state_t& s):key(s.key),depth(s.depth)
    {
        memcpy(str, s.str, sizeof(char)*4);
    }

    state_t& operator=(const state_t& s)
    {
        key = s.key;
        depth = s.depth;
        memcpy(str, s.str, sizeof(char)*4);
        return (*this);
    }

    bool operator==(const state_t& s) const
    {
        return key == s.key;
    }

    bool operator<(const state_t& s) const
    {
        return key < s.key;
    }

    void update()
    {
        key = 0;
        for(int i=0;i<4;i++)
        {
            key = key * 10;
            key += str[i];
        }
    }

    char str[4];
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
        s.str[i] = val;
    }
    return s;
}

void getCandidates(state_t state, state_t v[])
{
    for(int i=0;i<4;i++)
    {
        v[i] = v[i+4] = state;
        state_t& l = v[i];
        l.str[i] = l.str[i] - 1;
        l.depth = state.depth + 1;
        if( l.str[i] < 0 ) l.str[i] = 9;
        l.update();

        state_t& r = v[i+4];
        r.str[i] = r.str[i] + 1;
        r.depth = state.depth + 1;
        if( r.str[i] > 9 ) r.str[i] = 0;
        r.update();
    }
}

int solve(state_t state, state_t target, const set<state_t>& forbidStates)
{
    char visited[10000] = {0};
    state_t children[8];

    for(set<state_t>::iterator it = forbidStates.begin();
        it != forbidStates.end();
        it++)
        visited[(*it).key] = 2;

    queue<state_t> Q;

    Q.push( state );

    while( !Q.empty() )
    {
        state_t cur = Q.front();
        Q.pop();

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
                Q.push( children[i] );
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

        int nforbids;
        scanf("%d", &nforbids);
        set<state_t> forbidStates;
        for(int i=0;i<nforbids;i++)
        {
            state_t fs = getState();
            forbidStates.insert(fs);
        }

        printf("%d\n", solve(state, target, forbidStates));
    }
    return 0;
}
