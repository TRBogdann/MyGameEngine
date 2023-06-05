#include "graphic_engine/PSBgraphics.h"
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

int A_isPressed=0;
int S_isPressed=0;
int D_isPressed=0;
int W_isPressed=0;
int Space_isPressed=0;

float ar=600.0f/800.0f;


Math::vec2f Origin(float *vect)
{
Math::vec2f origin;

float x=(vect[0]+vect[5]+vect[10]+vect[15])/4;
float y=(vect[1]+vect[6]+vect[11]+vect[16])/4;

origin.x=x;
origin.y=y;

return origin;
}

void rotate(float alpha, float *vect)
{
 Math::vec2f point;
 Math::vec2f origin=Origin(vect);
 
 for(int i=0;i<4;i++)
 { 
  point=Math::rotationVec2f({vect[5*i]-origin.x,vect[5*i+1]-origin.y},alpha)+origin;
  vect[5*i]=point.x;
  vect[5*i+1]=point.y;
 }
}

void KeyDown(SDL_Event &event)
{
if(event.key.keysym.sym==SDLK_a)A_isPressed=1;
if(event.key.keysym.sym==SDLK_s)S_isPressed=1;
if(event.key.keysym.sym==SDLK_d)D_isPressed=1;
if(event.key.keysym.sym==SDLK_w)W_isPressed=1;
if(event.key.keysym.sym==SDLK_SPACE)Space_isPressed=1;
}

void KeyUp(SDL_Event &event)
{
if(event.key.keysym.sym==SDLK_a)A_isPressed=0;
if(event.key.keysym.sym==SDLK_s)S_isPressed=0;
if(event.key.keysym.sym==SDLK_d)D_isPressed=0;
if(event.key.keysym.sym==SDLK_w)W_isPressed=0;
if(event.key.keysym.sym==SDLK_SPACE)Space_isPressed=0;
}

int main()
{
  

Window window("My Window",800,600);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
SDL_Event event;
//0A.VERTEX DATA (opengl foloseste coordonate normalizate)

float vertexData2F[]=
{
-0.5f*ar, -0.5f,  0.0f,0.0f, 0.0f,
 0.5f*ar, -0.5f,  0.0f, 1.0f, 0.0f,
-0.5f*ar,  0.5f,  0.0f, 0.0f, 1.0f,
 0.5f*ar,  0.5f,  0.0f, 1.0f, 1.0f

};



//0B.INDEX DATA (Ordinera desenarii punctelor)
unsigned int indexData[6]=
{
0,2,1,
2,3,1
};


std::ifstream fs("graphic_engine/shaders/textureFragShader.shader");
std::ifstream vs("graphic_engine/shaders/textureVertShader.shader");
std::string vertexShader=FileToString(vs);
std::string fragmentShader=FileToString(fs);

Shader MyShader(vertexShader,fragmentShader);
VertexArray arr(5*sizeof(float));
VertexBuffer vert(vertexData2F,20*sizeof(float));
IndexBuffer ind(indexData,6);
graphicalAtribute atributes[2]=
{
{3,"Vertecies"},
{2,"Texture"}
};
arr.addData(vert,atributes,2);
MyShader.bind();
//MyShader.setUniform4f("color",1.0f,0.0f,0.0f,1.0f);
Texture texture("testTextures/wall.jpg",0);
MyShader.setUniform1i("textureSampler",0);
texture.bind();
Renderer renderer;







glClearColor(0.0f,0.3f,0.3f,0.0f);

while(!window.isClosed())
{
    renderer.clear();

VertexArray arr2(5*sizeof(float));
VertexBuffer v2(vertexData2F,20*sizeof(float));
arr2.addData(v2,atributes,2);

    window.pollEvents(event);

  if(event.type==SDL_WINDOWEVENT)
   if(event.window.event==SDL_WINDOWEVENT_RESIZED)
     {
      float oldAR=ar;
      ar=window.getHeight()/window.getWidth();
 vertexData2F[0]/=oldAR;
 vertexData2F[0]*=ar;
  vertexData2F[5]/=oldAR;
 vertexData2F[5]*=ar;
  vertexData2F[10]/=oldAR;
 vertexData2F[10]*=ar;
  vertexData2F[15]/=oldAR;
 vertexData2F[15]*=ar;
     }

  if(event.type==SDL_KEYDOWN)
    KeyDown(event);
  if(event.type==SDL_KEYUP)
    KeyUp(event);

  if(A_isPressed)
  {
   
 vertexData2F[0]-=0.001f;
 vertexData2F[5]-=0.001f;
 vertexData2F[10]-=0.001f;
 vertexData2F[15]-=0.001f;
  }

    if(D_isPressed)
  {
   
 vertexData2F[0]+=0.001f;
 vertexData2F[5]+=0.001f;
 vertexData2F[10]+=0.001f;
 vertexData2F[15]+=0.001f;
  }

    if(S_isPressed)
  {
   
 vertexData2F[1]-=0.001f;
 vertexData2F[6]-=0.001f;
 vertexData2F[11]-=0.001f;
 vertexData2F[16]-=0.001f;
  }

    if(W_isPressed)
  {
   
 vertexData2F[1]+=0.001f;
 vertexData2F[6]+=0.001f;
 vertexData2F[11]+=0.001f;
 vertexData2F[16]+=0.001f;
  }

  if(Space_isPressed)
  {
    rotate(0.2f,vertexData2F);
  }
    
    
    


  glViewport(0,0,window.getWidth(),window.getHeight());



    renderer.drawType1(arr,ind,MyShader);
 
    window.GLswap();
   



       
}
return 0;
}