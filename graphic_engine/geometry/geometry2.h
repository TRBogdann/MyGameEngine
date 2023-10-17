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
#include "geometry.h"
#include "../textures/texture.h"

#define TEXTURE_MODE 1
#define COLOR_MODE 0
#define LEFT_ROTATION 0
#define RIGHT_ROTATION 1


namespace Shape2{

class Triangle
{

public:
Math::vec2f coord[3];
Math::vec2f origin;
Math::vec2f position;
Math::vec2f texCoords[3];
Math::vec3f fill[3];
Texture *texture;
Triangle(Math::vec2f p1,Math::vec2f p2,Math::vec2f p3);
~Triangle();

float getRotation()const;
void setRotation(const float angle);
void rotate(float angle,bool direction=LEFT_ROTATION);//direction can either LEFT_ROTATION or RIGHT_ROTATION

void setOrigin(Math::vec2f newOrigin);
Math::vec2f getOrigin();

void setPosition(Math::vec2f newPosition);
Math::vec2f getPosition();

void setOpacity(unsigned int alpha);
float getOpacity()const;

void setFillTriangle(const Color color);
void setFillVert(const Color color,unsigned char index);
Color getFill(unsigned char index)const;

void setTextureCoords(unsigned char index,Math::vec2f coords);
Math::vec2f getTextureCoords(unsigned char index);

void setRenderMode(bool mode);// TEXTURE_MODE or COLOR_MODE
bool getRenderMode();


void setTexture(std::string texturePath);

void move(Math::vec2f vector);
void scale(float XSCALE, float YSCALE);

private:


bool textureUsed;
float angle;
unsigned int opacity;
};

class Rectangle
{
public:
Math::vec2f coord[4];
Math::vec2f texCoords[4];
Math::vec3f fill[4];
Math::vec2f origin;
Math::vec2f position;
Texture *texture;

Rectangle(Math::vec2f position,float width,float height);
~Rectangle();

//void reshape(float newWidth,float newHeight);
void move(Math::vec2f vector);
void rotate(float alpha,bool dir);
void scale(float XSCALE, float YSCALE);

float getRotation()const;
void setRotation(const float angle);

void setFillVert(unsigned int index, Color color);
void setFill(Color color);
Color getFill(unsigned int index);

void setOrigin(Math::vec2f newOrigin);
Math::vec2f getOrigin();

void setPosition(Math::vec2f newPosition);
Math::vec2f getPosition();

void setOpacity(unsigned int alpha);
unsigned int  getOpacity();

void setTexture(std::string);

void setRenderMode(bool mode);// TEXTURE_MODE or COLOR_MODE
bool getRenderMode();

void setTextureCoords(unsigned char index,Math::vec2f coords);
Math::vec2f getTextureCoords(unsigned char index);


private:
float _width;
float _height;
bool textureUsed;
float angle;
unsigned int opacity;
};


}
