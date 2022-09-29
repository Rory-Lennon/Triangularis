
#pragma once

#include "SJNode.h"
#include "SJBVec.h"
//#include "SJBRotation.h"

class SJNodeInSpace : public SJNode  
{
public:

					SJNodeInSpace();
	virtual			~SJNodeInSpace();

	void			set_pos(float px, float py, float pz);
	void			set_rot_x(float rot);
	void			set_rot_y(float rot);
	void			diff_move(float dx, float dy);
	virtual void	gl_render(int render_type);

protected:

	SJBVec			m_pos;
//	SJBRotation		m_rot_x;
//	SJBRotation		m_rot_y;
};


