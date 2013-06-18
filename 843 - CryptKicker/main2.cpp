#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

char dict[32][1024][17];
int dictCounter[32] = {0};

void split( const string& line, char words[80][17], int& wordCount )
{
    stringstream ss;
    ss.str(line);
    wordCount=0;
    while( true )
    {
        string word;
        ss >> word;
        if( word.empty() ) break;

        bool contains = false;
        for(int i=0;i<wordCount;i++)
        {
            if( strcmp( words[i], word.c_str() ) == 0 )
            {
                contains = true;
            }
        }
        if( !contains )
        {
            strcpy( words[wordCount], word.c_str() );
            wordCount++;
        }
    }
}

bool match( char word[17], char ref[17], int wLength, char key[128] )
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

bool conflict( const char* key )
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

bool decrypt( char wl[80][17], int wordCount, int i, char key[128] )
{
    if( i >= wordCount ) return true;

    // try to match 
    //cout << words[i] << endl;
    int wLength = strlen(wl[i]);
    int numCandidates = dictCounter[wLength];
    if( numCandidates == 0 ) return false;

    for(int j=0;j<numCandidates;j++)
    {
        char key_cpy[128];
        memcpy(key_cpy, key, sizeof(char)*128);

        //cout << candidates[j] << endl;
        if( match( wl[i], dict[wLength][j], wLength, key_cpy ) )
        {
            if( conflict( key_cpy ) ) continue;

            if( decrypt( wl, wordCount, i+1, key_cpy ) )
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
    scanf("%d", &wordCount);

    for(int i=0;i<wordCount;i++)
    {
        string word;
        cin >> word;
        int wLength = word.size();
        int count = dictCounter[wLength];
        strcpy(dict[ word.size() ][count], word.c_str());
        dictCounter[wLength]++;
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
        int wordCount;
         split( buf, words, wordCount );

        if( decrypt( words, wordCount, 0, key ) )
        {
            for(int i=0;i<buf.size();i++)
            {
                if( buf[i] != ' ' )
                {
                    putchar( key[buf[i]] );
                }
                else
                    putchar(' ');
            }
        }
        else
        {
            for(int i=0;i<buf.size();i++)
            {
                if( buf[i] != ' ' )
                {
                    putchar('*');
                }
                else
                    putchar(' ');
            }
        }
        putchar('\n');
    }
 
    return 0;
}
