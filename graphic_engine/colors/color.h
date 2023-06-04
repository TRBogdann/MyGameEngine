#pragma once

#include <SDL2/SDL_pixels.h>
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

class Color 
{
public:
int r;
int g;
int b;

 Color();
 Color(int _r ,int _g , int _b);
 Color& operator=(const Color &c);
~Color();

private:
};

const Color white(255,255,255);
const Color black(0,0,0);
const Color red(255,0,0);
const Color green(0,255,0);
const Color dark_green(0,155,0);
const Color blue(0,0,255);
const Color yellow(255,255,0);
const Color violet(255,0,255);
const Color cyan(0,255,255);
const Color orange(255,127,0);
