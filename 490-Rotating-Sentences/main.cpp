#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    vector<string> v;
    string s;
    int maxL = 0;
    while( getline(cin, s) ) {
        v.push_back(s);
        maxL = (s.length()>maxL)?s.length():maxL;
    }
    
    int n = v.size();
    
    for(int i=0;i<maxL;++i) {
        for(int j=n-1;j>=0;--j) {
            auto x = v[j];
            if( x.size() <= i ) {
                cout << ' ';
            }
            else cout << x[i];
        }
        cout << endl;
    }
    
    return 0;
}
