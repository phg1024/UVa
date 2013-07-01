#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
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

struct Record
{
	friend istream& operator>>(istream& is, Record& r);
	string license;
	string type;
	Time t;
    int pos;

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
	is >> r.license >> r.t >> r.type >> r.pos;
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
			stringstream ss;
			ss.str(buf);
			ss >> records[count++];
		}

		std::sort(records, records+count, std::less<Record>());

		map<string, float> costs;
		for(int i=0;i<count;i++)
		{
            if( costs.find( records[i].license ) == costs.end() )
            {
                // new license
                // account charge
                costs[records[i].license] = 2.0;
            }
            if( i == count - 1 ) break;

            // definitely unpaired
            if( records[i+1].license != records[i].license ) continue;

            // ignore unpaired exit
            if( records[i].type == "exit" ) continue;
            else
            {
                // ignore unpaired exit
                if( records[i+1].type == "enter" ) continue;
                else
                {
                    // a pair
                    float rate = fares[records[i].t.hh];
                    float fee = rate * fabs(records[i+1].pos - records[i].pos) / 100.0 + 1.0;
                    costs[records[i].license] += fee;
                    i++;
                }
            }
		}

        for(map<string, float>::iterator it=costs.begin();
            it != costs.end();
            ++it)
        {
            if( (*it).second > 2.0 )
            {
                cout << (*it).first << ' ' 
                     << '$' << setprecision(2) << fixed << (*it).second << endl;
            }
        }
		if( --ncases != 0 ) cout << endl;
	}
	return 0;
}
