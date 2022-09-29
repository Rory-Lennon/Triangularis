
#pragma once

#include "SJBVec.h"
#include "SJBRotation.h"

class SJBLine : public SJBVec
{
public:
						SJBLine(SJBVec& v1, SJBVec& v2);
						~SJBLine();
	static void		static_init();
	virtual void	gl_render();

	SJBRotation		m_rot_z;
	static GLuint	ms_line_list;
};

typedef SJPtrList<SJBLine*> PL_LINE;