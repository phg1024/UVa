#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int main(){
	int preval, curval;
	bool diffs[3000];
	int numcount, diffcount;
	while( (scanf("%d", &numcount) == 1) ){
		for(int i=0;i<numcount;i++)
			diffs[i] = false;

		scanf("%d", &preval);
		curval = preval;
		diffcount = 0;
		for(int i=1;i<numcount;i++)
		{
			preval = curval;
			scanf("%d", &curval);
			int diff = abs(curval - preval);
			if( diff > numcount) continue;
			if( !diffs[diff] ){
				diffcount++;
				diffs[diff] = true;
			}
		}

		printf("%s\n",((diffcount == numcount-1)?"Jolly":"Not jolly"));
	}
	return 0;
}