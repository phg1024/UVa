#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXPOINTS = 1001;
typedef long long int lint;

struct point_t
{
	point_t():x(0), y(0){}
	point_t(lint x, lint y):x(x), y(y){}
	point_t operator-(const point_t& p)
	{
		return point_t(x-p.x, y-p.y);
	}
	bool operator<(const point_t& p) const
	{
		if( angle != p.angle )
			return angle > p.angle;
		else
			return x < p.x;
	}
	double angle;
	lint x, y;
};

typedef point_t vec_t;

// Graham scan
void convexhull(point_t points[], int& n)
{	
	// find the first point
	int idx = 0;
	for(int i=1;i<n;i++)
	{
		if( points[i].y < points[idx].y )
		{
			idx = i;
		}
		else if( points[i].y == points[idx].y )
		{
			idx = (points[i].x < points[idx].x)?i:idx;
		}
	}
	// swap them
	point_t P = points[idx];
	points[idx] = points[0];
	points[0] = P;
	
	// make a loop
	points[n] = P;
	
	// compute the angles for all the rest of points
	for(int i=1;i<n;i++)
	{
		lint dx = points[i].x - P.x;
		lint dy = points[i].y - P.y;
		points[i].angle = dx / (double)sqrt((dx * dx + dy * dy));
	}
	
	// sort the points based on the angle to point P and x axis
	std::sort(points+1, points+n, std::less<point_t>());
		
	int pidx = 2;
	int count = 2;
	while( pidx <= n )
	{
		// check if we need to remove the second to last point		
		vec_t v1 = points[count-1] - points[count-2];
		vec_t v2 = points[pidx] - points[count-1];
		
		float flag = (v1.x*v2.y-v1.y*v2.x);
		if( flag < 0 )
		{
			// need to remove the second to last point
			points[count-1] = points[pidx];
		}
		else
			points[count++] = points[pidx];
		
		pidx++;
	}
	
	// the last point is duplicated
	n = count-1;
}

// test if (0, 0) is inside the polygon
bool isInside(point_t poly[], int n)
{	
	// ray shooting
	int hit = 0;
	for(int i=0;i<n;i++)
	{
		point_t& p1 = poly[i];
		point_t& p2 = poly[i+1];
		if( (p1.y >= 0 && p2.y < 0)
		 || (p1.y < 0 && p2.y >= 0) )
		{
			double hitx = p1.y / (double)(p1.y-p2.y) * (p2.x-p1.x) + p1.x;
			if( hitx >= 0 ) hit++;
		}
	}
	return (hit&0x1);
}

int main()
{
	int n;
	while( true )
	{
		scanf("%d", &n);
		if( n == 0 ) break;
		
		point_t points[MAXPOINTS];
		for(int i=0;i<n;i++)
		{
			lint a, b, c;
			scanf("%lld %lld %lld", &a, &b, &c);
			points[i].x = b-a;
			points[i].y = c-a;
		}
		convexhull( points, n );
		
		printf("%s\n", (isInside(points, n)?"Yes":"No"));
	}
    return 0;
}
