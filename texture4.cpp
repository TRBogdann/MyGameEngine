#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/buffers/buffers.h"
#include "graphic_engine/geometry/geometry2.h"
#include "graphic_engine/renderer/renderer.h"
#include "graphic_engine/shaders/Shader.h"
#include "graphic_engine/textures/texture.h"
#include "math_engine/PSBmath.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <alloca.h>
#include <bits/types/FILE.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>

int main()
{
  

Window window("My Window",800,600);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
SDL_Event event;



glClearColor(0.0f,0.3f,0.3f,0.0f);

Shape2::Triangle trig({100.0f,100.0f}, {200.0f,100.0f},{150.0f,200.0f});
Pencil pencil(window.getWidth(),window.getHeight());

trig.setFillVert(red,0);
trig.setFillVert(blue,1);
trig.setFillVert(green,2);

Shape2::Rectangle shape({400.0f,400.0f},200.0f,200.0f);
shape.setTexture("testTextures/wall.jpeg");
shape.setRenderMode(TEXTURE_MODE);

while(!window.isClosed())
{
 
    pencil.clear();
  
    window.pollEvents(event);

    glViewport(0,0,window.getWidth(),window.getHeight());


    pencil.draw(shape);
    pencil.draw(trig);
    
    


        window.GLswap();
        
    }
return 0;

}
