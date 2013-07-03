#include <cstdio>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cstring>
#include <cctype>
using namespace std;

bool comp(const char* str1, const char* str2)
{
    int L1 = strlen(str1);
    int L2 = strlen(str2);
    int L = min(L1, L2);
    for(int i=0;i<L;i++)
    {
        if( tolower(str1[i]) != tolower(str2[i]) )
            return tolower(str1[i]) < tolower(str2[i]);
    }

    return L1 < L2;
}

struct Team
{
    Team():points(0), wins(0), loses(0), ties(0), 
           goalsScored(0), goalsAgainst(0), games(0)
           {
               memset(name, 0, sizeof(char)*32);
           }
    bool operator>(const Team& t) const
    {
        if( points > t.points ) return true;
        else if( points == t.points )
        {
            if( wins > t.wins ) return true;
            else if( wins == t.wins )
            {
                if( goalsDiff > t.goalsDiff ) return true;
                else if( goalsDiff == t.goalsDiff )
                {
                    if( goalsScored > t.goalsScored ) return true;
                    else if( goalsScored == t.goalsScored )
                    {
                        if( games < t.games ) return true;
                        else if( games == t.games) 
                            return comp(name, t.name);
                    }
                }
            }
        }
        return false;
    }
    int points;
    int wins;
    int loses;
    int ties;
    int goalsScored;
    int goalsAgainst;
    int goalsDiff;
    int games;
    char name[32];
};

void parse(const char* str, char name[][32], int goals[])
{
    int pounds[2] = {0};
    pounds[0] = strchr(str, '#') - str;
    pounds[1] = strchr(str+pounds[0]+1, '#') - str;

    strncpy( name[0], str, pounds[0] );
    strncpy( name[1], str + pounds[1] + 1, strlen(str) - pounds[1] );
    char dummy;
    sscanf(str+pounds[0]+1,"%d%c%d", &(goals[0]), &dummy, &(goals[1]));
}

int teamIndex( Team teams[], int nTeams, char* name )
{
    for(int i=0;i<nTeams;i++)
        if( strcmp( teams[i].name, name ) == 0 )
        {
            return i;
        }
    return -1;
}

int main()
{
    int nTournaments;
    scanf("%d\n", &nTournaments);

    while( nTournaments > 0 )
    {
        char tournamentName[128];
        fgets(tournamentName, 128, stdin);

        int nTeams;
        scanf("%d\n", &nTeams);
        
        Team teams[30];
        for(int i=0;i<nTeams;i++)
        {
            fgets(teams[i].name, 32, stdin);
            teams[i].name[strlen(teams[i].name)-1] = '\0';
        }

        int nGames;
        scanf("%d\n", &nGames);

        char buf[128];
        for(int i=0;i<nGames;i++)
        {
            char name[2][32] = {0};
            int goals[2];

            fgets(buf, 128, stdin);
            buf[strlen(buf)-1] = '\0';
            parse(buf, name, goals);

            int idx[2];
            idx[0] = teamIndex(teams, nTeams, name[0]);
            idx[1] = teamIndex(teams, nTeams, name[1]);
            Team& team0 = teams[idx[0]];
            Team& team1 = teams[idx[1]];

            team0.goalsScored+=goals[0];
            team0.goalsAgainst+=goals[1];
            team0.games++;

            team1.goalsScored+=goals[1];
            team1.goalsAgainst+=goals[0];
            team1.games++;
 
            if( goals[0] > goals[1] )
            {
                // team 0 wins
                team0.points+=3;
                team0.wins++;
                team1.loses++;
           }
            else if( goals[0] < goals[1] )
            {
                // team 1 wins
                team1.points+=3;
                team1.wins++;
                team0.loses++;
            }
            else
            {
                // tie
                team1.ties++;
                team1.points+=1;
                team0.ties++;
                team0.points+=1;
            }
        }

        for(int i=0;i<nTeams;i++)
            teams[i].goalsDiff = teams[i].goalsScored - teams[i].goalsAgainst;

        std::sort(teams, teams+nTeams, std::greater<Team>());

        printf("%s", tournamentName);
        for(int i=0;i<nTeams;i++)
        {
            printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
                   i+1, teams[i].name, teams[i].points, teams[i].games,
                   teams[i].wins, teams[i].ties, teams[i].loses,
                   teams[i].goalsDiff, teams[i].goalsScored, teams[i].goalsAgainst );
        }

        if( -- nTournaments != 0 ) putchar('\n'); 
    }
    return 0;
}
