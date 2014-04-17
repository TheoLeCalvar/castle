#include "helper.hpp"


static std::stack<mat4> matrix_stack;

/****************************************************
						vec2
****************************************************/


vec2::vec2(float x, float y)
{
	v[0] = x;
	v[1] = y;
}

vec2::vec2(const vec2 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
}

vec2::vec2(const vec3 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
}

vec2::vec2(const vec4 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
}

vec2::vec2()
{
	v[0] = 0.0f;
	v[1] = 0.0f;
}

vec2 & vec2::operator()(const vec2 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];

	return *this;
}

vec2 & vec2::operator()(float x, float y)
{
	v[0] = x;
	v[1] = y;

	return *this;
}


vec2 vec2::operator+(const vec2 & vv) const
{
	return vec2(v[0] + vv.v[0], v[1] + vv.v[1]);
}

vec2 vec2::operator-(const vec2 & vv) const
{
	return vec2(v[0] - vv.v[0], v[1] - vv.v[1]);
}

vec2 & vec2::operator+=(const vec2 & vv)
{
	v[0] += vv.v[0];
	v[1] += vv.v[1];

	return *this;
}

vec2 & vec2::operator-=(const vec2 & vv)
{
	v[0] -= vv.v[0];
	v[1] -= vv.v[1];

	return *this;
}

vec2 vec2::operator-(void) const
{
	return vec2(-v[0], -v[1]);
}

vec2 vec2::operator*(const float t) const
{
	return vec2(v[0] * t, v[1] * t);
}

vec2 vec2::operator/(const float t) const
{
	return vec2(v[0] / t, v[1] / t);
}

vec2 & vec2::operator*=(const float t)
{
	v[0] *= t;
	v[1] *= t;

	return *this;
}

vec2 & vec2::operator/=(const float t)
{
	v[0] /= t;
	v[1] /= t;

	return *this;
}


vec2 & vec2::operator=(const vec2& vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];

	return *this;
}


float & vec2::operator[](int i)
{
	return v[i];
}

float vec2::operator[](int i) const
{
	return v[i];
}

float vec2::length() const
{
	return sqrt(v[0]*v[0] + v[1]*v[1]);
}

void vec2::normalize()
{
	float l = length();

	v[0] /= l;
	v[1] /= l;
}

/****************************************************
						vec3
****************************************************/


vec3::vec3(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

vec3::vec3(const vec2 & vv, float z)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = z;
}

vec3::vec3(const vec3 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = vv.v[2];
}

vec3::vec3(const vec4 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = vv.v[2];
}

vec3::vec3()
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

vec3 & vec3::operator()(const vec3 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = vv.v[2];

	return *this;
}

vec3 & vec3::operator()(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;

	return *this;
}

vec3 vec3::operator+(const vec3 & vv) const
{
	return vec3(v[0] + vv.v[0], v[1] + vv.v[1], v[2] + vv.v[2]);
}

vec3 vec3::operator-(const vec3 & vv) const
{
	return vec3(v[0] - vv.v[0], v[1] - vv.v[1], v[2] - vv.v[2]);
}

vec3 & vec3::operator+=(const vec3 & vv)
{
	v[0] += vv.v[0];
	v[1] += vv.v[1];
	v[2] += vv.v[2];

	return *this;
}

vec3 & vec3::operator-=(const vec3 & vv)
{
	v[0] -= vv.v[0];
	v[1] -= vv.v[1];
	v[2] -= vv.v[2];

	return *this;
}


vec3 vec3::operator-(void) const
{
	return vec3(-v[0], -v[1], -v[2]);
}

vec3 vec3::operator*(const float t) const
{
	return vec3(v[0] * t, v[1] * t, v[2] * t);
}

vec3 vec3::operator/(const float t) const
{
	return vec3(v[0] / t, v[1] / t, v[2] / t);
}

vec3 & vec3::operator*=(const float t)
{
	v[0] *= t;
	v[1] *= t;
	v[2] *= t;

	return *this;
}

vec3 & vec3::operator/=(const float t)
{
	v[0] /= t;
	v[1] /= t;
	v[2] /= t;

	return *this;
}


