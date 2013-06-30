#include <iostream>
using namespace std;

int main()
{
	int ncases;
	cin >> ncases;

	while( ncases > 0 )
	{
		int njobs;
		cin >> njobs;

		int t[1000];
		int s[1000];

		for(int i=0;i<njobs;i++)
		{
			cin >> t[i] >> s[i];
		}

		ncases--;
	};
	return 0;
}