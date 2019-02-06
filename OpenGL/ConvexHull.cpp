#include "stdafx.h"
#include "ConvexHull.h"


ConvexHull::ConvexHull(std::vector<vec2>& pts)
	: pts(pts), n((int)pts.size())
{
}

vec2 ConvexHull::p0 = vec2();

ConvexHull::~ConvexHull()
{
}

vec2 ConvexHull::NextToTop(std::vector<vec2>& s)
{
	vec2 p = s.back();
	s.pop_back();
	vec2 res = s.back();
	s.push_back(p);
	return res;
}

void ConvexHull::Swap(vec2& p1, vec2& p2)
{
	vec2 temp = p1;
	p1 = p2;
	p2 = temp;
}

int ConvexHull::Orientation(vec2 p, vec2 q, vec2 r)
{
	double val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0.0) return 0;  // colinear 
	return (val > 0.0) ? 1 : 2; // clock or counterclock wise 
}
int ConvexHull::comp(const void* vp1, const void* vp2)
{
	const vec2 *p1 = (vec2 *)vp1;
	const vec2 *p2 = (vec2 *)vp2;

	// Find orientation 
	int o = ConvexHull::Orientation(ConvexHull::p0, *p1, *p2);
	if (o == 0)
		return (ConvexHull::p0.distanceToSquared(*p2) >= ConvexHull::p0.distanceToSquared(*p1)) ? -1 : 1;

	return  (o == 2) ? -1 : 1;
}

void ConvexHull::Do()
{
	// Find the bottom most point 
	double ymin = pts[0].y;
	int min = 0;

	for (int i = 1; i < n; i++)
	{
		double y = pts[i].y;

		// Pick the bottom-most or chose the left 
		// most point in case of tie 
		if ((y < ymin) || (ymin == y &&
			pts[i].x < pts[min].x))
			ymin = pts[i].y, min = i;
	}

	// Place the bottom-most point at first position 
	Swap(pts[0], pts[min]);

	// Sort n-1 pts with respect to the first point. 
	// A point p1 comes before p2 in sorted ouput if p2 
	// has larger polar angle (in counterclockwise 
	// direction) than p1 
	p0 = pts[0];
	qsort(&pts[1], n - 1, sizeof(vec2), comp);

	// If two or more pts make same angle with p0, 
	// Remove all but the one that is farthest from p0 
	// Remember that, in above sorting, our criteria was 
	// to keep the farthest point at the end when more than 
	// one pts have same angle. 
	int m = 1; // Initialize size of modified array 
	for (int i = 1; i<n; i++)
	{
		// Keep removing i while angle of i and i+1 is same 
		// with respect to p0 
		while (i < n - 1 && Orientation(p0, pts[i],
			pts[i + 1]) == 0)
			i++;


		pts[m] = pts[i];
		m++;  // Update size of modified array 
	}

	// If modified array of pts has less than 3 pts, 
	// convex hull is not possible 
	if (m < 3) return;

	// Create an empty stack and push first three pts 
	// to it. 
	s.push_back(pts[0]);
	s.push_back(pts[1]);
	s.push_back(pts[2]);

	// Process remaining n-3 pts 
	for (int i = 3; i < m; i++)
	{
		// Keep removing top while the angle formed by 
		// pts next-to-top, top, and pts[i] makes 
		// a non-left turn 
		while (Orientation(NextToTop(s), s.back(), pts[i]) != 2)
			s.pop_back();
		s.push_back(pts[i]);
	}
}

std::vector<vec2> ConvexHull::GetVector() const
{
	return s;
}
