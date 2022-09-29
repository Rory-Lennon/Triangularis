
#pragma once

#include "SJBVec.h"

class SJBRotation;

typedef float f4x4[4][4];

class SJBMatrix
{
public:
   
	SJBMatrix();
	SJBMatrix(float a11, float a12, float a13, float a14,
             float a21, float a22, float a23, float a24,
             float a31, float a32, float a33, float a34,
             float a41, float a42, float a43, float a44);

	SJBMatrix(const f4x4 &m);
	SJBMatrix(SJBMatrix* p_mat);

	void                 set_value(const f4x4 &m);
   
	void                 set_value(float a11, float a12, float a13, float a14,
                                 float a21, float a22, float a23, float a24, 
                                 float a31, float a32, float a33, float a34, 
                                 float a41, float a42, float a43, float a44);

	void                 get_value(f4x4 &m) const;
	const f4x4&          get_value() const;
	void						get_value(SJBRotation* rotation);
	void                 makeIdentity();
	void                 setScale(float s);
	void                 setScale(const SJBVec &s);
	void                 setTranslate(const SJBVec &t);

	void                 setTransform(const SJBVec &t, 
		                               const SJBRotation &r, 
												 const SJBVec &s);

	void                 setTransform(const SJBVec &t, 
		                               const SJBRotation &r, 
												 const SJBVec &s, 
												 const SJBRotation &so);

   void                 setTransform(const SJBVec &translation, 
		                               const SJBRotation &rotation,
                                     const SJBVec &scaleFactor, 
												 const SJBRotation &scaleOrientation, 
												 const SJBVec &center);

   void                 getTransform(SJBVec &t, 
		                               SJBRotation &r, 
												 SJBVec &s, 
												 SJBRotation &so) const;

   float                det3(int r1, 
		                     int r2, 
							 int r3, 
							 int c1, 
							 int c2, 
							 int c3) const;

	float						det2(float a, float b, float c, float d) const;
   float                det3() const;
   float                det4() const;

   bool                 factor(SJBMatrix &r, 
								SJBVec &s, 
								SJBMatrix &u, 
								SJBVec &t, 
								SJBMatrix &proj) const;

	SJBMatrix           inverse() const;
	bool                LUDecomposition(int index[4], float &d);
	void                LUBackSubstitution(int index[4], float b[4]) const;
	SJBMatrix           transpose() const;
	SJBMatrix&          multRight(const SJBMatrix &m);
	SJBMatrix&			by(const SJBMatrix &b);
	SJBMatrix&          multLeft(const SJBMatrix &m);
	void                multMatrixVec(const SJBVec &src, SJBVec &dst) const;
	void                multVecMatrix(const SJBVec &src, SJBVec &dst) const;
	void                multDirMatrix(const SJBVec &src, SJBVec &dst) const;
	void				by(const SJBVec &src, SJBVec &dst) const;

   void                 print(FILE *fp) const;
   operator             float*();
   operator             f4x4&();
   float*               operator [](int i);
   const float*         operator [](int i) const;
   SJBMatrix&           operator =(const SJBMatrix &m);
   SJBMatrix&           operator =(const SJBRotation &q);
   void					getAdjoint(SJBMatrix&) const;

	SJBMatrix &operator *= (const SJBMatrix &m);

	void operator = (const f4x4 &f);  

protected:

	float matrix[4][4];
};
