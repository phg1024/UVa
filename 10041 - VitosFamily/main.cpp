#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
using namespace std;

inline void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int partition(int s[500], int left, int right, int pivotIndex)
{
    int pivotValue = s[pivotIndex];
    swap(s[right], s[pivotIndex]);
    
    int storeIndex = left;
    
    for(int i=left;i<=right-1;i++)
    {
        if( s[i] < pivotValue )
        {
            swap(s[storeIndex], s[i]);
            storeIndex++;
        }
    }
    
    swap(s[right], s[storeIndex]);
    return storeIndex;
}

int select(int s[], int left, int right, int k)
{
    if( left == right )
        return s[left];
    
    int pivotIndex = (left + right)/2;
    int pivotNewIndex = partition(s, left, right, pivotIndex);
    int pivotDist = pivotNewIndex - left;
    
    if( pivotDist == k )
        return s[pivotNewIndex];
    else if( k < pivotDist )
        return select(s, left, pivotNewIndex-1, k);
    else
        return select(s, pivotNewIndex + 1, right, k - pivotDist - 1);
}

int main()
{
    int ncases;
    int s[500];
    scanf("%d", &ncases);
    for(int i=0;i<ncases;i++)
    {
        int nneighbors;
        scanf("%d", &nneighbors);
        
        for(int i=0;i<nneighbors;i++)
            scanf("%d", s+i);
        
        if( nneighbors < 256 )
        {
            // sorting based method
            std::sort(s, s+nneighbors, std::greater<int>());
            
            int pos;
            if( nneighbors % 2 == 1 )
            {
                pos = s[nneighbors/2];
            }
            else
            {
                pos = (int)((s[nneighbors/2-1] + s[nneighbors/2]) * 0.5 + 0.5);
            }
            
            unsigned int d = 0;
            for(int j=0;j<nneighbors;j++)
            {
                int val = s[j] - pos;
                d += val>0?val:(-val);
            }
            
            printf("%d\n", d);
        }
        else{
            
            // selection based method
            int pos;
            unsigned int d = 0;
            if( nneighbors % 2 == 1 )
            {
                int pos = select(s, 0, nneighbors-1, nneighbors/2 );
                
                for(int j=0;j<nneighbors;j++)
                {
                    int val = pos - s[j];
                    d += (val>0)?val:(-val);
                }
            }
            else
            {
                int left = select(s, 0, nneighbors-1, nneighbors/2-1);
                int right = select(s, 0, nneighbors-1, nneighbors/2) ;
                pos = (int)(( left + right ) / 2.0 );
                
                for(int j=0;j<nneighbors;j++)
                {
                    int val = pos - s[j];
                    d += (val>0)?val:(-val);
                }
            }
            
            printf("%d\n", d);
            
        }
    }
    return 0;
}
