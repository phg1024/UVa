#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 25000;
const int MAXLENGTH = 18;

int main()
{
	int maxL = 1;

	map<string, int> dict[MAXLENGTH];
	int steps[MAXN] = {0};
	for(int i=0;i<MAXN;i++)
		steps[i] = 1;

	string s;
	int cnt=0;
	while( cin >> s )
	{
		int len = s.size();
		int L = 1;
		
		if( len > 1 )
		{
			// delete
			for(int i=0;i<len;i++)
			{
				if( (i == len-1 ) || (s[i+1] <= s[i]) ){
					string sc = s;
					sc.erase(sc.begin() + i);
					map<string, int>::iterator it = dict[len-1].find(sc);
					if( it != dict[len-1].end() )
						L = max(L, steps[(*it).second]+1);
				}
			}
			
			// replace
			for(int i=0;i<len;i++)
			{
				string sc = s;
				for(char c='a';c<s[i];c++)
				{
					sc[i] = c; 

					map<string, int>::iterator it = dict[len].find(sc);
					if( it != dict[len].end() )
						L = max(L, steps[(*it).second]+1);
				}
			}

			// insert
			for(int i=0;i<len;i++)
			{
				string sc = s;
				sc.insert(sc.begin()+i, s[i]);
				
				for(char c='a';c<s[i];c++)
				{
					sc[i] = c;
					map<string, int>::iterator it = dict[len+1].find(sc);
					if( it != dict[len+1].end() )
						L = max(L, steps[(*it).second]+1);
				}
			}
		}
		else
		{
			// replace
			string sc = s;
			for(char c='a';c<s[0];c++)
			{
				sc[0] = c; 

				if( dict[len].find(sc) != dict[len].end() )
					L = max(L, steps[dict[len][sc]]+1);
			}

		}

		if( L > maxL )
			maxL = L;

		steps[cnt] = L;
		dict[len].insert(make_pair(s, cnt));
		cnt++;
	}

	printf("%d\n", maxL);

	return 0;
}

