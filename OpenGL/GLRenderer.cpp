#include "stdafx.h"
#include "GLRenderer.h"

#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"

GLRenderer::GLRenderer(void)
{
}

GLRenderer::~GLRenderer(void)
{
}

bool GLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc) return false;

	return true;
}

void GLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	//---------------------------------

	std::vector<vec2> v = convex.GetVector();
	// TODO: add draw code here
	//
	//
	//
	glPointSize(5.0f);
	glColor3d(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	for (int i = 0; i < (int)vec.size(); ++i)
	{
		glVertex2d(vec[i].x, vec[i].y);
	}
	glEnd();

	if (v.size() > 2)
	{
		glColor3d(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < (int)v.size(); ++i)
		{
			glVertex2d(v[i].x, v[i].y);
		}
		glEnd();
	}
	//
	//
	//
	//
	//---------------------------------
	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void GLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	glOrtho(0, w , h, 0, 0, 1);
	
	glMatrixMode(GL_MODELVIEW);


	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}