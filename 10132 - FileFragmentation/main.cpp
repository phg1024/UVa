#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

bool match( const vector<string>& set1, const vector<string>& set2, const string& key )
{
    if( set1.size() != set2.size() )
        return false;

    if( set1.empty() ) return true;
    if( set1.size() == 1 )
    {
        return (key == (set1.front() + set2.front())) || (key == (set2.front() + set1.front()));
    }
    
    for(size_t i=0;i<set1.size();i++)
    {
        const string& s1 = set1[i];
        for(size_t j=0;j<set2.size();j++)
        {
            const string& s2 = set2[j];
            if( key == (s1 + s2) || key == (s2 + s1) )
            {
                vector<string> set1r = set1;
                set1r.erase(set1r.begin() + i);
                vector<string> set2r = set2;
                set2r.erase(set2r.begin() + j);
                return match(set1r, set2r, key);
            }
        }
    }

    return false;
}

int main()
{
    int ncases;
    cin >> ncases;
    cin.ignore();
    string buf;
    getline(cin, buf);

    for(int i=0;i<ncases;i++)
    {
        vector<string> fragments[257];
        int minL, maxL;
        minL = 257, maxL = 0;
        while( true )
        {
            getline(cin, buf);
            if( buf.empty() ) break;
            if( buf.size() > maxL ) maxL = buf.size();
            if( buf.size() < minL ) minL = buf.size();
            fragments[ buf.size() ].push_back( buf );
        }

        // the length of the original file
        int L = minL + maxL;

        // get all possible keys
        set<string> keys;
        for(size_t j=0;j<fragments[minL].size();j++)
        {
            for(size_t k=0;k<fragments[maxL].size();k++)
            {
                string key1 = fragments[minL][j] + fragments[maxL][k];
                string key2 = fragments[maxL][k] + fragments[minL][j];
                if( match( fragments[minL], fragments[maxL], key1 ) )
                    keys.insert(key1);
                if( match( fragments[minL], fragments[maxL], key2 ) )
                    keys.insert(key2);
            } 
        }

        for(set<string>::iterator kit = keys.begin();
            kit != keys.end();
            kit++)
        {
            bool flag = true;
            for(int j=minL+1;j<=128;j++)
            {
                if( fragments[j].empty() ) continue;
                if( !match( fragments[j], fragments[L - j], (*kit) ) )
                {
                    flag = false;
                    break;
                }
            }

            if( flag )
            {
                cout << (*kit) << endl;
                break;
            }
        }

        if( i != ncases - 1 ) cout << endl;
    }
    return 0;
}

