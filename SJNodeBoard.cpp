
#include "Jiki.h"
#include "SJNodeBoard.h"
#include "SJBTexture.h"

SJNodeBoard::SJNodeBoard()
{
	m_line_rows				= 5;
	m_line_cols				= 7;
	mp_selected_piece		= NULL;
	m_screen_x				= 50.0f;
	m_screen_y				= 30.0f;
	m_board_x				= 40.0f;
	m_board_y				= 25.0f;
	m_click_horizontal.	set_click_type(CLICK_HORIZONTAL);
	m_click_vertical.		set_click_type(CLICK_VERTICAL);
	m_wood.					init(IDB_WOOD);
	m_board_flip.			init(1, 0, 0, 0);
	m_show_grid				= false;
	m_show_index			= false;
}

SJNodeBoard::~SJNodeBoard()
{
	delete_components();
}

void SJNodeBoard::delete_components()
{
	ml_all_points.delete_data();
	ml_all_pieces.delete_data();
	ml_all_trias.delete_data();
}

void SJNodeBoard::gl_render(int render_mode)
{
	set_board_gl();

	m_board_flip.gl_render();

	if(render_mode != RENDER_SELECT) m_wood.gl_render();

	set_points_gl();
	if(render_mode != RENDER_SELECT) render_points();

	set_clicks_gl();
	if(render_mode != RENDER_FLIP_INFINITE) render_clicks();

	set_pieces_gl();
	render_pieces(render_mode);

	set_grid_gl();
	if(m_show_grid && (render_mode != RENDER_SELECT)) render_grid();

	set_index_gl();
	if(m_show_index && (render_mode != RENDER_SELECT)) render_index();
}

void SJNodeBoard::set_pieces_gl()
{
	::glDisable(GL_DEPTH_TEST);
	::glEnable(GL_BLEND);
	::glEnable(GL_POLYGON_SMOOTH);
}

void SJNodeBoard::set_points_gl()
{
	::glShadeModel(GL_SMOOTH);
	::glEnable(GL_DEPTH_TEST);
	::glDisable(GL_BLEND);
	::glEnable(GL_POLYGON_SMOOTH);
}

void SJNodeBoard::set_board_gl()
{
	::glDisable(GL_COLOR_MATERIAL);
	::glEnable(GL_LIGHTING);

	::glDisable(GL_DEPTH_TEST);
	::glDisable(GL_BLEND);
	::glShadeModel(GL_FLAT);
}

void SJNodeBoard::set_clicks_gl()
{
	::glShadeModel(GL_FLAT);
	::glDisable(GL_DEPTH_TEST);
	::glEnable(GL_BLEND);
	::glEnable(GL_POLYGON_SMOOTH);
}

void SJNodeBoard::set_grid_gl()
{
	::glEnable(GL_COLOR_MATERIAL);
	::glDisable(GL_BLEND);
	::glShadeModel(GL_FLAT);
	::glDisable(GL_LIGHTING);

	::glColor3f(1.0f, 1.0f, 0.0f);
}

void SJNodeBoard::set_index_gl()
{
	::glColor3f(0.0f, 1.0f, 1.0f);
}

void SJNodeBoard::render_points()
{
	POS pos = ml_all_points.get_head_pos();
	while(pos) ml_all_points.get_next(pos)->gl_render();
}

void SJNodeBoard::render_pieces(int render_mode)
{
	POS pos = ml_all_pieces.get_head_pos();
	while(pos) ml_all_pieces.get_next(pos)->gl_render(render_mode);
}

void SJNodeBoard::render_grid()
{
	POS pos = ml_all_trias.get_head_pos();
	while(pos) ml_all_trias.get_next(pos)->render_grid();
}

void SJNodeBoard::render_index()
{
	POS pos = ml_all_trias.get_head_pos();
	while(pos) ml_all_trias.get_next(pos)->print_index();
}

void SJNodeBoard::render_clicks()
{
	m_click_horizontal.gl_render();
	m_click_vertical	.gl_render();
}

