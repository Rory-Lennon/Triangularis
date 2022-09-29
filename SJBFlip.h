
#pragma once

#include "SJBVec.h"

#define TIMER_INC_ANGLE	10

class SJBFlip
{
public:
						SJBFlip();
	void				init(int x, int y, int z, int angle);
	virtual void	gl_render();
	bool				inc_flip();
	bool				inc_90();
	bool				inc_360();
	void				inc_infinite();
	int				get_flip();
	int				is_flip();
	void				orient(int ori);
	void				set_angle(int angle);

protected:

	SJBVec			m_axis;
	int				m_angle;
	int				m_flip;
};




