#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
bool isValid[20];
int voteCount[20];
int vote[1000][20];
string names[20];
int numCandidates;
int validCandidates;
int votes = 0;

void countVotes()
{
    for(int i=0;i<numCandidates;i++)
    {
        voteCount[i] = 0;
    }

    for(int i=0;i<votes;i++){
        for(int j=0;j<numCandidates;j++){
            if( vote[i][j] == 1 )
                voteCount[j]++;
        }
    }

    for(int i=0;i<numCandidates;i++)
    {
        cout << names[i] << ": " << voteCount[i] << endl;
    }

}

int findWinner()
{
    for(int i=0;i<numCandidates;i++)
    {
        if( voteCount[i] > (votes / 2) ) return i;
    }

    return -1;
}

void minmaxVote(int& minVote, int& maxVote)
{
    minVote = 1000;
    maxVote = 0;
    for(int i=0;i<numCandidates;i++)
    {
        if( isValid[i] )
        {
        if( voteCount[i] > maxVote ) maxVote = voteCount[i];
        if( voteCount[i] < minVote ) minVote = voteCount[i];
        }
    }
}

vector<int> getEliminateCandidates()
{
    vector<int> v;
    int minVote, maxVote;
    minmaxVote(minVote, maxVote);

    for(int i=0;i<numCandidates;i++)
    {
        if( isValid[i] )
        {
            if( voteCount[i] == minVote )
                v.push_back(i);
        }
    }
    return v;
}

void processVotes(){
    while( true ){
        countVotes();
        int winner = findWinner();
        if( winner != -1 )
        {
            cout << names[winner] << endl;
            return;
        }

        vector<int> v = getEliminateCandidates();
        if( v.size() == validCandidates )
        {
            // output every valid candidate
            for(int i=0;i<numCandidates;i++)
            {
                if( isValid[i] )
                    cout << names[i] << endl;
            }
            return;
        }
        else
        {
            for(int i=0;i<v.size();i++)
            {
                cout << "eliminated " << names[v[i]] << endl;
                isValid[v[i]] = false;
                validCandidates--;
                for(int j=0;j<votes;j++)
                {
                    if( vote[j][v[i]] == 1 )
                    {
                        // redistribute the ballot
                        // this is not correct though
                        for(int k=0;k<numCandidates;k++)
                        {
                            vote[j][k]--;
                        }
                    }
                }
            }
        }
    }
}

int main(){
    int cases = 0;
    cin >> cases;
    cin.ignore();

    for(int i=0;i<cases;i++){
        cin >> numCandidates;
        //cout << numCandidates << endl;
        validCandidates = numCandidates;
        cin.ignore();

        for(int j=0;j<numCandidates;j++)
        {
            getline(cin, names[j]);
            //cout << names[j] << endl;
            isValid[j] = true;
        }

        // read the ballots
        while(true){
            stringstream ss;
            string buf;
 
            getline(cin, buf);
            if( buf.empty() ) break;
            ss.str(buf);
            for(int j=0;j<numCandidates;j++)
            {
                ss >> vote[votes][j];
            }
            votes++;
        }

        // process votes
        processVotes();
        if( i != cases - 1 ) cout << endl;
    }

    return 0;
}
