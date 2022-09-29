
#include "Jiki.h"
#include "SJNodeLight.h"
#include "SJBMatrix.h"

SJNodeLight::SJNodeLight(SJBVec& pos, GLint light_id)
{
	m_pos.set_value(pos.get_value());
	m_light_id = light_id;
}

SJNodeLight::~SJNodeLight()
{}

void SJNodeLight::gl_render(int render_type)
{
	::glMatrixMode(GL_MODELVIEW);
	::glEnable(m_light_id);

	GLfloat vec_ambi[] = { 0.2f, 0.2f, 0.2f, 0.5f };
	::glLightfv(m_light_id, GL_AMBIENT, vec_ambi);

	GLfloat vec_diff[] = { 0.9f, 0.8f, 0.9f, 0.5f };
	::glLightfv(m_light_id, GL_DIFFUSE, vec_diff);

	GLfloat vec_spec[] = { 1.0f, 1.0f, 1.0f, 0.5f };
	::glLightfv(m_light_id, GL_SPECULAR, vec_spec);

	float lx, ly, lz;
	m_pos.get_value(lx, ly, lz);
	GLfloat vec_light[] = { lx, ly, lz, 0.0f };
	::glLightfv(m_light_id, GL_POSITION, vec_light);
}

