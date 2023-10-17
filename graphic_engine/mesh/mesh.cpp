#include "mesh.h"
#include <string>

namespace Models3D
{
 Quad::Quad():
 origin({0,0,0}),usable(0),_texture(0)
 {

    for(unsigned int i=0; i<4;i++)
    {

    colors[i]=white;
    vertecies[i]={0.0f,0.0f,0.0f};
    texCoord[i]={0.0f,0.0f};

    }

 }
 Quad::Quad(Math::vec3f p1,Math::vec3f p2,Math::vec3f p3, Math::vec3f p4):
 origin({0,0,0}),usable(0),_texture(0)
 {
      for(unsigned int i=0; i<4;i++)
    {

    colors[i]=white;
    texCoord[i]={0.0f,0.0f};

    }

vertecies[0]=p1;
vertecies[1]=p2;
vertecies[2]=p3;
vertecies[3]=p4;

 }

 Quad::~Quad()
 {

 }
 
 bool Quad::readyToUse()
 {
    return usable;
 }

 void Quad::changeCoordinates(Math::vec3f p1, Math::vec3f p2, Math::vec3f p3, Math::vec3f p4)
 {

    vertecies[0]=p1;
    vertecies[1]=p2;
    vertecies[2]=p3;
    vertecies[3]=p4;
    origin=(p1+p2+p3+p4)/4.0f;

}

void Quad::addTexture(std::string texture)
{
 _texture=texture;
}

void Quad::rotate(float angle, Math::vec3f axis)
{

    for(unsigned int i=0;i<4;i++)
    {
    vertecies[i]=Math::rotationVec3f(vertecies[i]-origin,axis, angle)+origin;
    }

}

void Quad::translate(float x, float y, float z)
{
     for(unsigned int i=0;i<4;i++)
    {
    vertecies[i]=vertecies[i]+Math::vec3f{x,y,z};
    }
}

void Quad::scale(float xSCALE, float ySCALE, float zSCALE)
{
     for(unsigned int i=0;i<4;i++)
    {
    vertecies[i].x=vertecies[i].x*xSCALE;
    vertecies[i].y=vertecies[i].y*ySCALE;
    vertecies[i].z=vertecies[i].z*zSCALE;
    }
}

void Quad::addUniformColor(Color color)
{

    for(unsigned int i=0;i<4;i++)
    {
    colors[i]=color;
    }

}

void Quad::changeVertexColor(Color color, unsigned int index)
{
    if(index<4)
    {
        colors[index]=color;
    }
}

void Quad::changeTextureCoordinates(Math::vec2f p1, Math::vec2f p2, Math::vec2f p3, Math::vec2f p4)
{
    texCoord[0]=p1;
    texCoord[1]=p2;
    texCoord[2]=p3;
    texCoord[3]=p4;
}

/*
Mesh::Mesh():
_shader(0),_texture(0),buff(0),ind(0),arr(0),usable(0),colors(0),texCoords(0),Vertecies(0),atrib(0)
{

};
*/


}