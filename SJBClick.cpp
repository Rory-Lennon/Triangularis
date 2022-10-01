
#include "Triangularis.h"
#include "SJBClick.h"

GLuint SJBClick::ms_click_list;	// STATIC

SJBClick::SJBClick()
{
	m_select_name = 1;
}

void SJBClick::static_init()
{
	float height = 0.075f;

	SJBVec vec_0( 0.00f,	 1.0f,		0.0f);		// CENTER
	SJBVec vec_1(-0.35f,	 0.7113f,   height);
	SJBVec vec_2( 0.35f,	 0.7113f,   height);
	SJBVec vec_3( 0.00f,	 2.5000f,   height);
	SJBVec vec_4(-0.35f,	 0.7113f,  -height);
	SJBVec vec_5( 0.35f,	 0.7113f,  -height);
	SJBVec vec_6( 0.00f,	 2.5000f,  -height);

	float shrink_1 = 0.70f;

	vec_1	*= shrink_1;
	vec_2	*= shrink_1;
	vec_3	*= shrink_1;
	vec_4	*= shrink_1;
	vec_5	*= shrink_1;
	vec_6	*= shrink_1;

	static_shrink(vec_1, vec_0);
	static_shrink(vec_2, vec_0);
	static_shrink(vec_3, vec_0);

	ms_click_list = ::glGenLists(1);

	glNewList(ms_click_list, GL_COMPILE);

		static_tria(vec_1, vec_2, vec_0);
		static_tria(vec_2, vec_3, vec_0);
		static_tria(vec_3, vec_1, vec_0);

		static_tria(vec_5, vec_4, vec_0);
		static_tria(vec_6, vec_5, vec_0);
		static_tria(vec_4, vec_6, vec_0);

		static_tria(vec_1, vec_5, vec_2);
		static_tria(vec_1, vec_4, vec_5);

		static_tria(vec_2, vec_5, vec_6);
		static_tria(vec_2, vec_6, vec_3);

		static_tria(vec_3, vec_6, vec_4);
		static_tria(vec_3, vec_4, vec_1);

	glEndList();
}

void SJBClick::static_tria(SJBVec &vec_1,
									SJBVec &vec_2,
									SJBVec &vec_3)
{
	SJBVec vn_1(vec_3);
	SJBVec vn_2(vec_3);
	vn_1 -= vec_1;
	vn_2 -= vec_2;

	SJBVec vec_normal(vn_1.cross(vn_2));
	vec_normal.normalize();

	::glBegin(GL_TRIANGLES);

		::glNormal3fv(vec_normal.get_value());
		::glVertex3fv(vec_1.get_value());

		::glNormal3fv(vec_normal.get_value());
		::glVertex3fv(vec_2.get_value());

		::glNormal3fv(vec_normal.get_value());
		::glVertex3fv(vec_3.get_value());

	::glEnd();
}

void SJBClick::static_shrink(SJBVec &vec_shrink, SJBVec &vec_towards)
{
	SJBVec vector(vec_towards);
	vector -= vec_shrink;
	vector /= 5.0f;
//	vec_shrink += vector;
	vec_shrink.set_component(0, vec_shrink.get_component(0) + vector.get_component(0));
	vec_shrink.set_component(1, vec_shrink.get_component(1) + vector.get_component(1));
}

SJBClick::~SJBClick()
{}

void SJBClick::gl_render()
{
	set_colors();

	::glPushMatrix();
		float dx, dy, dz;
		get_value(dx, dy, dz);
		::glTranslatef(dx, dy, dz);
		m_rot_z.gl_render();
		::glLoadName(m_select_name);
		::glCallList(ms_click_list);
	::glPopMatrix();
}

void SJBClick::set_colors()
{
	GLfloat vec_cyan[]	= { 0.0f, 0.0f, 0.0f, 0.5f };
	GLfloat vec_red[]		= { 1.0f, 0.0f, 0.0f, 0.5f };
	GLfloat no_color[]	= { 0.0f, 0.0f, 0.0f, 0.5f };
	GLfloat vec_white[]	= { 1.0f, 0.5f, 0.5f, 0.5f };

	::glMaterialfv(GL_FRONT_AND_BACK,	GL_AMBIENT,		no_color);
	::glMaterialfv(GL_FRONT_AND_BACK,	GL_SPECULAR,	vec_red);
	::glMaterialfv(GL_FRONT_AND_BACK,	GL_EMISSION,	no_color);
	::glMaterialfv(GL_FRONT,				GL_DIFFUSE,		vec_cyan);
	::glMaterialfv(GL_BACK,					GL_DIFFUSE,		vec_red);
}

void SJBClick::set_click_type(int click_type)
{
	m_click_type = click_type;
	if(m_click_type == CLICK_HORIZONTAL)	
	{
		m_rot_z.set_value(0.0f, 0.0f, 1.0f, -90.0f);
		m_select_name = 1000;
	}
	if(m_click_type == CLICK_VERTICAL)
	{
		m_rot_z.set_value(0.0f, 0.0f, 1.0f, 0.0f);
		m_select_name = 1001;
	}
}

void SJBClick::resize(float px, float py)
{
	float border = px / 15.0f;
	float cx = (-px / 2.0f) + border; 
	float cy = (-py / 2.0f) + border; 
	set_value(cx, cy, 0.0f);
}

