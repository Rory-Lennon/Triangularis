
#include "Triangularis.h"
#include "SJBFlip.h"

SJBFlip::SJBFlip()
{
	m_flip	= 1;
	set_angle(0);
}

void SJBFlip::init(int x, int y, int z, int angle)
{
	m_axis.set_value((float)x, (float)y, (float)z); 
	set_angle(angle);
}

void SJBFlip::gl_render()
{
	float x, y, z;
	m_axis.get_value(x, y, z); 
	::glRotatef((float)m_angle, x, y, z);
}

bool SJBFlip::inc_flip()
{
	m_angle += 30;
	if(m_angle == 180) 
	{
		m_flip *= -1;
		return false;
	}
	if(m_angle == 360) 
	{
		m_angle = 0;
		m_flip *= -1;
		return false;
	}
	return true;
}

bool SJBFlip::inc_90()
{
	m_angle += TIMER_INC_ANGLE;
	if(m_angle >= 90) return false;
	return true;
}

bool SJBFlip::inc_360()
{
	m_angle += TIMER_INC_ANGLE;
	if(m_angle >= 360) 
	{
		m_angle = 0;
		return false;
	}
	return true;
}

void SJBFlip::inc_infinite()
{
	m_angle += 5;
	if(m_angle >= 360) 
	{
		m_angle = 0;
	}
}

int SJBFlip::get_flip()
{
	return m_flip;
}

int SJBFlip::is_flip()
{
	if(m_flip == -1) return 1;
	else return 0;
}

void SJBFlip::orient(int ori)
{
	if((ori % 2) == 1) 
	{
		m_flip *= -1;
		set_angle(180);
	}
}

void SJBFlip::set_angle(int angle)
{
	m_angle = angle;
}
