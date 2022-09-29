
#include "Jiki.h"
#include "SJBVec.h"

SJBVec::SJBVec()
{
	vector[0] = 0.f;     
	vector[1] = 0.f;        
	vector[2] = 0.f;  
}

SJBVec::SJBVec(const float v[3])
{
   vector[0] = v[0];
   vector[1] = v[1];
   vector[2] = v[2];
}

SJBVec::SJBVec(float x, float y, float z)
{
   vector[0] = x;
   vector[1] = y;
   vector[2] = z;
}

SJBVec::~SJBVec()
{}

SJBVec SJBVec::cross(const SJBVec& v) const
{
   return SJBVec((vector[1] * v.vector[2]) - (vector[2] * v.vector[1]),
                 (vector[2] * v.vector[0]) - (vector[0] * v.vector[2]),
                 (vector[0] * v.vector[1]) - (vector[1] * v.vector[0]));
}

float SJBVec::dot(const SJBVec &v) const
{
   return (vector[0] * v.vector[0] + 
		     vector[1] * v.vector[1] + 
			  vector[2] * v.vector[2]);
}

bool SJBVec::equals(const SJBVec v, float tolerance) const
{
   return (fabs(vector[0] - v.vector[0]) < fabs(tolerance) && 
			  fabs(vector[1] - v.vector[1]) < fabs(tolerance) && 
			  fabs(vector[2] - v.vector[2]) < fabs(tolerance));
}

const float* SJBVec::get_value() const
{
   return &vector[0];
}

void SJBVec::get_value(float &x, float &y, float &z) const
{
   x = vector[0];
   y = vector[1];
   z = vector[2];
}

float	SJBVec::get_component(int component)
{
	return vector[component];
}

void SJBVec::set_component(int component, float value)
{
	vector[component] = value;
}

float SJBVec::length() const
{
   return float (sqrt(vector[0] * vector[0] + 
						vector[1] * vector[1] + 
						vector[2] * vector[2]));
}

float SJBVec::length(const SJBVec &other_vec) const
{
	float ov_x, ov_y, ov_z;
	float tv_x, tv_y, tv_z;

	float l_x, l_y, l_z;

	other_vec.get_value(ov_x, ov_y, ov_z);
				 get_value(tv_x, tv_y, tv_z);

	l_x = ov_x - tv_x;
	l_y = ov_y - tv_y;
	l_z = ov_z - tv_z;

   return float(sqrt(l_x * l_x + l_y * l_y + l_z * l_z));
}

float SJBVec::length_xy(const SJBVec &other_vec) const
{
	float ov_x, ov_y, ov_z;
	float tv_x, tv_y, tv_z;
	float l_x, l_y;

	other_vec.get_value(ov_x, ov_y, ov_z);
	get_value(tv_x, tv_y, tv_z);

	l_x = ov_x - tv_x;
	l_y = ov_y - tv_y;

   return float(sqrt(l_x * l_x + l_y * l_y));
}

float SJBVec::angle(const SJBVec &other_vec) const
{
	return 2.0f * (float)asin(length(other_vec) / 2.0f) * 180.0f / 3.1415926536f;
}

void SJBVec::negate()
{
   vector[0] = -vector[0];
   vector[1] = -vector[1];
   vector[2] = -vector[2];
}

float SJBVec::normalize()
{
   float f = length();
   vector[0] /= f;
   vector[1] /= f;
   vector[2] /= f;
   return f;
}

void SJBVec::check_unity()
{
	if(vector[0] < 0.0f) vector[0] = 0.0f;
	if(vector[1] < 0.0f) vector[1] = 0.0f;
	if(vector[2] < 0.0f) vector[2] = 0.0f;

	if(vector[0] > 1.0f) vector[0] = 1.0f;
	if(vector[1] > 1.0f) vector[1] = 1.0f;
	if(vector[2] > 1.0f) vector[2] = 1.0f;
}

SJBVec& SJBVec::set_value(const SJBVec &bvec)
{
	set_value(bvec.get_value());

   return *this;
}

SJBVec& SJBVec::set_value(const float v[3])
{
   vector[0] = v[0];
   vector[1] = v[1];
   vector[2] = v[2];
   return *this;
}

SJBVec& SJBVec::set_value(float x, float y, float z)
{
   vector[0] = x;
   vector[1] = y;
   vector[2] = z;
   return *this;
}

float& SJBVec::operator [](int i)
{
   return vector[i];
}

const float& SJBVec::operator [](int i) const
{
   return vector[i];
}

SJBVec& SJBVec::operator =(const SJBVec& vec3f)
{
	set_value(vec3f.get_value());

   return *this;
}

SJBVec& SJBVec::operator *=(float d)
{
   vector[0] *= d;
   vector[1] *= d;
   vector[2] *= d;
   return *this;
}

SJBVec& SJBVec::operator /=(float d)
{
   vector[0] /= d;
   vector[1] /= d;
   vector[2] /= d;
   return *this;
}

SJBVec& SJBVec::operator +=(const SJBVec &u)
{
   vector[0] += u.vector[0];
   vector[1] += u.vector[1];
   vector[2] += u.vector[2];
   return *this;
}

SJBVec& SJBVec::operator -=(const SJBVec &u)
{
   vector[0] -= u.vector[0];
   vector[1] -= u.vector[1];
   vector[2] -= u.vector[2];
   return *this;
}

SJBVec SJBVec::operator -() const
{
   return SJBVec(-vector[0], -vector[1], -vector[2]);
}

//const SJBVec SJBVec::operator(int)++ // prefix
//{
//	count += 1;
//	return *this;
//}
	
//SJBVec& SJBVec::operator++() // prefix
//{ 
//	count += 1;
//	return *this;
//}
