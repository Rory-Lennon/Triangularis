
#pragma once

class SJBTexture 
{
public:
							SJBTexture();
							~SJBTexture();
	void					init(int tex_res_id);

	virtual	void		gl_render();
	void					resize(float wx, float wy);

	float					m_board_x;
	float					m_board_y;
	GLuint				m_tex_bind;
};							