vec3 vec3::operator^(const vec3 & vv) const
{
	return vec3(v[1]*vv.v[2] - v[2]*vv.v[1],
				v[2]*vv.v[0] - v[0]*vv.v[2],
				v[0]*vv.v[1] - v[1]*vv.v[0]
			);
}

float vec3::operator*(const vec3 & vv) const
{
	return (v[0]*vv.v[0] + v[1]*vv.v[1] + v[2]*vv.v[2]);
}


vec3& vec3::operator=(const vec3 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = vv.v[2];

	return *this;
}

float & vec3::operator[](int i)
{
	return v[i];
}

float vec3::operator[](int i) const
{
	return v[i];
}

float vec3::length() const
{
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

void vec3::normalize()
{
	float l = length();

	v[0] /= l;
	v[1] /= l;
	v[2] /= l;
}

/****************************************************
						vec4
****************************************************/


vec4::vec4(float x, float y, float z, float w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

vec4::vec4(const vec2 & vv, float z, float w)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = z;
	v[3] = w;
}

vec4::vec4(const vec3 & vv, float w)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = vv.v[2];
	v[3] = w;
}

vec4::vec4(const vec4 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = vv.v[2];
	v[3] = vv.v[3];
}

vec4::vec4()
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;
}

vec4 & vec4::operator()(const vec4 & vv)
{
	v[0] = vv.v[0];
	v[1] = vv.v[1];
	v[2] = vv.v[2];
	v[3] = vv.v[3];

	return *this;
}

vec4 & vec4::operator()(float x, float y, float z, float w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;

	return *this;
}

vec4 vec4::operator+(const vec4 & vv) const
{
	return vec4(
		v[0] + vv.v[0],
		v[1] + vv.v[1],
		v[2] + vv.v[2],
		v[3] + vv.v[3]
		);
}

vec4 vec4::operator-(const vec4 & vv) const
{
	return vec4(
		v[0] - vv.v[0],
		v[1] - vv.v[1],
		v[2] - vv.v[2],
		v[3] - vv.v[3]
		);
}

vec4 & vec4::operator+=(const vec4 & vv)
{
	v[0] += vv.v[0];
	v[1] += vv.v[1];
	v[2] += vv.v[2];
	v[3] += vv.v[3];

	return *this;
}

vec4 & vec4::operator-=(const vec4 & vv)
{
	v[0] -= vv.v[0];
	v[1] -= vv.v[1];
	v[2] -= vv.v[2];
	v[3] -= vv.v[3];

	return *this;
}


vec4 vec4::operator-(void) const
{
	return vec4(-v[0], -v[1], -v[2], -v[3]);
}

vec4 vec4::operator*(const float t) const
{
	return vec4(
		v[0] * t,
		v[1] * t,
		v[2] * t,
		v[3] * t);
}

vec4 vec4::operator/(const float t) const
{
	return vec4(
		v[0] / t,
		v[1] / t,
		v[2] / t,
		v[3] / t);
}

vec4 & vec4::operator*=(const float t)
{
	v[0] *= t;
	v[1] *= t;
	v[2] *= t;
	v[3] *= t;

	return *this;
}

vec4 & vec4::operator/=(const float t)
{
	v[0] /= t;
	v[1] /= t;
	v[2] /= t;
	v[3] /= t;

	return *this;
}

float & vec4::operator[](int i)
{
	return v[i];
}

float vec4::operator[](int i) const
{
	return v[i];
}

float vec4::length() const
{
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
}

void vec4::normalize()
{
	float l = length();

	v[0] /= l;
	v[1] /= l;
	v[2] /= l;
	v[3] /= l;
}

/****************************************************
						mat3
****************************************************/

//null
mat3::mat3()
{
	m[0] = 0.0f; m[1] = 0.0f; m[2] = 0.0f;
	m[3] = 0.0f; m[4] = 0.0f; m[5] = 0.0f;
	m[6] = 0.0f; m[7] = 0.0f; m[8] = 0.0f;
}

//identity
mat3::mat3(int)
{
	m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f;
	m[3] = 0.0f; m[4] = 1.0f; m[5] = 0.0f;
	m[6] = 0.0f; m[7] = 0.0f; m[8] = 1.0f;
}

