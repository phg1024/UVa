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
    void print()
    {
        printf("%s of %s\n", CardName[value], SuitName[suit]);
    }

    friend ostream& operator<<(ostream& os, const Card& c);
    int value;
    Suit suit;
};

ostream& operator<<(ostream& os, const Card& c)
{
    os << CardName[c.value] << " of " << SuitName[c.suit];
    return os;
}


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
    int order[52];
    for(int i=0;i<52;i++)
        order[i] = i;

    int ncases;
    scanf("%d", &ncases);

    int shuffles[100][52];
 
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

        vector<int> sequence;
        string buf;
        while( true )
        {
            getline(cin, buf);
            if( buf.empty() ) break;
            sequence.push_back( atoi( buf.c_str() ) - 1 );
        }

        // apply the sequence to the order
        int oldorder[52];
        memcpy(oldorder, order, sizeof(int)*52);
        int neworder[52];
        for(int j=0;j<sequence.size();j++)
        {
            int* shuffle = &(shuffles[sequence[j]][0]);

            for(int k=0;k<52;k++)
            {
                neworder[k] = oldorder[shuffle[k]];
            }
            memcpy(oldorder, neworder, sizeof(int)*52);
        }

        for(int j=0;j<52;j++)
        {
            deck[oldorder[j]].print();
        }
        if( i != ncases - 1 )
            putchar('\n');
    }

    return 0;
}
