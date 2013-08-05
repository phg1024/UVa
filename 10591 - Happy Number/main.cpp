#include<cstdio>
#include<set>
using std::set;

int isHappy(int v, const set<int>& visited)
{
	if( v == 1 ) return 0;
	if( visited.find( v ) != visited.end() ) return 1;
	else
	{	
		set<int> s = visited;
		s.insert(v);
		int x = 0;
		while( v )
		{
			int d = v % 10;
			x += d * d;
			v /= 10;
		}
		return isHappy( x, s );
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
		printf("Case #%d: %d is %s.\n", ++caseid, n, str[ isHappy(n, set<int>()) ] );
	}
	return 0;
}