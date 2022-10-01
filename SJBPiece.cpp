
#include "Triangularis.h"
#include "SJBPiece.h"

SJBPiece::SJBPiece(PL_TRIA* pl_peice_trias, PL_TRIA* pl_all_trias, int piece_num)
{
///////////// INITIALISATION /////////////////////////////////
	POS pos;

	m_piece_num			= piece_num;
	m_state_slotted	= PIECE_FLOATING;
	m_state_selected	= SELECTED_NO;

	m_flip_x.init(0, 1, 0, 0);
	m_flip_y.init(1, 0, 0, 0);

	m_mouse_pos.set_value(0.0f, 0.0f, 0.0f);
	set_pos(0.0f, 0.0f, 0.0f);

	mpl_all_trias = pl_all_trias;
	ml_trias.transfer_from_list(pl_peice_trias);
//////////////////////////////////////////////////////////////

///////////// CENTROID ///////////////////////////////////////
	pos = ml_trias.get_head_pos();
	while(pos) 
	{
		SJBTria* p_tria = ml_trias.get_next(pos);	
		m_pos += *p_tria;
	}
	m_pos /= (float)(ml_trias.get_count());
//////////////////////////////////////////////////////////////

///////////// CONSTRUCTION ///////////////////////////////////
	pos = ml_trias.get_head_pos();
	while(pos) ml_trias.get_next(pos)->set_diff_pos(m_pos);
//////////////////////////////////////////////////////////////

	create_lines();
}

void SJBPiece::initialise(float px, float py, int ox, int oy)
{
	mouse_inc(px, py);
	orient(ox, oy);
}

