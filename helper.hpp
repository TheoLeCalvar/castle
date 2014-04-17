#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <stack>
#include <cmath>
#include <QDebug>
#include <QOpenGLFunctions_3_2_core>

#ifndef M_PI
#define M_PI 3.141592
#endif


#ifndef openGL_check_error
void __openGL_check_error(const char * file, int line);
#define openGL_check_error() __openGL_check_error(__FILE__, __LINE__) 
#endif

struct vec3;
struct vec4;


struct vec2 
{
	float v[2];

	vec2(float x, float y);
	vec2(const vec2 & vv);
	vec2(const vec3 & vv);
	vec2(const vec4 & vv);
	vec2();

	vec2 & operator()(const vec2 &);
	vec2 & operator()(float x, float y);

	vec2 operator+(const vec2 &) const;
	vec2 operator-(const vec2 &) const;
	vec2 & operator+=(const vec2 &);
	vec2 & operator-=(const vec2 &);

	vec2 operator-(void) const;

	vec2 operator*(const float) const;
	vec2 operator/(const float) const;
	vec2 & operator*=(const float);
	vec2 & operator/=(const float);

	vec2 & operator=(const vec2&);

	float & operator[](int);
	float operator[](int) const;

	float length() const;
	void  normalize();
};

struct vec3
{
	float v[3];

	vec3(float x, float y, float z);
	vec3(const vec2 & vv, float z);
	vec3(const vec3 & vv);
	vec3(const vec4 & vv);
	vec3();

	vec3 & operator()(const vec3 &);
	vec3 & operator()(float x, float y, float z);

	vec3 operator+(const vec3 &) const;
	vec3 operator-(const vec3 &) const;
	vec3 & operator+=(const vec3 &);
	vec3 & operator-=(const vec3 &);

	vec3 operator-(void) const;

	vec3 operator*(const float) const;
	vec3 operator/(const float) const;
	vec3 & operator*=(const float);
	vec3 & operator/=(const float);

	vec3 operator^(const vec3 &) const;
	float operator*(const vec3 &) const;

	vec3& operator=(const vec3 &);

	float & operator[](int);
	float operator[](int) const;

	float length() const;
	void  normalize();
};


struct vec4
{
	float v[4];

	vec4(float x, float y, float z, float w);
	vec4(const vec2 & vv, float z, float w);
	vec4(const vec3 & vv, float w);
	vec4(const vec4 & vv);
	vec4();

	vec4 & operator()(const vec4 &);
	vec4 & operator()(float x, float y, float z, float w);

	vec4 operator+(const vec4 &) const;
	vec4 operator-(const vec4 &) const;
	vec4 & operator+=(const vec4 &);
	vec4 & operator-=(const vec4 &);

	vec4 operator-(void) const;

	vec4 operator*(const float) const;
	vec4 operator/(const float) const;
	vec4 & operator*=(const float);
	vec4 & operator/=(const float);

	float & operator[](int);
	float operator[](int) const;

	float length() const;
	void  normalize();
};

//ordre de stockage
//0 3 6
//1 4 7
//2 5 8
struct mat3
{
	float m[9];

	//null
	mat3();
	//identity
	mat3(int);
	mat3(	float a, float b, float c, 
			float d, float e, float f, 
			float g, float h, float i);
	mat3(const mat3 &);

	mat3 operator+(const mat3 &) const;
	mat3 & operator+=(const mat3 &);
	mat3 operator-(const mat3 &) const;
	mat3 & operator-=(const mat3 &);

	mat3 operator*(const float) const;
	mat3 & operator*=(const float);

	mat3 operator*(const mat3 &) const;

	mat3 & operator=(const mat3 &);

	float & operator[](int);
	float operator[](int) const;

	vec3 operator*(const vec3 &) const;
};

//ordre de stockage
//0 4 8  12
//1 5 9  13
//2 6 10 14
//3 7 11 15
struct mat4
{
	float m[16];

	//null
	mat4();
	//identity
	mat4(int);
	mat4(	float a, float b, float c, float d, 
			float e, float f, float g, float h, 
			float i, float j, float k, float l,
			float m, float n, float o, float p);
	mat4(const mat4 &);

	mat4 operator+(const mat4 &) const;
	mat4 & operator+=(const mat4 &);
	mat4 operator-(const mat4 &) const;
	mat4 & operator-=(const mat4 &);

	mat4 operator*(const float) const;
	mat4 & operator*=(const float);

	mat4 operator*(const mat4 &) const;
	mat4 & operator*=(const mat4 &);

	mat4 & operator=(const mat4 &);

	float & operator[](int);
	float operator[](int) const;

	vec4 operator*(const vec4 &) const;

	mat4 transpose() const;
	mat4 inverse()const;
	float det() const;


};

typedef struct vec2 vec2;
typedef struct vec3 vec3;
typedef struct vec4 vec4;

typedef struct mat3 mat3;
typedef struct mat4 mat4;



void popMatrix();
void pushMatrix(mat4);

mat4 currentMatrix();



mat4 translationMatrix(float x, float y, float z);
mat4 translationMatrix(const vec3 &);

mat4 translate(const mat4 &, const vec3 &);

mat4 XrotationMatrix(float alpha);
mat4 YrotationMatrix(float alpha);
mat4 ZrotationMatrix(float alpha);

mat4 Xrotate(const mat4 &, float alpha);
mat4 Yrotate(const mat4 &, float alpha);
mat4 Zrotate(const mat4 &, float alpha);


mat4 scaleMatrix(float x, float y, float z);
mat4 scaleMatrix(const vec3 &);
mat4 scale(const mat4 &, const vec3 &);

mat4 viewMatrix(const vec3 & eye, const vec3 & center, const vec3 & up);
mat4 projectionMatrix(float fov, float aspect, float zNear, float zFar);

template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const vec2 &);
void print(const vec2 &);
template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const vec3 &);
void print(const vec3 &);
template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const vec4 &);
void print(const vec4 &);
template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const mat3 &);
void print(const mat3 &);
template <typename charT, typename traits>
std::basic_ostream<charT,traits> & operator << (std::basic_ostream<charT,traits> & os, const mat4 &);
void print(const mat4 &);

#endif