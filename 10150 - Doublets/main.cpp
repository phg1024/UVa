#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

set<string> visitedWords;
set<string> dict[17];

vector<string> getNeighbor(const set<string>& dict, set<string>& visitedWords, const string& word)
{
	vector<string> v;
	for(size_t i=0;i<word.size();i++)
	{
		for(int j='a';j<='z';j++)
		{
			string str = word;
			str[i] = j;
			if( (dict.find(str) != dict.end())
				&& (visitedWords.find(str) == visitedWords.end()) )
			{
				visitedWords.insert( str );
				v.push_back( str );
			}
		}
	}
	return v;
}

vector<string> findPath(const set<string>& dict, const string& a, const string& b)
{
	bool found = false;
	queue<string> Q;
	map<string, string> parent;
	parent[a] = "";
	Q.push(a);
	visitedWords.insert(a);
	while( !Q.empty() )
	{
		string word = Q.front();
		if( word == b )
		{
			found = true;
			break;
		}
		Q.pop();

		vector<string> neighbors = getNeighbor(dict, visitedWords, word );
		for(size_t i=0;i<neighbors.size();i++)
		{
			parent[neighbors[i]] = word;
			Q.push(neighbors[i]);
		}
	}

	if( found )
	{
		vector<string> path;
		string w = b;
		while(true)
		{
			path.push_back(w);
			if( parent[w] == "" ) break;
			w = parent[w];
		};

		return path;
	}
	else
		return vector<string>();
}

int main()
{
	string buf;
	while( true )
	{
		getline(cin, buf);
		if( buf.empty() ) break;

		dict[buf.size()].insert( buf );
	}

	string a, b;
	bool firstCase = true;
	while( cin >> a >> b )
	{
		if( !firstCase )
			cout << endl;
		firstCase = false;

		if( a.size() == b.size() )
		{
			visitedWords.clear();
			vector<string> path = findPath( dict[a.size()], a, b );
			if( !path.empty() )
			{
				for(vector<string>::reverse_iterator it = path.rbegin(); it!=path.rend(); it++)
					cout << (*it) << endl;
			}
			else		
			{
				cout << "No solution." << endl;
			}
		}
		else		
		{
			cout << "No solution." << endl;
		}
	}

	return 0;
}

