#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    string buf;
    string line;

    // get everything first
    while( getline(cin, line) )
    {
        buf = buf + line + "\n";
    }

    // break the buf into lines
    cout << buf << endl;
    return 0;
}
