#pragma once

#include "ConvexHull.h"

class GLRenderer
{
public:
	GLRenderer();
	~GLRenderer();
	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);
	void DestroyScene(CDC* pDC);

public:
	std::vector<vec2> vec;
	ConvexHull convex;
protected:
	HGLRC	 m_hrc;
};

