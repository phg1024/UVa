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
        int lineCount = 0;
        // input the strings 
        string lines[101];

        while( true )
        {
            getline(cin, lines[lineCount]);
            if( lines[lineCount].empty() ) break;
            lineCount++;
        }

       // find the mapping
       char mapping[128];
       bool valid = false;
       for(size_t j=0;j<lineCount;j++)
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
           for(size_t j=0;j<lineCount;j++)
           {
               string& str = lines[j];
               for(size_t k=0;k<str.size();k++)
               {
                  str[k] = mapping[str[k]]; 
               }
               cout << str << endl;
           }
       }
       else
           printf("No solution.\n");

       if( i != ncases - 1 ) putchar('\n');
    }
    return 0;
}
