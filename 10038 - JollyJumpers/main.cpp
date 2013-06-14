#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

int main(){
	int preval, curval;
	bool diffs[3000];
	int numcount, diffcount;
	while(true){
		cin >> numcount;
		if( cin.eof() ) break;

		for(int i=0;i<numcount;i++)
			diffs[i] = false;

		cin >> preval;
		curval = preval;
		diffcount = 0;
		for(int i=1;i<numcount;i++)
		{
			preval = curval;
			cin >> curval;
			int diff = abs(curval - preval);
			if( diff > numcount) continue;
			if( !diffs[diff] ){
				diffcount++;
				diffs[diff] = true;
			}
		}

		cout << ((diffcount == numcount-1)?"Jolly":"Not jolly") << endl;
	}
	return 0;
}