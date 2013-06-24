#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;

void computeScores(int dices[13][5], int scores[13][16])
{
    for(int i=0;i<13;i++)
    {
        for(int j=0;j<13;j++)
            scores[i][j] = 0;

        int counter[7] = {0};
        int maxCount = 0;

        for(int j=0;j<5;j++)
        {
            // ones, twos, threes, fours and fives
            int val = dices[i][j];
            scores[i][ val ] += val;
            counter[ val ] ++;
            if( counter[ val ] > maxCount )
                maxCount = counter[ val ];
            scores[i][ 7 ] += val;
        }

        if( maxCount >= 3 )
        {
            scores[i][8] = scores[i][7];

            if( maxCount >= 4 )
            {
                scores[i][9] = scores[i][7];

                if( maxCount == 5 )
                    scores[i][10] = 50;
            }
            else
            {
                // possibilly full house
                int nonzeroCount = 0;
                for(int j=1;j<7;j++)
                    nonzeroCount += (counter[j]!=0)?1:0;
                if( nonzeroCount == 2 )
                    scores[i][13] = 40;
            }
        }
 
        if( maxCount == 1 )
        {
            if( counter[5] == 0 
            ||  counter[2] == 0 )
            {
                // short straight
                scores[i][11] = 25;
            }
            else
            {
                scores[i][11] = 25;
                scores[i][12] = 35;
            }
        }
    }
}

/*
int getMaxScore(int scores[13][16], const vector<bool>& picked, vector<int>& maxScores, int index)
{
    if( index == 8 )
    {
        int sum6 = 0;
        for(int i=1;i<7;i++)
        {
            sum6 += maxScores[i];
        }
        if( sum6 >= 63 )
            maxScores[14] = 35;
        maxScores[15] = sum6;
        for(int i=7;i<15;i++)
            maxScores[15] += maxScores[i];

        return maxScores[15];
    }
    else
    {
        vector<int> result;
        result.resize(16);
        int s = 0;
        for(int i=0;i<13;i++)
        {
            if( picked[i] == false )
            {
                // recur on this
                vector<bool> flag = picked;
                vector<int> tempScores = maxScores;
                flag[i] = true;
                tempScores[index] = scores[i][index];
                int x = getMaxScore(scores, flag, tempScores, index+1); 
                if( x > s )
                {
                    s = x;
                    result = tempScores;
                }
            }
        }

        maxScores = result;

        return s;
    }
}
*/

void getMaxScore(int scores[13][16], vector<int>& maxScores)
{

    // 

}

int main()
{
    bool done = false;
    while( !done )
    {
        int dices[13][5];
        int scores[13][16];

        string buf;
        int lineCount = 0;
        while( true )
        {
            getline( cin, buf );
            if( buf.empty() )
            {
                done = true;
                break;
            }
            sscanf( buf.c_str(),
                    "%d %d %d %d %d",
                    &dices[lineCount][0],
                    &dices[lineCount][1],
                    &dices[lineCount][2],
                    &dices[lineCount][3],
                    &dices[lineCount][4]);
            lineCount++;
            if( lineCount == 13 ) break;
        }

        if( done ) break;

        computeScores(dices, scores);

        /*
        for(int i=0;i<13;i++)
        {
            for(int j=1;j<16;j++)
                cout << scores[i][j] << ' ';
            cout << endl;
        }
        */

        vector<int> maxScores;
        maxScores.resize(16);
        vector<bool> picked;
        for(int i=0;i<13;i++)
            picked.push_back(false);

        //getMaxScore(scores, picked, maxScores, 1);
        getMaxScore(scores, maxScores);

        for(int i=1;i<16;i++)
            cout << maxScores[i] << ' ';
        cout << endl;
    } 
    return 0;
}