mat3::mat3(	float a, float b, float c, 
		float d, float e, float f, 
		float g, float h, float i)
{
	m[0] = a; m[1] = b; m[2] = c;
	m[3] = d; m[4] = e; m[5] = f;
	m[6] = g; m[7] = h; m[8] = i;
}

mat3::mat3(const mat3 & mm)
{
	m[0] = mm.m[0]; m[1] = mm.m[1]; m[2] = mm.m[2];
	m[3] = mm.m[3]; m[4] = mm.m[4]; m[5] = mm.m[5];
	m[6] = mm.m[6]; m[7] = mm.m[7]; m[8] = mm.m[8];	
}


mat3 mat3::operator+(const mat3 & mm) const
{
	return mat3(
		m[0] + mm.m[0], m[1] + mm.m[1], m[2] + mm.m[2],
		m[3] + mm.m[3], m[4] + mm.m[4], m[5] + mm.m[5],
		m[6] + mm.m[6], m[7] + mm.m[7], m[8] + mm.m[8]
		);
}

mat3 & mat3::operator+=(const mat3 & mm)
{
	m[0] += mm.m[0]; m[1] += mm.m[1]; m[2] += mm.m[2];
	m[3] += mm.m[3]; m[4] += mm.m[4]; m[5] += mm.m[5];
	m[6] += mm.m[6]; m[7] += mm.m[7]; m[8] += mm.m[8];

	return *this;
}

mat3 mat3::operator-(const mat3 & mm) const
{
	return mat3(
		m[0] - mm.m[0], m[1] - mm.m[1], m[2] - mm.m[2],
		m[3] - mm.m[3], m[4] - mm.m[4], m[5] - mm.m[5],
		m[6] - mm.m[6], m[7] - mm.m[7], m[8] - mm.m[8]
		);
}

mat3 & mat3::operator-=(const mat3 & mm)
{
	m[0] -= mm.m[0]; m[1] -= mm.m[1]; m[2] -= mm.m[2];
	m[3] -= mm.m[3]; m[4] -= mm.m[4]; m[5] -= mm.m[5];
	m[6] -= mm.m[6]; m[7] -= mm.m[7]; m[8] -= mm.m[8];

	return *this;
}


mat3 mat3::operator*(const float t) const
{
	return mat3(
			m[0] * t, m[1] * t, m[2] * t,
			m[3] * t, m[4] * t, m[5] * t,
			m[6] * t, m[7] * t, m[8] * t
		);
}

mat3 & mat3::operator*=(const float t)
{
	m[0] *= t; m[1] *= t; m[2] *= t;
	m[3] *= t; m[4] *= t; m[5] *= t;
	m[6] *= t; m[7] *= t; m[8] *= t;

	return *this;
}

mat3 mat3::operator*(const mat3 & mm) const
{
	return mat3(
		m[0]*mm[0] + m[3]*mm[1] + m[6]*mm[2], 
		m[1]*mm[0] + m[4]*mm[1] + m[7]*mm[2], 
		m[2]*mm[0] + m[5]*mm[1] + m[8]*mm[2], 
		
		m[0]*mm[3] + m[3]*mm[4] + m[6]*mm[5], 
		m[1]*mm[3] + m[4]*mm[4] + m[7]*mm[5], 
		m[2]*mm[3] + m[5]*mm[4] + m[8]*mm[5], 

		m[0]*mm[6] + m[3]*mm[7] + m[6]*mm[8], 
		m[1]*mm[6] + m[4]*mm[7] + m[7]*mm[8], 
		m[2]*mm[6] + m[5]*mm[7] + m[8]*mm[8]
		);
}

mat3 & mat3::operator=(const mat3 & mm)
{
	m[0] = mm.m[0]; m[1] = mm.m[1]; m[2] = mm.m[2];
	m[3] = mm.m[3]; m[4] = mm.m[4]; m[5] = mm.m[5];
	m[6] = mm.m[6]; m[7] = mm.m[7]; m[8] = mm.m[8];

	return *this;
}

float & mat3::operator[](int i)
{
	return m[i];
}

float mat3::operator[](int i) const
{
	return m[i];
}

