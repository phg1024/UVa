#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

/*
// the mapping in main function is generated using this function
char sequence[128] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./  \n\n";

inline void createMapping( char m[128], char sequence[128])
{
	for(int i=1;i<128;i++)
	{
		m[sequence[i]] = sequence[i-1];
	}
}
*/

int main()
{
	char mapping[128] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 59, 40, 41, 42, 43,
        77, 48, 44, 46, 57, 96, 49, 50, 51, 52, 53, 54, 55, 56, 58,
        76, 60, 45, 62, 63, 64, 93, 86, 88, 83, 87, 68, 70, 71, 85,
        72, 74, 75, 78, 66, 73, 79, 61, 69, 65, 82, 89, 67, 81, 90,
        84, 39, 80, 92, 91, 94, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};

	char c;
	while( (c = getchar()) != EOF )
	{
		putchar(mapping[c]);
	}
	return 0;
}