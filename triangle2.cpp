#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/buffers/buffers.h"
#include "graphic_engine/geometry/geometry2.h"
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
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>



graphicalAtribute *atrib=TexAtrib();


    unsigned int indexData[6]=
{
0,2,1,
2,3,1
};

class Textured_Rectangle
{
    public:
    Math::vec2f coord[4];
    Math::vec2f texCoord[4];
    Math::vec2f origin;
    Math::vec2f position;
  
    Textured_Rectangle(Math::vec2f _position,float width, float height):
    position(_position),origin(_position)
    {


        
    coord[0]=position+Math::vec2f({-width/2.0f,height/2.0f});
    coord[1]=position+Math::vec2f({-width/2.0f,-height/2.0f});
    coord[2]=position+Math::vec2f({width/2.0f,height/2.0f});
    coord[3]=position+Math::vec2f({width/2.0f,-height/2.0f});

    texCoord[0]={0.0f,0.0f};
    texCoord[2]={1.0f,0.0f};
    texCoord[1]={0.0f,1.0f};
    texCoord[3]={1.0f, 1.0f};

/*
    Math::vec3f normal[4] = {
        utils::convertToGlCoords({coord[0].x, coord[0].y, 0.0f},
                                 window.getWidth(), window.getHeight()),
        utils::convertToGlCoords({coord[1].x, coord[1].y, 0.0f},
                                 window.getWidth(), window.getHeight()),
        utils::convertToGlCoords({coord[2].x, coord[2].y, 0.0f},
                                 window.getWidth(), window.getHeight()),
        utils::convertToGlCoords({coord[3].x, coord[3].y, 0.0f},
                                 window.getWidth(), window.getHeight()),
    };

float data[]
{
    normal[0].x,normal[0].y,1.0f,texCoord[0].x,texCoord[0].y,
    normal[1].x,normal[1].y,1.0f,texCoord[1].x,texCoord[1].y,
    normal[2].x,normal[2].y,1.0f,texCoord[2].x,texCoord[2].y,
    normal[3].x,normal[3].y,1.0f,texCoord[3].x,texCoord[3].y
};
*/



    };

  void copyToBuffer(VertexBuffer &buff,float width,float height)
{
  
    Math::vec3f normal[4] = {
        utils::convertToGlCoords({coord[0].x, coord[0].y, 0.0f},
                                 width, height),
        utils::convertToGlCoords({coord[1].x, coord[1].y, 0.0f},
                                 width, height),
        utils::convertToGlCoords({coord[2].x, coord[2].y, 0.0f},
                                 width, height),
        utils::convertToGlCoords({coord[3].x, coord[3].y, 0.0f},
                                 width, height),
    };

float data[]
{
    normal[0].x,normal[0].y,1.0f,texCoord[0].x,texCoord[0].y,
    normal[1].x,normal[1].y,1.0f,texCoord[1].x,texCoord[1].y,
    normal[2].x,normal[2].y,1.0f,texCoord[2].x,texCoord[2].y,
    normal[3].x,normal[3].y,1.0f,texCoord[3].x,texCoord[3].y
};

buff.update(data,20*sizeof(float));
};

/*
void draw(Renderer &renderer,Shader *shader)
{


}
*/


    private:

   

};
 




int main()
{

Window window("My Window",800,600);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
SDL_Event event;
Renderer renderer;

Textured_Rectangle shape(Math::vec2f(400.0f,400.0f),200.0f,200.0f);

Texture texture("testTextures/wall.jpeg",0);
graphicalAtribute *atributes=TexAtrib();
Shader *shader=TexShader();
VertexArray arr((5*sizeof(float)));
arr.bind();
VertexBuffer buff(0,20*sizeof(float));
shape.copyToBuffer(buff, 800,600);
arr.addData(buff,atributes,2);
IndexBuffer ind(indexData,6);
shader->bind();
shader->setUniform1i("textureSampler",0);
texture.bind();

Textured_Rectangle shape2(Math::vec2f(200.0f,200.0f),200.0f,200.0f);


glClearColor(0.0f,0.3f,0.3f,0.0f);





while(!window.isClosed())
{
 
    renderer.clear();

    glViewport(0,0,window.getWidth(),window.getHeight());
    window.pollEvents(event);

    
    shape.copyToBuffer(buff,800,600);
    renderer.drawType1(arr,ind,*shader);
    shape2.copyToBuffer(buff,800,600);
    
    renderer.drawType1(arr,ind,*shader);
    
    window.GLswap();

    }


    return 0;
}