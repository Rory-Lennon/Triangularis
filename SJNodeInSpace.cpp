
#include "Jiki.h"
#include "SJNodeInSpace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

SJNodeInSpace::SJNodeInSpace()
{}

SJNodeInSpace::~SJNodeInSpace()
{}

void SJNodeInSpace::set_pos(float px, float py, float pz)
{
	m_pos.set_value(px, py, pz);
}

void SJNodeInSpace::diff_move(float dx, float dy)
{
	float cx, cy, cz;
	m_pos.get_value(cx, cy, cz);
	cx += dx;
	cy += dy;
	m_pos.set_value(cx, cy, cz);
}

void SJNodeInSpace::gl_render(int render_type)
{
	SJNode::gl_render(render_type);
}