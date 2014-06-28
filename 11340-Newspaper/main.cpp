#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
using namespace std;

int main()
{
    int n = 0;
    scanf("%d\n", &n);
    for(int i=0;i<n;++i) {
        // the i the case
        int nv = 0;
        scanf("%d\n", &nv);
        map<char, int> values;
        for(int j=0;j<nv;++j) {
            char c;
            int v;
            scanf("%c %d\n", &c, &v);
            values[c] = v;
        }
        
        int nl = 0;
        scanf("%d\n", &nl);
        int sum = 0;        
        char buf[10000];
        for(int j=0;j<nl;++j) {
            gets(buf);
            int L = strlen(buf);
            for(int k=0;k<L;++k) {
                auto it = values.find(buf[k]);
                if( it != values.end() )
                    sum += it->second;
            }
        }
        printf("%.2f$\n", sum/100.0);
    }
    return 0;
}

