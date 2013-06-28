#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
using namespace std;

static const int LINE_LENGTH = 72;

string breakline(const string& src, size_t len)
{
    string result;
    string buf;

    int lbegin = 0, lend;
    int wbegin = 0, wend = 0;
    int linew;

    while( wend < src.size() )
    {
        // get the next word
        for(wend = wbegin;
            src[wend]!=' ' && wend < src.size();
            wend++);

        //cout << wbegin << " to " << wend << endl; 
        if( src[wend] == ' ' )
        {
            if( buf.size() + (wend - wbegin) <= len )
            {
                //cout << src.substr(wbegin, wend - wbegin) << endl;
                // put the word into the buffer
                buf = buf + src.substr(wbegin, wend - wbegin) + " ";
            }
            else
            {
                //cout << src.substr(wbegin, wend - wbegin) << endl;
                // break the line 
                result = result + buf;
                result[result.size()-1] = '\n';

                buf = src.substr(wbegin, wend - wbegin) + " ";
                if( buf.size() > len )
                {
                    result = result + buf;
                    result[result.size()-1] = '\n';
                    buf = "";
                }
            }
        }
        else
        {
            if( buf.size() + (wend-wbegin) <= len )
            {
                buf = buf + src.substr(wbegin, wend - wbegin);
                result = result + buf;
            }
            else
            {
                result = result + buf;
                result[result.size()-1] = '\n';
                buf = src.substr(wbegin, wend - wbegin);
                result += buf;
            }
        }

        wbegin = wend + 1;
    }

    return result;
}

string trim( const string& s )
{
    int pos = s.size()-1;
    while( s[pos] == ' ' )
    {
        pos--;
        if( pos == -1 ) break;
    }

    return s.substr(0, pos+1);
}

int main()
{
    string buf;
    string line;

    // get everything first
    while( getline(cin, line) )
    {
        buf = buf + line + "\n";
    }

    // merging lines 
    size_t curPos = 0;
    while( curPos != buf.size() )
    {
        // find the next line break
        size_t pos = buf.find_first_of("\n", curPos);
        if( pos == string::npos || pos >= buf.size() )
            break;

        // see if it can be replaced
        if( buf[pos+1] == ' ' || buf[pos+1] == '\n' )
        {
            // cannot be replaced, skip the next few places
            while( buf[pos] == ' ' || buf[pos] == '\n' )
                pos++;
        }
        else
        {
            buf[pos] = ' ';
        }

        curPos = pos;
    }

    // breaking lines
    stringstream ss;
    ss << buf;
    string srcline;
    while( getline( ss, srcline ) )
    {
        if( srcline.empty() )
        {
            cout << endl;
            continue;
        }

        srcline = trim( srcline );

        string dstline;
        if( srcline.size() <= LINE_LENGTH )
            dstline = srcline;
        else
        {
            dstline = breakline( srcline, LINE_LENGTH );
        }

        // break the line
        cout << trim(dstline) << endl;
    }
    return 0;
}
