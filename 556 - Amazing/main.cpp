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

static const int MAXW = 16; 
static const int MAXH = 16;

int move[4][2] = 
{
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
};

char maze[MAXH][MAXW];
int f[MAXH][MAXW]; 
int h, w;

struct Robot
{
    Robot(int px, int py):x(px), y(py), dir(0){}

    void advance()
    {
        // turn left until advance is possible
        while( true )
        {
            int nx = x + move[dir][0];
            int ny = y + move[dir][1];

            if( maze[ny][nx] == '0' )
            {
                x = nx;
                y = ny;
                f[y][x]++;

                int rightDir = (dir + 3) & 0x3;
                if( maze[ny + move[rightDir][1]][nx + move[rightDir][0]] == '0' )
                {
                    // turn right
                    dir += 3;
					dir &= 0x3;
                }

				
                break;
            }
            else
            {
                // turn left
                dir ++;
				dir &= 0x3;
            }
        }
    }

    int x, y;
    int dir;
};

void traverse(char maze[][MAXW], int counter[])
{
    // init counter map
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
        {
            if( maze[i][j] == '0' ) f[i][j] = 0;
            else f[i][j] = -1;
        }

    // set boundaries
    for(int x=0;x<=w+1;x++)
    {
        maze[0][x] = '1';
        maze[h+1][x] = '1';
    }

    for(int y=0;y<=h+1;y++)
    {
        maze[y][0] = '1';
        maze[y][w+1] = '1';
    }

    // init robot
    Robot r(1, h);
    while( true )
    {
        //cout << r.x << ", " << r.y << " # " << r.dir << "@" << r.rightWall << endl;
        r.advance();

        if( r.x == 1 && r.y == h )
            break;
    } 

    // count the blocks
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {
            //cout << f[i][j] << '\t';
            if( f[i][j] >= 0 ) counter[f[i][j]]++;
        }
        //cout << endl;
    }

}

int main()
{
    while( true )
    {
        int counter[5] = {0, 0, 0, 0, 0};
        scanf("%d %d", &h, &w);
        if( h == 0 && w == 0 ) break;

        for(int i=1;i<=h;i++)
        {
            scanf("%s", maze[i]+1);
        }

        traverse( maze, counter );

        for(int i=0;i<5;i++)
            printf("%3d", counter[i]);
        putchar('\n');
    }
    return 0;
}
