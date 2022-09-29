
#include "Jiki.h"
#include "SejikiView.h"
#include "SejikiParser.h"
#include "SJNodeBoard.h"
#include "SJBText.h"
#include "SJBTexture.h"
#include "fstream.h"
#include "SJBClick.h"

IMPLEMENT_DYNCREATE(CSejikiView, CBaseView)

CSejikiView::CSejikiView()
{
	mp_camera		= NULL;
	mp_board			= NULL;
	m_render_mode	= RENDER_NORMAL;
	m_chooser		= false;
	m_res_duck		= NULL;
	m_reg_clicks	= 0;
	m_show_grid		= false;
	m_show_index	= false;
}

CSejikiView::~CSejikiView()
{}

BEGIN_MESSAGE_MAP(CSejikiView, CBaseView)
	//{{AFX_MSG_MAP(CSejikiView)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSejikiView::static_init()
{
	SJBPoint::static_init();
	SJBTria::static_init();
	SJBLine::static_init();
	SJBPiece::static_init();
	SJBText::static_init();
	SJBClick::static_init();
}

void CSejikiView::set_chooser(HGLRC hglrc)
{
	m_chooser		= true;
	m_render_mode	= RENDER_FLIP_INFINITE;
	create_gl();
	::wglShareLists(hglrc, m_hglrc);
	build_scene_graph();
	mp_board->m_board_flip.init(1, 0, 0, 0);
}

void CSejikiView::set_main_board()
{
	m_chooser		= false;
	m_render_mode	= RENDER_NORMAL;
	create_gl();
	static_init();
	build_scene_graph();
}	

void CSejikiView::start_chooser_timer()
{
	SetTimer(TIMER_FLIP_PIECES_INF, 100, NULL);
}

void CSejikiView::build_scene_graph()
{
	set_gl();

	mp_camera = new SJNodeCamera;
	m_root.add_child(mp_camera);

	SJBVec light_pos;
	SJNodeLight* p_light;

	light_pos.set_value(1.0f, 1.0f, 2.0f);
	p_light = new SJNodeLight(light_pos, GL_LIGHT0);
	m_root.add_child(p_light);

	mp_board = new SJNodeBoard();
	mp_board->m_board_flip.init(1, 0, 0, 90);
	m_root.add_child(mp_board);
}

void CSejikiView::set_gl()
{
	::glEnable(GL_DEPTH_TEST);
	::glClearDepth(1.0f);
////////// GENERAL ///////////////////////
	::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	::glEnable(GL_DEPTH_TEST);
	::glEnable(GL_LIGHTING);
	::glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
	::glShadeModel(GL_SMOOTH);
	::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	::glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	::glDisable(GL_CULL_FACE);
	::glDisable(GL_COLOR_MATERIAL);
//////////////////////////////////////////

////////// TEXTURES //////////////////////
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	::glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	::glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//////////////////////////////////////////
}

bool CSejikiView::read_duck(CString file_path)
{
	CFile file;
	int opened = file.Open(file_path, false);
	if(opened == 0) return false;
	else file.Close();
	m_read_duck = file_path;
	SetTimer(TIMER_FLIP_READ, TIMER_FLIP_INC, NULL);
	return true;
}

void CSejikiView::read_pick_up()
{
	KillTimer(TIMER_FLIP_READ);
	read_file(m_read_duck);
	mp_board->update_covered();
	SetTimer(TIMER_FLIP_BOARD_360, TIMER_FLIP_INC, NULL);
}

void CSejikiView::read_file(CString file_path)
{
	CSejikiParser sjp(mp_board);
	sjp.read_file(file_path);
	resize();
}

void CSejikiView::res_duck(int RES_ID)
{
	m_res_duck = RES_ID;
	SetTimer(TIMER_FLIP_RES, TIMER_FLIP_INC, NULL);
}

void CSejikiView::res_pick_up()
{
	KillTimer(TIMER_FLIP_RES);
	res_file(m_res_duck);
	mp_board->update_covered();
	SetTimer(TIMER_FLIP_BOARD_360, TIMER_FLIP_INC, NULL);
}

bool CSejikiView::res_file(int RES_ID)
{
	CSejikiParser sjp(mp_board);
	int limit = RES_ID;
	if(limit > LAST_GAME) limit = LAST_GAME;
	bool returner = sjp.res_file(limit);
	resize();
	return returner;
}

void CSejikiView::save_file(CString file_path)
{
	ofstream open_file(file_path);
	if(open_file.fail()) return;
	m_root.write_to_file(&open_file);
	open_file.close();
}

int CSejikiView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	if(m_chooser) return 0;
	return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CSejikiView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(m_chooser) return;

	switch (nChar) 
	{	
		case 16: // shift
		break;
		case 37: // left arrow
		case 39: // right arrow
			SetTimer(TIMER_FLIP_PIECE_X, 10, NULL);
		break;
		case 38: // up arrow
		case 40: // down arrow
			SetTimer(TIMER_FLIP_PIECE_Y, 10, NULL);
		break;
	}
	gl_render();

//	CString str;
//	str.Format("nChar %i \n", nChar);
//	TRACE(str);	
}

void CSejikiView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(m_chooser) return;

	switch (nChar) 
	{	
		case 16: // shift
		case 17: // ctrl

		break;
		case 37: // left arrow
		case 39: // right arrow

		break;
		case 40: // down arrow
		case 38: // up arrow

		break;
	}
}

