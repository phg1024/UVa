#include <iostream>
#include <algorithm>
using namespace std;

struct Job
{
	bool operator<(const Job& j) const
	{
		if( ratio > j.ratio ) return true;
		else if( ratio == j.ratio )
			return id < j.id;
		else
			return false;
	}

	float ratio;
	int t;
	int s;
	int id;
};

int main()
{
	int ncases;
	cin >> ncases;

	while( ncases > 0 )
	{
		int njobs;
		cin >> njobs;

		Job jobs[1001];

		for(int i=1;i<=njobs;i++)
		{
			cin >> jobs[i].t >> jobs[i].s;
			jobs[i].id = i;
			jobs[i].ratio = jobs[i].s / (float) jobs[i].t;
		}

		std::sort(jobs+1, jobs+njobs+1, std::less<Job>());

		for(int i=1;i<=njobs;i++)
		{
			cout << jobs[i].id;
			if( i != njobs ) cout << ' ';
			else cout << endl;
		}

		if( (--ncases) != 0 ) 
			cout << endl;
	};
	return 0;
}