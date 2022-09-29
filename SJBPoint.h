
#pragma once

#include "SJPtrList.h"
#include "SJBVec.h"

#define POINT_STATE_NONE	0
#define POINT_STATE_PRIMED	1
#define POINT_STATE_LIGHT	2

class SJBPoint;
typedef SJPtrList<SJBPoint*> PL_POINTS;

class SJBPoint : public SJBVec
{

public:
							SJBPoint();
							SJBPoint(int num, float x, float y, float z);
							~SJBPoint();
	virtual	void		gl_render();
	virtual void		set_colors();
	static void			set_mat(GLfloat* mat, float f1, float f2, float f3, float f4);
	static void			static_init();
	void					pass_zero();

	int					m_num;
	static GLfloat		ms_diff_on[4];
	static GLfloat		ms_diff_off[4];
	static GLfloat		ms_ambi_on[4];
	static GLfloat		ms_ambi_off[4];
	static GLfloat		ms_spec_on[4];
	static GLfloat		ms_spec_off[4];
	static GLfloat		ms_none[4];
	static GLuint		ms_sphere_list;
	float					m_point_size;
	int					m_state_current;
	int					m_state_last;
	PL_POINTS			ml_sisters;
};

