#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{
	int ncases;
	scanf("%d\n", &ncases);
	
	char code[] = "OIZEASGTBP";
	
	while( true )
	{
		char buf[128] = {0};
		while( gets(buf) )
		{
			int L = strlen( buf );
			if( L == 0 ) break;
			for(int i=0;i<L;i++)
			{
				int k = buf[i] - '0';
				if( k >= 0 && k < 10 )
					buf[i] = code[k];
			}
			printf("%s\n", buf);
		}
		if( --ncases>0 ) putchar('\n');
		else break;
	}
	
	return 0;
}