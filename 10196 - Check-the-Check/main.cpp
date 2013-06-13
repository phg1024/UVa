#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cctype>
using namespace std;

enum Pos{
    X = 0,
    Y = 1
};

enum Color{
	Black = 0,
	White = 1
};

int dir[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
};

int knightPos[8][2] = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}
};

inline bool onboard(int x, int y){
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

bool check( char board[8][8], int kingPos[2], Color col )
{
    char c;
    for(int i=0;i<8;i++){
        int x = kingPos[X], y = kingPos[Y];
		c = board[x][y];
        while(true)
        {
            int newx = x + dir[i][X];
            int newy = y + dir[i][Y];
            if( !onboard(newx, newy) ){
                break;
            }
            x = newx, y = newy;
			c = board[x][y];
			if( c != '.' ) break;
		}
		
		if( islower(c) && col == Black ) continue;
		if( isupper(c) && col == White ) continue;
                
        int dx = x - kingPos[X];
        int dy = y - kingPos[Y];
		
        switch( c )
        {
			case 'b':
            case 'B':
            {
                if( abs(dx) == abs(dy) ) return true;
				break;
            }
			case 'r':
            case 'R':
            {
                if( (dx == 0) || (dy == 0) ) return true;
				break;
            }
			case 'q':
            case 'Q':
            {
                if( (dx == 0) || (dy == 0) || ( abs(dx) == abs(dy) ) ) return true;
				break;
            }
            case 'P':
            {
                if( (dx == 1) && (abs(dy) == 1)) return true;
				break;
            }
			case 'p':
            {
                if( (dx == -1) && (abs(dy) == 1)) return true;
				break;
            }			
            default:
                break;
        }
    }
    
    // check for knight
	char knightC;
	if( col == Black )
	{
		knightC = 'N';
	}
	else
	{
		knightC = 'n';
	}
		
    for(int i=0;i<8;i++)
    {
        int x = kingPos[X] + knightPos[i][X];
        int y = kingPos[Y] + knightPos[i][Y];
        if( onboard(x, y) ){
            if( board[x][y] == knightC ) return true;
        }
    }
    
    return false;
}

int checkboard( char board[8][8], int king[2][2] ){
    if( check( board, king[0], Black ) ) return Black;
    if( check( board, king[1], White ) ) return White;
    return 2;
}

int main(){
    int gameId = 1;
    
    char board[8][8];
    int king[2][2];
    
    while( true )
    {
        bool isValid = false;
		string buf;
        for(int i=0;i<8;i++)
        {
			cin >> buf;
            for(int j=0;j<8;j++)
            {
                char c = buf[j];
                isValid |= (c!='.');
                board[i][j] = c;
                switch( c )
                {
                    case 'k':
                    {
                        king[0][X] = i;
                        king[0][Y] = j;
                        break;
                    }
                    case 'K':
                    {
                        king[1][X] = i;
                        king[1][Y] = j;
                        break;
                    }
                }
            }
        }
		cin.ignore();
		if( !isValid ) break;
        
        int checkstate = checkboard( board, king );
		//print( board );
        
        cout << "Game #" << gameId << ": ";
        gameId++;
        switch( checkstate )
        {
            case 0:
            {
                cout << "black king is in check." << endl;
                break;
            }
            case 1:
            {
                cout << "white king is in check." << endl;
                break;
            }
            case 2:
            {
                cout << "no king is in check." << endl;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
