#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

static const int MAXL = 130;

int main()
{
	int n;
	scanf("%d\n", &n);

	while( n-- > 0 )
	{
		char S[MAXL] = {0};
        int pos = 0;
        char c;

        while( (c = getchar()) != '\n' )
        {
            if( (c == ')' && S[pos-1] == '(') || (c == ']' && S[pos-1] == '[') ) { pos--; continue; }
            S[pos++] = c;
        }

		printf("%s\n", (pos==0?"Yes":"No"));
	}
	return 0;
}
