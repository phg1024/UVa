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
		vector<int> idx;
		for(int i=1;i<turtles.size();i++)
		{
			if( turtles[i].rank < i || turtles[i].rank < turtles[i-1].rank)
				idx.push_back(i);
		}
		if( idx.empty() ) break;
		
		vector<Turtle> moveOuts;
		for(int i=0;i<idx.size();i++)
			moveOuts.push_back(turtles[idx[i]]);
		
		std::sort(moveOuts.begin(), moveOuts.end(), std::greater<Turtle>());
		
		for(int i=idx.size()-1;i>=0;i--)
			turtles.erase(turtles.begin()+idx[i]);
		
		for(int i=0;i<moveOuts.size();i++)
		{
            cout << moveOuts[i].name << endl;
			turtles.push_front(moveOuts[i]);
		}
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
			
		if( --ncases != 0 ) cout << endl;
	}
}
