#include "stdio.h"

unsigned char field[102][102];
unsigned char mine[102][102];

int main(){
	int m, n;
	int i, j;
	int id=1;
	int flag = 0;
	while(scanf("%d %d", &m, &n)){
		if( m == 0 && n == 0 ) break;
		for(i=1;i<=m;i++){
			scanf("%s", &(mine[i][0])+1);
		}
		
		for(i=1;i<=m;i++){
			for(j=1;j<=n;j++){
				field[i][j] = 0;
			}
		}

		for(i=1;i<=m;i++){
			for(j=1;j<=n;j++){
				if( mine[i][j] == '*' ){
					field[i+1][j]++;
					field[i-1][j]++;
					field[i][j-1]++;
					field[i][j+1]++;
					
					field[i-1][j+1]++;
					field[i+1][j-1]++;
					field[i-1][j-1]++;
					field[i+1][j+1]++;
				}
			}
		}
		
		if( flag == 1 )
			printf("\n");
		flag = 1;
		printf("Field #%d:\n", id++);
		for(i=1;i<=m;i++){
			for(j=1;j<=n;j++){
				if( mine[i][j] == '*' ){
					putchar('*');
				}
				else putchar(field[i][j] + '0');
			}
			putchar('\n');
		}
	}
	
	return 0;
}