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
vector<set<int> > variants[17];

inline bool isDoublet(const string& a, const string& b)
{
    int count = 0;
    for(size_t i=0;i<a.size();i++)
    {
        if( a[i] != b[i] ) count++;
    }

    return (count == 1);
}

void findVariants(int size)
{
    const map<string, int>& d = dict[size];
    const vector<string>& words = wordSet[size];

    variants[size].resize( words.size() );

    for(size_t i=0;i<words.size();i++)
    {
        const string& a = words[i];
        for(size_t j=0;j<words.size();j++)
        {
            const string& b = words[j];
            if( isDoublet( a, b ) ) 
            {
                variants[size][i].insert(j);
                variants[size][j].insert(i);
            }
        }
    }
}

vector<int> getNeighbor(int idx, set<int>& visitedWords, const set<int>& variant)
{
    vector<int> v;
    for(set<int>::iterator it = variant.begin();
        it != variant.end();
        it++)
    {
        if( visitedWords.find( (*it) ) == visitedWords.end() )
        {
            visitedWords.insert( (*it) );
            v.push_back( (*it) );
        }
    }

    return v;
}


vector<int> findPath(const map<string, int>& dict, const vector<string>& words, const vector<set<int> >& variant, const string& a, const string& b)
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
		if( wordIdx == targetIdx )
		{
			found = true;
			break;
		}
		Q.pop();

        vector<int> neighbors = getNeighbor(wordIdx, visitedWords, variant[wordIdx]);

        for(size_t i=0;i<neighbors.size();i++)
        {
            int idx = neighbors[i];
            parent[idx] = wordIdx;
            Q.push(idx);
        }
	}

	vector<int> path;
	if( found )
	{
		int w = targetIdx;
		while(true)
		{
			path.push_back( w );
			if( parent.at(w) == -1 ) break;
			w = parent.at(w);
		};
    }
	return path;
}

int main()
{
	string buf;
	while( true )
	{
		getline(cin, buf);
		if( buf.empty() ) break;

        size_t size = buf.size();

		dict[size][buf] = wordSet[size].size();
		wordSet[size].push_back(buf);
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
            if( variants[a.size()].empty() ) findVariants( a.size() );

			visitedWords.clear();
			vector<int> path = findPath( dict[a.size()], wordSet[a.size()], variants[a.size()], a, b );
			if( !path.empty() )
			{
				for(vector<int>::reverse_iterator it = path.rbegin(); it!=path.rend(); it++)
					cout << wordSet[a.size()][(*it)] << endl;
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

