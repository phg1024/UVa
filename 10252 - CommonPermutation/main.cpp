#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

void countWord(const char* s, int counter[128])
{
    int i=0;
    char c;
    while(( c = s[i++] ) != '\0' )
        counter[c]++;
}

int main(){
    string a, b;
    while( getline(cin, a) && getline(cin, b) )
    {
        int counter[2][128] = {0};

        countWord(a.c_str(), counter[0]);
        countWord(b.c_str(), counter[1]);

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
