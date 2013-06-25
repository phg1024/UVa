#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

bool findMapping( const string& s, const string& key, char mapping[128] )
{
    char mark[128] = {0};
    for(int i='a';i<='z';i++)
        mapping[i] = 0;

    for(size_t i=0;i<s.size();i++)
    {
        char c = s[i];
        if( c != ' ' )
        {
            if( mapping[c] == 0 )
            {
                // no mapping assigned yet
                if( mark[key[i]] == 0 )
                {
                    mapping[c] = key[i];
                    mark[key[i]] = c;
                }
                else return false;
            }
            else
            {
                if( mapping[c] != key[i] )
                    return false;
            }
        }
        else if( key[i] != ' ' ) return false;
    }

    mapping[' '] = ' ';
    return true;
}

int main(){
    const string key = "the quick brown fox jumps over the lazy dog";
    string buf;
    int ncases;
    cin >> ncases;
    cin.ignore();
    getline(cin, buf);

    for(int i=0;i<ncases;i++)
    {
       // input the strings 
       vector<string> lines;

       while( true )
       {
           getline(cin, buf);
           if( buf.empty() ) break;
           lines.push_back( buf );
       }

       // find the mapping
       char mapping[128] = {0};
       bool valid = false;
       for(size_t j=0;j<lines.size();j++)
       {
           if( lines[j].size() == key.size() )
           {
               if( findMapping(lines[j], key, mapping) )
               {
                   valid = true;
                   break;
               }
           }
       }

       if( valid )
       {
           for(size_t j=0;j<lines.size();j++)
           {
               for(size_t k=0;k<lines[j].size();k++)
               {
                   putchar( mapping[lines[j][k]] );
               }
               cout << endl;
           }
       }
       else
           cout << "No solution." << endl;

       if( i != ncases - 1 ) cout << endl;
    }
    return 0;
}
