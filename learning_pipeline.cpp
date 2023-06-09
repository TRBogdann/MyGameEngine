#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/colors/color.h"
#include "graphic_engine/geometry/geometry.h"
#include "graphic_engine/renderer/renderer.h"
#include "graphic_engine/shaders/Shader.h"
#include "graphic_engine/textures/texture.h"
#include "graphic_engine/windows/window.h"
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



Math::vec2f Origin(float *vect)
{
Math::vec2f origin;

float x=(vect[0]+vect[7]+vect[21]+vect[14])/4;
float y=(vect[1]+vect[8]+vect[22]+vect[15])/4;

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
  point=Math::rotationVec2f({vect[7*i]-origin.x,vect[7*i+1]-origin.y},alpha)+origin;
  vect[7*i]=point.x;
  vect[7*i+1]=point.y;
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
SDL_Event event;
//0A.VERTEX DATA (opengl foloseste coordonate normalizate)

float vertexData2F[]=
{
-0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 
 0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
-0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
 0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,

};



//0B.INDEX DATA (Ordinera desenarii punctelor)
unsigned int indexData[6]=
{
0,2,1,
2,3,1
};


std::ifstream fs("graphic_engine/shaders/fragmentShader.shader");
std::ifstream vs("graphic_engine/shaders/vertexShader.shader");
std::string vertexShader=FileToString(vs);
std::string fragmentShader=FileToString(fs);

Shader MyShader(vertexShader,fragmentShader);
VertexArray arr(7*sizeof(float));
VertexBuffer vert(vertexData2F,28*sizeof(float));
IndexBuffer ind(indexData,6);
graphicalAtribute atributes[2]=
{
{3,"Vertecies"},
{4,"Color"}
};
arr.addData(vert,atributes,2);
MyShader.bind();
//MyShader.setUniform4f("color",1.0f,0.0f,0.0f,1.0f);
Texture texture("wall.jpeg",0);
texture.bind();
MyShader.setUniform1i("u_Texture",0);
Renderer renderer;







glClearColor(0.0f,0.3f,0.3f,0.0f);

while(!window.isClosed())
{
    renderer.clear();

VertexArray arr2(7*sizeof(float));
VertexBuffer v2(vertexData2F,28*sizeof(float));
arr2.addData(v2,atributes,2);

    window.pollEvents(event);



  if(event.type==SDL_KEYDOWN)
    KeyDown(event);
  if(event.type==SDL_KEYUP)
    KeyUp(event);

  if(A_isPressed)
  {
   
 vertexData2F[0]-=0.001f;
 vertexData2F[7]-=0.001f;
 vertexData2F[14]-=0.001f;
 vertexData2F[21]-=0.001f;
  }

    if(D_isPressed)
  {
   
 vertexData2F[0]+=0.001f;
 vertexData2F[7]+=0.001f;
 vertexData2F[14]+=0.001f;
 vertexData2F[21]+=0.001f;
  }

    if(S_isPressed)
  {
   
 vertexData2F[1]-=0.001f;
 vertexData2F[8]-=0.001f;
 vertexData2F[15]-=0.001f;
 vertexData2F[22]-=0.001f;
  }

    if(W_isPressed)
  {
   
 vertexData2F[1]+=0.001f;
 vertexData2F[8]+=0.001f;
 vertexData2F[15]+=0.001f;
 vertexData2F[22]+=0.001f;
  }

  if(Space_isPressed)
  {
    rotate(1.0f,vertexData2F);
  }
    
    
    


  glViewport(0,0,window.getWidth(),window.getHeight());



    renderer.drawType1(arr,ind,MyShader);
 
    window.GLswap();
   



       
}
return 0;
}