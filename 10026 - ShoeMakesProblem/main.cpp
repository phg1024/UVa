#include <iostream>
#include <algorithm>
using namespace std;

struct Job
{
	int t;
	int s;
	int id;
};

bool comp(const Job& a, const Job& b)
{
	float ratioa = a.s / (float)a.t;
	float ratiob = b.s / (float)b.t;
	if( ratioa > ratiob ) return true;
	else if( ratioa == ratiob )
		return a.id < b.id;
	else
		return false;
}

int main()
{
	int ncases;
	cin >> ncases;

	while( ncases > 0 )
	{
		int njobs;
		cin >> njobs;

		Job jobs[1000];

		for(int i=0;i<njobs;i++)
		{
			jobs[i].id = i+1;
			cin >> jobs[i].t >> jobs[i].s;
		}

		std::sort(jobs, jobs+njobs, comp);

		for(int i=0;i<njobs;i++)
		{
			cout << jobs[i].id;
			if( i != njobs - 1 ) cout << ' ';
		}
		cout << endl;

		if( (--ncases) != 0 ) 
			cout << endl;
	};
	return 0;
}