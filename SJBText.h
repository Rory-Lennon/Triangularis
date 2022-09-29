
#pragma once

class SJBText
{
public:

							SJBText();
							~SJBText();
	static void			static_init();
	void					print_int(int num, float ras_x, float ras_y);

	static GLuint		ms_zero_list;
};