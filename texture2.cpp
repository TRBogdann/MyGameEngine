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

float a=600.0f/800.0f;
float d1=0.01f;
float d2=1000.0f;
float angle=90.0f;

struct order
{
int index;
float dist;
};
order dis[6]
{
{0,0.0f},
{1,0.0f},
{2,0.0f},
{3,0.0f},
{4,0.0f},
{5,0.0f}
};

Math::vec3f globalOrigin{500,500,1100};

Math::vec3f normal(Math::vec3f v[5])
{
  Math::vec3f line1=v[0]-v[1];
  Math::vec3f line2=v[0]-v[3];
  Math::vec3f normal=Math::VectorCrossProduct3D(line1, line2);
  return normal;
}

Math::vec3f convertToGlCoords(Math::vec3f point,float width,float height)
{
float ar=width/height;
point.x=point.x/width;
point.y=point.y/height;
point.x=(2*point.x-1);
point.y=(1-2*point.y);
return {point.x,point.y,point.z};
}

Math::vec3f Origin(Math::vec3f v[5])
{
float x=0,y=0,z=0;

for(int i=0;i<4;i++)
{
x+=v[i].x/4.0f;
y+=v[i].y/4.0f;
z+=v[i].z/4.0f;
}
Math::vec3f origin(x,y,z);
return origin;
}

void updateDis(float d0, float d1, float d2, float d3, float d4 , float d5)
{
dis[0].dist=d0;
dis[0].index=0;

dis[1].dist=d1;
dis[1].index=1;

dis[2].dist=d2;
dis[2].index=2;

dis[3].dist=d3;
dis[3].index=3;

dis[4].dist=d4;
dis[4].index=4;

dis[5].dist=d5;
dis[5].index=5;
}

void sortDis()
{
for(unsigned int i=0;i<5;i++)
for(unsigned int j=i+1;j<6;j++)
{
  if(dis[i].dist<dis[j].dist)
  {
    std::swap(dis[i],dis[j]);
  }
}
}

void dist(Math::vec3f v[5])
{
Math::vec3f origin=Origin(v);
v[4].x=origin.x*origin.x+origin.y+origin.y+origin.z*origin.z;
}