vec3 mat3::operator*(const vec3 & vv) const
{
	return vec3(
		vv.v[0]*m[0] + vv.v[1]*m[3] + vv.v[2]*m[6],
		vv.v[0]*m[1] + vv.v[1]*m[4] + vv.v[2]*m[7],
		vv.v[0]*m[2] + vv.v[1]*m[5] + vv.v[2]*m[8]
		);
}


/****************************************************
						mat4
****************************************************/

//null
mat4::mat4()
{
	m[0] = 0.0f; 	m[1] = 0.0f; 	m[2] = 0.0f; 	m[3] = 0.0f; 
	m[4] = 0.0f; 	m[5] = 0.0f; 	m[6] = 0.0f; 	m[7] = 0.0f; 
	m[8] = 0.0f; 	m[9] = 0.0f; 	m[10] = 0.0f; 	m[11] = 0.0f; 
	m[12] = 0.0f; 	m[13] = 0.0f; 	m[14] = 0.0f; 	m[15] = 0.0f; 
}

//identity
mat4::mat4(int)
{
	m[0] = 1.0f; 	m[1] = 0.0f; 	m[2] = 0.0f; 	m[3] = 0.0f; 
	m[4] = 0.0f; 	m[5] = 1.0f; 	m[6] = 0.0f; 	m[7] = 0.0f; 
	m[8] = 0.0f; 	m[9] = 0.0f; 	m[10] = 1.0f; 	m[11] = 0.0f; 
	m[12] = 0.0f; 	m[13] = 0.0f; 	m[14] = 0.0f; 	m[15] = 1.0f; 
}

mat4::mat4(	float a, float b, float c, float d, 
			float e, float f, float g, float h, 
			float i, float j, float k, float l,
			float mm, float n, float o, float p)
{
	m[0] = a; 	m[4] = e;	m[8] = i; 	m[12] = mm;
	m[1] = b; 	m[5] = f;	m[9] = j;	m[13] = n;
	m[2] = c; 	m[6] = g;	m[10] = k; 	m[14] = o;
	m[3] = d;   m[7] = h;	m[11] = l;	m[15] = p;
}

mat4::mat4(const mat4 & mm)
{
	m[0] = mm.m[0]; 	m[1] = mm.m[1]; 	m[2] = mm.m[2]; 	m[3] = mm.m[3]; 
	m[4] = mm.m[4]; 	m[5] = mm.m[5]; 	m[6] = mm.m[6]; 	m[7] = mm.m[7]; 
	m[8] = mm.m[8]; 	m[9] = mm.m[9]; 	m[10] = mm.m[10]; 	m[11] = mm.m[11]; 
	m[12] = mm.m[12]; 	m[13] = mm.m[13]; 	m[14] = mm.m[14]; 	m[15] = mm.m[15]; 
}


mat4 mat4::operator+(const mat4 & mm) const
{
	return mat4(
		m[0] + mm.m[0], 	m[1] + mm.m[1], 	m[2] + mm.m[2], 	m[3] + mm.m[3], 
		m[4] + mm.m[4], 	m[5] + mm.m[5], 	m[6] + mm.m[6], 	m[7] + mm.m[7], 
		m[8] + mm.m[8], 	m[9] + mm.m[9], 	m[10] + mm.m[10], 	m[11] + mm.m[11], 
		m[12] + mm.m[12], 	m[13] + mm.m[13], 	m[14] + mm.m[14], 	m[15] + mm.m[15] 
	);
}

mat4 & mat4::operator+=(const mat4 & mm)
{
	m[0] += mm.m[0]; 	m[1] += mm.m[1]; 	m[2] += mm.m[2]; 	m[3] += mm.m[3]; 
	m[4] += mm.m[4]; 	m[5] += mm.m[5]; 	m[6] += mm.m[6]; 	m[7] += mm.m[7]; 
	m[8] += mm.m[8]; 	m[9] += mm.m[9]; 	m[10] += mm.m[10]; 	m[11] += mm.m[11]; 
	m[12] += mm.m[12]; 	m[13] += mm.m[13]; 	m[14] += mm.m[14]; 	m[15] += mm.m[15]; 

	return *this;
}

