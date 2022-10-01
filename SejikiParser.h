
#pragma once

#include "SJPtrList.h"
#include "SJNodeBoard.h"

class CSetriangularisParser
{
public:

							CSetriangularisParser(SJNodeBoard* p_board);
							~CSetriangularisParser();
	bool					read_file(CString file_path);
	bool					res_file(int RES_ID);
	bool					process_file();
	void					new_game(CString line_data);
	void					new_piece(CString line_data);
	bool					read_seg(CString &str);
	bool					check_dims(int rows, int cols);

	CString				m_str;

protected:

	int					m_pos;
	int					m_left_mark;
	int					m_right_mark;

	float					extract_float(CString str_input, CString str_after);
	int					extract_int(CString str_input, CString str_after);
	float					string_to_float(CString str);
	int					string_to_int(CString str);

	SJNodeBoard*		mp_board;
};


