
#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/colors/color.h"
#include "graphic_engine/geometry/geometry.h"
#include "math_engine/PSBmath.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <vector>
#include <fstream>

std::ifstream f("Utah_teapot.txt");





int main(int argc,char **argv)
{
float vertices[20000];
int nOfVertices=0;
double alpha;
while(f>>alpha)
{
  nOfVertices++;
  vertices[nOfVertices-1]=alpha;
}

float a=600.0f/800.0f;
float d1=0.01f;
float d2=1000.0f;
float angle=90.0f;


  SDL_Event event;
  Window window("My Window",800,600);
  while(!window.isClosed())
  {
    window.pollEvents(event);
    for(int i=0;i<nOfVertices;i+=3)
    {
 Math::vec3f p3d1(vertices[i],vertices[i+1],vertices[i+2]);
 p3d1=Math::rotationVec3f(p3d1, Math::vec3f(1,1,0), 0.5f);
 vertices[i]=p3d1.x;
 vertices[i+1]=p3d1.y;
 vertices[i+2]=p3d1.z;

    }
   for(int i=0;i<nOfVertices;i+=9)
   {
  Math::vec3f p3d1(vertices[i],vertices[i+1],vertices[i+2]+10.0f);
  Math::vec3f p3d2(vertices[i+3],vertices[i+4],vertices[i+5]+10.0f);
  Math::vec3f  p3d3(vertices[i+6],vertices[i+7],vertices[i+8]+10.0f);

  Math::vec3f  line1=p3d2-p3d1;
  Math::vec3f  line2=p3d3-p3d1;
  Math::vec3f  normal=Math::VectorCrossProduct3D(line1, line2);

  if(normal*p3d1<0.0f){



    Math::vec2f  p1,p2,p3;

      Math::Matrix  m1=Math::ogProjection3f(p3d1, angle, d1, d2, a);
      Math::Matrix  m2=Math::ogProjection3f(p3d2, angle, d1, d2, a);
      Math::Matrix  m3=Math::ogProjection3f(p3d3, angle, d1, d2, a);


     p1=Math::vec2f (m1.mData[0],m1.mData[1]);
     p2=Math::vec2f (m2.mData[0],m2.mData[1]);
     p3=Math::vec2f (m3.mData[0],m3.mData[1]);


       Math::scalevec2f(p1, 2400.0f, 1800.0f);
       Math::scalevec2f(p2, 2400.0f, 1800.0f);
       Math::scalevec2f(p3, 2400.0f, 1800.0f);


       p1+={window.getWidth()/2,window.getHeight()/2};
       p2+={window.getWidth()/2,window.getHeight()/2};
       p3+={window.getWidth()/2,window.getHeight()/2};

        Shape::Triangle t(p1,p2,p3);
        t.setFill(orange);
       window.drawShape(t);

       window.drawline(p1.x,p1.y,p2.x,p2.y,white);
       window.drawline(p2.x,p2.y,p3.x,p3.y,white);
       window.drawline(p3.x,p3.y,p1.x,p1.y,white);
  }

   }


    window.clear();
  }

  return 0;
}