mat4 mat4::operator-(const mat4 & mm) const
{
	return mat4(
		m[0] - mm.m[0], 	m[1] - mm.m[1], 	m[2] - mm.m[2], 	m[3] - mm.m[3], 
		m[4] - mm.m[4], 	m[5] - mm.m[5], 	m[6] - mm.m[6], 	m[7] - mm.m[7], 
		m[8] - mm.m[8], 	m[9] - mm.m[9], 	m[10] - mm.m[10], 	m[11] - mm.m[11], 
		m[12] - mm.m[12], 	m[13] - mm.m[13], 	m[14] - mm.m[14], 	m[15] - mm.m[15] 
	);
}

mat4 & mat4::operator-=(const mat4 & mm)
{
	m[0] -= mm.m[0]; 	m[1] -= mm.m[1]; 	m[2] -= mm.m[2]; 	m[3] -= mm.m[3]; 
	m[4] -= mm.m[4]; 	m[5] -= mm.m[5]; 	m[6] -= mm.m[6]; 	m[7] -= mm.m[7]; 
	m[8] -= mm.m[8]; 	m[9] -= mm.m[9]; 	m[10] -= mm.m[10]; 	m[11] -= mm.m[11]; 
	m[12] -= mm.m[12]; 	m[13] -= mm.m[13]; 	m[14] -= mm.m[14]; 	m[15] -= mm.m[15]; 

	return *this;
}


mat4 mat4::operator*(const float t) const
{
	return mat4(
		m[0] * t, 	m[1] * t, 	m[2] * t, 	m[3] * t, 
		m[4] * t, 	m[5] * t, 	m[6] * t, 	m[7] * t, 
		m[8] * t, 	m[9] * t, 	m[10] * t, 	m[11] * t, 
		m[12] * t, 	m[13] * t, 	m[14] * t, 	m[15] * t
	);
}

mat4 & mat4::operator*=(const float t)
{
	m[0] *= t; 	m[1] *= t; 	m[2] *= t; 	m[3] *= t; 
	m[4] *= t; 	m[5] *= t; 	m[6] *= t; 	m[7] *= t; 
	m[8] *= t; 	m[9] *= t; 	m[10] *= t; m[11] *= t; 
	m[12] *= t; m[13] *= t; m[14] *= t; m[15] *= t; 

	return *this;
}

mat4 mat4::operator*(const mat4 & mm) const
{
	return mat4(
		m[0]*mm.m[0] + m[4]*mm.m[1] + m[8]*mm.m[2] + m[12]*mm.m[3], 
		m[1]*mm.m[0] + m[5]*mm.m[1] + m[9]*mm.m[2] + m[13]*mm.m[3], 
		m[2]*mm.m[0] + m[6]*mm.m[1] + m[10]*mm.m[2] + m[14]*mm.m[3], 
		m[3]*mm.m[0] + m[7]*mm.m[1] + m[11]*mm.m[2] + m[15]*mm.m[3], 
		
		m[0]*mm.m[4] + m[4]*mm.m[5] + m[8]*mm.m[6] + m[12]*mm.m[7],
		m[1]*mm.m[4] + m[5]*mm.m[5] + m[9]*mm.m[6] + m[13]*mm.m[7],
		m[2]*mm.m[4] + m[6]*mm.m[5] + m[10]*mm.m[6] + m[14]*mm.m[7],
		m[3]*mm.m[4] + m[7]*mm.m[5] + m[11]*mm.m[6] + m[15]*mm.m[7],
		
		m[0]*mm.m[8] + m[4]*mm.m[9] + m[8]*mm.m[10]+ m[12]*mm.m[11],
		m[1]*mm.m[8] + m[5]*mm.m[9] + m[9]*mm.m[10]+ m[13]*mm.m[11],
		m[2]*mm.m[8] + m[6]*mm.m[9] + m[10]*mm.m[10]+ m[14]*mm.m[11],
		m[3]*mm.m[8] + m[7]*mm.m[9] + m[11]*mm.m[10]+ m[15]*mm.m[11],
		
		m[0]*mm.m[12]+ m[4]*mm.m[13]+ m[8]*mm.m[14]+ m[12]*mm.m[15],
		m[1]*mm.m[12]+ m[5]*mm.m[13]+ m[9]*mm.m[14]+ m[13]*mm.m[15],
		m[2]*mm.m[12]+ m[6]*mm.m[13]+ m[10]*mm.m[14]+ m[14]*mm.m[15],
		m[3]*mm.m[12]+ m[7]*mm.m[13]+ m[11]*mm.m[14]+ m[15]*mm.m[15]
	);
}

