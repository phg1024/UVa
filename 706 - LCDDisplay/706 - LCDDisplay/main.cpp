#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char dmap[10][7] = {
	{1, 1, 1, 0, 1, 1, 1},
	{0, 0, 1, 0, 0, 1, 0},
	{1, 0, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 0, 1, 1},
	{0, 1, 1, 1, 0, 1, 0},
	{1, 1, 0, 1, 0, 1, 1},
	{1, 1, 0, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1}
};

int main(){
	int n;
	long num;
	char buf[9];

	int i, j, k;
	int cols, rows, ccount;
	while( scanf("%d %d", &n, &num) == 2 ){
		if( n == 0 && num == 0 ) break;
		sprintf (buf, "%d", num);
		ccount = strlen(buf);
		cols = (n + 2) * ccount;
		rows = n << 1 + 3;

		for(i=0;i<ccount;i++){
			int flag = dmap[buf[i]-'0'][0];
			putchar(' ');
			for(j=0;j<n;j++)
				putchar(((flag==0)?' ':'-'));
			putchar(' ');

			if( i!=ccount - 1 )
				putchar(' ');
		}
		putchar('\n');

		for(k=0;k<n;k++){
			for(i=0;i<ccount;i++){
				int flag1 = dmap[buf[i]-'0'][1];
				int flag2 = dmap[buf[i]-'0'][2];
				putchar(((flag1==0)?' ':'|'));
				for(j=0;j<n;j++)
					putchar(' ');
				putchar(((flag2==0)?' ':'|'));
				if( i!=ccount - 1)
					putchar(' ');
			}
			putchar('\n');
		}

		for(i=0;i<ccount;i++){
			int flag = dmap[buf[i]-'0'][3];
			putchar(' ');
			for(j=0;j<n;j++)
				putchar(((flag==0)?' ':'-'));
			putchar(' ');
			if( i!=ccount - 1)
			putchar(' ');
		}
		putchar('\n');

		for(k=0;k<n;k++){
			for(i=0;i<ccount;i++){
				int flag1 = dmap[buf[i]-'0'][4];
				int flag2 = dmap[buf[i]-'0'][5];
				putchar(((flag1==0)?' ':'|'));
				for(j=0;j<n;j++)
					putchar(' ');
				putchar(((flag2==0)?' ':'|'));
				if( i!=ccount - 1)
					putchar(' ');
			}
			putchar('\n');
		}

		for(i=0;i<ccount;i++){
			int flag = dmap[buf[i]-'0'][6];
			putchar(' ');
			for(j=0;j<n;j++)
				putchar(((flag==0)?' ':'-'));
			putchar(' ');
			if( i!=ccount - 1)
				putchar(' ');
		}
		putchar('\n');
		putchar('\n');
	}

	return 0;
}