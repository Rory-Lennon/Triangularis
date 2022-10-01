
#include "Triangularis.h"
#include "SJNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

SJNode::SJNode()
{}

SJNode::~SJNode()
{
	mpl_child_nodes.delete_data();
}

void SJNode::gl_render(int render_type)
{
	POS pos = mpl_child_nodes.get_head_pos();
	while(pos) mpl_child_nodes.get_next(pos)->gl_render(render_type);
}

void SJNode::add_child(SJNode* p_node)
{
	mpl_child_nodes.add_tail(p_node);
}
	
SJNode* SJNode::get_child(int num)
{
	return mpl_child_nodes.get_at(num);
}

int SJNode::get_num_kids()
{
	return mpl_child_nodes.get_count();
}

void SJNode::delete_data()
{
	mpl_child_nodes.delete_data();
}

void SJNode::write_to_file(ofstream* p_open_file)
{
	POS pos = mpl_child_nodes.get_head_pos();
	while(pos) mpl_child_nodes.get_next(pos)->write_to_file(p_open_file);
}

void SJNode::print_float_only(ofstream* p_open_file, float value)
{
	char szBuffer[6];
	::sprintf(szBuffer, "%6.1f", value);

	for(int i = 0; i < 6; i++)
	{
		if(szBuffer[i] != ' ') *p_open_file << szBuffer[i];
	}
}