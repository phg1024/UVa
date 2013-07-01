#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct Time
{
	friend istream& operator>>(istream& is, Time& t);
	friend ostream& operator<<(ostream& os, Time& t);

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

		for(int i=0;i<count;i++)
			cout << setw(20) << setfill(' ') << records[i].license << ' ' << records[i].t << ' ' << records[i].type << endl;

		ncases--;
	}
	return 0;
}