#include<cstdio>
#include<set>

static const int MAXN = 768;

int next(int v)
{
	int x = 0;
	while( v )
	{
		int d = v % 10;
		x += d * d;
		v /= 10;
	}
	return x;
}

int isHappy(int v)
{
	int visited[MAXN] = {0};
	// bring down the number
	v = next(v);
	
	while( true )
	{
		if( v == 1 || visited[v] ) return visited[v];

		visited[v] = 1;
		v = next(v);
	}
}

int main()
{
	int n;
	int caseid = 0, ncases;
	char str[][32] = {"a Happy number", "an Unhappy number"};
	scanf("%d", &ncases);
	while( ncases-- > 0 )
	{
		scanf("%d", &n);
		printf("Case #%d: %d is %s.\n", ++caseid, n, str[ isHappy(n) ] );
	}
	return 0;
}