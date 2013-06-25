#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
using namespace std;

void computeScores(int dices[13][5], int scores[13][16])
{
    for(int i=0;i<13;i++)
    {
		//cout << "round " << i << endl;
        for(int j=1;j<14;j++)
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

inline int countCategories( int j )
{
	int count = 0;
	for(int i=0;i<13;i++)
	{
		count += (j & 0x1);
		j = j >> 1;
	}
	return count;
}

struct Strategy
{
	Strategy():score(-1), s6(0), bonus(0){ 
		for(int i=0;i<13;i++)
		{
			category[i] = -1;
			invCategory[i] = -1;
		}
	}
	Strategy(const Strategy& s){
		memcpy(category, s.category, sizeof(int)*13);
		memcpy(invCategory, s.invCategory, sizeof(int)*13);
		score = s.score;
		s6 = s.s6;
		bonus = s.bonus;
	}

	Strategy& operator=(const Strategy& s)
	{
		if( this != &s )
		{
			memcpy(category, s.category, sizeof(int)*13);
			memcpy(invCategory, s.invCategory, sizeof(int)*13);
			score = s.score;
			s6 = s.s6;
			bonus = s.bonus;
		}
		return (*this);
	}

	void print()
	{
		cout << "score = " << score << endl;;
		for(int i=0;i<13;i++)
			cout << category[i] << " " ;
		cout << endl;
	}

	int category[13];
	int invCategory[13];
	int score;
	int s6;
	int bonus;
};

void getMaxScore(int scores[13][16], Strategy** scoreMap)
{
    // dynamic programming
	// sweep from the first round to the last round
	for(int i=0;i<13;i++)
	{
		int mask = (0x1 << i);
		Strategy s;
		s.score = scores[0][i+1];
		s.s6 = (i>5)?0:scores[0][i+1];
		s.category[0] = i;
		s.invCategory[i] = 0;
		if( s.s6 < 63 )
		{
			scoreMap[mask][s.s6] = s;	
		}
		else
		{
			scoreMap[mask][s.s6] = s;
		}
	}

	for(int i=1;i<13;i++)
	{
		//cout << "i = " << i << endl;
		for(int j=1;j<8192;j++)
		{
			if( countCategories(j) == i )
			{
				for(int k=0;k<13;k++)
				{
					int bitpos = (0x1 << k);
					if( (bitpos & j) == 0 )
					{
						// unused slot
						int slot = (bitpos | j);

						Strategy s = scoreMap[j][m];
							
							if( s.score == -1 )
								continue;

							s.score += scores[i][k+1];
							s.category[i] = k;
							s.invCategory[k] = i;
						
							if( k < 6 )
								s.s6 += scores[i][k+1];

							if( s.s6 >= 63 )
							{
								s.score += 35;
								s.s6 = 0;
								s.bonus = 35;
							}
						
							if( s.s6 < 63 )
							{
								if( scoreMap[slot][s.s6].score < s.score )
								{
									scoreMap[slot][s.s6] = s;
								}														
							}
							else
							{
								if( scoreMap[slot][63].score < s.score )
								{
									scoreMap[slot][63] = s;
								}							
							}
						}
					}
				}
			}
		}
	}
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

		Strategy* scoreMap[8192];
		for(int i=0;i<8192;i++)
			scoreMap[i] = new Strategy[64];

		/*
        for(int i=0;i<13;i++)
        {
            for(int j=1;j<16;j++)
                cout << scores[i][j] << ' ';
            cout << endl;
        }
		*/

        getMaxScore(scores, scoreMap);
		
		int maxIdx = 0;
		int maxScore = 0;
		for(int i=0;i<64;i++)
		{
			if( scoreMap[0x1fff][i].score > maxScore )
			{
				maxIdx = i;
				maxScore = scoreMap[0x1fff][i].score;
			}
		}
		
		Strategy& bs = scoreMap[0x1fff][maxIdx];
		//bs.print();
		for(int i=0;i<13;i++)
		{
			cout << scores[i][ bs.category[i] + 1 ] << ' ';
		}
		cout << bs.bonus << ' ' << bs.score << endl;
    } 
    return 0;
}
