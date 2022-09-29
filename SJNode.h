
#pragma once

#include "SJPtrList.h"
#include "fstream.h"

class SJNode;
typedef SJPtrList<SJNode*> PL_NODE;

class SJNode  
{
public:

						SJNode();
	virtual			~SJNode();
	virtual void	gl_render(int render_type);
	virtual void	write_to_file(ofstream* p_open_file);
	virtual void	add_child(SJNode* p_node);
	SJNode* 			get_child(int num);
	int				get_num_kids();
	virtual void	delete_data();
	void				print_float_only(ofstream* p_open_file, float value);

private:

	PL_NODE			mpl_child_nodes;
};