void SJNodeBoard::new_game(int num_rows, int num_cols, float height)
{	
	delete_components();

	m_screen_y = height;
	set_aspect();

	m_line_rows = num_rows + 1;
	m_line_cols = num_cols + 1;

	m_board_x = ((float)m_line_cols / 2.0f) + 1.0f;
	m_board_y = ((float)m_line_rows / 2.0f);
	m_wood.resize(m_board_x, m_board_y);

	create_points();
	create_trias();

	update_dims();
}

void	SJNodeBoard::create_points()
{
	int x, y;
	int num = 0;
	float px, py;
	int half_rows = m_line_rows / 2; 
	int half_cols = m_line_cols / 2;

	for (y = half_rows; y >= -half_rows; y--)
	{
		for (x = -half_cols; x <= half_cols; x++)
		{
			float indent = 0.0f;
			if((y % 2) == 0) indent = 0.5f;

			px = (float)x + indent - 0.25f;
			py = (float)(y * 0.8660f);

			SJBPoint* p_point = new SJBPoint(++num, px, py, 0.0f);
			ml_all_points.add_tail(p_point);
		}
	}
}

void SJNodeBoard::create_trias()
{	
	int x, y;
	int num = 0;
	int indent = 1;
	clear_temp_points();

	for (y = 0; y < (m_line_rows - 1); y++)
	{
		if((y % 2) == 0) indent = 0;
		else indent = 1;
		for (x = 0; x < (m_line_cols - 1); x++)
		{	
			add_temp_point((y * m_line_cols) + x);
			add_temp_point((y * m_line_cols) + x + 1);
			add_temp_point((y * m_line_cols) + x + m_line_cols + indent);
			add_tria(++num, TRIA_ORIENTATION_DOWN);
		}
	}

	for (y = 0; y < (m_line_rows - 1); y++)
	{
		if((y % 2) == 0) indent = 1;
		else indent = 0;
		for (x = 0; x < (m_line_cols - 1); x++)
		{	
			add_temp_point((y * m_line_cols) + x + indent);
			add_temp_point((y * m_line_cols) + x + m_line_cols + 1);
			add_temp_point((y * m_line_cols) + x + m_line_cols);
			add_tria(++num, TRIA_ORIENTATION_UP);
		}
	}
}

void SJNodeBoard::add_temp_point(int index)
{
	ml_temp_points.add_tail(ml_all_points.get_at(index));
}

void SJNodeBoard::add_temp_tria(int index)
{
	if(index > ml_all_trias.get_count()) return;
	SJBTria* p_tria = ml_all_trias.get_at(index - 1);
	if(p_tria->m_state_owned == TRIA_OWNED) return;
	p_tria->m_state_owned = TRIA_OWNED;
	ml_temp_trias.add_tail(p_tria);
}

void SJNodeBoard::clear_temp_points()
{
	ml_temp_points.delete_list_nodes();
}

void SJNodeBoard::clear_temp_trias()
{
	ml_temp_trias.delete_list_nodes();
}

void SJNodeBoard::add_tria(int num, int orientation)
{
	SJBTria* p_tria = new SJBTria(&ml_temp_points, num, orientation);
	ml_all_trias.add_tail(p_tria);
	clear_temp_points();
}

void SJNodeBoard::add_piece(float px, float py, int spx, int spy)
{
	SJBPiece* p_np = new SJBPiece(&ml_temp_trias, &ml_all_trias, ml_all_pieces.get_count() + 1);
	p_np->initialise(px, py, spx, spy);
	ml_all_pieces.add_tail(p_np);
	clear_temp_trias();
}

void SJNodeBoard::select_piece(int piece_num)
{
	int i;
	SJBPiece* p_np;

	for(i = 0; i < ml_all_pieces.get_count(); i++)
	{
		p_np = ml_all_pieces.get_at(i);
		{
			if((i + 1) == piece_num) 
			{
				mp_selected_piece = p_np;
				p_np->select_piece();
			}
			else p_np->unselect_piece();
		}
	}
	if(piece_num == -5) mp_selected_piece = NULL;
}

void SJNodeBoard::mouse_inc(float dx, float dy)
{
	if(mp_selected_piece != NULL) 
	{
		pass_zero();
		mp_selected_piece->mouse_inc(dx, dy);
	}
}

