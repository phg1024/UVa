#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

struct Time
{
	friend istream& operator>>(istream& is, Time& t);
	friend ostream& operator<<(ostream& os, Time& t);

	bool operator<(const Time& t) const
	{
		if( dd < t.dd ) return true;
		else if( dd == t.dd )
		{
			if( hh < t.hh ) return true;
			else if( hh == t.hh )
				return mm < t.mm;
			else
				return false;
		}
		else return false;
	}

	int MM, dd, hh, mm; 
};

istream& operator>>(istream& is, Time& t)
{
	char c;
	is >> t.MM >> c
		>> t.dd >> c
		>> t.hh >> c
		>> t.mm;
	return is;
}

ostream& operator<<(ostream& os, Time& t)
{
	os  << setw(2) << setfill('0')
		<< t.MM << ':'
		<< setw(2) << setfill('0')
		<< t.dd << ':'
		<< setw(2) << setfill('0')
		<< t.hh << ':'
		<< setw(2) << setfill('0')
		<< t.mm;
	return os;
}

struct Record
{
	friend istream& operator>>(istream& is, Record& r);
	string license;
	string type;
	Time t;

	bool operator<(const Record r) const
	{
		if( license < r.license ) return true;
		else if( license == r.license )
			return t < r.t;
		else
			return false;
	}
};

istream& operator>>(istream& is, Record& r)
{
	is >> r.license >> r.t >> r.type;
	return is;
}

int main()
{
	int ncases;
	cin >> ncases;

	while( ncases > 0 )
	{
		int fares[24];
		for(int i=0;i<24;i++)
			cin >> fares[i];

		cin.ignore();

		int count = 0;
		Record records[1000];
		string buf;
		while( true )
		{
			getline( cin, buf );
			if( buf.empty() ) break;
			cout << buf << endl;
			stringstream ss;
			ss.str(buf);
			ss >> records[count++];
		}

		std::sort(records, records+count, std::less<Record>());

		for(int i=0;i<count;i++)
			cout << setw(20) << setfill(' ') << records[i].license << ' ' << records[i].t << ' ' << records[i].type << endl;

		map<string, int> costs;
		for(int i=0;i<count;i++)
		{
		}
		ncases--;
	}
	return 0;
}