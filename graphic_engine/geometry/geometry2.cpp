#include "geometry2.h"
#include <string>


Shape2::Triangle::Triangle(Math::vec2f p1,Math::vec2f p2,Math::vec2f p3)
{

origin=(p1+p2+p3)/3.0f;

coord[0]=p1;
coord[1]=p2;
coord[2]=p3;

position=origin;

fill[0]={0,0,0};
fill[1]={0,0,0};
fill[2]={0,0,0};

texCoords[0]={0.0f,0.0f};
texCoords[2]={1.0f,0.0f};
texCoords[1]={0.0f,1.0f};


textureUsed=false;
texture=0;

angle=0.0f;

opacity=255;

};

Shape2::Triangle::~Triangle()
{
    
       
};

Color Shape2::Triangle::getFill(unsigned char index)const
{
return Color(fill[index].x,fill[index].y,fill[index].z);
}

float Shape2::Triangle::getOpacity()const 
{
    return opacity;
}

Math::vec2f Shape2::Triangle::getOrigin()
{
    return origin;
};

Math::vec2f Shape2::Triangle::getPosition()
{
    return (coord[0]+coord[1]+coord[2])/3.0f;
}

bool Shape2::Triangle::getRenderMode()
{
    return textureUsed;
}

float Shape2::Triangle::getRotation()const
{
    return angle;
}

void Shape2::Triangle::move(Math::vec2f vect)
{
    coord[0]+=vect;
    coord[1]+=vect;
    coord[2]+=vect;
    position+=vect;
    origin+=vect;
}

void Shape2::Triangle::rotate(float alpha,bool dir)
{

if(dir)
{
coord[0]=Math::rotationVec2f(coord[0]-origin, alpha)+origin;
coord[1]=Math::rotationVec2f(coord[1]-origin, alpha)+origin;
coord[2]=Math::rotationVec2f(coord[2]-origin, alpha)+origin;
angle+=alpha;
if(angle>=360.0f)angle=angle-360.0f;
}

else
{
coord[0]=Math::rotationVec2f(coord[0]-origin, -alpha)+origin;
coord[1]=Math::rotationVec2f(coord[1]-origin, -alpha)+origin;
coord[2]=Math::rotationVec2f(coord[2]-origin, -alpha)+origin;
angle-=alpha;
if(angle<0.0f)angle=angle+360.0f;
}

}

void Shape2::Triangle::scale(float XSCALE, float YSCALE)
{
coord[0].x*=XSCALE;
coord[0].y*=YSCALE;

coord[1].x*=XSCALE;
coord[1].y*=YSCALE;

coord[2].x*=XSCALE;
coord[2].y*=YSCALE;
}

void Shape2::Triangle::setFillTriangle(const Color color)
{
    fill[0]={float(color.r),float(color.g),float(color.b)};
    fill[1]={float(color.r),float(color.g),float(color.b)};
    fill[2]={float(color.r),float(color.g),float(color.b)};
}

void Shape2::Triangle::setFillVert(const Color color,unsigned char index)
{
    fill[index]={float(color.r),float(color.g),float(color.b)};
}

void Shape2::Triangle::setOpacity(unsigned int alpha)
{
    opacity=alpha;
}

void Shape2::Triangle::setOrigin(Math::vec2f newOrigin)
{
    origin=newOrigin;
}

void Shape2::Triangle::setPosition(Math::vec2f newPosition)
{
    Math::vec2f diff=position-newPosition;

    coord[0]+=diff;
    coord[1]+=diff;
    coord[2]+=diff;
    origin+=diff;
}

void Shape2::Triangle::setRenderMode(bool mode)
{
    if(texture!=0)
        textureUsed=mode;
}

void Shape2::Triangle::setRotation(const float alpha)
{
if(angle!=alpha)
{
coord[0]=Math::rotationVec2f(coord[0]-origin, alpha-angle)+origin;
coord[1]=Math::rotationVec2f(coord[1]-origin, alpha-angle)+origin;
coord[2]=Math::rotationVec2f(coord[2]-origin, alpha-angle)+origin;
angle=alpha;
}
}

void Shape2::Triangle::setTexture(std::string path)
{   
    
    if(texture!=0){
        delete texture;
    }
    
    texture=new Texture(path,0);
}

void Shape2::Triangle::setTextureCoords(unsigned char index,Math::vec2f coords)
{
    if(index<3)
         texCoords[index]=coords;
};

Math::vec2f Shape2::Triangle::getTextureCoords(unsigned char index)
{   
    if(index>2)return {0.0f,0.0f};
        
        return texCoords[index];
}

