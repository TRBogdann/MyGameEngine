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

float trig[]=
{
-0.75f,-0.75f,1.0f,0.0f,0.0f,
 0.0f,0.75f, 1.0f,0.0f,1.0f,
 0.75f,-0.75f,1.0f,1.0f,0.0f
};

unsigned int indexData[]={0,1,2};

graphicalAtribute *atributes=TexAtrib();
Shader *MyShader=TexShader();
VertexArray *arr=new VertexArray(5*sizeof(float));
arr->bind();
VertexBuffer *vert=new VertexBuffer(trig,15*sizeof(float));
arr->addData(*vert,atributes,2);
IndexBuffer *ind=new IndexBuffer(indexData,3);
MyShader->bind();
//MyShader.setUniform4f("color",1.0f,0.0f,0.0f,1.0f);
Texture *texture=new Texture("testTextures/wall.jpeg",0);
MyShader->setUniform1i("textureSampler",0);
texture->bind();
Renderer renderer;

glClearColor(0.0f,0.3f,0.3f,0.0f);



while(!window.isClosed())
{
 
    
    renderer.clear();

arr=new VertexArray(5*sizeof(float));
arr->bind();
vert=new VertexBuffer(trig,15*sizeof(float));
arr->addData(*vert,atributes,2);
ind=new IndexBuffer(indexData,3);
//texture=new Texture("testTextures/wall.jpeg",0);
texture->bind();
MyShader->bind();
//MyShader->setUniform4f("color",1.0f,0.0f,0.0f,1.0f);

MyShader->setUniform1i("textureSampler",0);




    window.pollEvents(event);

    glViewport(0,0,window.getWidth(),window.getHeight());


    renderer.drawType1(*arr,*ind, *MyShader);
   
    texture->unbind();
    MyShader->unbind();
    vert->unbind();
    ind->unbind();
    arr->bind();

    delete vert;
    delete ind;
    delete arr;
    


        window.GLswap();
        
    }
return 0;

}
