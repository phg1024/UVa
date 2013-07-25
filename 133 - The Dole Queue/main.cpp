#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXN = 21;

void print(const deque<int>& Q)
{
    for(int i=0;i<Q.size();i++)
        cout << Q[i] << " ";
    cout << endl;
}

int main()
{
    int person[MAXN];
    bool left[MAXN];

    while( true )
    {
        int n, k, m;
        scanf("%d %d %d", &n, &k, &m);
        if( (n | k | m) == 0 ) break;

        deque<int> person;

        for(int i=0;i<n;i++)
        {
            person.push_back(i+1);
        }
        
        int head = 0, tail = n-1;

        while( !person.empty() )
        {
            //print(person);
            if( person.size() == 1 )
            {
                printf("%3d\n", person.front());
                break;
            }
            head = (head + (k-1) % person.size() );
            if( head >= person.size() ) head -= person.size();
            tail = (tail - (m-1) % person.size() );
            if( tail < 0 ) tail += person.size();


            //cout << "h, t = " << head << ", " << tail << endl;
            if( head == tail )
            {
                int v = person[head];
                person.erase(person.begin()+head);
                tail--;
                if( tail < 0 ) tail += person.size();
                printf("%3d", v);
            }
            else
            {
                int vh = person[head];
                int vt = person[tail];
                if( head > tail )
                {
                    person.erase(person.begin()+head);
                    person.erase(person.begin()+tail);
                    head--;
                    tail--;
                    if( tail < 0 ) tail += person.size();
                }
                else
                {
                    person.erase(person.begin()+tail);
                    person.erase(person.begin()+head);
                    tail-=2;
                    if( tail < 0 ) tail += person.size();
                }
                printf("%3d%3d", vh, vt);
            }
            if( person.empty() ) putchar('\n');
            else putchar(',');
        }
    }

    return 0;
}
