#pragma once
//----------------------------------------------------------------------------------------------------------------
// vec2 - 2D vector
//----------------------------------------------------------------------------------------------------------------
#include <cstdlib>
class vec2
{
public:
	double x, y;

	vec2()									{ x = 0.0; y = 0.0; }
	vec2(const double &X, const double &Y)		{ x = X; y = Y; }
	vec2(const vec2& v)							{ x = v.x; y = v.y; }


	bool operator==(const vec2& v) const	{ return x==v.x && y==v.y; }
	bool operator!=(const vec2& v) const	{ return !(*this==v); }
	vec2 operator=(const double* fl)			{ x = fl[0]; y = fl[1]; return vec2(x,y); }
	vec2 operator=(const double fl)			{ x = y = fl; return vec2(x,y); }
											  
	vec2 operator-() const					{ return vec2(-x, -y); }
	vec2 operator+(const vec2& v) const 	{ return vec2(x+v.x, y+v.y); }
	vec2 operator+=(const vec2& v) 			{ x+=v.x; y+=v.y; return vec2(x, y); }
	vec2 operator*=(const vec2& v) 			{ x*=v.x; y*=v.y; return vec2(x, y); }
	vec2 operator-=(const vec2& v) 			{ x-=v.x; y-=v.y; return vec2(x, y); }
	vec2 operator-(const vec2& v) const		{ return vec2(x-v.x, y-v.y); }
	vec2 operator/(const vec2& v) const 	{ return vec2(x/v.x, y/v.y); }
	vec2 operator/=(const vec2& v)		 	{ x /= v.x; y /= v.y; return vec2(x, y); }

	vec2 operator*(const double fl) const	{ return vec2(x*fl, y*fl); }
	vec2 operator/(const double fl) const	{ return vec2(x/fl, y/fl); }
	vec2 operator+(const double fl) const	{ return vec2(x+fl, y+fl); }
	vec2 operator-(const double fl) const	{ return vec2(x-fl, y-fl); }
	vec2 operator+=(const double& fl) 		{ x+=fl; y+=fl; return vec2(x, y); }
	vec2 operator-=(const double& fl) 		{ x-=fl; y-=fl; return vec2(x, y); }
	vec2 operator*=(const double& fl) 		{ x*=fl; y*=fl; return vec2(x, y); }
	vec2 operator/=(const double& fl) 		{ x/=fl; y/=fl; return vec2(x, y); }
	operator double*()						{ return &x; }
	operator const double*() const			{ return &x; }


	bool	isZero() const					{ return x == 0.0 && y == 0.0; }
	double	length() const					{ return (double)sqrt(x*x + y*y); }
	double	lengthSquared() const			{ return x*x + y*y; }
	double	distanceTo(const vec2& v) const	{ return (*this - v).length(); }
	double	distanceToSquared(const vec2& v) const	{return (*this - v).lengthSquared();}
	void	normalize()
	{
		double flLen = length();
		if (flLen == 0.0) x = y = 0.0;
		x /= flLen;
		y /= flLen;
	}
	vec2	getNormalized()	const			{vec2 v = *this; v.normalize(); return v;}
	double	dot(const vec2& v) const		{return x*v.x + y*v.y;}
	double	cross(const vec2& v) const		{return (x*v.y) - (y*v.x);}
	vec2	perp() const { return vec2(-y, x); }
	bool isEqual(const vec2 &v, const double &flEpsilon) const
	{
		double _x = v.x - x;
		double _y = v.y - y;
		return (std::abs(_x) + std::abs(_y)) <= flEpsilon;
	}
};
