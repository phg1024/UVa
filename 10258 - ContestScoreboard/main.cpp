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
    Contestant(int x = 0):
        solvedProblems(-1),
        totalPenaltyTime(0),
        id(x),
        submitted(false)
    {
        for(int i=0;i<10;i++)
        {
            penaltyTime[i] = 0;
            solved[i] = false;
        }
    }
    int penaltyTime[16];
    bool solved[16];
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
    int nCases = 0;
    cin >> nCases;
    cin.ignore();
    string dummy;
    getline(cin, dummy);

    for(int i=0;i<nCases;i++)
    {
        Contestant cc[256];
        for(int j=1;j<101;j++)
        {
            cc[j].id = j;
        }

        string buf;
        int submissionCount = 0;
        while( true )
        {
            getline( cin, buf );
            if( buf.empty() )
                break;

            int cid, problem, time;
            char L;
            sscanf(buf.c_str(), "%d %d %d %c", &cid, &problem, &time, &L);

            Contestant& c = cc[cid];
            if( !c.submitted )
            {
                 c.submitted = true;
                 c.solvedProblems = 0;
                 submissionCount++;
            }
 
            if( L == 'I')
            {
                c.penaltyTime[problem] += 20;
            }
            else if( L == 'C')
            {
                if( !c.solved[problem] )
                {
                    c.solvedProblems ++;
                    c.penaltyTime[problem] += time;
                    c.totalPenaltyTime += c.penaltyTime[problem];
                    c.solved[problem] = true;
                }
            }
        }

        std::sort(cc+1, cc+101, comp);

        for(int j=1;j<=submissionCount;j++)
        {
            printf("%d %d %d\n", cc[j].id, cc[j].solvedProblems, cc[j].totalPenaltyTime);
        }

        if( i != nCases - 1 )
            cout << endl;
    }

    return 0;
}
