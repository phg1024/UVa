#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct Turtle
{
	bool operator>(const Turtle& t) const
	{
		return rank > t.rank;
	}
	string name;
	int rank;
};

void reorder( deque<Turtle>& turtles )
{
	while( true )
	{
        int currentMax = turtles[0].rank;
        int idx = -1, maxRank = -1;
		for(int i=1;i<turtles.size();i++)
		{
            if( turtles[i].rank < currentMax )
            {
                // out of order turtle
                if( turtles[i].rank > maxRank )
                {
                    idx = i;
                    maxRank = turtles[i].rank;
                }
            }
            else
            {
                currentMax = turtles[i].rank;
            }
		}
        if( idx == -1 ) break;
		
        Turtle t = turtles[idx];
        cout << t.name << endl;
		turtles.erase(turtles.begin()+idx);
	    turtles.push_front( t );	
	}
}

int main()
{
	int ncases;
	cin >> ncases;
	
	while( ncases > 0 )
	{
		int n;
		cin >> n;
		cin.ignore();
		deque<Turtle> turtles;
		turtles.resize(n);
		string buf;
		for(int i=0;i<n;i++)
		{
			getline(cin, buf);
			Turtle t;
			turtles[i].name = buf;
		}
		
		map<string, int> order;
		for(int i=0;i<n;i++)
		{
			getline(cin, buf);
			order[buf] = i;
		}
		
		for(int i=0;i<n;i++)
		{
			turtles[i].rank = order.at(turtles[i].name);
		}
		
		reorder( turtles );
        ncases --;
        cout << endl;
	}
}
