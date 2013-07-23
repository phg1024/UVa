#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXN = 11;
static const int MAXK = 5;

struct Combination
{
    typedef vector<int> comb_t;

    Combination(int N, int R):
        completed(N < 1 || R > N),
        generated(0),
        n(N), r(R)
    {
        for(int c=0;c<R;c++)
            curr.push_back(c);
    }

    comb_t next()
    {
        comb_t ret = curr;

        completed = true;
        for(int i=r-1;i>=0;i--)
        {
            if( curr[i] < n - r + i + 1 + 1 )
            {
                int j = curr[i] + 1;
                while( i <= r )
                    curr[i++] = j++;
                completed = false;
                generated++;
                break;
            }
        }

        return ret;
    }

    comb_t curr;
    bool completed;
    int generated;
    int n, r;
};

set<string> mutate(const string& seq, int K)
{
    set<string> dna;

    int N = seq.size();

    // mutate a seq by K pos
    int pointers[MAXK];

    Combination cs(N, K);

    while( !cs.completed )
    {
        Combination::comb_t c = cs.next();
        vector<string> s, t;
        s.push_back(seq);
        for(int i=0;i<c.size();i++)
        {
            for(int j=0;j<s.size();j++)
            {
                s[j][c[i]] = 'A';
                t.push_back(s[j]);
                s[j][c[i]] = 'G';
                t.push_back(s[j]);
                s[j][c[i]] = 'C';
                t.push_back(s[j]);
                s[j][c[i]] = 'T';
                t.push_back(s[j]);
            }
            s = t;
            t.clear();
        }
        dna.insert(s.begin(), s.end());
    }


    return dna;
}

int main()
{
    int T;
    scanf("%d", &T);

    while( T-- > 0 )
    {
        string seq;
        int N, K;
        scanf("%d %d", &N, &K);
        cin >> seq;
		
        // i th mutation
		set<string> dna = mutate(seq, K);
		
        printf("%d\n", (int)dna.size());
		for(set<string>::iterator sit=dna.begin();
			sit!=dna.end();
			sit++)
		{
			printf("%s\n", (*sit).c_str());
		}
    }

    return 0;
}
