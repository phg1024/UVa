#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

using namespace std;

#define BIT(s, n) (((s) >> (n)) & 0x1)

typedef int64_t state_t;

// transformation map
int64_t tmap[8] = {
	0x0,			// 0000 0000 0000
	0x4,			// 0000 0000 0100
	0x2,			// 0000 0000 0010
	0x6,			// 0000 0000 0110
	0x1,			// 0000 0000 0001
	0x5,			// 0000 0000 0101
	0x3,			// 0000 0000 0011
	0x7,			// 0000 0000 0111
};

bool hasAncestor(int automata, int cellidx, int ncells, state_t state, state_t prevstate)
{
	if( cellidx == 0 )
	{
		for(int i=0;i<8;i++)
		{
			// if the first digit of the state sequence is the mapped value of the given automata
			// start the search for the rest of the state sequence
			if( BIT(state, cellidx) == BIT(automata, i) )
			{
				// ps is an augmented state with 1 to n bits representing the actual state and 0, n+1 used as repeated bits
				state_t ps = tmap[i];

				// set the n-th and the n+1-th bit
				ps |= (BIT(tmap[i], 0) << (ncells));
				ps |= (BIT(tmap[i], 1) << (ncells+1));

				if( hasAncestor(automata, cellidx+1, ncells, state, ps) ) return true;
			}
		}
		return false;
	}
	else if( cellidx == ncells-2 )
	{
		// simply check if current state is satisfiable
		for (int i = 0; i < 8; i++)  
            if ( BIT(state, cellidx) == BIT(automata, i) )
			{
				if( ((prevstate >> cellidx) & 0x7) == tmap[i] )
				{  
					// check the last digit
					if( hasAncestor(automata, cellidx+1, ncells, state, prevstate) )
						return true;
				}  
			}
        return false; 
	}
	else if( cellidx == ncells-1 )
	{
		// simply check if current state is satisfiable
		for (int i = 0; i < 8; i++)  
            if ( BIT(state, cellidx) == BIT(automata, i) )
			{
				if( ((prevstate >> cellidx) & 0x7) == tmap[i] )
				{
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
			if( BIT(state, cellidx) == BIT(automata, i) )
			{
				// satisfy the digit preceding current digit 
				if( ((prevstate >> cellidx) & 0x3) == (tmap[i] & 0x3) )
				{
					state_t ps = prevstate;
					ps |= ((BIT(tmap[i], 2) << (cellidx + 2)));

					if( hasAncestor(automata, cellidx+1, ncells, state, ps) )
						return true;
				}
			}
		}
		return false;
	}
}

state_t str2state(char str[], int L)
{
	state_t s = 0;
	for(int i=0;i<L;i++)
	{
		s = ((s << 1) | (str[i] - '0'));
	}
	return s;
}

int main()
{
	int automata;
	int ncells;
	char str[33];

	while( cin >> automata >> ncells >> str )
	{
		state_t state = str2state( str, ncells );
		
		if( hasAncestor(automata, 0, ncells, state, (int64_t)0x0) )  
            printf("REACHABLE\n");  
        else  
            printf("GARDEN OF EDEN\n");
			
	}

	return 0;
}