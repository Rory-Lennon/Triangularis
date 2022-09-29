
#pragma once

#include "SJPtrList.h"

class SJBVec;
typedef SJPtrList<SJBVec*> PL_VECS;

class SJBVec
{
public:
					SJBVec();
					SJBVec(const float v[3]);
					SJBVec(float x, float y, float z);
					~SJBVec();

	SJBVec          cross(const SJBVec &v) const;
	float           dot(const SJBVec &v) const;
	bool			equals(const SJBVec v, float tolerance) const;
   
	const float*    get_value() const;
	void            get_value(float &x, float &y, float &z) const;
	float			get_component(int component);
	virtual void	set_component(int component, float value);

	float           length() const;
	float			length(const SJBVec &other_vec) const;
	float			length_xy(const SJBVec &other_vec) const;
	void            negate();
	float           normalize();
   
	float			angle(const SJBVec &bvec) const;

	void			check_unity();

	SJBVec&			set_value(const SJBVec &bvec);
	SJBVec&         set_value(const float v[3]);
	SJBVec&         set_value(float x, float y, float z);
	SJBVec&         set_value(const SJBVec &barycentic, const SJBVec &v0, const SJBVec &v1, const SJBVec &v2);
   
	float&          operator [](int i);
	const float&    operator [](int i) const;

	SJBVec&			operator =(const SJBVec& vec3f);
	SJBVec&         operator *=(float d);
	SJBVec&         operator /=(float d);
	SJBVec&         operator +=(const SJBVec& u);
	SJBVec&         operator -=(const SJBVec& u);
	SJBVec          operator -() const;
   
public:

   float			vector[3];
};
