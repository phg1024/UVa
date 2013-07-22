#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

typedef pair<char, int> freq_t;
bool comp(const freq_t& f1, const freq_t& f2)
{
    if( f1.second > f2.second ) return true;
    else if( f1.second == f2.second )
        return f1.first < f2.first;
    else return false;
}

int main()
{
    int n;
    scanf("%d\n",&n);

    int freq[128] = {0};

    while( n-- > 0 )
    {
        char buf[256] = {0};
        fgets(buf, 256, stdin);

        int L = strlen(buf);
        for(int i=0;i<L;i++)
            freq[ toupper(buf[i])]++;

    }

    freq_t f[26];
    for(char c='A', i=0;c<='Z';c++,i++)
    {
        f[i].first = c;
        f[i].second = freq[c];
    }

    std::sort(f, f+26, comp);

    int idx=0;
    while( f[idx].second > 0 )
    {
        printf("%c %d\n", f[idx].first, f[idx].second);
        idx++;
    }
 
    return 0;
}
