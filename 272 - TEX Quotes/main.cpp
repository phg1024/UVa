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

#include<stdio.h>
#include<string.h>
int main()
{
	int l,i;
	char s[1000];
	int state = 0;
	while(gets(s))
 	{
 		l=strlen(s);
 	   	for(i=0;i<l;i++)
		{
			if( s[i] == '\"' )
			{
				printf(state==0?"``":"''");
				state = state^0x1;
			}
			else
 				printf("%c",s[i]);
		}
 	 	printf("\n");
 	}
	return 0;
}