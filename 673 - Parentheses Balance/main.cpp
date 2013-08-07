#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

bool isvalid( const string& str )
{
	if( str.size() & 0x1 ){ return false; }
	if( str.empty() ){ return true; }
	string s;
	int i=0;
	while( i<str.size() )
	{
		if( i < str.size() - 1 )
		{
			if( str[i] == '(' && str[i+1] == ')' ){ i+=2; continue;}		
			if( str[i] == '[' && str[i+1] == ']' ){ i+=2; continue;}
		}
		s.push_back(str[i]);
		i++;
	}

	if( s == str ) return false;
	return isvalid( s );
}

int main()
{
	int n;
	cin >> n;
	cin.ignore();

	while( n-- > 0 )
	{
		string str;
		getline(cin, str);

		cout << (isvalid( str ) ? "Yes":"No") << endl;
	}
	return 0;
}