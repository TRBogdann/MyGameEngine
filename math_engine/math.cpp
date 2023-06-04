#include "PSBmath.h" 
#include <cinttypes>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <math.h>
#include <ostream>
#include <type_traits>


namespace Math{




float degreesToRad(const float &x)
{
return x*(PI/180);
}


const float theoremeOfCosine(float l1,float l2, float angle)
{
  angle=degreesToRad(angle);
  return sqrt(l1*l1+l2*l2-2*cosf(angle)*l1*l2);
}


const float polygonRfinder(float l,float angle)
{
   angle=degreesToRad(angle);
return sqrt((l*l)/(2*(1-cosf(angle))));

}



vec4f::vec4f():x(0.0f),y(0.0f),z(0.0f){};
vec4f::vec4f(float _x,float _y,float _z,float _k):x(_x),y(_y),z(_z),k(_k){};

vec4f::~vec4f(){}

vec4f::vec4f(const vec4f& v):x(v.x),y(v.y),z(v.z),k(v.k){};
vec4f& vec4f::operator=(const vec4f &v)
{

x=v.x;
y=v.y;
z=v.z;
k=v.k;
return *this;

}

vec4f vec4f::operator+(const vec4f &v)
{
 return vec4f(x+v.x,y+v.y,z+v.z,k+v.k);

}

void vec4f::operator+=(const vec4f &v)
{
x+=v.x;
y+=v.y;
z+=v.z;
k+=v.k;

}


vec4f vec4f::operator-(const vec4f &v)
{
 return vec4f(x-v.x,y-v.y,z-v.z,k-v.k);

}

void vec4f::operator-=(const vec4f &v)
{
x-=v.x;
y-=v.y;
z-=v.z;
k-=v.k;

}

vec4f vec4f::operator*(const float& a)
{
 return vec4f(a*x,a*y,a*z,a*k);

}

void vec4f::operator*=(const float& a)
{
x*=a;
y*=a;
z*=a;
k*=a;
}
vec4f vec4f::operator/(const float& a)
{
 return vec4f(x/a,y/a,z/a,k/a);

}

void vec4f::operator/=(const float& a)
{
x/=a;
y/=a;
z/=a;
k/=a;
}

float vec4f::operator*(const vec4f &v)
{
return x*v.x+y*v.y+z*v.z+k*v.k;
}

bool vec4f::operator==(const vec4f &v)
{
  if((x==v.x) && (y==v.y) && (z==v.z) && (k==v.k))return true;
  return false;
}

 std::ostream& operator<<(std::ostream &os,const vec4f &v)
{
return os<<"( "<<v.x<<" , "<<v.y<<" , "<<v.z<<" , "<<v.k<<" )";
}








vec3f::vec3f():x(0.0f),y(0.0f),z(0.0f){};
vec3f::vec3f(float _x,float _y,float _z):x(_x),y(_y),z(_z){};

vec3f::~vec3f(){}

vec3f::vec3f(const vec3f& v):x(v.x),y(v.y),z(v.z){};
vec3f& vec3f::operator=(const vec3f &v)
{

x=v.x;
y=v.y;
z=v.z;

return *this;

}

vec3f vec3f::operator+(const vec3f &v)
{
 return vec3f(x+v.x,y+v.y,z+v.z);

}

void vec3f::operator+=(const vec3f &v)
{
x+=v.x;
y+=v.y;
z+=v.z;


}


vec3f vec3f::operator-(const vec3f &v)
{
 return vec3f(x-v.x,y-v.y,z-v.z);

}

void vec3f::operator-=(const vec3f &v)
{
x-=v.x;
y-=v.y;
z-=v.z;

}

vec3f vec3f::operator*(const float& a)
const {
 return vec3f(a*x,a*y,a*z);

}

void vec3f::operator*=(const float& a)
{
x*=a;
y*=a;
z*=a;

}
vec3f vec3f::operator/(const float& a)
{
 return vec3f(x/a,y/a,z/a);

}

void vec3f::operator/=(const float& a)
{
x/=a;
y/=a;
z/=a;

}

float vec3f::operator*(const vec3f &v)
{
return x*v.x+y*v.y+z*v.z;
}

bool vec3f::operator==(const vec3f &v)
{
  if((x==v.x) && (y==v.y) && (z==v.z))return true;
  return false;
}