Shape2::Rectangle::Rectangle(Math::vec2f screePosition,float width,float height):
position(screePosition),_width(width),_height(height),opacity(255)
{
    coord[0]=position+Math::vec2f({-width/2.0f,height/2.0f});
    coord[1]=position+Math::vec2f({-width/2.0f,-height/2.0f});
    coord[2]=position+Math::vec2f({width/2.0f,height/2.0f});
    coord[3]=position+Math::vec2f({width/2.0f,-height/2.0f});

    origin=position;

    fill[0]={0,0,0};
    fill[1]={0,0,0};
    fill[2]={0,0,0};
    fill[3]={0,0,0};

    texCoords[0]={0.0f,0.0f};
    texCoords[2]={1.0f,0.0f};
    texCoords[1]={0.0f,1.0f};
    texCoords[3]={1.0f, 1.0f};

    textureUsed=false;
    texture=0;
    angle=0.0f;

    
}

Shape2::Rectangle::~Rectangle()
{

}

Color Shape2::Rectangle::getFill(unsigned int index)
{
if(index<4)
    return Color(fill[index].x,fill[index].y,fill[index].z);

return black;
}

unsigned int Shape2::Rectangle::getOpacity()
{
    return opacity;
}

Math::vec2f Shape2::Rectangle::getOrigin()
{
    return origin;
};

Math::vec2f Shape2::Rectangle::getPosition()
{
    return position;
}

bool Shape2::Rectangle::getRenderMode()
{
    return textureUsed;
}

float Shape2::Rectangle::getRotation()const
{
    return angle;
}

void Shape2::Rectangle::move(Math::vec2f vect)
{
    coord[0]+=vect;
    coord[1]+=vect;
    coord[2]+=vect;
    coord[3]+=vect;
    position+=vect;
    origin+=vect;
}

void Shape2::Rectangle::scale(float XSCALE, float YSCALE)
{
coord[0].x*=XSCALE;
coord[0].y*=YSCALE;

coord[1].x*=XSCALE;
coord[1].y*=YSCALE;

coord[2].x*=XSCALE;
coord[2].y*=YSCALE;

coord[3].x*=XSCALE;
coord[3].y*=YSCALE;
}

void Shape2::Rectangle::rotate(float alpha,bool dir)
{

if(dir)
{
coord[0]=Math::rotationVec2f(coord[0]-origin, alpha)+origin;
coord[1]=Math::rotationVec2f(coord[1]-origin, alpha)+origin;
coord[2]=Math::rotationVec2f(coord[2]-origin, alpha)+origin;
coord[3]=Math::rotationVec2f(coord[3]-origin, alpha)+origin;
angle+=alpha;
if(angle>=360.0f)angle=angle-360.0f;
}

else
{
coord[0]=Math::rotationVec2f(coord[0]-origin, -alpha)+origin;
coord[1]=Math::rotationVec2f(coord[1]-origin, -alpha)+origin;
coord[2]=Math::rotationVec2f(coord[2]-origin, -alpha)+origin;
coord[3]=Math::rotationVec2f(coord[3]-origin, alpha)+origin;
angle-=alpha;
if(angle<0.0f)angle=angle+360.0f;
}

}

void Shape2::Rectangle::setFill(const  Color color)
{
    fill[0]={float(color.r),float(color.g),float(color.b)};
    fill[1]={float(color.r),float(color.g),float(color.b)};
    fill[2]={float(color.r),float(color.g),float(color.b)};
    fill[3]={float(color.r),float(color.g),float(color.b)};
}

void Shape2::Rectangle::setFillVert(unsigned int index,Color color)
{
    fill[index]={float(color.r),float(color.g),float(color.b)};
}

void Shape2::Rectangle::setOpacity(unsigned int alpha)
{
    opacity=alpha;
}

void Shape2::Rectangle::setOrigin(Math::vec2f newOrigin)
{
    origin=newOrigin;
}

void Shape2::Rectangle::setPosition(Math::vec2f newPosition)
{
    Math::vec2f diff=position-newPosition;

    coord[0]+=diff;
    coord[1]+=diff;
    coord[2]+=diff;
    coord[3]+=diff;
    origin+=diff;
}

void Shape2::Rectangle::setRenderMode(bool mode)
{
    if(texture!=0)
        textureUsed=mode;
}

void Shape2::Rectangle::setRotation(const float alpha)
{
if(angle!=alpha)
{
coord[0]=Math::rotationVec2f(coord[0]-origin, alpha-angle)+origin;
coord[1]=Math::rotationVec2f(coord[1]-origin, alpha-angle)+origin;
coord[2]=Math::rotationVec2f(coord[2]-origin, alpha-angle)+origin;
coord[3]=Math::rotationVec2f(coord[3]-origin, alpha-angle)+origin;
angle=alpha;
}
}

void Shape2::Rectangle::setTexture(std::string path)
{   
    
    if(texture!=0){
        delete texture;
    }
    
    texture=new Texture(path,0);
}

void Shape2::Rectangle::setTextureCoords(unsigned char index,Math::vec2f coords)
{
    if(index<4)
         texCoords[index]=coords;
};

Math::vec2f Shape2::Rectangle::getTextureCoords(unsigned char index)
{   
    if(index>3)return {0.0f,0.0f};
        
        return texCoords[index];
}