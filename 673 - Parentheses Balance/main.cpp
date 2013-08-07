#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

static const int MAXL = 130;
bool isvalid( char str[], int L )
{
	if( L & 0x1 ) return false;
	if( L == 0 ) return true;
	char s[MAXL] = {0};
	int i=0, j=0;
	while( i < L )
	{
		if( i < L - 1 )
		{
			if( str[i] == '(' && str[i+1] == ')' ){ i+=2; continue;}		
			if( str[i] == '[' && str[i+1] == ']' ){ i+=2; continue;}
		}
		s[j++] = str[i++];
	}

	int Ls = strlen( s );
	if( Ls == L ) return false;
	return isvalid( s, Ls );
}

int main()
{
	int n;
	scanf("%d\n", &n);

	while( n-- > 0 )
	{
		char str[MAXL] = {0};
		fgets(str, MAXL, stdin);
		int L = strlen(str);
		if( str[L-1] == '\n' ) str[--L] = '\0';
		printf("%s\n", (isvalid( str, L )?"Yes":"No"));
	}
	return 0;
}