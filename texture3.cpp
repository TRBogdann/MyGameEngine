#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/buffers/buffers.h"
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

int A_isPressed=0;
int S_isPressed=0;
int D_isPressed=0;
int W_isPressed=0;
int Space_isPressed=0;

float a=800.0f/600.0f;
float d1=0.01f;
float d2=1000.0f;
float angle=90.0f;




Math::vec3f convertToGlCoords(Math::vec3f point,float width,float height)
{
float ar=width/height;
point.x=point.x/width;
point.y=point.y/height;
point.x=(2*point.x-1);
point.y=(1-2*point.y);
return {point.x,point.y,point.z};
}

float vertexData2F[]=
{
-0.25f, -0.25f*a,  1.0f,0.0f, 0.0f, 
 0.5f, -0.5f*a,  1.0f, 1.0f, 0.0f, 
-0.25f,  0.25f*a,  1.0f, 0.0f, 1.0f, 
 0.5f,  0.5f*a,  1.0f, 1.0f, 1.0f 

};

float v2[]=
{
-0.5f, -0.5f*a,  1.0f,0.0f, 0.0f, 
 0.5f, -0.5f*a,  1.0f, 1.0f, 0.0f, 
-0.5f,  0.5f*a,  1.0f, 0.0f, 1.0f, 
 0.5f,  0.5f*a,  1.0f, 1.0f, 1.0f 

};

float square2[]=
{
  -0.5f, -0.5f*a,  1.0f,0.0f, 0.0f, 
 0.5f, -0.5f*a,  1.0f, 1.0f, 0.0f, 
-0.5f,  0.5f*a,  1.0f, 0.0f, 1.0f, 
 0.5f,  0.5f*a,  1.0f, 1.0f, 1.0f 
};






//0B.INDEX DATA (Ordinera desenarii punctelor)
unsigned int indexData[6]=
{
0,2,1,
2,3,1
};

class Pencil1
{
public:
Pencil1()
{
isEmpty=1;
}
Pencil1(float *vertD)
{
isEmpty=0;
graphicalAtribute *atributes=TexAtrib();
shader=TexShader();
arr=new VertexArray((5*sizeof(float)));
arr->bind();
buff=new VertexBuffer(vertD,20*sizeof(float));
arr->addData(*buff,atributes,2);
ind=new IndexBuffer(indexData,6);
shader->bind();
texture=new Texture("testTextures/wall2k.jpg",0);
shader->setUniform1i("textureSampler",0);
texture->bind();
};

void change(float *vertD)
{
graphicalAtribute *atributes=TexAtrib();
buff->unbind();
delete buff;
buff=new VertexBuffer(vertD,20*sizeof(float));
arr->addData(*buff,atributes,2);
}

~Pencil1()
{

arr->unbind();
buff->unbind();
ind->unbind();
shader->unbind();
texture->unbind(); 

delete arr;
delete buff;
delete ind;
delete shader;
delete texture;

}

void refresh()
{
  VertexBuffer *buff1=new VertexBuffer(vertexData2F,20*sizeof(float));
  graphicalAtribute atributes[2]=
{
{3,"Vertecies"},
{2,"Texture"}
};
  arr->addData(*buff1,atributes,2);
}

void clear()
{
    renderer.clear();
}

void draw()
{
    renderer.drawType1(*arr,*ind,*shader);
}

private:
Shader *shader;
VertexArray *arr;
VertexBuffer *buff;
IndexBuffer *ind;
Texture *texture;
Renderer renderer;
bool isEmpty;
};


int main()
{
  

Window window("My Window",800,600);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
SDL_Event event;

Pencil1 pen(v2);


/*
std::ifstream fs("graphic_engine/shaders/textureFragShader.shader");
std::ifstream vs("graphic_engine/shaders/textureVertShader.shader");
std::string vertexShader=FileToString(vs);
std::string fragmentShader=FileToString(fs);

graphicalAtribute atributes[2]=
{
{3,"Vertecies"},
{2,"Texture"}
};
Shader MyShader(vertexShader,fragmentShader);
VertexArray arr(5*sizeof(float));
arr.bind();
VertexBuffer vert(vertexData2F,20*sizeof(float));
arr.addData(vert,atributes,2);
IndexBuffer ind(indexData,6);
MyShader.bind();
//MyShader.setUniform4f("color",1.0f,0.0f,0.0f,1.0f);
Texture texture("testTextures/wall2k.jpg",0);
MyShader.setUniform1i("textureSampler",0);
texture.bind();
Renderer renderer;



*/

glClearColor(0.0f,0.3f,0.3f,0.0f);


while(!window.isClosed())
{
  pen.clear();




 

  
    window.pollEvents(event);


  glViewport(0,0,window.getWidth(),window.getHeight());

  pen.draw();


        window.GLswap();
        
    }
return 0;

}
