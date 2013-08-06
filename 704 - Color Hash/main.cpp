#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <queue>
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

struct state_t
{
	state_t(const string& ss, const string& sq):str(ss), seq(sq){}

	bool operator<(const state_t& s) const
	{
		return str < s.str;
	}

	string str;
	string seq;
};

// move 1
string leftCW(const string& state)
{
	// rotate the first 12 right
	string res = state;
	char a = res[10], b = res[11];
	for(int i=11;i>1;i--)
		res[i] = res[i-2];
	res[0] = a, res[1] = b;

	// make it consistent
	res[21] = res[9], res[22] = res[10], res[23] = res[11];
	return res;
}

// move 2
string rightCW(const string& state)
{
	// rotate the last 12 left
	string res = state;
	char a = res[12], b = res[13];

	for(int i=12;i<22;i++)
		res[i] = res[i+2];

	res[22] = a, res[23] = b;

	// make it consistent
	res[9] = res[21], res[10] = res[22], res[11] = res[23];
	return res;
}

// move 3
string leftCCW(const string& state)
{
	// rotate the first 12 left
	string res = state;
	char a = res[0], b = res[1];
	for(int i=0;i<10;i++)
		res[i] = res[i+2];
	res[10] = a, res[11] = b;

	// make it consistent
	res[21] = res[9], res[22] = res[10], res[23] = res[11];
	return res;
}

// move 4
string rightCCW(const string& state)
{
	// rotate the last 12 right
	string res = state;
	char a = res[22], b = res[23];

	for(int i=23;i>13;i--)
		res[i] = res[i-2];

	res[12] = a, res[13] = b;

	// make it consistent
	res[9] = res[21], res[10] = res[22], res[11] = res[23];
	return res;
}

char rmap[] = {0, '3', '4', '1', '2'};

string reverse_steps( const string& s )
{
	string seq = s;
	std::reverse(seq.begin(), seq.end());
	for(int i=0;i<seq.size();i++)
		seq[i] = rmap[ seq[i] - '0' ];
	return seq;
}

bool solve(map<state_t, bool>& boundary, const string& state, string& seq)
{
	set<state_t> visited;

	// bfs + visited states
	queue<state_t> Q;
	Q.push(state_t(state, ""));

	while( !Q.empty() )
	{
		state_t cur = Q.front();
		Q.pop();

		// no more search
		if( cur.seq.size() > 9 ) continue;

		map<state_t, bool>::iterator bit = boundary.find( cur );
		if( bit != boundary.end() )
		{
			string bseq = reverse_steps( (*bit).first.seq );
			seq = cur.seq + bseq;
			return true;
		}

		set<state_t>::iterator it = visited.find( cur );
		if( it != visited.end() )
			continue;

		visited.insert( cur );
		Q.push( state_t( leftCW( cur.str ), cur.seq + "1" ) );
		Q.push( state_t( rightCW( cur.str ), cur.seq + "2" ) );
		Q.push( state_t( leftCCW( cur.str ), cur.seq + "3" ) );
		Q.push( state_t( rightCCW( cur.str ), cur.seq + "4" ) );
	}
	
	return false;
}

void init(map<state_t, bool>& s)
{
	queue<state_t> Q;
	Q.push( state_t(TARGET, "") );

	while( !Q.empty() )
	{
		state_t cur = Q.front();
		Q.pop();

		map<state_t, bool>::iterator sit = s.find( cur );

		if( cur.seq.size() > 8 ) continue;

		if( sit == s.end() )
		{
			s.insert( make_pair(cur, true) );
			Q.push( state_t( leftCW( cur.str ), cur.seq + "1") );
			Q.push( state_t( rightCW( cur.str ), cur.seq + "2") );
			Q.push( state_t( leftCCW( cur.str ), cur.seq + "3") );
			Q.push( state_t( rightCCW( cur.str ), cur.seq + "4") );
		}
	}
}

int main(){

	map<state_t, bool> boundary;
	init( boundary );

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
			if( solve(boundary, state, seq) )
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

