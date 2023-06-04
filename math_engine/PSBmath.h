
#pragma once 

#include <iostream>
#include <vector>
#include <cmath>
#include <ostream>


 namespace Math
 {

const float PI = 3.14159265f;


float degreesToRad(const float &x);


const float theoremeOfCosine(float l1,float l2, float angle);

const float polygonRfinder(float l,float angle);

class vec4f 
{
public:


float x; 
float y; 
float z; 
float k;

vec4f();
vec4f(float _x , float _y, float _z,float _k);


~vec4f();

vec4f(const vec4f &v);
vec4f& operator=(const vec4f &v);


friend std::ostream& operator<<(std::ostream &os, vec4f const &m) ;


vec4f operator+(const vec4f &v);
void operator+=(const vec4f &v);
vec4f operator-(const vec4f &v);
void operator-=(const vec4f &v);
float operator*(const vec4f &v);
vec4f operator*(const float &a);
void operator*=(const float &a);
vec4f operator/(const float &a);
void operator/=(const float &a);
bool operator==(const vec4f &v);

private:


};
class vec3f 
{
public:


float x; 
float y; 
float z; 


vec3f();
vec3f(float _x , float _y, float _z);

~vec3f();


vec3f(const vec3f &v);
vec3f& operator=(const vec3f &v);


friend std::ostream& operator<<(std::ostream &os, vec3f const &m) ;



vec3f operator+(const vec3f &v);
void operator+=(const vec3f &v);
vec3f operator-(const vec3f &v);
void operator-=(const vec3f &v);
float operator*(const vec3f &v);
vec3f operator*(const float &a)const;
void operator*=(const float &a);
vec3f operator/(const float &a);
void operator/=(const float &a);
bool operator==(const vec3f &v);

private:


};

class vec2f
{
public:

float x; 
float y; 


vec2f();
vec2f(float _x , float _y);


~vec2f();


vec2f(const vec2f &v);
vec2f& operator=(const vec2f &v);


friend std::ostream& operator<<(std::ostream &os, vec2f const &m) ;


vec2f operator+(const vec2f &v);
void  operator+=(const vec2f &v);
vec2f operator-(const vec2f &v);
void operator-=(const vec2f &v);
float operator*(const vec2f &v);
void operator*=(const float &a);
vec2f operator*(const float &a);
void operator/=(const float &a);
vec2f operator/(const float &a); 
bool operator==(const vec2f &v);


vec3f to3DVector(); 

private:
};

class Matrix
{
public:
std::vector<float> mData;
int nOfRows;
int nOfColumns;
int liniarIndex;

Matrix();
Matrix(int _nOfRows,int _nOfColumns);
Matrix(int _nOfRows,int _nOfColumns, const std::vector<float> inputData);



~Matrix();


friend std::ostream& operator<<(std::ostream &os, Matrix const &m) ;



void setElement(const int &n, const int &m,const float &a);
float getElement(const int &n, const int &m);
float getDeterminant();
Matrix getInverse();
Matrix getTranspose();

Matrix(const Matrix &v);
Matrix& operator=(const Matrix &v);


std::vector<float*> operator[](const int &a);
Matrix operator+(const Matrix &n);
void operator+=(const Matrix &n);
Matrix operator-(const Matrix &n);
void operator-=(const Matrix &n);
Matrix operator*(const Matrix &n);
void operator*=(const Matrix &n);
Matrix operator*(const float &a);
void operator*=(const float  &a);
Matrix operator/(const float &a);
void operator/=(const float  &a);
bool operator==(const Matrix &n);


private:
};

const Matrix O3;
const Matrix I3(3,3,{1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f});
vec3f VectorCrossProduct2D(const vec2f &u,const vec2f &v);
vec3f VectorCrossProduct3D(const vec3f &u,const vec3f &v);
float magnitudevec2f(const vec2f &v);
float magnitudevec3f(const vec3f &v);
vec3f unitvec3f(const vec3f &v);
vec2f unitvec2f(const vec2f &v);

Math::Matrix ogProjection3f(Math::vec3f p,float angle, float d1, float d2,float  a);
void scalevec2f(Math::vec2f &p,float xSCALE_FACTOR, float ySCALE_FACTOR);








class complex
{
public:
float real;
float imaginary;

complex();
complex(float _real, float _imaginary);

~complex();

float abs();
complex getConjugate();

complex& operator=(const complex &z);
complex& operator=(const float &a);

friend std::ostream& operator<<(std::ostream &os, complex const &z) ;

complex operator+(const complex &z);
void operator+=(const complex &z);
complex operator-(const complex &z);
void operator-=(const complex &z);
complex operator*(const complex &z);
void operator*=(const complex &z);
complex operator/(const complex &z);
void operator/=(const complex &z);
bool operator==(const complex &z);

complex operator+(const float&a);
void operator+=(const float&a);
complex operator-(const float&a);
void operator-=(const float&a);
complex operator*(const float&a);
void operator*=(const float&a);
complex operator/(const float&a);
void operator/=(const float&a);
bool operator==(const float &a);



private:

};




class quaternion
{
public:
float real;
vec3f imaginary;

quaternion();
quaternion(float _real, vec3f _imaginary);
~quaternion();

quaternion& operator=(const quaternion &q);
quaternion& operator=(const float &a);
quaternion& operator=(const complex &z);
quaternion& operator=(const vec3f &v);


float abs();
quaternion getConjugate();

friend std::ostream& operator<<(std::ostream &os, quaternion const &q) ;

quaternion operator+(const quaternion &q);
void operator+=(const quaternion &q);
quaternion operator-(const quaternion &q);
void operator-=(const quaternion &q);
quaternion operator*(const quaternion &q);
void operator*=(const quaternion &q);
bool operator==(const quaternion &q);

quaternion operator+(const float &a);
void operator+=(const float &a);
quaternion operator-(const float &a);
void operator-=(const float &a);
quaternion operator*(const float &a);
void operator*=(const float &a);
quaternion operator/(const float &a);
void operator/=(const float &a);
bool operator==(const float &a);


quaternion getUnitquaternion();
quaternion getInverse();
quaternion operator/(const quaternion&q);
void operator/=(const quaternion &q);

quaternion operator+(const complex &z);
void operator+=(const complex &z);
quaternion operator-(const complex &z);
void operator-=(const complex &z);
quaternion operator*(const complex &z);
void operator*=(const complex &z);
quaternion operator/(const complex &z);
void operator/=(const complex &z);
bool operator==(const complex &z);

quaternion operator+(const vec3f &v);
void operator+=(const vec3f &v);
quaternion operator-(const vec3f &v);
void operator-=(const vec3f &v);
quaternion operator*(const vec3f &v);
void operator*=(const vec3f &v);
quaternion operator/(const vec3f &v);
void operator/=(const vec3f &v);
bool operator==(const vec3f &v);




private:

};

vec3f rotationVec3f( vec3f v,vec3f axis,float angle);
vec2f rotationVec2f( vec2f v,float angle);
 };