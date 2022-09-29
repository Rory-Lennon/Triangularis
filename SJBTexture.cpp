
#include "Jiki.h"
#include "SJBTexture.h"

SJBTexture::SJBTexture()
{
	resize(40.0f, 25.0f);
	m_tex_bind = 0;
	m_board_x = 4.0f;
	m_board_y = 3.0f;
}

SJBTexture::~SJBTexture()
{}

void SJBTexture::init(int tex_res_id)
{
   HBITMAP hbm = (HBITMAP) ::LoadImage(AfxGetResourceHandle(), 
                  MAKEINTRESOURCE(tex_res_id), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        
	BITMAP bm; 
	::GetObject(hbm, sizeof (bm), &bm);

	::glGenTextures(1, &m_tex_bind);	
	::glBindTexture(GL_TEXTURE_2D, m_tex_bind);

	::gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bm.bmWidth, bm.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE,
								bm.bmBits );

	DeleteObject(hbm);
}

void SJBTexture::resize(float wx, float wy)
{
	m_board_x = wx;
	m_board_y = wy;
}

void SJBTexture::gl_render()
{
	::glPushMatrix();

		::glScalef(m_board_x, m_board_y, 1.0f);

		::glEnable(GL_TEXTURE_2D);

		GLfloat no_color[]	= { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat some_color[]	= { 1.0f, 1.0f, 1.0f, 1.0f };
		::glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,	some_color);
		::glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,	no_color);
		::glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,	no_color);
		::glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,	no_color);

		::glBindTexture(GL_TEXTURE_2D, m_tex_bind);

		float bx = 1.0f;
		float by = 1.0f;

		::glBegin(GL_QUADS);
		
		::glNormal3f(0.0f, 0.0f, 1.0f);
		::glTexCoord2f(0.0f, 0.0f);	::glVertex3f(-bx, -by, -0.2f);
		::glTexCoord2f(1.0f, 0.0f);	::glVertex3f( bx, -by, -0.2f);
		::glTexCoord2f(1.0f, 1.0f);	::glVertex3f( bx,  by, -0.2f);
		::glTexCoord2f(0.0f, 1.0f);	::glVertex3f(-bx,  by, -0.2f);

		::glEnd();

		::glDisable(GL_TEXTURE_2D);

	::glPopMatrix();
}