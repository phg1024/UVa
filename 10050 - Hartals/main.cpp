//
//  main.cpp
//  10050 - Hartals
//
//  Created by Peihong Guo on 6/16/13.
//  Copyright (c) 2013 Peihong Guo. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, char * argv[])
{
    int ncases;
    int ndays, nparties;
    int h[100] = {0};
    int calendar[3650] = {0};
    
    cin >> ncases;

    for(int cid=0;cid<ncases;cid++)
    {
        cin >> ndays;
        cin >> nparties;
        for(int i=0;i<nparties;i++)
            cin >> h[i];
        
        for(int i=0;i<ndays;i++)
            calendar[i] = 0;

        for(int i=0;i<nparties;i++)
        {
            for(int j=h[i]-1;j<ndays;j+=h[i])
            {
                int r = j % 7;
                if( r == 5 || r == 6 ) continue;
                else calendar[j] = 1;
            }
        }
        
        int count = 0;
        for(int i=0;i<ndays;i++)
            if( calendar[i] == 1 ) count++;
        cout << count << endl;
    }
    return 0;
}