 std::ostream& operator<<(std::ostream &os,const vec3f &v)
{
return os<<"( "<<v.x<<" , "<<v.y<<" , "<<v.z<<" )";
}





vec2f::vec2f():x(0.0f),y(0.0f){};
vec2f::vec2f(float _x,float _y):x(_x),y(_y){};

vec2f::~vec2f(){}

vec2f::vec2f(const vec2f& v):x(v.x),y(v.y){};
vec2f& vec2f::operator=(const vec2f &v)
{

x=v.x;
y=v.y;

return *this;

}

vec2f vec2f::operator+(const vec2f &v)
{
 return vec2f(x+v.x,y+v.y);

}

void vec2f::operator+=(const vec2f &v)
{
x+=v.x;
y+=v.y;


}

vec2f vec2f::operator-(const vec2f &v)
{
 return vec2f(x-v.x,y-v.y);

}

void vec2f::operator-=(const vec2f &v)
{
x-=v.x;
y-=v.y;


}


vec2f vec2f::operator*(const float& a)
{
 return vec2f(a*x,a*y);

}

void vec2f::operator*=(const float& a)
{
x*=a;
y*=a;

}

vec2f vec2f::operator/(const float& a)
{
 return vec2f(x/a,y/a);

}

void vec2f::operator/=(const float& a)
{
x/=a;
y/=a;

}

float vec2f::operator*(const vec2f &v)
{
return x*v.x+y*v.y;
}

vec3f vec2f::to3DVector()
{
return vec3f(x,y,0.0f);
}


bool vec2f::operator==(const vec2f &v)
{
  if((x==v.x) && (y==v.y))return true;
  return false;
}


 std::ostream& operator<<(std::ostream &os,const vec2f &v)
{
return os<<"( "<<v.x<<" , "<<v.y<<" )";
}



Matrix::Matrix():nOfRows(3),nOfColumns(3)
{
for(int i=0;i<9;i++)mData.push_back(0.0f);
};

Matrix::Matrix(int _nOfRows,int _nOfColumns):nOfRows(_nOfRows),nOfColumns(_nOfColumns)
{
for(int i=0;i<nOfRows*nOfColumns;i++)mData.push_back(0.0f);
};

Matrix::Matrix(int _nOfRows,int _nOfColumns,const std::vector<float> inputData):nOfRows(_nOfRows),nOfColumns(_nOfColumns)
{
for(int i=0;i<nOfRows*nOfColumns;i++)
{
  if(i<inputData.size())mData.push_back(inputData[i]);
  else mData.push_back(0.0f);
}
};

Matrix::~Matrix(){};

std::ostream& operator<<(std::ostream &os, Matrix const &m)
{ 

  for(int i=0;i<m.nOfRows;i++){
  os<<"[ ";
  for(int j=0;j<m.nOfColumns;j++)os<<m.mData[i*m.nOfColumns+j]<<' ';
  os<<" ]";
  os<<'\n';
  }

  return os;
};

std::vector<float*> Matrix::operator[](const int &a)
{
 std::vector<float*> p;

 for(int index=a*nOfColumns; index<(a+1)*nOfColumns;index++)p.push_back(&mData[index]);
 return p;
}

float  Matrix::getElement(const int &n, const int &m)
{
return mData[n*nOfColumns+m];
}

void  Matrix::setElement(const int &n, const int &m,const float &a)
{
mData[n*nOfColumns+m] = a;
}

Matrix::Matrix(const Matrix &m):
 mData(m.mData),nOfRows(m.nOfRows),nOfColumns(m.nOfColumns){};
 
Matrix& Matrix::operator=(const Matrix &m)
{
mData = m.mData;
nOfRows = m.nOfRows;
nOfColumns = m.nOfColumns;

return *this;

}


Matrix Matrix::operator+(const Matrix &n)
{
  
if((nOfRows==n.nOfRows) && (nOfColumns==n.nOfColumns))
{
Matrix m(nOfRows,nOfColumns);
for(int i=0;i<nOfColumns*nOfRows;i++)m.mData[i]=mData[i]+n.mData[i];
return m;
}
return O3;
}

void Matrix::operator+=(const Matrix &n)
{
if((nOfRows==n.nOfRows) && (nOfColumns==n.nOfColumns))

 for(int i=0;i<nOfColumns*nOfRows;i++)mData[i]=mData[i]+n.mData[i];


}

Matrix Matrix::operator-(const Matrix &n)
{
  
if((nOfRows==n.nOfRows) && (nOfColumns==n.nOfColumns))
{
Matrix m(nOfRows,nOfColumns);
for(int i=0;i<nOfColumns*nOfRows;i++)m.mData[i]=mData[i]-n.mData[i];
return m;
}
return O3;
}

void Matrix::operator-=(const Matrix &n)
{
if((nOfRows==n.nOfRows) && (nOfColumns==n.nOfColumns))

 for(int i=0;i<nOfColumns*nOfRows;i++)mData[i]=mData[i]-n.mData[i];


}

Matrix Matrix::operator*(const float &a)
{
  Matrix m(nOfRows,nOfColumns);
 for(int i=0;i<nOfColumns*nOfRows;i++) m.mData[i] = mData[i]*a;

 return m;

}

void Matrix::operator*=(const float &a)
{
 
 for(int i=0;i<nOfColumns*nOfRows;i++) mData[i] = mData[i]*a;
 

}

Matrix Matrix::operator/(const float &a)
{
  Matrix m(nOfRows,nOfColumns);
 for(int i=0;i<nOfColumns*nOfRows;i++) m.mData[i] = mData[i]/a;

 return m;

}

void Matrix::operator/=(const float &a)
{
 
 for(int i=0;i<nOfColumns*nOfRows;i++) mData[i] = mData[i]/a;
 

}

bool Matrix::operator==(const Matrix &n)
{
if((nOfRows==n.nOfRows) && (nOfColumns== n.nOfColumns))
{
for(int i=0;i<nOfColumns*nOfRows;i++)if(mData[i]!=n.mData[i])return false;

return true;
}

return false;
}


