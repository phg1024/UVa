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

void process( const string& s )
{
    int count = 0;
    int i = 0;
    while( i < s.size() )
    {
        while( s[i] >= '1' && s[i] <= '9' )
        {
            count += (s[i] - '0');
            i++;
        }

        char c = s[i++];
        for(int j=0;j<count;j++)
        {
            putchar( (c == 'b')?' ':c );
        }
        count = 0;

        if( s[i] == '!' ){ putchar('\n'); i++; }
    }
    putchar('\n');
}

int main()
{
    while( true )
    {
        string buf;
        while( true )
        {
            if( !getline(cin, buf) )
                return 0;

            if( buf.empty() ) break;

            process( buf );
        }

        cout << endl;
    }
    return 0;
}
