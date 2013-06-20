#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Contestant
{
    int penaltyTime[10];
    bool solved[10];
    int solvedProblems;
    int totalPenaltyTime;
    int id;
    bool submitted;
};

bool comp(const Contestant& c1, const Contestant& c2)
{
    if( c1.solvedProblems > c2.solvedProblems )
        return true;
    else if( c1.solvedProblems == c2.solvedProblems )
    {
        if( c1.totalPenaltyTime < c2.totalPenaltyTime )
            return true;
        else if( c1.totalPenaltyTime == c2.totalPenaltyTime )
        {
            return c1.id < c2.id;
        }
        else
            return false;
    }
    else
        return false;
}

int main()
{
    Contestant cc[101];

    int nCases = 0;
    cin >> nCases;
    cin.ignore();
    string dummy;
    getline(cin, dummy);

    for(int i=0;i<nCases;i++)
    {
        for(int j=1;j<101;j++)
        {
            for(int k=1;k<10;k++)
            {
                cc[j].penaltyTime[k] = 0;
                cc[j].solved[k] = false;
            }
            cc[j].solvedProblems = 0;
            cc[j].totalPenaltyTime = 0;
            cc[j].id = j;
            cc[j].submitted = false;
        }

        string buf;
        while( true )
        {
            getline( cin, buf );
            if( buf.empty() )
                break;

            int cid, problem, time;
            char L;
            sscanf(buf.c_str(), "%d %d %d %c", &cid, &problem, &time, &L);
            switch( L )
            {
                case 'I':
                    {
                        cc[cid].penaltyTime[problem] += 20;
                        cc[cid].submitted = true;
                        break;
                    }
                case 'C':
                    {
                        if( !cc[cid].solved[problem] )
                        {
                            cc[cid].solvedProblems ++;
                            cc[cid].penaltyTime[problem] += time;
                            cc[cid].totalPenaltyTime += cc[cid].penaltyTime[problem];
                            cc[cid].submitted = true;
                            cc[cid].solved[problem] = true;
                        }
                        break;
                    }
                case 'R':
                case 'E':
                case 'U':
                    {
                        cc[cid].submitted = true;
                        break;
                    }
                default:
                    break;
            } 
        }

        std::sort(cc+1, cc+101, comp);

        for(int j=1;j<101;j++)
        {
            if( cc[j].submitted )
            {
                cout << cc[j].id << " " << cc[j].solvedProblems << " " << cc[j].totalPenaltyTime << endl;
            }
        }

        if( i != nCases - 1 )
            cout << endl;
    }

    return 0;
}
