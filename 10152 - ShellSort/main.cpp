#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
	int ncases;
    scanf("%d\n", &ncases);
	
	while( ncases-- > 0 )
	{
		int n;
        scanf("%d\n", &n);

        char src[200][128] = {0};
        char dst[200][128] = {0};

		for(int i=0;i<n;i++)
		{
            fgets(src[i], 128, stdin);
		}
		
		for(int i=0;i<n;i++)
		{
            fgets(dst[i], 128, stdin);
		}
		
        int i, j;
		for(i=n-1, j=n-1;i>=0;i--)
		{
            if( strcmp(dst[j], src[i]) == 0 ) 
                j--;
		}

        while( j>=0 )
            printf("%s", dst[j--]);
		
        putchar('\n');
	}
}
