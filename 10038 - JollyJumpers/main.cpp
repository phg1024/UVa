#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

int main(){
	int numbers[3000];
	bool diffs[3000];
	int numcount, diffcount;
	while(true){
		cin >> numcount;
		if( cin.eof() ) break;

		for(int i=0;i<numcount;i++)
			cin >> numbers[i];

		for(int i=0;i<numcount;i++)
			diffs[i] = false;

		diffcount = 0;
		for(int i=0;i<numcount-1;i++){
			int diff = abs(numbers[i+1] - numbers[i]);
			if( diff < 0 ) diff = -diff;

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