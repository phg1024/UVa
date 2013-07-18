#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

int countWords(const string& str)
{
	int count = 0, i = 0;
	while( str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z' )
	{
		i++;
		if( i >= str.size() ) break;
	}
	
	for(;i<str.size();i++)
	{
		while( (str[i] >= 'A' && str[i] <= 'Z') 
			|| (str[i] >= 'a' && str[i] <= 'z') )
		{
				i++;
				if( i >= str.size() ) break;
		}
		count++;
		
		while( str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z' )
		{
			i++;
			if( i >= str.size() ) break;
		}
	}
	
	return count;
}

int main()
{
	string line;
	while( getline(cin, line) )
 	{
		cout << countWords(line) << endl;
 	}
	return 0;
}

