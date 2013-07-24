#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int main()
{
    string line;
    while( getline(cin, line) )
    {
        stringstream ss;
        ss.str(line);

        string str;
        while( ss >> str )
        {
            std::reverse(str.begin(), str.end());
            cout << str;
            if( !ss.eof() ) cout << ' '; 
        }
        cout << endl;
    }
    return 0;
}
