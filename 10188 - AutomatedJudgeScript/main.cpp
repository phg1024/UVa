#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string filter( const string& s )
{
	string v;
	for(int i=0;i<s.size();i++)
	{
		if( s[i] >= '0' && s[i] <= '9' )
			v.append(s[i]);
	}
	return v;
}

bool matchNumber( const vector<string>& answer, const vector<string>& solution )
{
	bool flag = true;

	if( answer.size() == solution.size() )
	{
		// match for all lines of input
		for(int i=0;i<answer.size();i++)
		{
			string va = filter(answer[i]);
			string vs = filter(solution[i]);
			flag &= (va == vs);
		}
	}
	else
	{
		// match for the first x lines of input
		int x = min( answer.size(), solution.size() );
		for(int i=0;i<x;i++)
		{
			string va = filter(answer[i]);
			string vs = filter(solution[i]);
			flag &= (va == vs);
		}

		// then check if the remaining has numbers
		if( answer.size() > solution.size() )
		{
			
		}
		else
		{
		}
	}
	return flag;
} 

int main()
{
	int id = 0;
	while( true )
	{
		id++;
		int n, m;
		cin >> n;
		if( n == 0 ) break;
		string buf;
		vector<string> solution;
		for(int i=0;i<n;i++)
		{
			getline(cin, buf);
			solution.push_back(buf);
		}

		cin >> m;
		vector<string> answer;
		for(int i=0;i<m;i++)
		{
			getline(cin, buf);
			answer.push_back(buf);
		}

		if( n == m )
		{
			bool flag = true;
			for(int i=0;i<n;i++)
				flag &= (solution[i] == answer[i]);

			if( flag )
				cout << "Run #" << id << ": Accepted" << endl;
			else
			{
				if( matchNumber( solution, answer ) )
					cout << "Run #" << id << ": Presentation Error" << endl;
				else
					cout << "Run #" << id << ": Wrong Answer" << endl;
			}
		}
		else
		{
			// WA or PE
			if( matchNumber( solution, answer ) )
				cout << "Run #" << id << ": Presentation Error" << endl;
			else
				cout << "Run #" << id << ": Wrong Answer" << endl;

		}
	}
	return 0;
}
