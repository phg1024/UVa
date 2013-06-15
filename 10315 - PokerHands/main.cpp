#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

int cardmap[128];
int kindmap[128];

void createCardMap()
{
	for(char c = '2';c<='9';c++)
		cardmap[c] = c-'0';

	cardmap['T'] = 10;
	cardmap['J'] = 11;
	cardmap['Q'] = 12;
	cardmap['K'] = 13;
	cardmap['A'] = 14;
}

void createKindMap()
{
	kindmap['C'] = 0;
	kindmap['D'] = 1;
	kindmap['H'] = 2;
	kindmap['S'] = 3;
}

struct Card
{
	int val;
	char suit;
};

struct Result
{
	Result()
	{
		for(int i=0;i<5;i++)
			val[i] = 0;
	};
	bool operator>(const Result& r)
	{
		if( kind > r.kind ) return true;
		else if( kind == r.kind )
		{
			// compare the values
			for(int i=0;i<5;i++)
				if( val[i] > r.val[i] ) return true;
				else if( val[i] < r.val[i] ) return false;
			return false;
		}
		else return false;
	}

	bool operator<(const Result& r)
	{
		if( kind < r.kind ) return true;
		else if( kind == r.kind )
		{
			for(int i=0;i<5;i++)
				if( val[i] < r.val[i] ) return true;
				else if( val[i] > r.val[i] ) return false;
			return false;
		}
		else return false;
	}

	bool operator==(const Result& r)
	{
		if( r.kind != kind ) return false;
		for(int i=0;i<5;i++) 
			if( val[i] != r.val[i] ) return false;
		return true;
	}
	char kind;
	char val[5];
};

bool cardcomp(const Card& c1, const Card& c2)
{
	return c1.val < c2.val;
}

Result computeCardValue( char c[5][3] )
{
	Card cards[5];
	for(int i=0;i<5;i++)
	{
		cards[i].val = cardmap[c[i][0]];
		cards[i].suit = c[i][1];
	}
	std::sort(cards, cards+5, cardcomp);

	bool isStraight = true;
	for(int i=0;i<4;i++)
		isStraight &= (cards[i+1].val - cards[i].val == 1);
	int kindCount[4] = {0};
	int cardCount[15] = {0};
	for(int i=0;i<5;i++)
	{
		kindCount[ kindmap[cards[i].suit] ]++;
		cardCount[ cards[i].val  ]++;
	}

	int sameCardCount[6] = {0};
	for(int i=2;i<15;i++)
	{
		sameCardCount[ cardCount[i] ] ++;
	}

	int maxKindCount = 0;
	for(int i=0;i<4;i++)
		maxKindCount = (kindCount[i] > maxKindCount)?kindCount[i]:maxKindCount;

	Result r;
	if( maxKindCount == 5 )
	{
		// flush or flush straight
		if( isStraight )
		{
			// flush straight
			r.kind = 9;
			r.val[0] = cards[4].val;
			return r;
		}
		else
		{
			// flush
			r.kind = 6;
			for(int i=0;i<5;i++)
				r.val[i] = cards[5 - 1 - i].val;
			return r;
		}
	}
	else if( sameCardCount[4] == 1 )
	{
		r.kind = 8;
		// four of a kind
		r.val[0] = cards[2].val;
		return r;
	}
	else if( maxKindCount == 3 )
	{
		// three of a kind
		r.kind = 4;
		r.val[0] = cards[2].val;
		return r;
	}
	else if( sameCardCount[2] == 2 )
	{
		// two pairs
		r.kind = 3;

		r.val[0] = cards[4].val;
		if( cards[3].val != cards[4].val )
		{
			r.val[1] = cards[3].val;
			r.val[2] = cards[1].val;
		}
		else
		{
			r.val[1] = cards[2].val;
			if( cards[1].val != cards[2].val )
				r.val[2] = cards[1].val;
			else
				r.val[2] = cards[0].val;
		}

		return r;
	}
	else if( sameCardCount[2] == 1 && sameCardCount[3] == 1 )
	{
		// full house
		r.kind = 7;
		r.val[0] = cards[2].val;
		return r;
	}
	else if( sameCardCount[2] == 1 )
	{
		// plain pair
		r.kind = 2;

		int pairval;
		for(int i=4, j=1;i>0;i--)
		{
			if( cards[i].val == cards[i-1].val )
			{
				pairval = cards[i].val;
				break;
			}
		}

		for(int i=4,j=1;i>=0;i--)
		{
			if( cards[i].val == pairval )
			{
				r.val[0] = cards[i].val;
			}
			else
				r.val[j++] = cards[i].val;
		}
		return r;
	}
	else
	{
		// high card or straight
		if( isStraight )
		{
			r.kind = 5;
			r.val[0] = cards[4].val;
		}
		else
		{
			r.kind = 1;
			for(int i=0;i<5;i++)
				r.val[i] = cards[5 - 1 - i].val;
		}
		return r;
	}
}

int main(){
	createCardMap();
	createKindMap();
	string buf;
	char hands[2][5][3];
	Result cardValue[2];

	while( true )
	{
		getline(cin, buf);
		if( buf.empty() ) break;
		stringstream ss;
		ss.str(buf);

		for(int i=0;i<2;i++)
			for(int j=0;j<5;j++)
				ss >> hands[i][j];

		cardValue[0] = computeCardValue( hands[0] );
		cardValue[1] = computeCardValue( hands[1] );

		if( cardValue[0] > cardValue[1] )
			cout << "Black wins." << endl;
		else if( cardValue[0] < cardValue[1] )
			cout << "White wins." << endl;
		else
			cout << "Tie." << endl;
	}
	return 0;
}