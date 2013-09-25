#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 50;

bool issquare(int n)
{
    int m = sqrt(n);
    return (m*m == n);
}

int main(){
    int ncases;
    scanf("%d", &ncases);

    while( ncases-- > 0 )
    {
        int N;
        scanf("%d", &N);

        int pegs[MAXN] = {0};

        int k=0;
        while( true )
        {
            k++;
            bool placed = false;
            for(int i=0;i<N;i++)
            {
                if( pegs[i] == 0 || issquare(pegs[i]+k) )
                {
                    placed = true;
                    pegs[i] = k;
                    //cout << k << " @ peg #" << i << endl;
                    break;
                }
            }

            if(!placed) break;
        }

        printf("%d\n", --k);
    }
    return 0;
}

