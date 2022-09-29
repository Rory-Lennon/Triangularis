
#include "Jiki.h"
#include "SJBTria.h"

GLuint SJBTria::ms_tria_list; // STATIC

SJBTria::SJBTria(PL_POINTS* pl_points, int num, int orientation)
{
	m_num					= num;
	m_board_ori			= orientation;
	m_state_primed		= TRIA_NOT_PRIMED;
	m_state_covered	= TRIA_NOT_COVERED;
	m_state_owned		= TRIA_INDEPENDANT;

	ml_points.transfer_from_list(pl_points);

	set_value(0.0f, 0.0f, 0.0f);

	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		SJBPoint* p_point = ml_points.get_next(pos);
		*this += *p_point;
	}
	*this /= (float)(ml_points.get_count());

	if(m_board_ori == TRIA_ORIENTATION_UP)
	{
		set_sis(0, 1, 1);
		set_sis(0, 2, 2);
		set_sis(2, 0, 1);
	}
	if(m_board_ori == TRIA_ORIENTATION_DOWN)
	{
		set_sis(0, 0, 1);
		set_sis(0, 1, 2);
		set_sis(1, 2, 2);
	}
}

void SJBTria::static_init()
{
	float height = 0.075f;

	SJBVec vec_0	( 0.0f,	 0.0f,		0.0f);		// CENTER
	SJBVec vec_1	(-0.5f,	-0.2887f,   height);
	SJBVec vec_2	( 0.5f,	-0.2887f,   height);
	SJBVec vec_3	( 0.0f,	 0.5774f,   height);
	SJBVec vec_4	(-0.5f,	-0.2887f,  -height);
	SJBVec vec_5	( 0.5f,	-0.2887f,  -height);
	SJBVec vec_6	( 0.0f,	 0.5774f,  -height);

	float shrink = 0.70f;
	vec_1	*= shrink;
	vec_2	*= shrink;
	vec_3	*= shrink;
	vec_4	*= shrink;
	vec_5	*= shrink;
	vec_6	*= shrink;

	ms_tria_list = ::glGenLists(1);

	glNewList(ms_tria_list, GL_COMPILE);

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

void SJBTria::static_tria(SJBVec &vec_1,
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

void SJBTria::set_sis(int pt_from, int sis_num, int pt_to)
{
	ml_points.get_at(pt_from)->ml_sisters.set_at(sis_num, ml_points.get_at(pt_to));
}

SJBTria::~SJBTria()
{}

void SJBTria::get_xyz(int i, SJBVec& vec)
{
	float x, y, z;
	ml_points.get_at(i)->get_value(x, y, z);
	vec.set_value(x, y, z);
}

void SJBTria::prime()
{
	POS pos = ml_points.get_head_pos();
	while(pos) ml_points.get_next(pos)->m_state_current = POINT_STATE_PRIMED;
}

void SJBTria::pass_zero()
{
	m_state_primed = TRIA_NOT_PRIMED;
}

void SJBTria::set_diff_pos(SJBVec &vec)
{
	SJBVec centroid(*this);
	centroid -= vec;
	m_diff_pos.set_value(centroid);
}

void SJBTria::slot()
{
	m_state_covered = TRIA_COVERED;
	m_state_primed = TRIA_NOT_PRIMED;
}

void SJBTria::gl_render()
{
	::glMatrixMode(GL_MODELVIEW);

	float dx, dy, dz;
	m_diff_pos.get_value(dx, dy, dz);

	::glPushMatrix();
		::glTranslatef(dx, dy, dz);
		if(m_board_ori == TRIA_ORIENTATION_DOWN) ::glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		::glCallList(ms_tria_list);
	::glPopMatrix();
}

void SJBTria::write_to_file(ofstream* p_open_file)
{
	char dqs = '"';
	*p_open_file << "<PART INDEX=" << dqs << m_num << dqs << "/>" << endl; 
}

void SJBTria::print_index()
{
	float xp = get_component(0);
	float yp = get_component(1);
	m_text.print_int(m_num, xp, yp);
}

void SJBTria::render_grid()
{
	::glBegin(GL_LINE_LOOP);

	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		SJBPoint* p_point = ml_points.get_next(pos);
		::glVertex3fv(p_point->get_value());
	}
	::glEnd();
}