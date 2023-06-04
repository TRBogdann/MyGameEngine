#pragma once

#include <SDL2/SDL_shape.h>
#include <string>
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_events.h> 
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include "../../math_engine/PSBmath.h"
#include "../colors/color.h"

namespace Shape
{
class Triangle
{
public:
Math::vec2f position;
Math::vec2f origin;
std::vector<Math::vec2f> ListOfVertices;

Triangle(Math::vec2f p1,Math::vec2f p2,Math::vec2f p3);
~Triangle();



void rotate(const float angle);
float getRotation()const;
void setRotation(const float angle);

void setPosition(const Math::vec2f newPosition);
Math::vec2f getPosition()const;
void setOrigin(const Math::vec2f newOrigin);
Math::vec2f getOrigin()const;

void setTransparency(int a);
int getOpacity()const;

void setFill(const Color color);
Color getFill()const;

std::vector<float> getSides() const;
private:

int opacity;
float rotation;
Color fill;

};

class RegularPolygon
{
public:
Math::vec2f position;
Math::vec2f origin;
std::vector<Math::vec2f> ListOfVertices;
float sideLenght;

RegularPolygon(int nrOfVertices,Math::vec2f _position,float _sideLenght);
~RegularPolygon();

void rotate(const float angle);
float getRotation()const;
void setRotation(const float angle);

void setPosition(const Math::vec2f newPosition);
Math::vec2f getPosition()const;
void setOrigin(const Math::vec2f newOrigin);
Math::vec2f getOrigin()const;


void setTransparency(int a);
int getOpacity()const;

void setFill(const Color color);
Color getFill()const;

float getSideLenght() const;
private:



private:
int opacity;
float rotation;
Color fill;


};

class Rectangle
{
    public:
Math::vec2f position;
Math::vec2f origin;
std::vector<Math::vec2f> ListOfVertices;
float sideLenght;

Rectangle(Math::vec2f _position,float _width,float _height);
~Rectangle();

void rotate(const float angle);
float getRotation()const;
void setRotation(const float angle);

void setPosition(const Math::vec2f newPosition);
Math::vec2f getPosition()const;
void setOrigin(const Math::vec2f newOrigin);
Math::vec2f getOrigin()const;

void setWidth(float newWidth);
void setHeight(float newHeight);
float getWidth()const;
float getHeight()const;

void setTransparency(int a);
int getOpacity()const;

void setFill(const Color color);
Color getFill()const;
private:



private:
int opacity;
float rotation;
float width;
float height;
Color fill;


};



};
