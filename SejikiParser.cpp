
#include "Jiki.h"
#include "SejikiParser.h"
#include "SJBPiece.h"

CSejikiParser::CSejikiParser(SJNodeBoard* p_board)
{
	mp_board			= p_board;
	m_pos				= 0;
	m_left_mark		= 0;
	m_right_mark	= 0;
}

bool CSejikiParser::read_file(CString file_path)
{
	CFile file;
	int opened = file.Open(file_path, false);

	if(opened == 0) return false;

	int len = file.GetLength();
	char* p_char = m_str.GetBuffer(len);
	file.Read(p_char, len);
	m_str.ReleaseBuffer();

	return process_file();
}
 
bool CSejikiParser::res_file(int RES_ID)
{
	HMODULE hModule	= GetModuleHandle(NULL);
	HRSRC hResInfo		= FindResource(hModule, MAKEINTRESOURCE(RES_ID), "SJK");	

	if(hResInfo == 0)	return false;

	HGLOBAL hGlobal	= LoadResource(hModule, hResInfo);
	char* p_chars		= (char*) LockResource(hGlobal);
	DWORD dwLength		= SizeofResource(hModule, hResInfo);
	CString str(p_chars, dwLength);
	m_str = str;
	FreeResource(hGlobal);

	return process_file();
}

CSejikiParser::~CSejikiParser()
{}

bool CSejikiParser::process_file()
{
	bool valid = false;

	CString single_line;
	while(read_seg(single_line))
	{
		valid = true;
		if(single_line.Find("/BOARD")	>= 0)	break;
		if(single_line.Find("BOARD")	>= 0)	new_game(single_line);
	}
	mp_board->shuffle();
	mp_board->select_piece(1);
	return valid;
}

bool CSejikiParser::check_dims(int rows, int cols)
{
	bool state = false;

	if( ((rows == 2)		&& (cols == 8	)) |
		 ((rows == 6)		&& (cols == 18	)) |
		 ((rows == 6)		&& (cols == 2	)) |
		 ((rows == 6)		&& (cols == 4	)) |
		 ((rows == 6)		&& (cols == 6	)) |
		 ((rows == 6)		&& (cols == 8	)) |
		 ((rows == 14)		&& (cols == 4	)) |
		 ((rows == 10)		&& (cols == 12	))) state = true;

	return state;
}

void CSejikiParser::new_game(CString line_data)
{
	int	num_rows = extract_int(line_data, "NUMROWS");
	int	num_cols = extract_int(line_data, "NUMCOLS");
	float height	= extract_float(line_data, "HEIGHT");

	if(!check_dims(num_rows, num_cols)) return;

	mp_board->new_game(num_rows, num_cols, height);

	CString single_line;
	while(read_seg(single_line))
	{
		if(single_line.Find("/PIECE")	>= 0) break;
		if(single_line.Find("PIECE")	>= 0)	new_piece(single_line);
	}
}

void CSejikiParser::new_piece(CString line_data)
{
	float posx	= extract_float(line_data, "POSX");
	float posy	= extract_float(line_data, "POSY");
	int	flipx = extract_int(line_data,	"FLIPX");
	int	flipy = extract_int(line_data,	"FLIPY");

	mp_board->clear_temp_trias();

	CString single_line;
	while(read_seg(single_line))
	{
		if(single_line.Find("PART") >= 0) 
		{
			int part_index = extract_int(single_line, "INDEX");
			if(part_index > 0) mp_board->add_temp_tria(part_index);
		}
		else break;
	}
	mp_board->add_piece(posx, posy, flipx, flipy);
	mp_board->clear_temp_trias();
}

bool CSejikiParser::read_seg(CString &str)
{
	bool keep_going = true;
	while(keep_going)
	{
		if(m_pos >= m_str.GetLength()) return false;
		if(m_str.GetAt(m_pos) == '<') m_left_mark = m_pos;
		if(m_str.GetAt(m_pos) == '>') keep_going = false;
		m_pos++;
	}
	str = m_str.Mid(m_left_mark, m_pos - m_left_mark);
//	str.Remove("\n");
	str.MakeUpper();
	return true;
}

float CSejikiParser::string_to_float(CString str)
{
	if(str.GetLength() <= 0) return 0.0f;
	if(str.GetLength() >= 100) return 0.0f;

	LPTSTR p_chars = str.GetBuffer(0);
	float ret_float = (float)atof(p_chars);
	str.ReleaseBuffer();
	return ret_float;
}

int CSejikiParser::string_to_int(CString str)
{
	if(str.GetLength() <= 0) return 0;
	if(str.GetLength() >= 100) return 0;

	LPTSTR p_chars = str.GetBuffer(0);
	int ret_int = atoi(p_chars);
	str.ReleaseBuffer();

   return ret_int;
}

float CSejikiParser::extract_float(CString str_input, CString str_after)
{
	char dqs = 34;
	int pos_char = str_input.Find(str_after);
	if(pos_char <= 0) return 0.0f;
	int dqs_pos_1 = str_input.Find(dqs, pos_char);
	int dqs_pos_2 = str_input.Find(dqs, dqs_pos_1 + 1);
	return string_to_float(str_input.Mid(dqs_pos_1 + 1, dqs_pos_2 - dqs_pos_1 - 1));
}

int CSejikiParser::extract_int(CString str_input, CString str_after)
{
	char dqs = 34;
	int pos_char = str_input.Find(str_after);
	if(pos_char <= 0) return 0;
	int dqs_pos_1 = str_input.Find(dqs, pos_char);
	int dqs_pos_2 = str_input.Find(dqs, dqs_pos_1 + 1);
	return string_to_int(str_input.Mid(dqs_pos_1 + 1, dqs_pos_2 - dqs_pos_1 - 1));
}
