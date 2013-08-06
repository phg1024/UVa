#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

static const string TARGET = "034305650121078709A90121";
char key[] = "0123456789A";

bool solve(const string& state, string& seq)
{
	// bidirectional bfs + visited states
	
	return true;
}

int main(){

    int ncases = 0;
    scanf("%d", &ncases);

    while( ncases-- > 0 )
    {
        string state;
        for(int i=0;i<24;i++)
        {
            int val;
            scanf("%d", &val);
            state.push_back(key[val]);
        }

		if( state == TARGET )
		{
			printf("PUZZLE ALREADY SOLVED\n");
		}
		else
		{
			string seq;
			if( solve(state, seq) )
			{
				printf("%s\n", seq.c_str());
			}
			else
			{
				printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
			}
		}
    }
    return 0;
}

