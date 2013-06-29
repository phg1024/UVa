#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

int crossBridge(int Q[1000], int count, stringstream& str)
{
	switch( count )
	{
	case 0:
		{
			return 0;
		}
	case 1:
		{
			str << Q[0] << endl;
			return Q[0];
		}
	case 2:
		{
			str << Q[0] << ' ' << Q[1] << endl;
			return Q[1];
		}
	case 3:
		{
			str << Q[0] << ' ' << Q[1] << endl;
			str << Q[0] << endl;
			str << Q[0] << ' ' << Q[2] << endl;
			return Q[0] + Q[1] + Q[2];
		}
	default:
		{
			// AB A YZ B
			int t1 = Q[0] + Q[1] * 2 + Q[count-1];

			// AZ A AY A
			int t2 = Q[0] * 2 + Q[count-2] + Q[count-1];

			if( t1 <= t2 )
			{
				// AB A YZ B
				str << Q[0] << ' ' << Q[1] << endl;
				str << Q[0] << endl;
				str << Q[count-2] << ' ' << Q[count-1] << endl;
				str << Q[1] << endl;
				return t1 + crossBridge( Q, count-2, str );
			}
			else
			{
				// AZ A AY A
				str << Q[0] << ' ' << Q[count-1] << endl;
				str << Q[0] << endl;
				str << Q[0] << ' ' << Q[count-2] << endl;
				str << Q[0] << endl;
				return t2 + crossBridge( Q, count-2, str );
			}
		}
	}
}

int main()
{
	int ncases;
	scanf("%d", &ncases);

	while( ncases > 0 )
	{
		int npeople;
		scanf("%d", &npeople);

		int speed[1000] = {0};
		for(int i=0;i<npeople;i++)
		{
			scanf("%d", speed+i);
		}

		std::sort(speed, speed+npeople, std::less<int>());

		stringstream output;
		int t = crossBridge( speed, npeople, output );

		printf("%d\n", t);
		printf("%s", output.str().c_str());
		ncases--;
		if( ncases > 0 ) putchar('\n');
	}
	return 0;
}
