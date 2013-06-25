#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

void countWord(const string& s, int counter[128])
{
    for(size_t i=0;i<s.size();i++)
        counter[s[i]]++;
}

int main(){
    string a, b;

    while( getline(cin, a) )
    {
        getline(cin, b);

        int counter[2][128] = {0};
        countWord(a, counter[0]);
        countWord(b, counter[1]);

        char buf[1001]={0};
        for(int i='a', pos=0;i<='z';i++)
        {
            int count = min( counter[0][i], counter[1][i] );
            for(int j=0;j<count;j++)
                buf[pos++] = i;
        }
        printf("%s\n", buf);
    }
    return 0;
}
