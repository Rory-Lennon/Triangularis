
#pragma once

#include "SJBLine.h"
#include "SJBTria.h"
#include "SJBPoint.h"
#include "SJBFlip.h"

#define PIECE_FLOATING	0
#define PIECE_PRIMED	1
#define PIECE_SLOTTED	2

#define FLIP_X			0
#define FLIP_Y			1

#include "SJNodeInSpace.h"

class SJBPiece : public SJNodeInSpace
{
public:	
								SJBPiece(PL_TRIA* pl_peice_trias, PL_TRIA* pl_all_trias, int piece_num);
								~SJBPiece();
	virtual void			gl_render(int render_mode);
	void						initialise(float px, float py, int ox, int oy);
	void						mouse_inc(float dx, float dy);
	void						slot_move();
	void						check_prox();
	void						create_lines();
	void						add_line(SJBPoint* p_p1, SJBPoint* p_p2);
	void 						select_piece();
	void						unselect_piece();
	void						orient(int ox, int oy);
	void						get_tria_diff_pos(SJBTria* p_tria, SJBVec &vec);
	void						set_colors();
	void						uncover();
	void						mouse_up();
	static void				set_mat(GLfloat* mat, float f1, float f2, float f3, float f4);
	static void				static_init();
	SJBVec*					get_mouse_pos();
	bool						inc_x();
	bool						inc_y();
	virtual void			write_to_file(ofstream* p_open_file);
	void						print_float_only(ofstream* p_open_file, float value);
	void						show_select();

	SJBText					m_text;
	SJBFlip					m_flip_x;
	SJBFlip					m_flip_y;
	static GLfloat			ms_shine;
	static GLfloat			ms_color_green[4];
	static GLfloat			ms_color_green_2[4];
	static GLfloat			ms_color_red[4];
	static GLfloat			ms_color_blue[4];
	static GLfloat			ms_color_yellow[4];
	static GLfloat			ms_emit_yellow[4];
	static GLfloat			ms_emit_blue[4];
	static GLfloat			ms_color_cyan[4];
	static GLfloat			ms_color_purple[4];
	static GLfloat			ms_color_white[4];
	static GLfloat			ms_color_dark[4];
	static GLfloat			ms_color_emit[4];
	SJBVec					m_mouse_pos;
	SJBVec					m_prime_vec;
	unsigned char			m_piece_num;

	int						m_state_slotted;
	int						m_state_selected;
	PL_TRIA					ml_trias;
	PL_TRIA*					mpl_all_trias;
	PL_TRIA					ml_primed_trias;
	PL_LINE					ml_lines;
};

typedef SJPtrList<SJBPiece*> PL_PIECE;