void rotate(float alpha, Math::vec3f v[5])
{
 Math::vec3f point;
 Math::vec3f origin=Origin(v);
 
 for(int i=0;i<4;i++)
 { 
  v[i] = Math::rotationVec3f(v[i]-globalOrigin,{0,1,0}, alpha)+globalOrigin;
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

void addData(float *vect, Math::vec3f v[5], float width, float height)
{
  for(int i=0;i<4;i++){
      Math::Matrix  mat=Math::ogProjection3f(v[i]/800.0f, angle, d1, d2, a);
      vect[5*i]=convertToGlCoords({mat.mData[0]*800.0f,mat.mData[1]*800.0f,0},width, height).x;
      vect[5*i+1]=convertToGlCoords({mat.mData[0]*800.0f,mat.mData[1]*800.0f,0},width, height).y;
  }

}

void draw(Math::vec3f face[5],float *vect,float width, float height,graphicalAtribute *atributes)
{
VertexArray arr2(5*sizeof(float));
VertexBuffer v2(vect,20*sizeof(float));
arr2.addData(v2,atributes,2);
addData(vect,face,width,height);

}

int main()
{
  

Window window("My Window",800,600);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
SDL_Event event;
//0A.VERTEX DATA (opengl foloseste coordonate normalizate)



Math::vec2f v[4]=
{
{0,600}, //3
{600,600}, //4
{0,0}, //2
{600,0} //1
};

Math::vec3f front[5]
{
{200,800,800}, //3 
{800,800,800}, //4 
{200,200,800}, //2 
{800,200,800}, //1 
{0,0,0}
};

Math::vec3f back[5]
{
{200,800,1400}, //3 
{800,800,1400}, //4 
{200,200,1400}, //2 
{800,200,1400}, //1 
{0,0,0}
};

Math::vec3f up[5]
{
{200,200,800}, //3
{800,200,800}, //4
{200,200,1400}, //2
{800,200,1400}, //1
{0,0,0 }
};

Math::vec3f down[5]
{
{200,800,800}, //3
{800,800,800}, //4
{200,800,1400}, //2
{800,800,1400}, //1
{0,0,0 }
};
Math::vec3f left[5]
{
{200,800,1400}, //3 
{200,800,800}, //4 
{200,200,1400}, //2 
{200,200,800}, //1 
{0,0,0}
};

Math::vec3f right[5]
{
{800,800,800}, //3 
{800,800,1400}, //4 
{800,200,800}, //2 
{800,200,1400}, //1 
{0,0,0}
};

float vertexData2F[]=
{
-0.5f, -0.5f,  1.0f,0.0f, 0.0f, 
 0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 
-0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 
 0.5f,  0.5f,  1.0f, 1.0f, 1.0f 

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

addData(vertexData2F,front, window.getWidth(), window.getHeight());

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







glClearColor(0.0f,0.3f,0.3f,0.0f);

while(!window.isClosed())
{
    renderer.clear();

    dist(front);
    dist(back);
    dist(left);
    dist(right);
    dist(up);
    dist(down);
    updateDis(front[4].x,back[4].x,left[4].x,right[4].x,up[4].x,down[4].x);
    sortDis();
 


 
        if(normal(front)*front[1]<0.0f){
     VertexArray arr2(5*sizeof(float));
       VertexBuffer v2(vertexData2F,20*sizeof(float));
      arr2.addData(v2,atributes,2);
      addData(vertexData2F,front,window.getWidth(),window.getHeight());
      renderer.drawType1(arr,ind,MyShader);
        }
        
          if(normal(back)*back[1]<0.0f){
     VertexArray arr2(5*sizeof(float));
       VertexBuffer v2(vertexData2F,20*sizeof(float));
      arr2.addData(v2,atributes,2);
      addData(vertexData2F,back,window.getWidth(),window.getHeight());
      renderer.drawType1(arr,ind,MyShader);
        }

            if(normal(left)*left[1]<0.0f){
     VertexArray arr2(5*sizeof(float));
       VertexBuffer v2(vertexData2F,20*sizeof(float));
      arr2.addData(v2,atributes,2);
      addData(vertexData2F,left,window.getWidth(),window.getHeight());
      renderer.drawType1(arr,ind,MyShader);
        }
        if(normal(right)*right[1]<0.0f){
     VertexArray arr2(5*sizeof(float));
       VertexBuffer v2(vertexData2F,20*sizeof(float));
      arr2.addData(v2,atributes,2);
      addData(vertexData2F,right,window.getWidth(),window.getHeight());
      renderer.drawType1(arr,ind,MyShader);
        }

                if(normal(up)*up[1]<0.0f){
     VertexArray arr2(5*sizeof(float));
       VertexBuffer v2(vertexData2F,20*sizeof(float));
      arr2.addData(v2,atributes,2);
      addData(vertexData2F,up,window.getWidth(),window.getHeight());
      renderer.drawType1(arr,ind,MyShader);
        }
                if(normal(down)*down[1]<0.0f){
     VertexArray arr2(5*sizeof(float));
       VertexBuffer v2(vertexData2F,20*sizeof(float));
      arr2.addData(v2,atributes,2);
      addData(vertexData2F,down,window.getWidth(),window.getHeight());
      renderer.drawType1(arr,ind,MyShader);
        }
  

    window.pollEvents(event);



    
    rotate(0.05f,front);
    rotate(0.05f,back);
    rotate(0.05f,left);
    rotate(0.05f,right);
    rotate(0.05f,up);
    rotate(0.05f,down);
    


  glViewport(0,0,window.getWidth(),window.getHeight());



    
 
    window.GLswap();
   



       
}
return 0;
}