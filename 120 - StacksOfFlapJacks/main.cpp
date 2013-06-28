#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Pancake
{
    Pancake& operator=(const Pancake& p)
    {
        if( this != &p )
        {
            this->r = p.r;
            this->id = p.id;
            this->order = p.order;
        }
        return (*this);
    }

   bool operator==(const Pancake& p) const
    {
        return (id == p.id);
    }
    bool operator<(const Pancake& p) const
    {
        if( r < p.r ) return true;
        else if( r == p.r )
        {
            return id < p.id;
        }
        else return false;
    }
    bool operator>(const Pancake& p) const
    {
        if( r > p.r ) return true;
        else if( r == p.r )
            return id > p.id;
        else
            return false;
    }
    bool operator<=(const Pancake& p) const
    {
        return ((*this) < p) || ((*this) == p);
    }

    friend ostream& operator<<(ostream& os, const Pancake& p)
    {
        os << "(" << p.r << ", " << p.id << ")";
        return os;
    }
    int r;
    int id;
    int order;
};

int main()
{
    string buf;
    while( getline(cin, buf) )
    {
        Pancake sequence[30];
        Pancake sortedSequence[30];

        stringstream ss;
        ss << buf;
        int x;
        int count = 0;
        while( ss >> x )
        {
            Pancake p;
            p.r = x;
            p.id = count;
            sequence[count] = p;
            sortedSequence[count] = p;
            count++;
        }

        // output the original sequence
        for(int i=0;i<count;i++)
            printf("%d ", sequence[i].r);
        putchar('\n');

        std::sort(sortedSequence, sortedSequence+count, std::less<Pancake>());

        for(int i=0;i<count;i++)
            sequence[sortedSequence[i].id].order = i;

        vector<int> operations;
        while( true )
        {
            // search for the first out-of-order item
            int pos = -1;
            for(int i=0;i<count - 1;i++)
            {
                if( sequence[i] > sequence[i+1] )
                {
                    pos = i;
                    break;
                }
            }

            if( pos == -1 ) break;

            // flip to top
            if( pos != 0 )
            {
                std::reverse(sequence, sequence+pos+1);
                operations.push_back(count - pos);
            }

            // take the top item
            int targetPos = sequence[0].order;
            // flip to the right place
            if( targetPos != 0 )
            {
                std::reverse(sequence, sequence+targetPos+1);
                operations.push_back(count-targetPos);
            }
        }

        operations.push_back(0);
        for(int i=0;i<operations.size();i++)
            printf("%d ", operations[i]);
        putchar('\n');
    }
    return 0;
}