mat4 & mat4::operator*=(const mat4 & mm)
{
		m[0] = m[0]*mm.m[0] + m[4]*mm.m[1] + m[8]*mm.m[2] + m[12]*mm.m[3]; 
		m[1] = m[1]*mm.m[0] + m[5]*mm.m[1] + m[9]*mm.m[2] + m[13]*mm.m[3]; 
		m[2] = m[2]*mm.m[0] + m[6]*mm.m[1] + m[10]*mm.m[2] + m[14]*mm.m[3]; 
		m[3] = m[3]*mm.m[0] + m[7]*mm.m[1] + m[11]*mm.m[2] + m[15]*mm.m[3]; 
		
		m[4] = m[0]*mm.m[4] + m[4]*mm.m[5] + m[8]*mm.m[6] + m[12]*mm.m[7];
		m[5] = m[1]*mm.m[4] + m[5]*mm.m[5] + m[9]*mm.m[6] + m[13]*mm.m[7];
		m[6] = m[2]*mm.m[4] + m[6]*mm.m[5] + m[10]*mm.m[6] + m[14]*mm.m[7];
		m[7] = m[3]*mm.m[4] + m[7]*mm.m[5] + m[11]*mm.m[6] + m[15]*mm.m[7];
		
		m[8] = m[0]*mm.m[8] + m[4]*mm.m[9] + m[8]*mm.m[10]+ m[12]*mm.m[11];
		m[9] = m[1]*mm.m[8] + m[5]*mm.m[9] + m[9]*mm.m[10]+ m[13]*mm.m[11];
		m[10] = m[2]*mm.m[8] + m[6]*mm.m[9] + m[10]*mm.m[10]+ m[14]*mm.m[11];
		m[11] = m[3]*mm.m[8] + m[7]*mm.m[9] + m[11]*mm.m[10]+ m[15]*mm.m[11];
		
		m[12] = m[0]*mm.m[12]+ m[4]*mm.m[13]+ m[8]*mm.m[14]+ m[12]*mm.m[15];
		m[13] = m[1]*mm.m[12]+ m[5]*mm.m[13]+ m[9]*mm.m[14]+ m[13]*mm.m[15];
		m[14] = m[2]*mm.m[12]+ m[6]*mm.m[13]+ m[10]*mm.m[14]+ m[14]*mm.m[15];
		m[15] = m[3]*mm.m[12]+ m[7]*mm.m[13]+ m[11]*mm.m[14]+ m[15]*mm.m[15];

	return *this;
}


mat4 & mat4::operator=(const mat4 & mm)
{
	m[0] = mm.m[0]; 	m[1] = mm.m[1]; 	m[2] = mm.m[2]; 	m[3] = mm.m[3]; 
	m[4] = mm.m[4]; 	m[5] = mm.m[5]; 	m[6] = mm.m[6]; 	m[7] = mm.m[7]; 
	m[8] = mm.m[8]; 	m[9] = mm.m[9]; 	m[10] = mm.m[10]; 	m[11] = mm.m[11]; 
	m[12] = mm.m[12]; 	m[13] = mm.m[13]; 	m[14] = mm.m[14]; 	m[15] = mm.m[15]; 

	return *this;
}

float & mat4::operator[](int i)
{
	return m[i];
}

float mat4::operator[](int i) const
{
	return m[i];
}

vec4 mat4::operator*(const vec4 & vv) const
{
	return vec4(
		vv.v[0]*m[0] + vv.v[1]*m[4] + vv.v[2]*m[8] + vv.v[3]*m[12],
		vv.v[0]*m[1] + vv.v[1]*m[5] + vv.v[2]*m[9] + vv.v[3]*m[13],
		vv.v[0]*m[2] + vv.v[1]*m[6] + vv.v[2]*m[10]+ vv.v[3]*m[14],
		vv.v[0]*m[3] + vv.v[1]*m[7] + vv.v[2]*m[11]+ vv.v[3]*m[15]
		);
}

