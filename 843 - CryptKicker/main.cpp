#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector< vector< string > > Dict;
typedef vector<string> WordList;
typedef vector<char> Key;

inline WordList split( const string& line )
{
    stringstream ss;
    ss.str(line);
    WordList wl;
    while( true )
    {
        string word;
        ss >> word;
        if( word.empty() ) break;
        if( std::find(wl.begin(), wl.end(), word) == wl.end() )
        {
            wl.push_back(word);
        }
    }
    return wl;
}

inline bool match( const string& word, const string& ref, Key& key )
{
    for(int i=0;i<word.size();i++)
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

bool conflict( const Key& key )
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

bool decrypt( const Dict& dict, const WordList& wl, int i, Key& key )
{
    if( i >= wl.size() ) return true;

    bool flag = false;

    // try to match 
    //cout << words[i] << endl;
    const string& word = wl[i];
    const WordList& candidates = dict[word.size()];

    for(int j=0;j<candidates.size();j++)
    {
        Key key_cpy = key;
        //cout << candidates[j] << endl;
        if( match( word, candidates[j], key_cpy ) )
        {
            if( decrypt( dict, wl, i+1, key_cpy ) )
            {
                if( !conflict( key_cpy ) )
                {
                    key = key_cpy;
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

    Dict dict;
    dict.resize(32);

    for(int i=0;i<wordCount;i++)
    {
        string word;
        cin >> word;
        dict[ word.size() ].push_back(word);
    }
    cin.ignore();

    string buf;
    while( true )
    {
        getline(cin, buf);
        if( buf.empty() ) break;

        Key key;
        key.resize(128);
        for(char c='a';c<='z';c++)
        {
            key[c] = '*';
        }
        
        WordList words = split( buf );


        if( decrypt( dict, words, 0, key ) )
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
