
#pragma once

#include "SJNodeInSpace.h"
#include "SJBPoint.h"

class SJNodeLight : public SJNodeInSpace
{
public:

							SJNodeLight(SJBVec& pos, GLint light_id);
	virtual				~SJNodeLight();
	static void			static_init();
	virtual void		gl_render(int render_type);

	GLint					m_light_id;
	SJBPoint				m_point;
};	

