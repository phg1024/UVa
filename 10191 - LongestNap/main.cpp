#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Time
{
	Time(){}
	Time(int h, int m):hh(h), mm(m){}

	bool operator==(const Time& t) const
	{
		return hh == t.hh && mm == t.mm;
	}
	
	bool operator<(const Time& t) const
	{
		if( hh < t.hh ) return true;
		else if( hh == t.hh ) 
			return mm < t.mm;
		else
			return false;
	}

	int timeTo(const Time& t) const
	{
		return (t.hh - hh) * 60 + t.mm - mm;
	}

	int hh;
	int mm;
	friend istream& operator>>(istream& is, Time& t);
	friend ostream& operator<<(ostream& os, const Time& t);
};

struct Period
{
	Period(){}
	Period(const Time& t1, const Time& t2):start(t1), end(t2){}
	bool operator<(const Period& g) const
	{
		if( start == g.start )
			return end < g.end;
		else
			return start < g.start;
	}

	int length() const
	{
		return start.timeTo(end);
	}

	Time start, end;
};

istream& operator>>(istream& is, Time& t)
{
    char c;
	is >> t.hh >> c >> t.mm;
	return is;
}

ostream& operator<<(ostream& os, const Time& t)
{
	os << t.hh << ':' << ((t.mm<10)?"0":"") << t.mm;
	return os;
}

int main()
{
	int day = 0;
	int ntasks;
	while( cin >> ntasks )
	{
		cin.ignore();
		Period tasks[102];

		Time start(10, 0), end(18, 0);

		tasks[0] = Period(start, start);
		string buf;
		for(int i=1;i<=ntasks;i++)
		{
			Time t1, t2;
			getline(cin, buf);
			stringstream ss;
			ss << buf;
			ss >> t1 >> t2;
			tasks[i] = Period(t1, t2);
		}
		tasks[ntasks+1] = Period(end, end);

		std::sort(tasks, tasks+ntasks+2, std::less<Period>());

		int longestNap = 0;
		int longestIdx = 0;
		for(int i=0;i<ntasks+1;i++)
		{
			int slot = tasks[i].end.timeTo(tasks[i+1].start);
			if( slot > longestNap )
			{
				longestNap = slot;
				longestIdx = i;
			}
		}

		cout << "Day #" << (++day) << ": the longest nap starts at " << tasks[longestIdx].end << " and will last for ";
		if( longestNap >= 60 )
		{
			cout << (longestNap / 60) << " hours and " << (longestNap % 60) << " minutes." << endl;
		}
		else
		{
			cout << longestNap << " minutes." << endl;
		}
	}
	return 0;
}
