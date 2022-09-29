
#pragma once

#include "SJBVec.h"
#include "SJBRotation.h"

#define CLICK_HORIZONTAL	0
#define CLICK_VERTICAL		1

class SJBClick : public SJBVec
{
public:
								SJBClick();
								~SJBClick();
	static void				static_init();
	static void				static_tria(SJBVec &vec_1,
												SJBVec &vec_2,
												SJBVec &vec_3);
	static void				static_shrink(SJBVec &vec_shrink,
													SJBVec &vec_towards);

	virtual void			gl_render();
	void						set_colors();	
	void						set_click_type(int click_type);
	void						resize(float px, float py);

	int						m_select_name;
	int						m_click_type;
	SJBRotation				m_rot_z;
	static GLuint			ms_click_list;
};

