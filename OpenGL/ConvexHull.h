#pragma once


#include "vec2.h"
#include <stack>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>


class ConvexHull
{
public:
	static vec2 p0;

public:
	ConvexHull() = default;
	ConvexHull(std::vector<vec2>& pts);
	~ConvexHull();

	vec2 NextToTop(std::vector<vec2>& s);
	void Swap(vec2& p1, vec2& p2);
	void Do();
	std::vector<vec2> GetVector() const;

	static int Orientation(vec2 p, vec2 q, vec2 r);
	static int comp(const void* vp1, const void* vp2);
private:
	std::vector<vec2> pts;
	std::vector<vec2> s;
	int n;
	vec2 top;
};

