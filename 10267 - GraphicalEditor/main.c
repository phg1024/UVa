#include "stdio.h"

char I[252][252];
char mask[252][252];
int m, n;

void markRegion(int y, int x, char c)
{
    if( mask[y][x] == 1 ) return;
    if( x < 1 || x > m ) return;
    if( y < 1 || y > n ) return;
    mask[y][x] = 1;

    if(y-1>0 && I[y-1][x] == c) markRegion(y-1, x, c);
    if(y+1<=n && I[y+1][x] == c) markRegion(y+1, x, c);
    if(x-1>0 && I[y][x-1] == c) markRegion(y, x-1, c);
    if(x+1<=m && I[y][x+1] == c) markRegion(y, x+1, c);
}

int main(){
    char op;
    int i, j;
    while( (scanf("%c", &op)) == 1 ){
        if( op == 'X' ) break; 
        if( op == '\n' || op == ' ' ) continue;

        switch( op )
        {
            case 'I':{
                scanf("%d %d", &m, &n);
                for(i=1;i<=n;i++)
                    for(j=1;j<=m;j++)
                        I[i][j] = 'O';
                break;}
            case 'C':{
                for(i=1;i<=n;i++)
                    for(j=1;j<=m;j++)
                        I[i][j] = 'O';
                break;}
            case 'L':{
                int x, y;
                char c;
                scanf("%d %d %c", &x, &y, &c);
                I[y][x] = c;
                break;}
            case 'V':{
                int x, y1, y2;
                char c;
                scanf("%d %d %d %c", &x, &y1, &y2, &c);
                for(i=y1;i<=y2;i++)
                    I[i][x] = c;
                break;}
            case 'H':{
                int x1, x2, y;
                char c;
                scanf("%d %d %d %c", &x1, &x2, &y, &c);
                for(i=x1;i<=x2;i++)
                    I[y][i] = c;
                break;}
            case 'K':{
                int x1, y1, x2, y2;
                char c;
                scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
                
                for(i=y1;i<=y2;i++)
                    for(j=x1;j<=x2;j++)
                        I[i][j] = c;
                break;}
            case 'F':{
                int x, y;
                char c;
                scanf("%d %d %c", &x, &y, &c);
                for(i=1;i<=n;i++)
                    for(j=1;j<=m;j++)
                        mask[i][j] = 0;
                markRegion(y, x, I[y][x]);
                for(i=1;i<=n;i++)
                    for(j=1;j<=m;j++)
                        if( mask[i][j] == 1 ) I[i][j] = c;               
                break;}
            case 'S':{
                char name[16];
                scanf("%s", name);
                printf("%s\n", name);
                for(i=1;i<=n;i++)
                {
                    for(j=1;j<=m;j++)
                        putchar(I[i][j]);
                    putchar('\n');
                }
                break;}
            default:{
                char buf[128];
                int count;
                getline(buf, &count, stdin);
                break;}
        }
    }
}
