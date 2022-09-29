
#pragma once

#include "SJBVec.h"
#include "SJBMatrix.h"

class SJBRotation
{
public:

						SJBRotation();
						SJBRotation(const float v[4]);
						SJBRotation(float q0, float q1, float q2, float q3);
						SJBRotation(const SJBMatrix &m);
						SJBRotation(const SJBVec &axis, float radians);
						SJBRotation(const SJBVec &rotateFrom, const SJBVec &rotateTo);

	void				get_angle(float &angle);
	void				set_angle(float angle);
	void				inc_angle(float angle);
	const float*		get_value() const;
	void				get_value(float& q0, float& q1, float& q2, float& degrees) const;
	SJBRotation&		set_value(float q0, float q1, float q2, float degrees);
	void				get_value(SJBVec &axis, float &degrees) const;
	void				get_value(SJBMatrix &matrix) const;
	SJBRotation&		set_value(const float q[4]);
	SJBRotation&		set_value(const SJBMatrix &m);
	SJBRotation&		set_value(const SJBVec &axis, float degrees);
	SJBRotation&		set_value(const SJBVec &rotateFrom, const SJBVec &rotateTo);
	SJBRotation&		invert();
	SJBRotation			inverse() const;
//  void				multVec(const SJBVec &src, SJBVec &dst) const;
	void				scaleAngle(float scaleFactor);   
	static SJBRotation	slerp(const SJBRotation &rot0, const SJBRotation &rot1, float t);
	static SJBRotation	identity();
	void				gl_render();
	float&				operator [](int i);
	const float&		operator [](int i) const;

protected:

	float				quaternion[4];
};




