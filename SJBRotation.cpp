
#include "Jiki.h"
#include "SJBRotation.h"

SJBRotation::SJBRotation()
{
	set_value(0.0f, 0.0f, 1.0f, 0.0f);
}

SJBRotation::SJBRotation(const float v[4])
{
	set_value(v);
}

SJBRotation::SJBRotation(float q0, float q1, float q2, float q3)
{
	set_value(q0, q1, q2, q3);
}

SJBRotation::SJBRotation(const SJBMatrix &m)
{
	set_value(m);
}

SJBRotation::SJBRotation(const SJBVec &axis, float degrees)
{
	set_value(axis, degrees);
}

SJBRotation::SJBRotation(const SJBVec &rotateFrom, const SJBVec &rotateTo)
{
	set_value(rotateFrom, rotateTo);
}

SJBRotation& SJBRotation::set_value(const SJBMatrix& m)
{
	double tr, s;
	int i, j, k;
	const int nxt[3] = { 1, 2, 0 };
   
	tr = m[0][0] + m[1][1] + m[2][2];
   
	if ( tr > 0.0 )
	{
		s = sqrt( tr + 1.0 );
        quaternion[3] = float ( s * 0.5 );
        s = 0.5 / s;
         
        quaternion[0] = float ( ( m[1][2] - m[2][1] ) * s );
        quaternion[1] = float ( ( m[2][0] - m[0][2] ) * s );
        quaternion[2] = float ( ( m[0][1] - m[1][0] ) * s );
    }
	else
    {
        i = 0;
        if(m[1][1] > m[0][0]) i = 1;
         
        if(m[2][2] > m[i][i]) i = 2;
         
        j = nxt[i];
        k = nxt[j];
         
        s = sqrt((m[i][j] - (m[j][j] + m[k][k])) + 1.0);
         
        quaternion[i] = float ( s * 0.5 );
        s = 0.5 / s;
         
        quaternion[3] = float((m[j][k] - m[k][j]) * s );
        quaternion[j] = float((m[i][j] + m[j][i]) * s );
        quaternion[k] = float((m[i][k] + m[k][i]) * s );
	}
	return *this;
}

SJBRotation& SJBRotation::set_value(const float q[4])
{
	quaternion[0] = q[0];
	quaternion[1] = q[1];
	quaternion[2] = q[2];
	quaternion[3] = q[3];
	return *this;
}

SJBRotation& SJBRotation::set_value(float q0, float q1, float q2, float q3)
{
	quaternion[0] = q0;  
	quaternion[1] = q1;     
	quaternion[2] = q2; 
	quaternion[3] = q3;
	return *this;
}

SJBRotation& SJBRotation::set_value(const SJBVec& axis, float degrees)
{
	quaternion[0] = axis[0];
	quaternion[1] = axis[1];
	quaternion[2] = axis[2];
	quaternion[3] = degrees;
	return *this;
}

const float* SJBRotation::get_value() const
{
   return &quaternion[0];
}

void SJBRotation::get_value(float &q0, float &q1, float &q2, float &q3) const
{
   q0 = quaternion[0];  
	q1 = quaternion[1];     
	q2 = quaternion[2];     
	q3 = quaternion[3];
}

void SJBRotation::get_angle(float &angle)
{
	angle = quaternion[3];	
}

void SJBRotation::set_angle(float angle)
{
	quaternion[3] = angle;	
}

void SJBRotation::inc_angle(float angle)
{
	quaternion[3] += angle;	
}

void SJBRotation::get_value(SJBVec& axis, float& degrees) const
{
	axis[0] = quaternion[0];  
	axis[1] = quaternion[1];     
	axis[2] = quaternion[2]; 
	degrees = quaternion[3];	
}

void SJBRotation::get_value(SJBMatrix &matrix) const
{
	SJBVec naxis(quaternion[0], quaternion[1], quaternion[2]);
	naxis.normalize();

	float radians = DEG2RAD * quaternion[3];

//	float degsTemp = (float)fmod(quaternion[3], 360.0);
//	if(degsTemp < 0.f) degsTemp += 360.0f;
//	float radians = M_PI * degsTemp / 180.0f;

	double sint = sin(radians);
	double cost = cos(radians);
	double ux   = naxis[0];
	double ux2  = ux * ux;
	double uy   = naxis[1];
	double uy2  = uy * uy;
	double uz   = naxis[2];
	double uz2  = uz * uz;

	matrix[0][0] = (float)(ux2 + cost * (1 - ux2));
	matrix[0][1] = (float)(ux * uy * (1 - cost) - uz * sint);
	matrix[0][2] = (float)(uz * ux * (1 - cost) + uy * sint);
	matrix[0][3] = 0.f;
	matrix[1][0] = (float)(ux * uy * (1 - cost) + uz * sint);
	matrix[1][1] = (float)(uy2 + cost * (1 - uy2));
	matrix[1][2] = (float)(uy * uz * (1 - cost) - ux * sint);
	matrix[1][3] = 0.f;
	matrix[2][0] = (float)(uz * ux * (1 - cost) - uy * sint);
	matrix[2][1] = (float)(uy * uz * (1 - cost) + ux * sint);
	matrix[2][2] = (float)(uz2 + cost * (1 - uz2));
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 1.f;
}

SJBRotation& SJBRotation::set_value(const SJBVec& rotateFrom, const SJBVec& rotateTo)
{
	SJBVec from(rotateFrom);  
	from.normalize();
	SJBVec to(rotateTo);      
	to.normalize();
	SJBVec axis = from.cross(to);

	float radsin  = float(sqrt((1 - from.dot(to)) / 2));
 	quaternion[0] = float(radsin * axis[0]);
 	quaternion[1] = float(radsin * axis[1]);
 	quaternion[2] = float(radsin * axis[2]);
 	quaternion[3] = float(sqrt((1 + from.dot(to)) / 2));
	return *this;
}

SJBRotation& SJBRotation::invert()
{
   SJBVec axis;
   float   radians;
   get_value(axis,radians);
   set_value(axis,-radians);
   return *this;
}

SJBRotation SJBRotation::inverse() const
{
   SJBVec axis;
   float   radians;
   get_value(axis,radians);
   return SJBRotation(axis,-radians);
}

void SJBRotation::scaleAngle( float scaleFactor )
{
	SJBVec axis;
	float   radians;

	get_value(axis, radians);
	set_value(axis, radians * scaleFactor);
}

SJBRotation SJBRotation::slerp( const SJBRotation & /*rot0*/, const SJBRotation & /*rot1*/, float /*t*/ )
{
   return SJBRotation();
}

SJBRotation SJBRotation::identity()
{
   static SJBRotation ident(SJBVec(0.f, 0.f, 1.f), 0.f);
   return ident;
}

float& SJBRotation::operator [](int i)
{
   return quaternion[i];
}

const float& SJBRotation::operator [](int i) const
{
   return quaternion[i];
}

void SJBRotation::gl_render()
{
	::glRotatef(quaternion[3], quaternion[0], quaternion[1], quaternion[2]);
}
