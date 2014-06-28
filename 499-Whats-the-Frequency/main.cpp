#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string s;
    int maxL = 0;
    while( getline(cin, s) ) {
        vector<int> count(128, 0);
        int maxcount = 0;
        for(int i=0;i<s.length();++i) {
            if( s[i] < 'A' || s[i] > 'z' ) continue;
            ++count[s[i]];
            maxcount = (count[s[i]]>maxcount)?count[s[i]]:maxcount;
        }
        
        for(char i='A';i<='z';++i) {
            if( count[i] == maxcount ) cout << i;
        }
        cout << ' ' << maxcount << endl;
    }
    
    return 0;
}
