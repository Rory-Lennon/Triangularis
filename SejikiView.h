
#pragma once

#include "BaseView.h"
#include "SJBVec.h"
#include "SJNodeCamera.h"
#include "SJNodeBoard.h"

#define TIMER_FLIP_BOARD_90			1
#define TIMER_FLIP_BOARD_360			2
#define TIMER_FLIP_READ					3
#define TIMER_FLIP_RES					4
#define TIMER_FLIP_PIECE_X				5
#define TIMER_FLIP_PIECE_Y				6
#define TIMER_FLIP_PIECES_INF			7

#define TIMER_FLIP_INC				 100
#define CLICKS_TO_REG				  10

class CSetriangularisView : public CBaseView
{
public:

	DECLARE_DYNCREATE(CSetriangularisView)

							CSetriangularisView(); 
	virtual				~CSetriangularisView();
	static void			static_init();
	virtual void		build_scene_graph();
	void					set_gl();
	void					gl_render();
	void					read_file(CString file_path);
	bool					res_file(int RES_ID);
	void					save_file(CString str);
	void					resize();
	void					res_duck(int RES_ID);
	void					res_pick_up();
	bool					read_duck(CString file_path);
	void					read_pick_up();
	void					set_chooser(HGLRC hglrc);
	void					start_chooser_timer();
	void					set_main_board();
	void					check_click();
	void					spin_360();
	void					toggle_grid();
	void					toggle_index();
	void					select(CPoint pt);

	bool					m_show_grid;
	bool					m_show_index;
	int					m_render_mode;
	int					m_res_duck;
	CString				m_read_duck;
	float					m_aspect_ratio;
	CPoint				m_mouse_last;
	SJNode				m_root;
	SJNodeCamera*		mp_camera;
	SJNodeBoard*		mp_board;

protected:

	int					m_reg_clicks;

	//{{AFX_VIRTUAL(CSetriangularisView)
protected:
	virtual void		OnDraw(CDC* pDC);      
	//}}AFX_VIRTUAL

public:
	//{{AFX_MSG(CSetriangularisView)
	afx_msg void		OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void		OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void		OnSize(UINT nType, int cx, int cy);
	afx_msg void		OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void		OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void		OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void		OnTimer(UINT nIDEvent);
	afx_msg int			OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