void CSejikiView::OnSize(UINT nType, int cx, int cy) 
{
	CPaintDC dc(this); 

	::wglMakeCurrent(dc.m_ps.hdc, m_hglrc);
	::glViewport(0, 0, cx, cy);
//	::wglMakeCurrent(NULL, NULL);

	m_aspect_ratio = (float)cx / (float)cy;

	if(mp_board	== NULL) return;
	mp_board->set_aspect(m_aspect_ratio);

	if(mp_camera == NULL) return;
	mp_camera->set_aspect(m_aspect_ratio, mp_board->get_y_extent());

	gl_render();

	CView::OnSize(nType, cx, cy);
}

void CSejikiView::OnDraw(CDC* pDC)
{
	gl_render();
}

void CSejikiView::gl_render()
{
	CPaintDC dc(this); 
	::wglMakeCurrent(dc.m_ps.hdc, m_hglrc);
	::glDrawBuffer(GL_BACK);
	::glRenderMode(GL_RENDER);
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	m_root.gl_render(m_render_mode);
	glFlush();
	SwapBuffers(dc.m_ps.hdc);
//	::wglMakeCurrent(NULL, NULL);
}

void CSejikiView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_chooser) return;
	CView::OnLButtonDown(nFlags, point);
	SetCapture();
	check_click();
	m_mouse_last = point;
	select(point);
	gl_render();
}

void CSejikiView::select(CPoint pt)
{
	CPaintDC dc(this); 
	::wglMakeCurrent(dc.m_ps.hdc, m_hglrc);

	GLint viewport[4];
	::glGetIntegerv(GL_VIEWPORT, viewport);

	double px = (double)pt.x;
	double py = (double)(viewport[3] - pt.y);
	GLuint selectbuf[100];
	GLint hits;

	::glSelectBuffer(100, selectbuf);
	::glRenderMode(GL_SELECT);
	::glInitNames();
	::glPushName(0);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPickMatrix(px, py, 2.0, 2.0, viewport);
	m_root.gl_render(RENDER_SELECT);
	::glFlush();

	hits = ::glRenderMode(GL_RENDER);
	if(hits > 0) 
	{
		switch ((int)selectbuf[3]) 
		{	
			case 1000: // FLIP HORIZONTAL
				SetTimer(TIMER_FLIP_PIECE_X, 10, NULL);
			break;
			case 1001: // FLIP VERTICAL
				SetTimer(TIMER_FLIP_PIECE_Y, 10, NULL);
			break;
			default:
				mp_board->select_piece((int)selectbuf[3]);
			break;
		}
	}
	else mp_board->select_piece(-5);

	::wglMakeCurrent(NULL, NULL);
}

void CSejikiView::check_click()
{
	return;

	if(((CJikiApp*)AfxGetApp())->m_reg) return;

	if(++m_reg_clicks >= CLICKS_TO_REG)
	{
		m_reg_clicks = 0;
		ReleaseCapture();
		((CJikiApp*)AfxGetApp())->OnRegister();
	}
}

void CSejikiView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_chooser) return;
	CBaseView::OnMouseMove(nFlags, point);

	if(GetCapture() == this)
	{
		GLint viewport[4];
		::glGetIntegerv(GL_VIEWPORT, viewport);
		float scaler = mp_board->get_y_extent() / (float)viewport[3];
		float dx = (float)(point.x - m_mouse_last.x);
		float dy = (float)(point.y - m_mouse_last.y);	
		mp_board->mouse_inc(dx * scaler, -dy * scaler);
	}
	m_mouse_last = point;
	gl_render();
}

void CSejikiView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_chooser) return;
	CBaseView::OnLButtonUp(nFlags, point);
	mp_board->mouse_up();
	if(mp_board->check_win()) 
	{
		int game = ((CJikiApp*)AfxGetApp())->get_last_game();
		res_duck(++game);
		((CJikiApp*)AfxGetApp())->set_last_game(game);
	}
	gl_render();
	ReleaseCapture();
}

void CSejikiView::OnTimer(UINT nIDEvent) 
{
	CView::OnTimer(nIDEvent);

	switch(nIDEvent) 
	{	
		case TIMER_FLIP_RES:
			if (!mp_board->inc_board_90()) res_pick_up();
		break;
		case TIMER_FLIP_READ:
			if (!mp_board->inc_board_90()) read_pick_up();
		break;
		case TIMER_FLIP_BOARD_360:
			if (!mp_board->inc_board_360()) KillTimer(TIMER_FLIP_BOARD_360);
		break;
		case TIMER_FLIP_PIECE_X:
			if (!mp_board->inc_x_selected()) KillTimer(TIMER_FLIP_PIECE_X);
		break;
		case TIMER_FLIP_PIECE_Y:
			if (!mp_board->inc_y_selected()) KillTimer(TIMER_FLIP_PIECE_Y);
		break;
		case TIMER_FLIP_PIECES_INF:
			gl_render();
		break;
	}
	gl_render();
}

void CSejikiView::resize()
{
	CRect rect;
	GetClientRect(&rect);
	OnSize(NULL, rect.right, rect.bottom);
}

void CSejikiView::toggle_grid()
{
	m_show_grid = !m_show_grid;
	mp_board->m_show_grid = m_show_grid;
}

void CSejikiView::toggle_index()
{
	m_show_index = !m_show_index;
//	if(m_show_index) m_render_mode = RENDER_HINT;
//	else m_render_mode = RENDER_NORMAL;
	mp_board->m_show_index = m_show_index;	
}

void CSejikiView::spin_360()
{
	SetTimer(TIMER_FLIP_BOARD_360, 50, NULL);
}
