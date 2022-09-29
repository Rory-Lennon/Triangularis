
#include "Jiki.h"
#include "SJBLine.h"

GLuint SJBLine::ms_line_list;	// STATIC

SJBLine::SJBLine(SJBVec& v1, SJBVec& v2)
{
	SJBVec diff(v2);
	diff -= v1;
	diff /= 2.0f;
	diff += v1;
	set_value(diff);

	float dx = v2.get_component(0) - v1.get_component(0);
	float dy = v2.get_component(1) - v1.get_component(1);
	float rangle = (float)acos(dx) ;
	float dangle = rangle * 360.0f / (2 * PI);

	m_rot_z.set_value(0.0f, 0.0f, 1.0f, -dangle);
}

void SJBLine::static_init()
{
	ms_line_list = ::glGenLists(1);
	::glNewList(ms_line_list, GL_COMPILE);
		GLUquadric* qobj = ::gluNewQuadric();
		::gluQuadricDrawStyle(qobj, GLU_FILL);
		::gluQuadricOrientation(qobj, GLU_OUTSIDE);
		::gluQuadricNormals(qobj, GLU_SMOOTH);
		::glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		::glTranslatef(0.0f, 0.0f, -0.25f);
		::gluCylinder(qobj, 0.15f, 0.15f, 0.5f, 15, 4);
	::glEndList();
}

SJBLine::~SJBLine()
{}

void SJBLine::gl_render()
{
	::glPushMatrix();
		float dx, dy, dz;
		get_value(dx, dy, dz);
		::glTranslatef(dx, dy, dz);
		m_rot_z.gl_render();
		::glCallList(ms_line_list);
	::glPopMatrix();
}