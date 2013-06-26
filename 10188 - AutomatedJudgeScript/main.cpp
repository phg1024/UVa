#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string filter( const vector<string>& s )
{
	string v;
	for(int i=0;i<s.size();i++)
	{
        for(int j=0;j<s[i].size();j++)
    		if( s[i][j] >= '0' && s[i][j] <= '9' )
    			v.push_back(s[i][j]);
	}
	return v;
}

bool isAC( const vector<string>& answer, const vector<string>& solution )
{
    if( answer.size() != solution.size() )
        return false;
    else
    {
        for(int i=0;i<answer.size();i++)
        {
            if( answer[i] != solution[i] )
                return false;
        }
        return true;
    }
}

int judge( const vector<string>& answer, const vector<string>& solution )
{
    // 0: AC
    // 1: WA
    // 2: PE
    if( isAC( answer, solution ) ) return 0;

    string va = filter(answer);
    string vs = filter(solution);
    if( va != vs )
        return 1;
    else
        return 2;
} 

int main()
{
	int id = 0;
	while( true )
	{
		id++;
		int n, m;
		cin >> n;
        cin.ignore();
		if( n == 0 ) break;
		string buf;
		vector<string> solution;
		for(int i=0;i<n;i++)
		{
			getline(cin, buf);
			solution.push_back(buf);
		}

		cin >> m;
        cin.ignore();
		vector<string> answer;
		for(int i=0;i<m;i++)
		{
			getline(cin, buf);
			answer.push_back(buf);
		}

        int result = judge( answer, solution );
        switch( result )
        {
            case 0:
                {
                    cout << "Run #" << id << ": Accepted" << endl;
                    break;
                }
            case 1:
                {
                    cout << "Run #" << id << ": Wrong Answer" << endl;
                    break;
                }
            case 2:
                {
                    cout << "Run #" << id << ": Presentation Error" << endl;
                    break;
                }
        }
	}
	return 0;
}
