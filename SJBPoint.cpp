
#include "Jiki.h"
#include "SJBPoint.h"

SJBPoint::SJBPoint() : SJBVec()
{
	m_point_size = 0.1f;
	m_state_current = POINT_STATE_LIGHT;
}

SJBPoint::SJBPoint(int num, float x, float y, float z) : SJBVec(x, y, z)
{
	m_num = num;
	m_point_size = 0.5f;
	set_component(2, 0.0f);
	m_state_current = POINT_STATE_NONE;
}

SJBPoint::~SJBPoint()
{}

GLuint	SJBPoint::ms_sphere_list;	// STATIC
GLfloat	SJBPoint::ms_diff_on[4];	// STATIC
GLfloat	SJBPoint::ms_diff_off[4];	// STATIC
GLfloat	SJBPoint::ms_ambi_on[4];	// STATIC
GLfloat	SJBPoint::ms_ambi_off[4];	// STATIC
GLfloat	SJBPoint::ms_spec_on[4];	// STATIC
GLfloat	SJBPoint::ms_spec_off[4];	// STATIC
GLfloat	SJBPoint::ms_none[4];		// STATIC

void SJBPoint::static_init()
{
	ms_sphere_list = ::glGenLists(1);

	GLUquadric* qobj = ::gluNewQuadric();
	::gluQuadricDrawStyle(qobj, GLU_FILL);
	::gluQuadricOrientation(qobj, GLU_OUTSIDE);
	::gluQuadricNormals(qobj, GLU_SMOOTH);
	::glNewList(ms_sphere_list, GL_COMPILE);
		::gluSphere(qobj, 0.1f, 20, 15);
	::glEndList();

	float lowio = 0.50f;
	float vario = 0.80f;
	float trans = 0.50f;

	set_mat(ms_diff_on,		vario, vario, vario, trans);
	set_mat(ms_diff_off,	vario, lowio, 0.00f, trans);
	set_mat(ms_ambi_on,		lowio, lowio, lowio, trans);
	set_mat(ms_ambi_off,	lowio, lowio, 0.00f, trans);
	set_mat(ms_spec_on,		vario, vario, vario, trans);
	set_mat(ms_spec_off,	vario, vario, vario, trans);
	set_mat(ms_none,		0.00f, 0.00f, 0.00f, trans);
}

void SJBPoint::set_colors()
{
	GLfloat shine = 3.0f;
	::glMaterialfv(GL_FRONT, GL_SHININESS,	&shine);
	::glMaterialfv(GL_FRONT, GL_EMISSION,	ms_none);

	switch(m_state_current) 
	{	
		case POINT_STATE_NONE:
			::glMaterialfv(GL_FRONT, GL_DIFFUSE,	ms_diff_off);
			::glMaterialfv(GL_FRONT, GL_AMBIENT,	ms_ambi_off);
			::glMaterialfv(GL_FRONT, GL_SPECULAR,	ms_spec_off);
			::glMaterialfv(GL_FRONT, GL_EMISSION,	ms_none);
		break;
		case POINT_STATE_PRIMED:
			::glMaterialfv(GL_FRONT, GL_DIFFUSE,	ms_diff_on);
			::glMaterialfv(GL_FRONT, GL_AMBIENT,	ms_ambi_on);
			::glMaterialfv(GL_FRONT, GL_SPECULAR,	ms_spec_on);
//			::glMaterialfv(GL_FRONT, GL_DIFFUSE,	ms_diff_off);
//			::glMaterialfv(GL_FRONT, GL_AMBIENT,	ms_ambi_off);
//			::glMaterialfv(GL_FRONT, GL_SPECULAR,	ms_spec_off);
//			::glMaterialfv(GL_FRONT, GL_EMISSION,	ms_ambi_on);
		break;
	}
}

void SJBPoint::set_mat(GLfloat* mat, float f0, float f1, float f2, float f3)
{
	mat[0] = f0;
	mat[1] = f1;
	mat[2] = f2;
	mat[3] = f3;
}

void SJBPoint::gl_render()
{
	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
		float px, py, pz;
		get_value(px, py, pz);
		::glTranslatef(px, py, pz);
		set_colors();
		::glCallList(ms_sphere_list);
	::glPopMatrix();
}

void SJBPoint::pass_zero()
{
	m_state_current = POINT_STATE_NONE;
}



