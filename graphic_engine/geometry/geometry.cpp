#include "geometry.h"
#include <vector>

namespace Shape
{

Triangle::Triangle(Math::vec2f p1,Math::vec2f p2,Math::vec2f p3)
{
ListOfVertices.push_back(p1);
ListOfVertices.push_back(p2);
ListOfVertices.push_back(p3);
opacity=255;
origin=(p1+p2+p3)/3;
position=origin;
fill=white;
rotation=0;
}

Triangle::~Triangle(){};

Math::vec2f Triangle::getPosition() const {return position;}
Math::vec2f Triangle::getOrigin() const {return origin;}

void Triangle::setPosition(const Math::vec2f newPosition)
{
position=newPosition;
};


void Triangle::setOrigin(const Math::vec2f newOrigin)
{
origin=newOrigin;
};

float Triangle::getRotation()const {return rotation ; }


void Triangle::setFill(const Color color)
{
fill=color;
}

std::vector<float> Triangle::getSides()const
{
std::vector<float>sides;
Math::vec2f v(ListOfVertices[0].x-ListOfVertices[1].x,ListOfVertices[0].y-ListOfVertices[1].y);
sides.push_back(Math::magnitudevec2f(v));

v=Math::vec2f(ListOfVertices[1].x-ListOfVertices[2].x,ListOfVertices[1].y-ListOfVertices[2].y);
sides.push_back(Math::magnitudevec2f(v));

v=Math::vec2f (ListOfVertices[2].x-ListOfVertices[0].x,ListOfVertices[2].y-ListOfVertices[0].y);
sides.push_back(Math::magnitudevec2f(v));
return sides;
}

void Triangle::setRotation(const float angle)
{
if(angle!=rotation){
ListOfVertices[0]=Math::rotationVec2f(ListOfVertices[0]-origin, angle-rotation)+origin;
ListOfVertices[1]=Math::rotationVec2f(ListOfVertices[1]-origin, angle-rotation)+origin;
ListOfVertices[2]=Math::rotationVec2f(ListOfVertices[2]-origin, angle-rotation)+origin;
rotation=angle;
}
}

void Triangle::rotate(const float angle)
{
ListOfVertices[0]=Math::rotationVec2f(ListOfVertices[0]-origin, angle)+origin;
ListOfVertices[1]=Math::rotationVec2f(ListOfVertices[1]-origin, angle)+origin;
ListOfVertices[2]=Math::rotationVec2f(ListOfVertices[2]-origin, angle)+origin;
rotation+=angle;
if(rotation>=360.0f)rotation=rotation-360.0f;
}

int Triangle::getOpacity()const {return opacity;}

void Triangle::setTransparency(int a)
{
 opacity=a;
}

Color Triangle::getFill()const{return fill;}

RegularPolygon::RegularPolygon(int nrOfVertices, Math::vec2f _position, float _sideLenght)
{
position=_position;
sideLenght=_sideLenght;
origin=_position;
float angleF=360.0f/nrOfVertices;
rotation=0;
opacity=255;
fill=white;
if(nrOfVertices>=1)
{
ListOfVertices.push_back(Math::vec2f(origin.x,origin.y-Math::polygonRfinder(_sideLenght, angleF)));
for(int i=1;i<nrOfVertices;i++)
    ListOfVertices.push_back(Math::vec2f(Math::rotationVec2f(ListOfVertices[i-1]-position,angleF))+position);
}


}

RegularPolygon::~RegularPolygon(){};

Color RegularPolygon::getFill() const {return fill;}

void RegularPolygon::setFill(const Color color) 
{
    fill=color;
}

int RegularPolygon::getOpacity() const {return opacity;}

void RegularPolygon::setTransparency(int a)
{
opacity=a;
}

Math::vec2f RegularPolygon::getOrigin() const {return origin;}

void RegularPolygon::setOrigin(const Math::vec2f newOrigin)
{
    origin=newOrigin;
}

Math::vec2f RegularPolygon::getPosition() const {return position;}

void RegularPolygon::setPosition(const Math::vec2f newPosition)

{
    position=newPosition;
}



float RegularPolygon::getRotation() const{return rotation;}

float RegularPolygon::getSideLenght() const{return sideLenght;}

void RegularPolygon::setRotation(const float angle)
{
if(angle!=rotation){
for(int i=0;i<ListOfVertices.size();i++){
ListOfVertices[i]=Math::rotationVec2f(ListOfVertices[i]-origin, angle-rotation)+origin;
}
rotation=angle;
}
}

void RegularPolygon::rotate(const float angle)
{
    for(int i=0;i<ListOfVertices.size();i++){
ListOfVertices[i]=Math::rotationVec2f(ListOfVertices[i]-origin, angle)+origin;
    }
rotation+=angle;
if(rotation>=360.0f)rotation=rotation-360.0f;

}

Rectangle::Rectangle(Math::vec2f _position,float _width,float _height):
position(_position),width(_width),height(_height)
{
 origin=position;
 fill=white;
 opacity=255;
 rotation=0;
ListOfVertices.push_back(Math::vec2f(position.x-(width)/2,position.y+(height/2))); 
ListOfVertices.push_back(Math::vec2f(position.x-(width)/2,position.y-(height/2)));    
ListOfVertices.push_back(Math::vec2f(position.x+(width)/2,position.y-(height/2))); 
ListOfVertices.push_back(Math::vec2f(position.x+(width)/2,position.y+(height/2)));   
};

Rectangle::~Rectangle(){};

Color Rectangle::getFill() const {return fill;}

void Rectangle::setFill(const Color color)
{
    fill=color;
};

int Rectangle::getOpacity()const {return opacity;}

void Rectangle::setTransparency(int a)
{
opacity=a;
}

float Rectangle::getHeight() const {return height;}

void Rectangle::setHeight(float newHeight)
{
if(height!=newHeight){
height=newHeight;
ListOfVertices[0]=Math::vec2f(position.x-(width)/2,position.y+(height/2)); 
ListOfVertices[1]=Math::vec2f(position.x-(width)/2,position.y-(height/2));    
ListOfVertices[2]=Math::vec2f(position.x+(width)/2,position.y-(height/2)); 
ListOfVertices[3]=Math::vec2f(position.x+(width)/2,position.y+(height/2));   
}
}


float Rectangle::getWidth() const {return width;}

void Rectangle::setWidth(float newWidth)
{
if(width!=newWidth){
width=newWidth;
ListOfVertices[0]=Math::vec2f(position.x-(width)/2,position.y+(height/2)); 
ListOfVertices[1]=Math::vec2f(position.x-(width)/2,position.y-(height/2));    
ListOfVertices[2]=Math::vec2f(position.x+(width)/2,position.y-(height/2)); 
ListOfVertices[3]=Math::vec2f(position.x+(width)/2,position.y+(height/2));   
}
}
Math::vec2f Rectangle::getPosition() const {return position;}

void Rectangle::setPosition(const Math::vec2f newPosition)
{
    position=newPosition;
ListOfVertices.push_back(Math::vec2f(position.x-(width)/2,position.y+(height/2))); 
ListOfVertices.push_back(Math::vec2f(position.x-(width)/2,position.y-(height/2)));    
ListOfVertices.push_back(Math::vec2f(position.x+(width)/2,position.y-(height/2))); 
ListOfVertices.push_back(Math::vec2f(position.x+(width)/2,position.y+(height/2)));   
}

Math::vec2f Rectangle::getOrigin() const {return origin;}

void Rectangle::setOrigin(const Math::vec2f newOrigin)
 {
    origin=newOrigin;
 }

float Rectangle::getRotation() const {return rotation;}

void Rectangle::setRotation(const float angle)
{
if(angle!=rotation)
{
ListOfVertices[0]=Math::rotationVec2f(ListOfVertices[0]-origin, angle-rotation)+origin;
ListOfVertices[1]=Math::rotationVec2f(ListOfVertices[1]-origin, angle-rotation)+origin;
ListOfVertices[2]=Math::rotationVec2f(ListOfVertices[2]-origin, angle-rotation)+origin;
ListOfVertices[3]=Math::rotationVec2f(ListOfVertices[3]-origin, angle-rotation)+origin;
rotation=angle;
}
}

void Rectangle::rotate(const float angle)
{
ListOfVertices[0]=Math::rotationVec2f(ListOfVertices[0]-origin, angle)+origin;
ListOfVertices[1]=Math::rotationVec2f(ListOfVertices[1]-origin, angle)+origin;
ListOfVertices[2]=Math::rotationVec2f(ListOfVertices[2]-origin, angle)+origin;
ListOfVertices[3]=Math::rotationVec2f(ListOfVertices[3]-origin, angle)+origin;
rotation+=angle;
if(rotation>=360.0f)rotation=rotation-360.0f;
}

}
