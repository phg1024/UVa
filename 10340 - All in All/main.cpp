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

static const int MAXL = 2000010;

bool issub(char s[], char t[])
{
    int Ls = strlen(s);
    int Lt = strlen(t);

    for(int i=0, pos=0;i<Ls;i++)
    {
        char c = s[i];
        while( t[pos] != c )
        {
            pos++;
            if( pos >= Lt ) return false;
        }
        pos++;
    }

    return true;
}

int main()
{
    char s[MAXL], t[MAXL];
    while( scanf("%s %s", s, t) != EOF )
    {
        printf("%s\n", (issub(s, t)?"Yes":"No"));
    }
    return 0;
}
