
#include "Triangularis.h"
#include "SJNodeCamera.h"
#include "SJBMatrix.h"

SJNodeCamera::SJNodeCamera()
{
	m_fov_y	= 25.0f;
	m_aspect_ratio = 1.0f;
}

SJNodeCamera::~SJNodeCamera()
{}

void SJNodeCamera::gl_render(int render_type)
{
	::glMatrixMode(GL_PROJECTION);
	::gluPerspective(m_fov_y, m_aspect_ratio, 0.1f, 500.0f);
	::glMatrixMode(GL_MODELVIEW);

	float sx, sy, sz;
	m_pos.get_value(sx, sy, sz);
	::glTranslatef(sx, sy, sz);
}

void SJNodeCamera::set_aspect(float aspect, float y_extent)
{
	m_aspect_ratio = aspect;
	float z_back = (y_extent / 2.0f) / (float)tan((m_fov_y / 2.0f) * PI / 180.0f);
	m_pos.set_component(2, -z_back);
}

