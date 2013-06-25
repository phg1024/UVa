#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

inline bool match(char* s1, char* s2, int len)
{
	//cout << "matching " << s1 << " and " << s2 << endl;
	for(int i=0;i<len;i++)
		if( s1[i] != s2[i] ) return false;
	return true;
}

inline bool rmatch(char* s1, char* s2, int len)
{
	//cout << "matching " << s1 << " and " << s2 << endl;
	for(int i=0;i<len;i++)
		if( s1[i] != s2[len-1-i] ) return false;
	return true;
}

struct Location
{
    Location():r(-1), c(-1){}
    Location(int row, int column):r(row), c(column){}
    bool operator<(const Location& l)
    {
        if( r < l.r ) return true;
        else if( r == l.r )
        {
            return c < l.c;
        }
        else return false;
    }
    int r, c;
};

Location findword(char grid[50][50], char gridT[50][50], int rows, int cols, char word[])
{
	int l = strlen( word );

    Location loc(rows+1, cols+1);

	// search by row
	for(int j=0;j<rows;j++)
	{
		// regular order
		for(int i=0;i<=cols-l;i++)
		{
			if( match( word, grid[j]+i, l ) ) 
            {
                Location L(j+1, i+1);
                if( L < loc ) loc = L;
            }

			if( rmatch( word, grid[j]+i, l ) ) 
            {
                Location L(j+1, i+l);
                if( L < loc ) loc = L;
            }
		}
	}

	// search by column
	for(int j=0;j<cols;j++)
	{
		// regular order
		for(int i=0;i<=rows-l;i++)
		{
			if( match( word, gridT[j]+i, l ) ) 
            {
				// need to swap x and y
                Location L(i+1, j+1);
                if( L < loc ) loc = L;
            }

			if( rmatch( word, gridT[j]+i, l ) ) 
            {
				// need to swap x and y
                Location L(i+l, j+1);
                if( L < loc ) loc = L;
            }
		}
	}

	// search by diagonal
	// rows x cols grid
	int diagSize = (cols > rows)?cols:rows;
    for(int j=0;j<rows;j++)
    {
        if( j + l > rows ) break;
        for(int i=0;i<cols;i++)
        {
            if( i + l > cols ) break; 

            // diagonal string starting from (j, i)
            bool flag = true;
            for(int k=0;k<l;k++)
            {
                if( grid[j+k][i+k] != word[k] )
                {
                    flag = false;
                    break;
                }
            }
            if( flag ) {
                Location L(j+1, i+1);
                if( L < loc ) loc = L;
            }
            
            // diagonal string starting from (j, col-i)
            flag = true;
            for(int k=0;k<l;k++)
            {
                if( grid[j+k][cols-1-i-k] != word[k] )
                {
                    flag = false;
                    break;
                }
            }
            if( flag ) {
                Location L(j+1, cols-i);
                if( L < loc ) loc = L;
            }
            

            // diagonal string starting from (row-j, i)
            flag = true;
            for(int k=0;k<l;k++)
            {
                if( grid[rows-1-j-k][i+k] != word[k] )
                {
                    flag = false;
                    break;
                }
            }
            if( flag ) {
                Location L(rows-j, i+1);
                if( L < loc ) loc = L;
            }
             
            
            // diagonal string starting from (row-j, col-i)
            flag = true;
            for(int k=0;k<l;k++)
            {
                if( grid[rows-1-j-k][cols-1-i-k] != word[k] )
                {
                    flag = false;
                    break;
                }
            }
            if( flag ) {
                Location L(rows-j, cols-i);
                if( L < loc ) loc = L;
            }
             
        }
    }

	return loc;
}

int main()
{
	int ncases;
	cin >> ncases;
	cin.ignore();
	string dummy;

	int rows, cols;
	int nwords;
	for(int i=0;i<ncases;i++)
	{
		getline(cin, dummy);
		cin >> rows >> cols;

		char grid[50][50];
		char gridT[50][50];

		for(int y=0;y<rows;y++)
		{
			for(int x=0;x<cols;x++)
			{
				char c;
				cin >> c;
				c = tolower(c);
				grid[y][x] = c;
				gridT[x][y] = c;
			}
		}

		cin >> nwords;
		char word[128];
		for(int j=0;j<nwords;j++)
		{
			scanf("%s", word);
			int len = strlen( word );
			for(int k=0;k<len;k++)
				word[k] = tolower(word[k]);
			
			Location pos = findword( grid, gridT, rows, cols, word );
			cout << pos.r << ' ' << pos.c << endl;
		}
		if( i != ncases - 1 ) cout << endl;
	}

	return 0;
}
