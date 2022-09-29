
#pragma once

#include "SJNodeInSpace.h"
#include "SJBPiece.h"
#include "SJNodeLight.h"
#include "SJBPoint.h"
#include "SJBTria.h"
#include "SJBFlip.h"
#include "SJBTexture.h"
#include "SJBClick.h"

class SJNodeBoard : public SJNodeInSpace
{
public:
							SJNodeBoard();
	virtual				~SJNodeBoard();
	virtual void		gl_render(int render_mode);
	void					set_points_gl();
	void					set_pieces_gl();
	void					set_board_gl();
	void					set_clicks_gl();
	void					set_grid_gl();
	void					set_index_gl();
	void					render_points();
	void					render_pieces(int render_mode);
	void					render_grid();
	void					render_index();
	void					render_clicks();
	void					new_game(int num_rows, int num_cols, float height);
	void					create_points();		
	void					create_trias();	
	void					add_temp_point(int index);
	void					add_temp_tria(int index);
	void					clear_temp_points();
	void					clear_temp_trias();
	void					add_tria(int num, int orientation);
	void					add_piece(float px, float py, int spx, int spy);
	void					select_piece(int piece_num);
	void					mouse_inc(float dx, float dy);
	void					shuffle();
	void					mouse_up();
	SJBVec*				get_mouse_pos();
	bool					inc_x_selected();
	bool					inc_y_selected();
	bool					inc_board_90();
	bool					inc_board_360();
	void					pass_zero();
	void					set_aspect();
	void					set_aspect(float aspect);
	float					get_y_extent();
	void					delete_components();
	virtual void		write_to_file(ofstream* p_open_file);
	bool					check_win();
	void					update_covered();
	void					update_dims();

	bool					m_show_grid;
	bool					m_show_index;
	SJBClick				m_click_horizontal;
	SJBClick				m_click_vertical;
//	SJBTexture			m_warp;
	SJBTexture			m_wood;
	float					m_screen_x;
	float					m_screen_y;
	float					m_board_x;
	float					m_board_y;
	float					m_aspect;
	SJBFlip				m_board_flip;
	SJBPiece*			mp_selected_piece;
	int					m_line_rows;
	int					m_line_cols;
	PL_POINTS			ml_all_points;
	PL_TRIA				ml_all_trias;
	PL_PIECE				ml_all_pieces;
	PL_POINTS			ml_temp_points;
	PL_TRIA				ml_temp_trias;
};