mat4 mat4::transpose() const
{
	return mat4(
			m[0] , m[4] , m[8] , m[13],
			m[1] , m[5] , m[9] , m[14],
			m[2] , m[6] , m[10] , m[15],
			m[3] , m[7] , m[11] , m[12]
		);
}

float mat4::det()const
{
	return (
			m[0] * m[5] * m[10] * m[15] +
			m[1] * m[6] * m[11] * m[12] +
			m[2] * m[7] * m[8] * m[11] 	+
			m[3] * m[4] * m[9] * m[14] 	
			- (
			m[3] * m[6] * m[9] * m[12] 	+
			m[2] * m[5] * m[8] * m[15] 	+
			m[1] * m[4] * m[11] * m[14] +
			m[0] * m[7] * m[10] * m[11] 		
			 )
		);
}

mat4 mat4::inverse()const
{
	return ( transpose() * (1/det()) );
}
/*****************************
		Utility
*****************************/

void popMatrix()
{
	if (!matrix_stack.empty())
	{
		matrix_stack.pop();
	}
}

void pushMatrix(mat4 m)
{
	matrix_stack.push(m);
}

mat4 currentMatrix()
{
	if (matrix_stack.empty())
	{
		return mat4(1);
	}
	return matrix_stack.top();
}

mat4 translationMatrix(float x, float y, float z)
{
	return mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x, 	  y, 	z, 	  1.0f
		);
}

mat4 translationMatrix(const vec3 & vv)
{
	return mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			vv[0],vv[1],vv[2],1.0f
		);
}

mat4 translate(const mat4 & mm, const vec3 & vv)
{
	return translationMatrix(vv) * mm;
}

mat4 XrotationMatrix(float alpha)
{
	return mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(alpha),  sin(alpha), 0.0f,
			0.0f, -sin(alpha), cos(alpha), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
}
mat4 YrotationMatrix(float alpha)
{
	return mat4(
			cos(alpha), 0.0f, -sin(alpha), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin(alpha), 0.0f, cos(alpha), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
}
mat4 ZrotationMatrix(float alpha)
{
	return mat4(
			cos(alpha), sin(alpha), 0.0f, 0.0f,
			-sin(alpha), cos(alpha), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
}

mat4 Xrotate(const mat4 & mm, float alpha)
{
	return XrotationMatrix(alpha) * mm;
}

mat4 Yrotate(const mat4 & mm, float alpha)
{
	return YrotationMatrix(alpha) * mm;
}

mat4 Zrotate(const mat4 & mm, float alpha)
{
	return ZrotationMatrix(alpha) * mm;
}


mat4 scaleMatrix(float x, float y, float z)
{
	return mat4(
		x, 0.0f, 0.0f, 0.0f, 
		0.0f, y, 0.0f, 0.0f, 
		0.0f, 0.0f, z, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f
		);
}

mat4 scaleMatrix(const vec3 & vv)
{
	return mat4(
		vv[0], 0.0f, 0.0f, 0.0f, 
		0.0f, vv[1], 0.0f, 0.0f, 
		0.0f, 0.0f, vv[2], 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f
		);	
}

mat4 scaleMatrix(const mat4 & mm, const vec3 & vv)
{
	return scaleMatrix(vv) * mm;
}


mat4 viewMatrix(const vec3& eye,const vec3 & center, const vec3& up) {
	// inverse translation
	mat4 p = translationMatrix(-eye);

	// distance vector
	vec3 d = center - eye;
	// forward vector
	vec3 f = d;
	f.normalize();
	// right vector
	vec3 r = f ^ up;
	r.normalize();
	// real up vector
	vec3 u = r ^ f;
	u.normalize();

	mat4 ori(1);
	ori.m[0] = r.v[0];
	ori.m[4] = r.v[1];
	ori.m[8] = r.v[2];
	ori.m[1] = u.v[0];
	ori.m[5] = u.v[1];
	ori.m[9] = u.v[2];
	ori.m[2] = -f.v[0];
	ori.m[6] = -f.v[1];
	ori.m[10] = -f.v[2];
	
	return ori * p;
}

mat4 projectionMatrix(float fovy, float aspect, float near, float far) {
	float fov_rad = fovy * (M_PI / 180.0f);
	float range = tan (fov_rad / 2.0f) * near;
	float sx = (2.0f * near) / (range * aspect + range * aspect);
	float sy = near / range;
	float sz = -(far + near) / (far - near);
	float pz = -(2.0f * far * near) / (far - near);
	mat4 m(1); // make sure bottom-right corner is zero
	m.m[0] = sx;
	m.m[5] = sy;
	m.m[10] = sz;
	m.m[14] = pz;
	m.m[11] = -1.0f;
	return m;
}

template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const vec2 & vv)
{
   os << "(" << vv[0] << "," << vv[1] << ")" << std::endl;
   return os;
}

void print(const vec2 & vv)
{
	std::cout << "(" << vv[0] << "," << vv[1] << ")" << std::endl;
}

template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const vec3 & vv)
{
   os << "(" << vv[0] << "," << vv[1] << "," << vv[2] << ")" << std::endl;
   return os;
}

