#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

struct point_t
{
	point_t():x(0),y(0){}
	point_t(float x, float y):x(x), y(y){}

	point_t operator-(const point_t& p) const
	{
		point_t res;
		res.x = x - p.x;
		res.y = y - p.y;
		return res;
	}

	bool operator<(const point_t& p) const
	{
		if( x == p.x ) return y < p.y;
		return x < p.x;
	}

	bool operator==(const point_t& p) const
	{
		return (x == p.x) && (y == p.y);
	}
    float x, y;
};

struct tri_t
{
    point_t p[3];
};

float cross( const point_t& p1, const point_t& p2 )
{
	return p1.x * p2.y - p1.y * p2.x;
}

float sign(const point_t& p1, const point_t& p2, const point_t& p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool isInside( const point_t& p, const tri_t& tri )
{
	bool b1, b2, b3;

	if( p == tri.p[0] || p == tri.p[1] || p == tri.p[2] ) return false;

	b1 = sign(p, tri.p[0], tri.p[1]) < 0.0f;
	b2 = sign(p, tri.p[1], tri.p[2]) < 0.0f;
	b3 = sign(p, tri.p[2], tri.p[0]) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

bool intersect( const point_t& p1, const point_t& p2,
				const point_t& p3, const point_t& p4 )
{
	float px, py;
	float base = (p1.x - p2.x)*(p3.y - p4.y) - (p1.y - p2.y)*(p3.x - p4.x);
	float p1xp2 = cross(p1, p2);
	float p3xp4 = cross(p3, p4);
	px = (p1xp2 * (p3.x - p4.x) - (p1.x - p2.x) * p3xp4) / base;
	//py = (p1xp2 * (p3.y - p4.y) - (p1.y - p2.y) * p3xp4) / base;
	
	float t1 = (px - p1.x) / (p2.x - p1.x);
	float t2 = (px - p3.x) / (p4.x - p3.x);
	
	return ( t1 > 0.0f && t1 < 1.0f && t2 > 0.0f && t2 < 1.0f );
}

int solve(tri_t tris[])
{
	std::sort(tris[0].p, tris[0].p+3, std::less<point_t>());
	std::sort(tris[1].p, tris[1].p+3, std::less<point_t>());

	// bounding box test
	int minx[2], maxx[2], miny[2], maxy[2];
	minx[0] = numeric_limits<int>::max(), maxx[0] = -numeric_limits<int>::max();
	miny[0] = numeric_limits<int>::max(), maxy[0] = -numeric_limits<int>::max();
	minx[1] = numeric_limits<int>::max(), maxx[1] = -numeric_limits<int>::max();
	miny[1] = numeric_limits<int>::max(), maxy[1] = -numeric_limits<int>::max();
	
	for(int i=0;i<3;i++)
	{
		if( tris[0].p[i].x > maxx[0] ) maxx[0] = tris[0].p[i].x;
		if( tris[1].p[i].x > maxx[1] ) maxx[1] = tris[1].p[i].x;
		
		if( tris[0].p[i].y > maxy[0] ) maxy[0] = tris[0].p[i].y;
		if( tris[1].p[i].y > maxy[1] ) maxy[1] = tris[1].p[i].y;

		if( tris[0].p[i].x < minx[0] ) minx[0] = tris[0].p[i].x;
		if( tris[1].p[i].x < minx[1] ) minx[1] = tris[1].p[i].x;
		
		if( tris[0].p[i].y < miny[0] ) miny[0] = tris[0].p[i].y;
		if( tris[1].p[i].y < miny[1] ) miny[1] = tris[1].p[i].y;		
	}
	
	// no overlap
	if( (maxx[0] < minx[1]) || (maxx[1] < minx[0])
	||  (maxy[0] < miny[1]) || (maxy[1] < miny[0]) ) return 1;
	
	// handle edge overlap cases
	float cx[2], cy[2];
	cx[0] = (tris[0].p[0].x + tris[0].p[1].x + tris[0].p[2].x) / 3.0;
	cx[1] = (tris[1].p[0].x + tris[1].p[1].x + tris[1].p[2].x) / 3.0;

	cy[0] = (tris[0].p[0].y + tris[0].p[1].y + tris[0].p[2].y) / 3.0;
	cy[1] = (tris[1].p[0].y + tris[1].p[1].y + tris[1].p[2].y) / 3.0;

	if( isInside( point_t(cx[0], cy[0]), tris[1] ) 
	||  isInside( point_t(cx[1], cy[1]), tris[0] )  ) return 0;

	// vertex test
	if( isInside( tris[0].p[0], tris[1] ) 
	||  isInside( tris[0].p[1], tris[1] ) 
	||  isInside( tris[0].p[2], tris[1] ) ) return 0;

	if( isInside( tris[1].p[0], tris[0] ) 
	||  isInside( tris[1].p[1], tris[0] ) 
	||  isInside( tris[1].p[2], tris[0] ) ) return 0;
	
	// edge intersection test
	if( intersect(tris[0].p[0], tris[0].p[1], tris[1].p[0], tris[1].p[1])
	||  intersect(tris[0].p[0], tris[0].p[1], tris[1].p[1], tris[1].p[2])
	||  intersect(tris[0].p[0], tris[0].p[1], tris[1].p[2], tris[1].p[0])
	||  intersect(tris[0].p[1], tris[0].p[2], tris[1].p[0], tris[1].p[1])
	||  intersect(tris[0].p[1], tris[0].p[2], tris[1].p[1], tris[1].p[2])
	||  intersect(tris[0].p[1], tris[0].p[2], tris[1].p[2], tris[1].p[0])
	||  intersect(tris[0].p[2], tris[0].p[0], tris[1].p[0], tris[1].p[1])
	||  intersect(tris[0].p[2], tris[0].p[0], tris[1].p[1], tris[1].p[2])
	||  intersect(tris[0].p[2], tris[0].p[0], tris[1].p[2], tris[1].p[0]) ) return 0;
	
	// no overlap
	return 1;
}

int main(){

    int ncases;
    scanf("%d", &ncases);

    char str[][4] = {"yes", "no"};
    for(int i=1;i<=ncases;i++)
    {
        tri_t tris[2]; 

        for(int j=0;j<2;j++)
            for(int k=0;k<3;k++)
                scanf("%f %f", &tris[j].p[k].x, &tris[j].p[k].y);

        printf("pair %d: %s\n", i, str[ solve(tris) ]);
    }
    return 0;
}

