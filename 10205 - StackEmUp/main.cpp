#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

string SuitName[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
string CardName[15] = {"", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

typedef vector<int> Shuffle;

enum Suit{
    Clubs = 0,
    Diamonds = 1,
    Hearts = 2,
    Spades = 3
};

struct Card
{
    friend ostream& operator<<(ostream& os, const Card& c);
    int value;
    Suit suit;
};

ostream& operator<<(ostream& os, const Card& c)
{
    os << CardName[c.value] << " of " << SuitName[c.suit];
    return os;
}


vector<Card> newDeck()
{
    vector<Card> deck;
    for(int i=0;i<4;i++)
    {
        Suit s = (Suit)i;
        for(int j=2;j<=14;j++)
        {
            Card c;
            c.value = j;
            c.suit = s;

            deck.push_back(c);
        }
    }
    return deck;
}

int main()
{
    vector<Card> newdeck = newDeck();
    vector<int> order;
    for(int i=0;i<52;i++)
        order.push_back(i);

    int ncases;
    cin >> ncases;
    cin.ignore();
    string dummy;
    getline(cin, dummy); 
 
    for(int i=0;i<ncases;i++)
    {
       int nshuffles;
        cin >> nshuffles;

        vector<Shuffle> shuffles;
        shuffles.resize(nshuffles);
        for(int j=0;j<nshuffles;j++)
        {
            shuffles[j].resize(52);
            for(int k=0;k<52;k++)
            {
                int val;
                cin >> val;
                shuffles[j][k] = val - 1;
            }
        }
        cin.ignore();

        vector<int> sequence;
        string buf;
        while( true )
        {
            getline(cin, buf);
            if( buf.empty() ) break;
            sequence.push_back( atoi( buf.c_str() ) - 1 );
        }

        // apply the sequence to the order
        vector<int> oldorder = order;
        vector<int> neworder;
        neworder.resize(52);
        for(int j=0;j<sequence.size();j++)
        {
            const Shuffle& shuffle = shuffles[sequence[j]];

            for(int k=0;k<52;k++)
            {
                neworder[k] = oldorder[shuffle[k]];
            }
            oldorder = neworder;
        }

        for(int j=0;j<52;j++)
        {
            cout << newdeck[oldorder[j]] << endl;
        }
        if( i != ncases - 1 )
            cout << endl;
    }

    return 0;
}