void print(const vec3 & vv)
{
	std::cout << "(" << vv[0] << "," << vv[1] << "," << vv[2] << ")" << std::endl;
}

template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const vec4 & vv)
{
   os << "(" << vv[0] << "," << vv[1] << "," << vv[2] << "," << vv[3] <<  ")" << std::endl;
   return os;
}

void print(const vec4 & vv)
{
	std::cout << "(" << vv[0] << "," << vv[1] << "," << vv[2] << "," << vv[3] << ")" << std::endl;
}

template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const mat3 & mm)
{
	os << "[" << mm[0] << "][" << mm[3] << "][" << mm[6] << "]" << std::endl;
	os << "[" << mm[1] << "][" << mm[4] << "][" << mm[7] << "]" << std::endl;
	os << "[" << mm[2] << "][" << mm[5] << "][" << mm[8] << "]" << std::endl;

	return os;
}

void print(const mat3 & mm)
{
	std::cout << "[" << mm[0] << "][" << mm[3] << "][" << mm[6] << "]" << std::endl;
	std::cout << "[" << mm[1] << "][" << mm[4] << "][" << mm[7] << "]" << std::endl;
	std::cout << "[" << mm[2] << "][" << mm[5] << "][" << mm[8] << "]" << std::endl;
}

template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const mat4 & mm)
{
	os << "[" << mm[0] << "][" << mm[4] << "][" << mm[8] << "][" << mm[12] << "]" << std::endl;
	os << "[" << mm[1] << "][" << mm[5] << "][" << mm[9] << "][" << mm[13] << "]" << std::endl;
	os << "[" << mm[2] << "][" << mm[6] << "][" << mm[10] << "][" << mm[14] << "]" << std::endl;
	os << "[" << mm[3] << "][" << mm[7] << "][" << mm[11] << "][" << mm[15] << "]" << std::endl;

	return os;
}


void print(const mat4 & mm)
{
	std::cout << "[" << mm[0] << "][" << mm[4] << "][" << mm[8] << "][" << mm[12] << "]" << std::endl;
	std::cout << "[" << mm[1] << "][" << mm[5] << "][" << mm[9] << "][" << mm[13] << "]" << std::endl;
	std::cout << "[" << mm[2] << "][" << mm[6] << "][" << mm[10] << "][" << mm[14] << "]" << std::endl;
	std::cout << "[" << mm[3] << "][" << mm[7] << "][" << mm[11] << "][" << mm[15] << "]" << std::endl;
}

void __openGL_check_error(const char * file, int line)
{
	QOpenGLFunctions_3_2_Core f;
	f.initializeOpenGLFunctions();

	GLenum error = f.glGetError();

	while(error != GL_NO_ERROR) 
	{
        std::string errorString;

        switch(error) {
                case GL_INVALID_OPERATION:				errorString="INVALID_OPERATION";      		break;
                case GL_INVALID_ENUM:					errorString="INVALID_ENUM";           		break;
                case GL_INVALID_VALUE:					errorString="INVALID_VALUE";          		break;
                case GL_OUT_OF_MEMORY:					errorString="OUT_OF_MEMORY";          		break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:  errorString="INVALID_FRAMEBUFFER_OPERATION";  break;
        }

        qWarning() << "GL_" << errorString.c_str() << " - " << file << ":" << line;

        error = f.glGetError();
    }
}

