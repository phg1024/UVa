#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

char *SuitName[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
char *CardName[] = {"", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

enum Suit{
    Clubs = 0,
    Diamonds = 1,
    Hearts = 2,
    Spades = 3
};

struct Card
{
    int value;
    Suit suit;
};

void genNewDeck(Card deck[52])
{
    int count = 0;
    for(int i=0;i<4;i++)
    {
        Suit s = (Suit)i;
        for(int j=2;j<=14;j++)
        {
            deck[count].value = j;
            deck[count].suit = s;
            count ++;
        }
    }
}

int main()
{
    Card deck[52];
    genNewDeck(deck);

    int ncases;
    scanf("%d", &ncases);

    int shuffles[100][52];
    int sequence[1024];

    for(int i=0;i<ncases;i++)
    {
        int nshuffles;
        scanf("%d", &nshuffles);

        for(int j=0;j<nshuffles;j++)
        {
            for(int k=0;k<52;k++)
            {
                int val;
                scanf("%d", &val);
                shuffles[j][k] = val - 1;
            }
        }
        // get the dummy
        getchar();

        int pool[2][52];
        int* oldorder = &(pool[0][0]);
        int* neworder = &(pool[1][0]);

        // apply the sequence to the order
        for(int j=0;j<52;j++)
            oldorder[j] = j;

        int scount = 0;
        string buf;
        while( true )
        {
            getline(cin, buf);
            if( buf.empty() ) break;
            
            int sid = atoi( buf.c_str() ) - 1;
            sequence[scount++] = sid;
        }
        
        for(int j=0;j<scount;j++)
        {
            int* shuffle = &(shuffles[sequence[j]][0]);

            for(int k=0;k<52;k++)
            {
                neworder[k] = oldorder[shuffle[k]];
            }

            // swap the pointers
            int *tmp = neworder;
            neworder = oldorder;
            oldorder = tmp;
        }

        for(int j=0;j<52;j++)
        {
            printf("%s of %s\n", CardName[deck[oldorder[j]].value], SuitName[deck[oldorder[j]].suit]);
        }
        if( i != ncases - 1 )
            putchar('\n');
    }

    return 0;
}
