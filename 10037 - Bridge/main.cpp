#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

pair<int, int> chooseBestPair(deque<int>& Q, int speed[])
{
    std::sort(Q.begin(), Q.end(), std::less<int>());

    int p1, p2;
    if( Q[0] == speed[0] && Q[1] == speed[1] )
    {
        p1 = Q.front();
        Q.pop_front();
        p2 = Q.front();
        Q.pop_front();

        return make_pair(p1, p2);
    }
    else
    {
        p1 = Q.back();
        Q.pop_back();
        p2 = Q.back();
        Q.pop_back();

        return make_pair(p2, p1);
    }

}

int main()
{
    int ncases;
    cin >> ncases;

    while( ncases > 0 )
    {
        int npeople;
        cin >> npeople;

        if( npeople == 1 )
        {
            int val;
            cin >> val;
            cout << val << endl;
            cout << val << endl;
        }
        else
        {

        int speed[1000];
        for(int i=0;i<npeople;i++)
            cin >> speed[i];

        std::sort(speed, speed+npeople, std::less<int>());

        deque<int> left;
        deque<int> right;

        for(int i=0;i<npeople;i++)
            left.push_back( speed[i] );

        string output;
        stringstream ss;
        int t = 0;
        while( true )
        {
            pair<int, int> bestPair = chooseBestPair( left, speed );
            int p1 = bestPair.first, p2 = bestPair.second;

            ss << p1 << ' ' << p2 << endl;
            t += p2;

            if( left.empty() )
                break;
            right.push_back(p1);
            right.push_back(p2);

            std::sort(right.begin(), right.end(), std::less<int>());

            int pr = right.front();
            right.pop_front();
            ss << pr << endl;

            t += pr;
            left.push_back(pr);
        }

        cout << t << endl;
        cout << ss.str();

        }
        ncases--;
        if( ncases > 0 ) cout << endl;
    }
    return 0;
}
