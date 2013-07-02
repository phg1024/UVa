#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

string lower(const string& str)
{
    string s;
    std::transform(str.begin(), str.end(), s.begin(), ::tolower);
    return s;
}

struct Team
{
    Team():points(0), wins(0), loses(0), ties(0), 
           goalsScored(0), goalsAgainst(0), games(0),
           name(""){}
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
                            return lower(name) < lower(t.name);
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
    string name;
};

void parse(const string& str, string name[], int goals[])
{
    int pounds[2];
    int at;
    pounds[0] = str.find_first_of('#');
    pounds[1] = str.find_last_of('#');
    at = str.find_first_of('@');
    name[0] = str.substr(0, pounds[0]);
    name[1] = str.substr(pounds[1]+1, str.size()-pounds[1]);
    goals[0] = atoi(str.substr(pounds[0]+1, at - pounds[0] - 1).c_str());
    goals[1] = atoi(str.substr(at+1, pounds[1] - at - 1).c_str());
}

int main()
{
    int nTournaments;
    cin >> nTournaments;
    cin.ignore();

    while( nTournaments > 0 )
    {
        string tournamentName;
        getline(cin, tournamentName);

        int nTeams;
        cin >> nTeams;
        cin.ignore();
        
        Team teams[30];

        map<string, int> order;
        for(int i=0;i<nTeams;i++)
        {
            getline(cin, teams[i].name);
            order[teams[i].name] = i;
        }

        int nGames;
        cin >> nGames;
        cin.ignore();
        string buf;
        for(int i=0;i<nGames;i++)
        {
            string name[2];
            int goals[2];

            getline(cin, buf);
            parse(buf, name, goals);

            int idx[2];
            idx[0] = order.at(name[0]);
            idx[1] = order.at(name[1]);
            Team& team0 = teams[idx[0]];
            Team& team1 = teams[idx[1]];

            if( goals[0] > goals[1] )
            {
                // team 0 wins
                team0.points+=3;
                team0.wins++;

                team0.goalsScored+=goals[0];
                team0.goalsAgainst+=goals[1];
                team0.games++;

                team1.loses++;

                team1.goalsScored+=goals[1];
                team1.goalsAgainst+=goals[0];
                team1.games++;
            }
            else if( goals[0] < goals[1] )
            {
                // team 1 wins
                team1.points+=3;
                team1.wins++;

                team1.goalsScored+=goals[1];
                team1.goalsAgainst+=goals[0];
                team1.games++;

                team0.loses++;
                team0.goalsScored+=goals[0];
                team0.goalsAgainst+=goals[1];
                team0.games++;
            }
            else
            {
                // tie
                team1.ties++;
                team1.points+=1;
                team1.goalsScored+=goals[1];
                team1.goalsAgainst+=goals[0];
                team1.games++;

                team0.ties++;
                team0.points+=1;
                team0.goalsScored+=goals[0];
                team0.goalsAgainst+=goals[1];
                team0.games++;
            }
        }

        for(int i=0;i<nTeams;i++)
            teams[i].goalsDiff = teams[i].goalsScored - teams[i].goalsAgainst;

        std::sort(teams, teams+nTeams, std::greater<Team>());

        cout << tournamentName << endl;
        for(int i=0;i<nTeams;i++)
        {
            printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
                   i+1, teams[i].name.c_str(), teams[i].points, teams[i].games,
                   teams[i].wins, teams[i].ties, teams[i].loses,
                   teams[i].goalsDiff, teams[i].goalsScored, teams[i].goalsAgainst );
        }

        if( -- nTournaments != 0 ) cout << endl; 
    }
    return 0;
}
