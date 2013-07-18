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

int main()
{
    long long unsigned int c[3],b[3],g[3],ans[3],i,m,point;
    char req[][5]={"BCG","BGC","CBG","CGB","GBC","GCB"};
    while( cin>>b[0]>>g[0]>>c[0]>>b[1]>>g[1]>>c[1]>>b[2]>>g[2]>>c[2])
    {
           //bgc
           ans[1]=b[1]+b[2]+g[0]+g[2]+c[0]+c[1];
           //bcg
           ans[0]=b[1]+b[2]+g[0]+g[1]+c[0]+c[2];
           //gbc
           ans[4]=b[0]+b[2]+g[1]+g[2]+c[0]+c[1];
           //gcb
           ans[5]=b[1]+b[0]+g[1]+g[2]+c[0]+c[2];
           //cgb
           ans[3]=b[1]+b[0]+g[0]+g[2]+c[2]+c[1];
           //cbg
           ans[2]=b[0]+b[2]+g[0]+g[1]+c[2]+c[1];
           //cout<<ans[0];
           for(i=1,m=ans[0],point=0;i<6;i++)
           {
                   //cout<<ans[i]<<” “;
                   if( ans[i] < m)
                   {
                       m=ans[i];
                       point=i;
                   }
           }
           cout<<req[point]<<" "<<m<<endl;
    }
    return 0;
}

