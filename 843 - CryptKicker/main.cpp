#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

char dict[32][1024][17];
int dictCounter[32] = {0};
 
inline void split( const string& line, char words[80][17], int& wCount )
{
    stringstream ss;
    ss.str(line);
    vector<string> wordlist;
    wCount = 0;
    while( true )
    {
        string word;
        ss >> word;
        if( word.empty() ) break;
        if( std::find(wordlist.begin(), wordlist.end(), word) == wordlist.end() )
        {
            strcpy(words[wCount], word.c_str());
            wCount++;
        }
    }
}

inline bool match( char* word, char* ref, int wLength, char* key )
{
    for(int i=0;i<wLength;i++)
    {
        if( key[ word[i] ] == '*' )
        {
            key[ word[i] ] = ref[i];
        }
        else if( key[ word[i] ] == ref[i] )
            continue;
        else
            return false;
    }
    return true;
}

bool conflict( char* key )
{
    for(char c1='a';c1<='z';c1++)
    {
        if( key[c1] == '*' ) continue;
        for(char c2 = c1 + 1;c2<='z';c2++)
        {
            if( key[c2] == '*' ) continue;
            if( key[c1] == key[c2] ) return true;
        }
    }
    return false;
}

bool decrypt( char words[80][17], int wCount, int i, char key[128] )
{
    if( i >= wCount ) return true;

    bool flag = false;

    // try to match 
    //cout << words[i] << endl;

    int wLength = strlen( words[i] );

    for(int j=0;j<dictCounter[wLength];j++)
    {
        char key_cpy[128];
        memcpy(key_cpy, key, sizeof(char)*128);
        //cout << candidates[j] << endl;
        if( match( words[i], dict[wLength][j], wLength, key_cpy ) )
        {
            if( decrypt( words, wCount, i+1, key_cpy ) )
            {
                if( !conflict( key_cpy ) )
                {
                    memcpy(key, key_cpy, sizeof(char)*128);
                    return true;
                }
            }
        }
    }

    return false;
}

int main(){
    int wordCount;
    cin >> wordCount;

    for(int i=0;i<wordCount;i++)
    {
        char buf[17];
        cin >> buf;
        int length = strlen(buf);
        strcpy(dict[ length ][dictCounter[length]], buf);
        dictCounter[length]++;
    }
    cin.ignore();

    string buf;
    while( true )
    {
        getline(cin, buf);
        if( buf.empty() ) break;

        char key[128];
        for(char c='a';c<='z';c++)
        {
            key[c] = '*';
        }
        
        char words[80][17];
        int wCount;
        split( buf, words, wCount );


        if( decrypt( words, wCount, 0, key ) )
        {
            for(int i=0;i<buf.size();i++)
            {
                if( buf[i] != ' ' )
                {
                    cout << key[buf[i]];
                }
                else
                    cout << ' ';
            }
        }
        else
        {
            for(int i=0;i<buf.size();i++)
            {
                if( buf[i] != ' ' )
                {
                    cout << '*';
                }
                else
                    cout << ' ';
            }
        }
        cout << endl;
    }
 
    return 0;
}
