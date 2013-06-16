//
//  main.cpp
//  10050 - Hartals
//
//  Created by Peihong Guo on 6/16/13.
//  Copyright (c) 2013 Peihong Guo. All rights reserved.
//

#include <cstdio>

int main(int argc, char * argv[])
{
    int ncases;
    int ndays, nparties;
    int h[100] = {0};
    int calendar[3650] = {0};
    int weekends[3651] = {0};
    for(int i=5;i<3650;i+=7)
    {
        weekends[i] = 1;
        weekends[i+1] = 1;
    }
    
    scanf("%d", &ncases);

    for(int cid=0;cid<ncases;cid++)
    {
        scanf("%d", &ndays);
        scanf("%d", &nparties);
        for(int i=0;i<nparties;i++)
            scanf("%d", h+i);
        
        for(int i=0;i<nparties;i++)
        {
            for(int j=h[i]-1;j<ndays;j+=h[i])
            {
                calendar[j] = 1;
            }
        }
        
        int count = 0;
        for(int i=0;i<ndays;i++)
        {
            if( weekends[i] == 1 ){
                calendar[i] = 0;
                continue;
            }
            if( calendar[i] == 1 ){
                calendar[i] = 0;
                count++;
            }
        }

        printf("%d\n", count);
    }
    return 0;
}