void SJNodeBoard::mouse_up()
{
	if(mp_selected_piece != NULL) mp_selected_piece->mouse_up();
	pass_zero();
}

bool SJNodeBoard::check_win()
{
	bool win = true;
	POS pos_tria = ml_all_trias.get_head_pos();
	while(pos_tria) if(ml_all_trias.get_next(pos_tria)->m_state_covered != TRIA_COVERED) win = false;
	update_covered();
	return win;
}

void SJNodeBoard::update_covered()
{
	int covered = 0;

	POS pos_tria = ml_all_trias.get_head_pos();
	while(pos_tria) if(ml_all_trias.get_next(pos_tria)->m_state_covered == TRIA_COVERED) covered++;

	if(ml_all_trias.get_count() <= 0) return;
	int percent = (covered * 100) /  ml_all_trias.get_count();

	AfxGetMainWnd()->PostMessage(MSG_UPDATE_COVERED, (WPARAM)percent, 0);
}

void SJNodeBoard::update_dims()
{
	AfxGetMainWnd()->PostMessage(MSG_UPDATE_DIMS, (WPARAM)m_line_rows - 1, (LPARAM)m_line_cols - 1);
}

void SJNodeBoard::shuffle()
{
	POS pos = ml_all_pieces.get_head_pos();
	while(pos) 
	{
		SJBPiece* p_piece = ml_all_pieces.get_next(pos);
		p_piece->mouse_inc(0.0f, 0.0f);
		p_piece->mouse_up();
		pass_zero();
	}
}

SJBVec* SJNodeBoard::get_mouse_pos()
{
	if(mp_selected_piece != NULL) return mp_selected_piece->get_mouse_pos();
	else return NULL;
}

bool SJNodeBoard::inc_x_selected()
{
	if(mp_selected_piece == NULL) return false;
	if(!mp_selected_piece->inc_x())
	{
		mouse_inc(0.0f, 0.0f);
		mouse_up();
		return false;
	}
	return true;
}

bool SJNodeBoard::inc_y_selected()
{
	if(mp_selected_piece == NULL) return false;
	if(!mp_selected_piece->inc_y())
	{
		mouse_inc(0.0f, 0.0f);
		mouse_up();
		return false;
	}
	return true;
}

bool SJNodeBoard::inc_board_90()
{
	return m_board_flip.inc_90();
}

bool SJNodeBoard::inc_board_360()
{
	return m_board_flip.inc_360();
}

void SJNodeBoard::pass_zero()
{
	POS pos_point = ml_all_points.get_head_pos();
	while(pos_point) ml_all_points.get_next(pos_point)->pass_zero();

	POS pos_tria = ml_all_trias.get_head_pos();
	while(pos_tria) ml_all_trias.get_next(pos_tria)->pass_zero();
}

void SJNodeBoard::set_aspect()
{
	m_screen_x = m_screen_y * m_aspect;
//	m_warp.					resize(m_screen_x,	m_screen_y);
	m_click_horizontal.	resize(m_screen_x,	m_screen_y);
	m_click_vertical.		resize(m_screen_x,	m_screen_y);
}

void SJNodeBoard::set_aspect(float aspect)
{
	m_aspect = aspect;
	set_aspect();
}

float SJNodeBoard::get_y_extent()
{
	return m_screen_y;
}

void SJNodeBoard::write_to_file(ofstream* p_open_file)
{
	char dqs = '"';

	*p_open_file << "<BOARD"; 
	*p_open_file << " NUMROWS=" << dqs << (m_line_rows - 1) << dqs;
	*p_open_file << " NUMCOLS=" << dqs << (m_line_cols - 1) << dqs;
	*p_open_file << " HEIGHT="  << dqs;
	print_float_only(p_open_file, m_screen_y);
	*p_open_file << dqs << ">" << endl;

	POS pos = ml_all_pieces.get_head_pos();
	while(pos) ml_all_pieces.get_next(pos)->write_to_file(p_open_file);
	
	*p_open_file << "</BOARD>" << endl;
}