 Matrix Matrix::operator*(const Matrix &n)
 {
if (nOfColumns!=n.nOfRows) return I3;


Matrix m(nOfRows,n.nOfColumns);

for(int i=0;i<nOfRows;i++)
{
 for(int j=0;j<n.nOfColumns;j++)
 {
    for(int k=0;k<n.nOfRows;k++)
    m.mData[i*m.nOfColumns+j]= 
    m.mData[i*m.nOfColumns+j]+(n.mData[k*n.nOfColumns+j])*(mData[i*nOfColumns+k]);
 }
}

return m;
 }

void Matrix::operator*=(const Matrix &n)
 {


Matrix m(nOfRows,n.nOfColumns);

for(int i=0;i<nOfRows;i++)
{
 for(int j=0;j<n.nOfColumns;j++)
 {
    for(int k=0;k<n.nOfRows;k++)
    m.mData[i*m.nOfColumns+j]= 
    m.mData[i*m.nOfColumns+j]+(n.mData[k*n.nOfColumns+j])*(mData[i*nOfColumns+k]);
 }
}

*this=m;

 }

 float Matrix::getDeterminant()
 {
  
  if(nOfColumns!=nOfRows)return 0.0f;
  
  if(nOfColumns==1)return mData[0];
  
  if(nOfColumns==2) {return mData[0]*mData[3]-mData[1]*mData[2];}
  
  if(nOfColumns==3) {return 
  mData[0]*mData[4]*mData[8]+
  mData[5]*mData[1]*mData[6]+
  mData[2]*mData[3]*mData[7]-
  mData[2]*mData[4]*mData[6]-
  mData[0]*mData[5]*mData[7]-
  mData[8]*mData[1]*mData[3];
  }

  if(nOfColumns>3)
  {float s=0;
    for(int j=0;j<nOfColumns;j++)
    {
      Matrix m(nOfColumns-1,nOfColumns-1);
      int a=0;
      for(int i=1;i<nOfRows;i++)
      {
        for(int k=0;k<nOfColumns;k++)
        {
         if(k!=j){m.mData[a]=mData[i*nOfColumns+k];
           a++;
         }
        }
      }

     s=s+mData[j]*(1-2*(j%2))*m.getDeterminant();

    }
    return s;
  }
  
  return 0.0f;
 }

Matrix Matrix::getTranspose()
{
Matrix m(nOfColumns,nOfRows);

for(int j=0;j<nOfColumns;j++){
for(int i=0;i<nOfRows;i++)
m.mData[j*nOfRows+i]=mData[i*nOfColumns+j];
}

return m;

}


Matrix Matrix::getInverse()
{
if(nOfColumns!=nOfRows || getDeterminant()==0)return O3;
else{
Matrix m(nOfColumns,nOfColumns);
Matrix t=this->getTranspose();
for(int i=0;i<nOfColumns;i++){
for(int j=0;j<nOfRows;j++)
{
    Matrix n(nOfColumns-1,nOfColumns-1);
    int a=0;
    for(int y=0;y<nOfColumns;y++)
    for(int z=0;z<nOfRows;z++)
    {
      if(y!=i && z!=j){
        n.mData[a]=t.mData[y*nOfColumns+z];
      a++;
      }
    }
m.mData[i*nOfColumns+j]=(1-2*((i+j)%2))*n.getDeterminant();
}
}

return m/getDeterminant();
}
}





//Functii  mixte
vec3f VectorCrossProduct2D(const vec2f &u,const vec2f &v)
{
 return vec3f(0.0f,0.0f,u.x*v.y-u.y*v.x);
}


vec3f VectorCrossProduct3D(const vec3f &u,const vec3f &v)
{
 return vec3f(u.y*v.z-u.z*v.y,u.z*v.x-u.x*v.z,u.x*v.y-u.y*v.x);
}

float magnitudevec2f(const vec2f &v)
{
    return sqrt(v.x*v.x+v.y*v.y);
}


float magnitudevec3f(const vec3f &v)
{
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}


vec3f unitvec3f(const vec3f &v)
{
  return vec3f(v.x/magnitudevec3f(v),v.y/magnitudevec3f(v),v.z/magnitudevec3f(v))  ;
}


vec2f unitvec2f(const vec2f &v)
{
  return vec2f(v.x/magnitudevec2f(v),v.y/magnitudevec2f(v))  ;
}






complex::complex():real(0.0f),imaginary(0.0f){};
complex::complex(float _real, float _imaginary):real(_real),imaginary(_imaginary){};

complex::~complex(){};

complex& complex::operator=(const complex &z)
{ real=z.real;
  imaginary=z.imaginary;
  return *this;
}

complex& complex::operator=(const float &a)
{
 real=a;
 imaginary=0.0f;
 return *this;
}


std::ostream& operator<<(std::ostream &os, complex const &z) 
{
if(z.imaginary>0)return os<<z.real<<" + "<<z.imaginary<<'i';
else return os<<z.real<<" - "<<std::abs(z.imaginary)<<'i';
}

complex complex::operator+(const complex &z)
{
return complex(real+z.real,imaginary+z.imaginary);
}

void complex::operator+=(const complex &z)
{
real+=z.real;
imaginary+=z.imaginary;
}

complex complex::operator-(const complex &z)
{
return complex(real-z.real,imaginary-z.imaginary);
}

void complex::operator-=(const complex &z)
{
real-=z.real;
imaginary-=z.imaginary;
}

complex complex::operator*(const complex &z)
{
  return complex(real*z.real-imaginary*z.imaginary,real*z.imaginary+imaginary*z.real);
}
void complex::operator*=(const complex &z)
{ float x=real;
  real=real*z.real-imaginary*z.imaginary;
  imaginary=x*z.imaginary+imaginary*z.real;
}

float complex::abs()
{
 return std::sqrt(real*real+imaginary*imaginary);
}

complex complex::operator/(const complex &z)
{
return complex(real*z.real/(z.real*z.real+z.imaginary*z.imaginary)
-imaginary*((-z.imaginary)/(z.real*z.real+z.imaginary*z.imaginary))
,real*((-z.imaginary)/(z.real*z.real+z.imaginary*z.imaginary))
+imaginary*z.real/(z.real*z.real+z.imaginary*z.imaginary));
}

void complex::operator/=(const complex &z)
{
float x=real;
real=real*z.real/(z.real*z.real+z.imaginary*z.imaginary)
-imaginary*((-z.imaginary)/(z.real*z.real+z.imaginary*z.imaginary));
imaginary=x*((-z.imaginary)/(z.real*z.real+z.imaginary*z.imaginary))
+imaginary*z.real/(z.real*z.real+z.imaginary*z.imaginary);
}

complex complex::operator+(const float&a)
{
return complex(a+real,imaginary);
}

void complex::operator+=(const float&a)
{
real=real+a;
}

complex complex::operator-(const float&a)
{
return complex(real-a,imaginary);
}

void complex::operator-=(const float&a)
{
real=real-a;
}

complex complex::operator*(const float&a)
{
return complex(a*real,a*imaginary);
}


void complex::operator*=(const float&a)
{
real=real*a;
imaginary=imaginary*a;
}

complex complex::operator/(const float&a)
{
return complex(real/a,imaginary/a);
}

void complex::operator/=(const float&a)
{
real=real/a;
imaginary=imaginary/a;
}

bool complex::operator==(const complex &z)
{
return ((real==z.real) && (imaginary==z.imaginary));
}

bool complex::operator==(const float &a)
{
return ((real==a) && (imaginary==0));
}

complex complex::getConjugate()
{
return complex(real,-imaginary);
}




quaternion::quaternion():real(0.0f),imaginary(vec3f(0.0f,0.0f,0.0f)){};
quaternion::quaternion(float _real, vec3f _imaginary):real(_real),imaginary(_imaginary){};

quaternion::~quaternion(){};

float quaternion::abs()
{
  return real*real + imaginary*imaginary;
}

quaternion quaternion::getConjugate()
{
  return quaternion(real,imaginary*(-1));
}

quaternion& quaternion::operator=(const quaternion &q)
{
real=q.real;
imaginary=q.imaginary;

return *this;
}

quaternion& quaternion::operator=(const float &a)
{
real=a;
imaginary=vec3f();
return *this;
}

quaternion& quaternion::operator=(const complex &z)
{
real=z.real;
imaginary=vec3f(z.imaginary,0,0);
return *this;
}
quaternion& quaternion::operator=(const vec3f &v)
{
real=0;
imaginary=v;
return *this;
}

std::ostream& operator<<(std::ostream &os, quaternion const &q)
{
  return os<<"( "<<q.real<<' '<<q.imaginary.x<<' '<<q.imaginary.y<<' '<<q.imaginary.z<<" )";
}

quaternion quaternion::operator+(const quaternion &q)
{
return quaternion(real+q.real,imaginary+q.imaginary);
}

void quaternion::operator+=(const quaternion &q)
{
real+=q.real;
imaginary+=q.imaginary;
}

quaternion quaternion::operator-(const quaternion &q)
{
return quaternion(real-q.real,imaginary-q.imaginary);
}

void quaternion::operator-=(const quaternion &q)
{
real-=q.real;
imaginary-=q.imaginary;
}

quaternion quaternion::operator*(const quaternion &q)
{
return quaternion(real*q.real-imaginary*q.imaginary
,(q.imaginary*real)+(imaginary*q.real)+VectorCrossProduct3D(imaginary, q.imaginary));
}

void quaternion::operator*=(const quaternion &q)
{
float x=real;
real=real*q.real-imaginary*q.imaginary;
imaginary=(q.imaginary*x)+(imaginary*q.real)+VectorCrossProduct3D(imaginary, q.imaginary);

}




bool quaternion::operator==(const quaternion &q)
{
return ((real==q.real) && (imaginary==q.imaginary));
}

quaternion quaternion::operator+(const float &a)
{
return quaternion(real+a,imaginary);
}

void quaternion::operator+=(const float &a)
{
real=real+a;
}
quaternion quaternion::operator-(const float &a)
{
return quaternion(real-a,imaginary);
}

void quaternion::operator-=(const float &a)
{
real=real-a;
}

quaternion quaternion::operator*(const float &a)
{
return quaternion(real*a,imaginary*a);
}

void quaternion::operator*=(const float &a)
{
real=real*a;
imaginary=imaginary*a;
}

quaternion quaternion::operator/(const float &a)
{
return quaternion(real/a,imaginary/a);
}

void quaternion::operator/=(const float &a)
{
real=real/a;
imaginary=imaginary/a;
}

bool quaternion::operator==(const float &a)
{
  if(imaginary==vec3f()){
  if(real==a)return true;
  }
  return false;
}

quaternion quaternion::getUnitquaternion()
{
return *this/this->abs();
}

quaternion quaternion::getInverse()
{
float norm=this->abs();
return quaternion(real/norm,(imaginary*(-1))/norm);
}

quaternion quaternion::operator/(const quaternion &q)
{
quaternion d=q;

return *this*d.getInverse();
}

void  quaternion::operator/=(const quaternion &q)
{
quaternion d=q;

*this=*this*d.getInverse();
}


quaternion quaternion::operator+(const complex &z)
{
return quaternion(real+z.real,imaginary + vec3f(z.imaginary,0.0f,0.0f));
}

void quaternion::operator+=(const complex &z)
{
  real+=z.real;
  imaginary+=vec3f(z.imaginary,0,0);
}

quaternion quaternion::operator-(const complex &z)
{
return quaternion(real+z.real,imaginary - vec3f(z.imaginary,0.0f,0.0f));
}

void quaternion::operator-=(const complex &z)
{
  real-=z.real;
  imaginary-=vec3f(z.imaginary,0,0);
}

quaternion quaternion::operator*(const complex &z)
{
return (*this)*quaternion(z.real,vec3f(z.imaginary,0.0f,0.0f));
}

void quaternion::operator*=(const complex &z)
{
 *this=(*this)*quaternion(z.real,vec3f(z.imaginary,0.0f,0.0f));
}

quaternion quaternion::operator/(const complex &z)
{
return (*this)/quaternion(z.real,vec3f(z.imaginary,0.0f,0.0f));
}

void quaternion::operator/=(const complex &z)
{
 *this=(*this)/quaternion(z.real,vec3f(z.imaginary,0.0f,0.0f));
}

quaternion quaternion::operator+(const vec3f &v)
{
return quaternion(real,imaginary+v);
}

void quaternion::operator+=(const vec3f &v)
{
imaginary+=v;
}

quaternion quaternion::operator-(const vec3f &v)
{
return quaternion(real,imaginary-v);
}

void quaternion::operator-=(const vec3f &v)
{
imaginary-=v;
}

quaternion quaternion::operator*(const vec3f &v)
{
return (*this)*quaternion(0.0f,v);
}

void quaternion::operator*=(const vec3f &v)
{
 *this=(*this)*quaternion(0.0f,v);
}

quaternion quaternion::operator/(const vec3f &v)
{
return (*this)/quaternion(0.0f,v);
}

void quaternion::operator/=(const vec3f &v)
{
 *this=(*this)/quaternion(0.0f,v);
}

vec3f rotationVec3f( vec3f v,vec3f axis,float angle)
{
axis=unitvec3f(axis);
quaternion q(0,axis);
q=q.getUnitquaternion();
angle=degreesToRad(angle);
q=quaternion(cosf(angle/2.0f),q.imaginary*sinf(angle/2.0f));
return (q*v*q.getInverse()).imaginary;
}

vec2f rotationVec2f( vec2f v,float angle)
{
angle=degreesToRad(angle);
complex z1(v.x,v.y);
complex z2(cos(angle),sin(angle));
complex z3=z2*z1;
return vec2f(z3.real,z3.imaginary);
}

Math::Matrix ogProjection3f(Math::vec3f p,float angle, float d1, float d2,float  a)
{
float d=d2-d1;
float z=p.z;
angle=Math::degreesToRad(angle);
if(z==0)z=1;
return (Math::Matrix(1,4,{p.x,p.y,p.z,1.0f})*
Math::Matrix(4,4,
{a*(1/tanf(angle/2)) , 0.0f, 0.0f , 0.0f,
           0.0f, 1/tanf(angle/2), 0.0f , 0.0f,
           0.0f, 0.0f, d2/d, 1.0f,
           0.0f, 0.0f , -d1*(d2/d),0.0f



})/z

)

;
};

void scalevec2f(Math::vec2f &p,float xSCALE_FACTOR, float ySCALE_FACTOR)
{
p.x*=xSCALE_FACTOR;
p.y*=ySCALE_FACTOR;
};

}