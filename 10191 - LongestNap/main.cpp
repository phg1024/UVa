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
	Time(int h, int m):hh(h), mm(m), c(':'){}
	Time(const Time& t):hh(t.hh), mm(t.mm), c(t.c){}

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
	char c;
	friend istream& operator>>(istream& is, Time& t);
	friend ostream& operator<<(ostream& os, const Time& t);
};

struct Period
{
	Period(){}
	Period(const Time& t1, const Time& t2):start(t1), end(t2){}
	Period(const Period& p):start(p.start),end(p.end){}
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

	string lengthString() const
	{
		int L = length();
		int hh = floor(L / 60);
		int mm = L % 60;

		stringstream ss;
		if( hh != 0 )
			ss << hh << " hours and ";
		ss << mm << " minutes";
		return ss.str();
	}
	Time start, end;
};

istream& operator>>(istream& is, Time& t)
{
	is >> t.hh >> t.c >> t.mm;
	return is;
}

ostream& operator<<(ostream& os, const Time& t)
{
	os << t.hh << t.c << ((t.mm<10)?"0":"") << t.mm;
	return os;
}

bool lengthcomp(const Period& p1, const Period& p2)
{
	if( p1.length() > p2.length() ) return true;
	else if( p1.length() == p2.length() )
		return p1.start < p2.start;
	else
		return false;
}

int main()
{
	int day = 0;
	int ntasks;
	while( cin >> ntasks )
	{
		cin.ignore();
		vector<Period> tasks;

		Time start(10, 0), end(18, 0);

		tasks.push_back( Period(start, start) );
		string buf;
		for(int i=0;i<ntasks;i++)
		{
			Time t1, t2;
			getline(cin, buf);
			stringstream ss;
			ss << buf;
			ss >> t1 >> t2;
			Period task(t1, t2);
			tasks.push_back(task);
		}
		tasks.push_back( Period(end, end) );

		std::sort(tasks.begin(), tasks.end(), std::less<Period>());

		for(int i=0;i<tasks.size();i++)
			cout << tasks[i].start << ", " << tasks[i].end << endl;

		int longestNap = 0;
		int longestIdx = 0;
		for(int i=0;i<tasks.size()-1;i++)
		{
			int slot = tasks[i].end.timeTo(tasks[i+1].start);
			if( slot > longestNap )
			{
				longestNap = slot;
				longestIdx = i;
			}
		}

		cout << "Day #" << (++day) << ": the longest nap starts at " << tasks[longestIdx].end << " and will last for ";
		if( longestNap > 60 )
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