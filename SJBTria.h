
#pragma once

#include "SJBPoint.h"
#include "SJBText.h"
#include "fstream.h"

#define TRIA_NOT_PRIMED				0
#define TRIA_PRIMED					1

#define TRIA_NOT_COVERED			0
#define TRIA_COVERED					1

#define TRIA_INDEPENDANT			0
#define TRIA_OWNED					1

#define TRIA_ORIENTATION_UP		1
#define TRIA_ORIENTATION_DOWN   -1

class SJBTria : public SJBVec
{
public:
								SJBTria(PL_POINTS* pl_points, int num, int orientation);
								~SJBTria();
	static void				static_init();
	static void				static_tria(SJBVec &vec_1,
								SJBVec &vec_2,
								SJBVec &vec_3);
	void						pass_zero();
	void						prime();
	void						get_xyz(int i, SJBVec& vec);
	void						set_sis(int pt_from, int sis_num, int pt_to);
	void						set_diff_pos(SJBVec &vec);
	void						slot();
	virtual void			gl_render();
	virtual void			render_grid();
	virtual void			write_to_file(ofstream* p_open_file);
	void						print_index();

	SJBText					m_text;
	int						m_num;
	static GLuint			ms_tria_list;
	SJBVec					m_diff_pos;
	int						m_board_ori;
	int						m_state_primed;
	int						m_state_covered;
	int						m_state_owned;
	PL_POINTS				ml_points;
};

typedef SJPtrList<SJBTria*> PL_TRIA;