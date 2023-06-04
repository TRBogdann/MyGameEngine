#pragma once
#include <cstddef>
#include <string>
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_events.h> 
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <GL/glew.h>
#include "../geometry/geometry.h"
#include "../geometry/geometry.h"
#include "../../math_engine/PSBmath.h"



class Window
{
public:
    Window(const std::string &title,int width,int height); 
    ~Window(); 
 void pollEvents(SDL_Event &e);
 void close();
   inline bool isClosed()
 
   const {
        return _closed;
    }
    void render_object() const;
    void drawShape(Shape::Triangle shape) const;
    void drawShape(Shape::RegularPolygon shape)const;
    void drawShape(Shape::Rectangle shape)const;
    void drawPixel(Math::vec2f position,Color _color)const;
    void drawline(float a,float b,float x, float y, Color color)const;
    void clear() const;
    float getWidth() const;
    float getHeight() const;
    void GLswap()const;


private:
bool init();


private:
std::string _title; 
int _width = 800;
int _height = 600;
bool _closed=false; 
 SDL_Window *_window = nullptr;
 SDL_Renderer *_renderer= nullptr;
 SDL_GLContext _glcontext=NULL ;

};

void delay(int ms);