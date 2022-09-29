
#pragma once

#include "SJNodeInSpace.h"

class SJNodeCamera : public SJNodeInSpace
{
public:
						SJNodeCamera();
	virtual				~SJNodeCamera();
	virtual void		gl_render(int render_type);
	void				set_aspect(float aspect, float y_extent);

	float				m_fov_y;
	float				m_aspect_ratio;
};

