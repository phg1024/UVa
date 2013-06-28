#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Pancake
{
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

    Pancake& operator=(const Pancake& p)
    {
        if( this != &p )
        {
            this->r = p.r;
            this->id = p.id;
        }
        return (*this);
    }

    friend ostream& operator<<(ostream& os, const Pancake& p)
    {
        os << "(" << p.r << ", " << p.id << ")";
        return os;
    }
    int r;
    int id;
};

inline bool inorder( const vector<Pancake>& v )
{
    for(int i=0;i<v.size()-1;i++)
        if( v[i] > v[i+1] )
            return false;
    
    return true;
}

vector<Pancake> flip( const vector<Pancake>& v, int pos )
{
    int actualPos = pos - 1;
    /*
    cout << "flipping " << pos << endl;
    cout << "actual pos " << actualPos << endl;
    */

    vector<Pancake> result;
    for(int i=0;i<=actualPos;i++)
    {
        result.push_back(v[i]);
    }

    std::reverse(result.begin(), result.end());

    for(int i=actualPos+1;i<v.size();i++)
        result.push_back(v[i]);

    return result;
}

int main()
{
    string buf;
    while( getline(cin, buf) )
    {
        vector<Pancake> sequence;

        stringstream ss;
        ss << buf;
        int x;
        int count = 0;
        while( ss >> x )
        {
            Pancake p;
            p.r = x;
            p.id = count++;
            sequence.push_back(p);
        }


        // output the original sequence
        for(int i=0;i<sequence.size();i++)
            cout << sequence[i].r << ' ';
        cout << endl;

        vector<Pancake> sortedSequence = sequence;
        std::sort(sortedSequence.begin(), sortedSequence.end(), std::less<Pancake>());
        /*
        for(int i=0;i<sequence.size();i++)
            cout << sortedSequence[i] << ' ';
        cout << endl;
        */


        map<Pancake, int> positionMap;
        for(int i=0;i<sortedSequence.size();i++)
            positionMap[sortedSequence[i]] = i;

        vector<int> operations;
        while( !inorder(sequence) )
        {
            // search for the first out-of-order item
            int pos = 0;
            for(int i=0;i<sequence.size() - 1;i++)
            {
                if( sequence[i] > sequence[i+1] )
                {
                    pos = i;
                    break;
                }
            }

            // locate its actual position
            int targetPos = positionMap.at(sequence[pos]);

            // flip to top
            sequence = flip( sequence, pos+1);
            
            /*
            for(int i=0;i<sequence.size();i++)
                cout << sequence[i]<< ' ';
            cout << endl;
            */
            

            if( pos != 0 )
            {
                operations.push_back(sequence.size() - pos);
            }

            // flip to the right place

            sequence = flip( sequence, targetPos+1);
           
            /*
            for(int i=0;i<sequence.size();i++)
                cout << sequence[i] << ' ';
            cout << endl;
            */
          
            if( targetPos != 0 )
                operations.push_back(sequence.size()-targetPos);
        }
        operations.push_back(0);
        for(int i=0;i<operations.size();i++)
            cout << operations[i] << ' ';
        cout << endl;
    }
    return 0;
}
