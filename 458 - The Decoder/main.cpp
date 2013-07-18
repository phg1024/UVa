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
	while(gets(s))
 	{
 		l=strlen(s);
 	   	for(i=0;i<l;i++)
 			printf("%c",s[i]-7);
 	 	printf("\n");
 	}
	return 0;
}