#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
bool isValid[20];
int voteCount[20];
int vote[1000][20];
int toEliminate[20];
int eliminateCount;
unsigned char ballotPointer[1000];
string names[20];
int numCandidates;
int validCandidates;
int votes = 0;
int minVote, maxVote;

void countVotes()
{
    for(int i=0;i<numCandidates;i++)
    {
        voteCount[i] = 0;
    }

    minVote = 1000;
    maxVote = 0;
 
    for(int i=0;i<votes;i++){
        int cid = vote[i][ballotPointer[i]];
        //cout << cid << endl;
        voteCount[cid]++;
    }

    for(int i=0;i<numCandidates;i++)
    {
        if( isValid[i] )
        {
            if( voteCount[i] > maxVote ) maxVote = voteCount[i];
            if( voteCount[i] < minVote ) minVote = voteCount[i];
        }
    }
}

inline int findWinner()
{
    for(int i=0;i<numCandidates;i++)
    {
        if( voteCount[i] > (votes / 2) ) return i;
    }

    return -1;
}

void getEliminateCandidates()
{
    eliminateCount = 0;
    for(int i=0;i<numCandidates;i++)
    {
        if( isValid[i] )
        {
            if( voteCount[i] == minVote )
                toEliminate[eliminateCount++] = i;
        }
    }
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

        getEliminateCandidates();
        if( eliminateCount == validCandidates )
        {
            // output every valid candidate
            for(int i=0;i<eliminateCount;i++)
            {
                cout << names[toEliminate[i]] << endl;
            }
            return;
        }
        else
        {
            for(int i=0;i<eliminateCount;i++)
            {
                int cid = toEliminate[i];
                //cout << "eliminated " << names[cid] << endl;
                isValid[cid] = false;
                validCandidates--;

                for(int j=0;j<votes;j++)
                {
                    int bp = ballotPointer[j];
                    while( !isValid[vote[j][bp]] )
                    {
                        // move to the next candidate
                        ballotPointer[j]++;
                        bp = ballotPointer[j];
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
        //cout << "# candidates = " << numCandidates << endl;
        validCandidates = numCandidates;
        cin.ignore();

        for(int j=0;j<numCandidates;j++)
        {
            getline(cin, names[j]);
            //cout << names[j] << endl;
            isValid[j] = true;
        }

        // read the ballots
        votes = 0;
        while(true){
            stringstream ss;
            string buf;
 
            getline(cin, buf);
            //cout << buf << endl;
            if( buf.empty() ) break;
            ss.str(buf);
            for(int j=0;j<numCandidates;j++)
            {
                int id;
                ss >> id; 
                // store the votes in preference order
                vote[votes][j] = id-1;
            }
            ballotPointer[votes] = 0;
            votes++;
        }

        //cout << "# votes = " << votes << endl;

        // process votes
        processVotes();
        if( i != cases - 1 ) cout << endl;
    }

    return 0;
}
