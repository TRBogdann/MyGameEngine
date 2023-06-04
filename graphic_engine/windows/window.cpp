#include "window.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <GL/glew.h>
#include <cstdlib>
#include <vector>
#include "../geometry/geometry.h"
#include "../../math_engine/PSBmath.h"
#include "../shaders/Shader.h"

Window::Window(const std::string &title,int width,int height): 
 _title(title), _width(width),_height(height)
{
    _closed=!init();
   
}
Window::~Window()
{   SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}
bool Window::init() 
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
      std::cerr<<"Failed to initialize window.\n";
      return false ;

    }
    _window=SDL_CreateWindow(_title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,_width,_height,SDL_WINDOW_RESIZABLE);//creare fereastra;
    if(_window==nullptr){
    std::cerr<<"Failed to create window.\n";
    return false;
    }
    _renderer=SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED); 
  
    _glcontext=SDL_GL_CreateContext(_window);

    glewInit();


 if(_renderer==nullptr){
    std::cerr<<"Failed to render window.\n";
    return false;
    }




    return true;
}
void Window::pollEvents(SDL_Event &event) 
{
    
    if(SDL_PollEvent(&event))
    {
    switch(event.type)
     {
       case SDL_QUIT:
        _closed=true;
        break;
          
      case SDL_WINDOWEVENT:
        
        switch (event.window.event) {
        
        case SDL_WINDOWEVENT_RESIZED:
            _width=event.window.data1;
            _height=event.window.data2;
        break;
        }
      break;

        default:
        break;

     }
    }
}

void Window::GLswap() const
{
SDL_GL_SwapWindow(_window);
}

void Window::close()
{
_closed=true;
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

void Window::drawPixel(Math::vec2f position, Color color)const
{
  SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, 255);
  SDL_RenderDrawPoint(_renderer, position.x, position.y);
  
}

void Window::drawShape(Shape::Triangle shape) const
{

  SDL_Vertex vert[3];
  vert[0].position.x=shape.ListOfVertices[0].x;
  vert[0].position.y=shape.ListOfVertices[0].y;
  vert[0].color.a=shape.getOpacity();
  vert[0].color.r=shape.getFill().r;
  vert[0].color.g=shape.getFill().g;
  vert[0].color.b=shape.getFill().b;

  vert[1].position.x=shape.ListOfVertices[1].x;
  vert[1].position.y=shape.ListOfVertices[1].y;
  vert[1].color.a=shape.getOpacity();
  vert[1].color.r=shape.getFill().r;
  vert[1].color.g=shape.getFill().g;
  vert[1].color.b=shape.getFill().b;

  vert[2].position.x=shape.ListOfVertices[2].x;
  vert[2].position.y=shape.ListOfVertices[2].y;
  vert[2].color.a=shape.getOpacity();
  vert[2].color.r=shape.getFill().r;
  vert[2].color.g=shape.getFill().g;
  vert[2].color.b=shape.getFill().b;
  
  SDL_RenderGeometry(_renderer,NULL, vert,3, NULL, 0);

 
 
}

void Window::drawShape(Shape::RegularPolygon shape) const
{

  SDL_Vertex vert[3];
  for(int i=0;i<shape.ListOfVertices.size()-1;i++){
  vert[0].position.x=shape.position.x;
  vert[0].position.y=shape.position.y;
  vert[0].color.a=shape.getOpacity();
  vert[0].color.r=shape.getFill().r;
  vert[0].color.g=shape.getFill().g;
  vert[0].color.b=shape.getFill().b;

  vert[1].position.x=shape.ListOfVertices[i].x;
  vert[1].position.y=shape.ListOfVertices[i].y;
  vert[1].color.a=shape.getOpacity();
  vert[1].color.r=shape.getFill().r;
  vert[1].color.g=shape.getFill().g;
  vert[1].color.b=shape.getFill().b;

  vert[2].position.x=shape.ListOfVertices[i+1].x;
  vert[2].position.y=shape.ListOfVertices[i+1].y;
  vert[2].color.a=shape.getOpacity();
  vert[2].color.r=shape.getFill().r;
  vert[2].color.g=shape.getFill().g;
  vert[2].color.b=shape.getFill().b;
  
  SDL_RenderGeometry(_renderer,NULL, vert,3, NULL, 0);

  }
  vert[0].position.x=shape.position.x;
  vert[0].position.y=shape.position.y;
  vert[0].color.a=shape.getOpacity();
  vert[0].color.r=shape.getFill().r;
  vert[0].color.g=shape.getFill().g;
  vert[0].color.b=shape.getFill().b;

  vert[1].position.x=shape.ListOfVertices.front().x;
  vert[1].position.y=shape.ListOfVertices.front().y;
  vert[1].color.a=shape.getOpacity();
  vert[1].color.r=shape.getFill().r;
  vert[1].color.g=shape.getFill().g;
  vert[1].color.b=shape.getFill().b;

  vert[2].position.x=shape.ListOfVertices.back().x;
  vert[2].position.y=shape.ListOfVertices.back().y;
  vert[2].color.a=shape.getOpacity();
  vert[2].color.r=shape.getFill().r;
  vert[2].color.g=shape.getFill().g;
  vert[2].color.b=shape.getFill().b;
  
  SDL_RenderGeometry(_renderer,NULL, vert,3, NULL, 0);
 
}

void Window::drawShape(Shape::Rectangle shape)const
{
   SDL_Vertex vert[3];
  vert[0].position.x=shape.ListOfVertices[0].x;
  vert[0].position.y=shape.ListOfVertices[0].y;
  vert[0].color.a=shape.getOpacity();
  vert[0].color.r=shape.getFill().r;
  vert[0].color.g=shape.getFill().g;
  vert[0].color.b=shape.getFill().b;

  vert[1].position.x=shape.ListOfVertices[1].x;
  vert[1].position.y=shape.ListOfVertices[1].y;
  vert[1].color.a=shape.getOpacity();
  vert[1].color.r=shape.getFill().r;
  vert[1].color.g=shape.getFill().g;
  vert[1].color.b=shape.getFill().b;

  vert[2].position.x=shape.ListOfVertices[2].x;
  vert[2].position.y=shape.ListOfVertices[2].y;
  vert[2].color.a=shape.getOpacity();
  vert[2].color.r=shape.getFill().r;
  vert[2].color.g=shape.getFill().g;
  vert[2].color.b=shape.getFill().b;
  
  SDL_RenderGeometry(_renderer,NULL, vert,3, NULL, 0);
  vert[1].position.x=shape.ListOfVertices[3].x;
  vert[1].position.y=shape.ListOfVertices[3].y;
   SDL_RenderGeometry(_renderer,NULL, vert,3, NULL, 0);
}

void Window::render_object() const {
     SDL_Rect rect;
      rect.w=120;
      rect.h=120;
      rect.x=(_width/2)-(rect.w/2);
      rect.y=(_height/2)-(rect.h/2);
    SDL_SetRenderDrawColor(_renderer, 200, 0, 200, 255);
    SDL_RenderFillRect(_renderer,&rect);
}
void Window::drawline(float a,float b, float x, float y, Color color) const
{ 
                                        
         SDL_SetRenderDrawColor(_renderer, color.r,color.g, color.b, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(_renderer, a, b, x,y );
}

void Window::clear() const  {
   SDL_RenderPresent(_renderer);
   SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255); 
  SDL_RenderClear(_renderer); 

 }

    float Window::getWidth() const
    {
       return _width;
    }

    float Window::getHeight() const
    {
      return _height;
    }

 void delay(int ms)
 {
    SDL_Delay(ms);
 }