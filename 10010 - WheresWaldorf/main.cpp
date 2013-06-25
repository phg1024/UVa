#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

bool match(char* s1, char* s2, int len)
{
	//cout << "matching " << s1 << " and " << s2 << endl;
	for(int i=0;i<len;i++)
		if( s1[i] != s2[i] ) return false;
	return true;
}

bool rmatch(char* s1, char* s2, int len)
{
	//cout << "matching " << s1 << " and " << s2 << endl;
	for(int i=0;i<len;i++)
		if( s1[i] != s2[len-1-i] ) return false;
	return true;
}

pair<int, int> findword(char grid[50][50], char gridT[50][50], char diag[100][50], int rows, int cols, char word[])
{
	int l = strlen( word );

	// search by row
	for(int j=0;j<rows;j++)
	{
		// regular order
		for(int i=0;i<=cols-l;i++)
		{
			if( match( word, grid[j]+i, l ) ) 
				return make_pair(j+1, i+1);

			if( rmatch( word, grid[j]+i, l ) ) 
				return make_pair(j+1, i+l);
		}
	}

	// search by column
	for(int j=0;j<cols;j++)
	{
		// regular order
		for(int i=0;i<=rows-l;i++)
		{
			if( match( word, gridT[j]+i, l ) ) 
				// need to swap x and y
				return make_pair(i+1, j+1);

			if( rmatch( word, gridT[j]+i, l ) ) 
				// need to swap x and y
				return make_pair(i+l, j+1);
		}
	}

	// search by diagonal
	// rows x cols grid
	int diagSize = (cols > rows)?cols:rows;

	return make_pair(-1, -1);
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
		char diag[200][50];

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

		// create diagonal words

		cin >> nwords;
		char word[128];
		for(int j=0;j<nwords;j++)
		{
			scanf("%s", word);
			int len = strlen( word );
			for(int k=0;k<len;k++)
				word[k] = tolower(word[k]);
			
			pair<int, int> pos = findword( grid, gridT, rows, cols, word );
			cout << pos.first << ' ' << pos.second << endl;
		}
		if( i != ncases - 1 ) cout << endl;
	}

	return 0;
}