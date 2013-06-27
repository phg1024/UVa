#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

set<int> visitedWords;
map<string, int> dict[17];
vector<string> wordSet[17];

vector<string> getNeighbor(const map<string,int>& dict, const vector<string>& words, set<int>& visitedWords, const string& word)
{
	vector<string> v;
	for(size_t i=0;i<word.size();i++)
	{
		for(int j='a';j<='z';j++)
		{
			string str = word;
			str[i] = j;
			if( (dict.find(str) != dict.end()) )
			{
				int idx = dict.at(str);
				if( (visitedWords.find(idx) == visitedWords.end()) )
				{
					visitedWords.insert( idx );
					v.push_back( str );
				}
			}
		}
	}
	return v;
}

vector<string> findPath(const map<string, int>& dict, const vector<string>& words, const string& a, const string& b)
{
	bool found = false;
	queue<int> Q;
	map<int, int> parent;
	int rootIdx = dict.at(a);
	int targetIdx = dict.at(b);
	parent[rootIdx] = -1;
	Q.push( rootIdx );
	visitedWords.insert( rootIdx );
	while( !Q.empty() )
	{
		int wordIdx = Q.front();
		string word = words[wordIdx];
		if( wordIdx == targetIdx )
		{
			found = true;
			break;
		}
		Q.pop();

		vector<string> neighbors = getNeighbor(dict, words, visitedWords, word );
		for(size_t i=0;i<neighbors.size();i++)
		{
			int idx = dict.at(neighbors[i]);
			parent[idx] = wordIdx;
			Q.push( idx );
		}
	}

	if( found )
	{
		vector<string> path;
		int w = targetIdx;
		while(true)
		{
			path.push_back( words[w] );
			if( parent.at(w) == -1 ) break;
			w = parent.at(w);
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

		dict[buf.size()][buf] = wordSet[buf.size()].size();
		wordSet[buf.size()].push_back(buf);
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
			vector<string> path = findPath( dict[a.size()], wordSet[a.size()], a, b );
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

