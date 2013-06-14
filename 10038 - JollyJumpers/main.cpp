#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

int main(){
	int preval, curval;
	bool diffs[3000];
	int numcount, diffcount;
	string buf;
	while( true ){
		getline(cin, buf);
		if( buf.empty() ) break;
		stringstream ss;
		ss.str(buf);
		ss >> numcount;
		for(int i=0;i<numcount;i++)
			diffs[i] = false;

		ss >> preval;
		curval = preval;
		diffcount = 0;
		for(int i=1;i<numcount;i++)
		{
			preval = curval;
			ss >> curval;
			int diff = abs(curval - preval);
			if( diff > numcount) break;		// impossible to be jolly, no need to do more checking
			if( !diffs[diff] ){
				diffcount++;
				diffs[diff] = true;
			}
		}

		cout << ((diffcount == numcount-1)?"Jolly":"Not jolly") << endl;
	}
	return 0;
}