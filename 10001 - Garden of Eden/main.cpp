#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef unsigned int state_t;

// transformation map
char tmap[8][3] = { {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
{1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

bool hasAncestor(const bitset<8>& automata, int cellidx, int ncells, const bitset<32>& state, const bitset<32>& prevstate)
{
	//cout << cellidx << '\t' << prevstate <<endl;
	if( cellidx == 0 )
	{
		for(int i=0;i<8;i++)
		{
			// if the first digit of the state sequence is the mapped value of the given automata
			// start the search for the rest of the state sequence
			if( state[cellidx] == automata[i] )
			{
				bitset<32> ps;
				ps[0] = tmap[i][1];
				ps[1] = tmap[i][2];
				ps[ncells-1] = tmap[i][0];
				if( hasAncestor(automata, cellidx+1, ncells, state, ps) ) return true;
			}
		}
		return false;
	}
	else if( cellidx == ncells-2 )
	{
		// simply check if current state is satisfiable
		for (int i = 0; i < 8; i++)  
            if (state[cellidx] == automata[i] )
			{
				if( tmap[i][0] == prevstate[cellidx - 1] &&  
					tmap[i][1] == prevstate[cellidx]     &&  
					tmap[i][2] == prevstate[cellidx + 1] )  
				{  
					// check the last digit
					return hasAncestor(automata, cellidx+1, ncells, state, prevstate);
				}  
			}
        return false; 
	}
	else if( cellidx == ncells-1 )
	{
		// simply check if current state is satisfiable
		for (int i = 0; i < 8; i++)  
            if (state[cellidx] == automata[i] )
			{
				if( tmap[i][0] == prevstate[cellidx - 1] &&  
					tmap[i][1] == prevstate[cellidx]     &&  
					tmap[i][2] == prevstate[0] )  
				{
					//cout << prevstate << endl;
					// check the last digit
					return true;
				}  
			}
        return false; 
	}
	else
	{
		for(int i=0;i<8;i++)
		{
			// if the cellidx-th digit of the state sequence is the mapped value of the given automata
			// start the search for the rest of the state sequence
			if( state[cellidx] == automata[i] )
			{
				// satisfy the digit preceding current digit
				if( prevstate[cellidx-1] == tmap[i][0] && prevstate[cellidx] == tmap[i][1] )
				{
					bitset<32> ps = prevstate;
					ps[cellidx+1] = tmap[i][2];
					if( hasAncestor(automata, cellidx+1, ncells, state, ps) )
						return true;
				}
			}
		}
		return false;
	}
}

int main()
{
	int code;
	int ncells;
	char buf[33];

	while( scanf("%d %d %s", &code, &ncells, buf) != EOF )
	{
		bitset<8> automata(code);
		string str(buf);

		std::reverse(str.begin(), str.end());
		bitset<32> state(str);
		//cout << automata << '\t' << ncells << '\t' << state << endl;

		if( hasAncestor(automata, 0, ncells, state, bitset<32>()) )  
            printf("REACHABLE\n");  
        else  
            printf("GARDEN OF EDEN\n");
	}

	return 0;
}