void SJBPiece::create_lines()
{
///////////// LINES //////////////////////////////////////////
	int i, j, k, l;

	POS pos_tria_1 = ml_trias.get_head_pos();
	while(pos_tria_1) 
	{
		SJBTria* p_tria_1 = ml_trias.get_next(pos_tria_1);

		POS pos_tria_2 = pos_tria_1;
		while(pos_tria_2) 
		{
			SJBTria* p_tria_2 = ml_trias.get_next(pos_tria_2);

			if(p_tria_2 != p_tria_1)
			{
				for (i = 0; i < 3; i++)
				{
					SJBPoint* p_point_1 = p_tria_1->ml_points.get_at(i);

					for (j = 0; j < 3; j++)
					{
						SJBPoint* p_point_2 = p_tria_2->ml_points.get_at(j);
							
						if(p_point_1 == p_point_2)
						{
							for (k = 0; k < 3; k++)
							{
							SJBPoint* p_point_3 = p_tria_1->ml_points.get_at(k);

								for (l = 0; l < 3; l++)
								{
									SJBPoint* p_point_4 = p_tria_2->ml_points.get_at(l);
							
									if(p_point_3 == p_point_4)
									{					
										if(p_point_1 != p_point_3)
										{
											if(p_point_1->ml_sisters.get_at(0) == p_point_3)
											{
												add_line(p_point_1, p_point_3);
											}
											if(p_point_1->ml_sisters.get_at(1) == p_point_3)
											{
												add_line(p_point_1, p_point_3);
											}
											if(p_point_1->ml_sisters.get_at(2) == p_point_3)
											{
												add_line(p_point_1, p_point_3);
											}											
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
////////////////////////
}

void SJBPiece::gl_render(int render_mode)
{
	POS pos;
	float px, py, pz;

	::glPushMatrix();

		switch(render_mode) 
		{	
			case RENDER_FLIP_INFINITE:
				m_flip_x.inc_infinite();
			case RENDER_NORMAL:
			case RENDER_SELECT:
				m_mouse_pos.get_value(px, py, pz);
				::glTranslatef(px, py, pz);
				m_flip_x.gl_render();
				m_flip_y.gl_render();
			break;
			case RENDER_HINT:
				m_pos.get_value(px, py, pz);
				::glTranslatef(px, py, pz);
			break;

		}
		set_colors();

		::glLoadName(m_piece_num);

		::glShadeModel(GL_FLAT);

		pos = ml_trias.get_head_pos();
		while(pos) ml_trias.get_next(pos)->gl_render();

		::glShadeModel(GL_SMOOTH);

		pos = ml_lines.get_head_pos();
		while(pos) ml_lines.get_next(pos)->gl_render();

	::glPopMatrix();
}

void SJBPiece::show_select()
{
	m_text.print_int(m_state_selected, m_mouse_pos.get_component(0), m_mouse_pos.get_component(1));
//	m_text.print_int(m_piece_num, m_mouse_pos.get_component(0) + 0.2f, m_mouse_pos.get_component(1));
}

void SJBPiece::add_line(SJBPoint* p_p1, SJBPoint* p_p2)
{
	SJBVec pv1(*p_p1);
	pv1 -= m_pos;

	SJBVec pv2(*p_p2);
	pv2 -= m_pos;

	SJBLine* p_line = new SJBLine(pv1, pv2);
	ml_lines.add_tail(p_line);
}

SJBPiece::~SJBPiece()
{
	ml_lines.delete_data();
}

void SJBPiece::get_tria_diff_pos(SJBTria* p_tria, SJBVec &vec)
{
	float forix = (float)(m_flip_x.get_flip());
	float foriy = (float)(m_flip_y.get_flip());

	vec.set_component(0, (p_tria->m_diff_pos.get_component(0) * forix) + m_mouse_pos.get_component(0));
	vec.set_component(1, (p_tria->m_diff_pos.get_component(1) * foriy) + m_mouse_pos.get_component(1));
	vec.set_component(2, 0.0f);
}

GLfloat		SJBPiece::ms_shine;
GLfloat		SJBPiece::ms_color_green[4];		// STATIC
GLfloat		SJBPiece::ms_color_green_2[4];	// STATIC
GLfloat		SJBPiece::ms_color_red[4];			// STATIC
GLfloat		SJBPiece::ms_color_blue[4];		// STATIC
GLfloat		SJBPiece::ms_color_yellow[4];		// STATIC
GLfloat		SJBPiece::ms_color_cyan[4];		// STATIC
GLfloat		SJBPiece::ms_color_purple[4];		// STATIC
GLfloat		SJBPiece::ms_color_white[4];		// STATIC
GLfloat		SJBPiece::ms_color_dark[4];		// STATIC
GLfloat		SJBPiece::ms_emit_yellow[4];		// STATIC
GLfloat		SJBPiece::ms_emit_blue[4];			// STATIC

void SJBPiece::static_init()
{
	float lowio = 0.20f;
	float vario = 1.00f;
	float trans = 0.50f;
	ms_shine = 80.0f;
	set_mat(ms_color_red,		vario, 0.00f, 0.00f, trans);
	set_mat(ms_color_green,		0.00f, vario, 0.00f, trans);
	set_mat(ms_color_green_2,	0.00f, 0.50f, 0.00f, trans);
	set_mat(ms_color_blue,		0.00f, 0.00f, vario, trans);
	set_mat(ms_color_cyan,		0.00f, 0.00f, 0.50f, trans);
	set_mat(ms_color_yellow,	vario, vario, 0.00f, trans);
	set_mat(ms_color_purple,	vario, 0.00f, vario, trans);
	set_mat(ms_color_white,		vario, vario, vario, trans);
	set_mat(ms_color_dark,		0.00f, 0.00f, 0.00f, trans);
	set_mat(ms_emit_yellow,		trans, 0.00f, 0.00f, trans);
	set_mat(ms_emit_blue,		0.00f, 0.00f, lowio, trans);
}

void SJBPiece::set_colors()
{
	::glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,		&ms_shine);
//	::glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,		ms_color_dark);
	::glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,		ms_color_dark);
//	::glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,		ms_color_white);

	switch (m_state_slotted) 
	{	
		case PIECE_FLOATING:
			::glMaterialfv(GL_BACK,  GL_DIFFUSE, ms_color_blue);
			::glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_color_cyan);
			::glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms_color_blue);
		break;
		case PIECE_SLOTTED:
		case PIECE_PRIMED:
			::glMaterialfv(GL_BACK,  GL_DIFFUSE, ms_color_green);
			::glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_color_green_2);
			::glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms_color_green);
		break;
	}
	switch (m_state_selected) 
	{	
		case SELECTED_NO:
			::glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ms_color_dark);
		break;
		case SELECTED_YES:
			::glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ms_emit_yellow);
		break;
	}
}

void SJBPiece::set_mat(GLfloat* mat, float f0, float f1, float f2, float f3)
{
	mat[0] = f0; mat[1] = f1; mat[2] = f2; mat[3] = f3;
}

void SJBPiece::mouse_inc(float dx, float dy)
{
	m_mouse_pos.set_value((m_mouse_pos.get_component(0) + dx), 
		(m_mouse_pos.get_component(1) + dy), 0.0f);

	uncover();
	check_prox();
}

void SJBPiece::mouse_up()
{
	if(m_state_slotted == PIECE_PRIMED) slot_move();
}

void SJBPiece::slot_move()
{
	m_mouse_pos += m_prime_vec;
//	unselect_piece();
	m_state_slotted = PIECE_SLOTTED;

	POS pos = ml_primed_trias.get_head_pos();
	while(pos) ml_primed_trias.get_next(pos)->slot();
}

void SJBPiece::uncover()
{
	m_state_slotted = PIECE_FLOATING;
	POS pos_primed = ml_primed_trias.get_head_pos();
	while(pos_primed) ml_primed_trias.get_next(pos_primed)->m_state_covered = TRIA_NOT_COVERED;	
}

void SJBPiece::check_prox()
{
	POS pos_piece, pos_board;
	SJBVec diff_vec;
	SJBTria* p_piece_tria; 
	SJBTria* p_board_tria;

	ml_primed_trias.delete_list_nodes();

	pos_piece = ml_trias.get_head_pos();
	while(pos_piece) 
	{	
		p_piece_tria = ml_trias.get_next(pos_piece);
		get_tria_diff_pos(p_piece_tria, diff_vec);

		pos_board = mpl_all_trias->get_head_pos();
		while(pos_board) 
		{	
			p_board_tria = mpl_all_trias->get_next(pos_board);
			
			int piece_ori = p_piece_tria->m_board_ori * m_flip_y.get_flip();
			if(p_board_tria->m_board_ori == piece_ori)
			{
				if(p_board_tria->m_state_covered == TRIA_NOT_COVERED) 
				{
					float len = p_board_tria->length_xy(diff_vec);
					if(len < 0.45f) 
					{
						p_piece_tria->m_state_primed = TRIA_PRIMED;
						ml_primed_trias.add_tail(p_board_tria);

						SJBVec slot_vec(*p_board_tria);
						slot_vec -= diff_vec;
						m_prime_vec.set_value(slot_vec);
					}
				}
			}
		}
	}

	int temp_state = TRUE;
	pos_piece = ml_trias.get_head_pos();
	while(pos_piece) 
	{	
		SJBTria* p_piece_tria = ml_trias.get_next(pos_piece);
		if(p_piece_tria->m_state_primed == TRIA_NOT_PRIMED) temp_state = FALSE;
	}
	if(temp_state == TRUE)
	{
		m_state_slotted = PIECE_PRIMED;
		pos_board = ml_primed_trias.get_head_pos();
		while(pos_board) ml_primed_trias.get_next(pos_board)->prime();
	}
	else m_state_slotted = PIECE_FLOATING;
}

void SJBPiece::select_piece()
{
	m_state_selected = SELECTED_YES;
}

void SJBPiece::unselect_piece()
{
	m_state_selected = SELECTED_NO;
}

void SJBPiece::orient(int ox, int oy)
{
	m_flip_x.orient(ox);
	m_flip_y.orient(oy);
}

bool SJBPiece::inc_x()
{
	return m_flip_x.inc_flip();
}

bool SJBPiece::inc_y()
{
	return m_flip_y.inc_flip();
}

SJBVec* SJBPiece::get_mouse_pos()
{
	return &m_mouse_pos;
}

void SJBPiece::write_to_file(ofstream* p_open_file)
{
	char dqs = '"';

	*p_open_file << "<PIECE"; 
	*p_open_file << " POSX=" << dqs;
	print_float_only(p_open_file, m_mouse_pos.get_component(0));	
	*p_open_file << dqs << " POSY=" << dqs;
	print_float_only(p_open_file, m_mouse_pos.get_component(1));	
	*p_open_file << dqs << " FLIPX=" << dqs << m_flip_x.is_flip() << dqs;
	*p_open_file << " FLIPY=" << dqs << m_flip_y.is_flip() << dqs << ">" << endl;

	POS pos = ml_trias.get_head_pos();
	while(pos) ml_trias.get_next(pos)->write_to_file(p_open_file);

	*p_open_file << "</PIECE>" << endl;
}

void SJBPiece::print_float_only(ofstream* p_open_file, float value)
{
	char szBuffer[6];
	::sprintf(szBuffer, "%6.1f", value);

	for(int i = 0; i < 6; i++)
	{
		if(szBuffer[i] != ' ') *p_open_file << szBuffer[i];
	}
}