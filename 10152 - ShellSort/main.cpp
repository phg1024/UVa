#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int ncases;
    scanf("%d\n", &ncases);
	
    char src[256][128] = {0};
    char dst[256][128] = {0};

	while( ncases-- > 0 )
	{
		int n;
        scanf("%d\n", &n);


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
