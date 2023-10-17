#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/buffers/buffers.h"
#include "graphic_engine/colors/color.h"
#include "graphic_engine/geometry/geometry.h"
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
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


struct texMap{
    texMap *next;
    texMap *prev;
    Math::vec2f p1,p2;
};

texMap *newTextureMap(float growth)
{
    texMap *first= new texMap;
    first->p1={0.0f,0.0f};
    first->p2={0.0f,1.0f};

    texMap *k=new texMap;
    k->p1=first->p1+Math::vec2f{growth,0};
    k->p2=first->p2+Math::vec2f{growth,0};

    k->prev=first;
    first->next=k;

    while(k->p1.x+growth<1)
    {
        texMap *z=new texMap;
        z->p1=k->p1+Math::vec2f{growth,0};
        z->p2=k->p2+Math::vec2f{growth,0};

        z->prev=k;
        k->next=z;
        k=k->next;
    }
     texMap *z=new texMap;
      z->p1=Math::vec2f{1.0f,0.0};
      z->p2=Math::vec2f{1.0f,1.0f};

      z->prev=k;
      k->next=z;
      k=k->next;
      k->next=first;
      first->prev=k;

    return first;
}

void rotateTex(int rotations,texMap *map)
{
    for(int i=0;i<rotations;i++)
      map=map->next;
}

texMap *wallMap=newTextureMap(0.00555555555f);
float secureRot=0.0f;
float secureMov=0.0f;


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
 




bool A_isPressed=0,W_isPressed=0,S_isPressed=0,D_isPressed=0;
bool Left_isPressed=0,Right_isPressed=0;
bool Space_isPressed=0;
float oHeight=1024;
float angle=0.1f;
float distance=0.1f;
bool type;
Math::vec2f f1(-distance,0);
Math::vec2f b1(distance,0);
Math::vec2f r1(0,-distance);
Math::vec2f l1(0,+distance);

class Gun
{
public:
Gun(std::string path);
~Gun();

void draw();

private:
std::string image;
float vert[20];
float ind[6];
};

std::ifstream f("dots.txt");

struct Dots
{
float x,y;
bool type;
};

Dots rays[365];

float margin(float x)
{
if(x<0)x-=10.0f;
if(x>0)x+=10.0f;
return x;
}


bool mapMatrix[100]=
{
  1,1,1,1,1,1,1,1,
  1,0,1,1,0,1,0,1,
  1,0,0,0,0,1,0,1,
  1,1,1,0,0,0,0,1,
  1,0,1,1,0,0,0,1,
  1,0,0,0,0,1,0,1,
  1,0,1,0,0,0,0,1,
  1,1,1,1,1,1,1,1
};


int checkSpace(float x,float y)
{
int i=0,j=0,index;
while(i*128.0f<x)i++;
while(j*128.0f<y)j++;
j--;
i--;
index=j*8+i;
return mapMatrix[index];

}

struct Player
{
float x, y, width, height;
Dots pov[361];
float angle[361];
Color color;

}player;

void drawPlayer(Player player, Window &window)
{
  Shape::Rectangle shape(Math::vec2f(player.x,player.y),player.width,player.height);
  shape.setFill(player.color);
  window.drawShape(shape);

}

void KeyDown(SDL_Event &event)
{
if(event.key.keysym.sym==SDLK_a)A_isPressed=1;

if(event.key.keysym.sym==SDLK_w)W_isPressed=1;

if(event.key.keysym.sym==SDLK_s)S_isPressed=1;

if(event.key.keysym.sym==SDLK_d)D_isPressed=1;

if(event.key.keysym.sym==SDLK_LEFT)Left_isPressed=1;

if(event.key.keysym.sym==SDLK_RIGHT)Right_isPressed=1;

if(event.key.keysym.sym==SDLK_SPACE)Space_isPressed=1;

}

void KeyUp(SDL_Event &event)
{
if(event.key.keysym.sym==SDLK_a)A_isPressed=0;

if(event.key.keysym.sym==SDLK_w)W_isPressed=0;

if(event.key.keysym.sym==SDLK_s)S_isPressed=0;

if(event.key.keysym.sym==SDLK_d)D_isPressed=0;

if(event.key.keysym.sym==SDLK_LEFT)Left_isPressed=0;

if(event.key.keysym.sym==SDLK_RIGHT)Right_isPressed=0;

if(event.key.keysym.sym==SDLK_SPACE)Space_isPressed=0;

}

void OnKeyPressed(Player &player)
{

if(A_isPressed)
 if(!checkSpace(player.x+margin(l1.x), player.y+margin(l1.y)))
{
  player.x+=l1.x;
  player.y+=l1.y;
  for(int i=0;i<181;i++)
  {
  player.pov[i].x+=l1.x;
  player.pov[i].y+=l1.y;
  }
  secureMov-=distance;
  if(secureMov<0.0f){
  wallMap=wallMap->prev;
  secureMov=2.599999f;
  }
}

if(D_isPressed)
 if(!checkSpace(player.x+margin(r1.x), player.y+margin(r1.y)))
{
  player.x+=r1.x;
  player.y+=r1.y;
  for(int i=0;i<181;i++)
  {
  player.pov[i].x+=r1.x;
  player.pov[i].y+=r1.y;
  }
  secureMov+=distance;
  if(secureMov>2.6f){
  wallMap=wallMap->next;
  secureMov=0.0001f;
  }
}

if(S_isPressed)
 if(!checkSpace(player.x+margin(b1.x), player.y+margin(b1.y)))
{
   player.x+=b1.x;
  player.y+=b1.y;
  for(int i=0;i<181;i++)
  {
  player.pov[i].x+=b1.x;
  player.pov[i].y+=b1.y;
  }

}

if(W_isPressed)
 if(!checkSpace(player.x+margin(f1.x), player.y+margin(f1.y)))
{
  player.x+=f1.x;
  player.y+=f1.y;
  for(int i=0;i<181;i++)
  {
  player.pov[i].x+=f1.x;
  player.pov[i].y+=f1.y;
  }
}


if(Left_isPressed)
{
  Math::vec2f origin(player.x,player.y);

l1=Math::rotationVec2f(l1, -angle);
r1=Math::rotationVec2f(r1, -angle);
f1=Math::rotationVec2f(f1, -angle);
b1=Math::rotationVec2f(b1, -angle);

for(int i=0;i<181;i++){

Math::vec2f camera(player.pov[i].x,player.pov[i].y);
camera=Math::rotationVec2f(camera-origin, -angle)+origin;
player.angle[i]-=angle;
secureRot-=angle;
if(player.angle[i]<0.0f)player.angle[i]=359.99f;
player.pov[i].x=camera.x;
player.pov[i].y=camera.y;

}
if(secureRot<0.0f){
wallMap=wallMap->prev;
secureRot=89.99999f;
}

}

if(Right_isPressed)
{

    Math::vec2f origin(player.x,player.y);

  l1=Math::rotationVec2f(l1, angle);
  r1=Math::rotationVec2f(r1, angle);
  f1=Math::rotationVec2f(f1, angle);
  b1=Math::rotationVec2f(b1, angle);

for(int i=0;i<181;i++){
Math::vec2f camera(player.pov[i].x,player.pov[i].y);

camera=Math::rotationVec2f(camera-origin, angle)+origin;
secureRot+=angle;
player.angle[i]+=angle;
if(player.angle[i]>360.0f)player.angle[i]=0.01f;
player.pov[i].x=camera.x;
player.pov[i].y=camera.y;
  }
if(secureRot>90.0f){
wallMap=wallMap->next;
secureRot=0.00001f;
}
}


}




Math::vec2f Vray(Player &player, Window &window,float x,float y,float angle1)
{
float x1, y1;
float left=0.0f,right=0.0f;
float left1=0.0f,right1=0.0f;
int alpha=0;

while(right<player.x)
 right+=128.0f;

left=right-128.0f;

while(right1<x)
 right1+=128.0f;

left1=right1-128.0f;



if(angle1>=90 && angle1<=270)
{
alpha=(right1-right)/128.0f;
if(alpha==0)
{
  x1=x;
  y1=y;
}

while(alpha>0)
{
x1=right;
y1=((player.y-y)/(player.x-x))*(x1-player.x)+player.y;
if(checkSpace(x1+128.0f,y1))break;
alpha--;
right+=128.0f;
}
if(alpha==0 && !checkSpace(x,y))

{
  x1=x;
  y1=y;
}


}


if(angle1>270 || angle1<90)
{
alpha=(left-left1)/128.0f;
while(alpha>0)
{
x1=left;
y1=((player.y-y)/(player.x-x))*(x1-player.x)+player.y;
if(checkSpace(x1, y1))break;
alpha--;
left-=128.0f;


}

if(alpha==0)
{
  x1=x;
  y1=y;
}

}

return Math::vec2f(x1,y1);

}

Math::vec2f  Hray(Player &player,Window &window,float x, float y, float angle1)
{
float x1,y1;
int alpha=0;
float down=0.0f,up=0.0f;
float down1=0.0f,up1=0.0f;

while(up<player.y)
up+=128.0f;
  down=up-128.0f;

while(up1<y)
up1+=128.0f;
  down1=up1-128.0f;

if(angle1>=0 && angle1<=180)
{
  alpha=(down-down1)/128.0f;

    if(alpha==0)
  {
    x1=x;
    y1=y;
  }

  while(alpha>0){

    y1=down;
    x1=(y1-player.y)/((player.y-y)/(player.x-x))+player.x;
    if(checkSpace(x1, y1))break;
    alpha--;
    down-=128.0f;
  }
  if(alpha==0 && !checkSpace(x,y))
    {
    x1=x;
    y1=y;
  }



}


if(angle1<360 && angle1>180)
{
  alpha=(up1-up)/128.0f;

  if(alpha==0)
  {
    x1=x;
    y1=y;
  }

  while(alpha>0)
  {
    y1=up;
    x1=(y1-player.y)/((player.y-y)/(player.x-x))+player.x;
    if(checkSpace(x1, y1+128.0f))break;
    alpha--;
    up+=128.0f;


  }

  if(alpha==0 && !checkSpace(x, y))
   {
    x1=x;
    y1=y;
  }



}

return Math::vec2f(x1,y1);





}

Math::vec2f finalRay(Math::vec2f hRay,Math::vec2f vRay,Player &player)
{
bool k1;
bool k2;
if(vRay.x>player.x)
  k1=checkSpace(vRay.x+128.0f, vRay.y);
else k1=checkSpace(vRay.x, vRay.y);

if(hRay.y>player.y)
  k2=checkSpace(hRay.x, hRay.y+128.0f);
else k2=checkSpace(hRay.x, hRay.y);

if(k1==1 && k2==0) {type=0; return vRay;}
if(k1==0 && k2==1) {type=1; return hRay;}

Math::vec2f p(player.x,player.y);
if((Math::magnitudevec2f(hRay-p)>Math::magnitudevec2f(vRay-p)))
{type=0; return vRay;}

{type=1; return hRay;}
}





void drawMap(bool mapMatrix[100],Window &window)
{
float w=1028.0f/8.0f;
float h=1028.0f/8.0f;
float xm=0,ym=-h/2;
Color color;
for(int i=0;i<64;i++)
{
 if(i%8==0)
 {
   xm=w/2;
    ym+=h;
 }

 else
  xm+=w;

Shape::Rectangle shape(Math::vec2f(xm,ym),w,h);
if(mapMatrix[i]==0)
{shape.setFill(black);
 color=white;
}
else{
shape.setFill(white);
color=black;
}

window.drawShape(shape);
}





}

void drawSectors(Window &window)
{
float h=1028.0f;
float w=1028.0f;
float w1=w/8 ,h1=h/8;
for(int i=1;i<8;i++)
{
window.drawline(w1,0,w1,h,red);
w1+=w/8;
}
for(int i=1;i<8;i++)
{
window.drawline(0,h1,w,h1,red);
h1+=h/8;
}


}

void drawPov(Player player , Window &window )
{
for(int i=0;i<181;i++)
window.drawline(player.x, player.y, player.pov[i].x, player.pov[i].y,blue);

}

void drawRay(float x,float y,Player& player, Window &window)
{

window.drawline(player.x,player.y,x,y,orange);
}

void drawWalls(Player &player, Window &window,Renderer renderer,Shader *shader,VertexBuffer &buff, VertexArray &arr, IndexBuffer &ind)
{
texMap *map=wallMap;

float mx=(window.getWidth()/181.0f)/2.0f;
float my=window.getHeight()/2;
float w=window.getWidth()/181.0f;
float h;
float dis;
float angle;
 
 float m=0;
 if(player.x!=rays[90].x)m=(player.y-rays[90].y)/(player.x-rays[90].x);
 

for(int i=0;i<181;i++)
{

if(i<90)
{
  angle=(90.0f-i)/2;
}
if(i>90)
{
  angle=(i-90.0f)/2;
}
if(i==90)angle=0;

angle=Math::degreesToRad(angle);

float px,py;
if(player.x!=rays[90].x){
px=(player.x+m*player.y+m*m*rays[i].x-m*rays[i].y)/(m*m+1);
py=m*(px-rays[i].x)+rays[i].y;
}
else
{
  px=player.x;
  py=rays[i].y;
}
dis=sqrt((rays[i].y-py)*(rays[i].y-py)+(rays[i].x-px)*(rays[i].x-px));


dis*=0.025f;

//dis=0.025f*std::sqrt((player.x-rays[i].x)*(player.x-rays[i].x)+(player.y-rays[i].y)*(player.y-rays[i].y));
//dis=dis*cosf(angle);
if(dis<1)dis=1;

h=window.getHeight()/dis;
/*
Shape2::Rectangle shape(Math::vec2f(mx,my),w,h);
shape.setTexture("testTextures/wall.jpeg");
shape.setRenderMode(TEXTURE_MODE);
shape.setFill(green);
if(rays[i].type)shape.setFill(dark_green);

if(i==90 && Space_isPressed)shape.setFill(orange);
*/


Textured_Rectangle shape(Math::vec2f(mx,my),w,h);
shape.texCoord[0]=map->p1;
shape.texCoord[1]=map->p2;
shape.texCoord[2]=map->next->p1;
shape.texCoord[3]=map->next->p2;
shape.copyToBuffer(buff,window.getWidth(),window.getHeight());
renderer.drawType1(arr, ind, *shader);

mx+=window.getWidth()/181.0f;
map=map->next;
}

}

void drawCrossHair(Window &window, Pencil &pencil)
{
Shape2::Rectangle leftCR(Math::vec2f(window.getWidth()/2,window.getHeight()/2),window.getWidth()/160,
window.getHeight()/40);
Shape2::Rectangle rightCR(Math::vec2f(window.getWidth()/2,window.getHeight()/2),window.getWidth()/40,
window.getHeight()/160);
leftCR.setFill(red);
rightCR.setFill(red);
pencil.draw(leftCR);
pencil.draw(rightCR);
}

void drawCeiling(Window &window, Pencil &pencil)
{
Shape2::Rectangle ceiling(Math::vec2f(window.getWidth()/2,window.getHeight()/4)
,window.getWidth(),window.getHeight()/2);

ceiling.setFill(blue);

pencil.draw(ceiling);
}

void drawFloor(Window &window,Renderer renderer,Shader *shader,VertexArray arr, VertexBuffer buff, IndexBuffer ind )
{

  Textured_Rectangle floor(Math::vec2f(window.getWidth()/2,window.getHeight()/2)
,window.getWidth(),window.getHeight()/2);

//floor.copyToBuffer(buff,window);

/*
Shape2::Rectangle ceiling(Math::vec2f(window.getWidth()/2,window.getHeight()/4*3)
,window.getWidth(),window.getHeight()/2);
ceiling.setTexture("testTextures/rock.avif");
*/


renderer.drawType1(arr, ind, *shader);

}


int main(int argc, char **argv)
{
 



  player.color=yellow;
  player.x=400.0f;
  player.y=300.0f;
  player.width=20.0f;
  player.height=20.0f;

for(int i=0;i<181;i++)
{
 f>>player.pov[i].x>>player.pov[i].y;
}
float ang=360.0f-45.0f;
for(int i=0;i<181;i++)
{
 player.angle[i]=ang;
 ang+=0.5f;
 if(ang==360.0f)ang=0.0f;
}

Window window("My Window",1028,1028);
rotateTex(40,wallMap);

glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
SDL_Event event;
Renderer renderer;

Textured_Rectangle floor(Math::vec2f(window.getWidth()/2,window.getHeight()/4*3)
,window.getWidth(),window.getHeight()/1.1);

Textured_Rectangle gun(Math::vec2f(window.getWidth()/2.5,400.0f),400.0f,400.0f);

Texture textureGun("testTextures/gun.png",0,1);
Texture textureFloor("testTextures/concrete.jpg",0);
Texture textureWall("testTextures/doomwall.jpg",0);

graphicalAtribute *atributes=TexAtrib();
Shader *shader=TexShader();
VertexArray arr((5*sizeof(float)));
arr.bind();
VertexBuffer buff(0,20*sizeof(float));
floor.copyToBuffer(buff, 800,600);
arr.addData(buff,atributes,2);
IndexBuffer ind(indexData,6);
shader->bind();
shader->setUniform1i("textureSampler",0);
textureFloor.bind();



glClearColor(0, 0, 1, 0);

while(!window.isClosed())
{

    renderer.clear();
    glViewport(0,0,window.getWidth(),window.getHeight());




window.pollEvents(event);
if(event.type==SDL_QUIT)window.close();
if(event.type==SDL_KEYDOWN)
 KeyDown(event);




if(event.type==SDL_KEYUP)
  KeyUp(event);



OnKeyPressed(player);

//drawMap(mapMatrix,window);
//drawSectors(window);
//drawPlayer(player,window);



for(int i=0;i<181;i++){
Math::vec2f ray=finalRay(Hray(player,window,player.pov[i].x,player.pov[i].y,player.angle[i])
,Vray(player,window,player.pov[i].x,player.pov[i].y,player.angle[i]),player);
//zdrawRay(ray.x, ray.y, player, window);
rays[i].x=ray.x;
rays[i].y=ray.y;
rays[i].type=type;
}

floor.copyToBuffer(buff, 800,600);
textureFloor.bind();
renderer.drawType1(arr,ind,*shader);


//floorTex.bind();
//drawFloor(window,renderer,shader,arr,buff,ind);

//drawCeiling(window,renderer);
textureWall.bind();
drawWalls(player,window,renderer,shader,buff,arr,ind);
//drawCrossHair(window,renderer);


textureGun.bind();
gun.copyToBuffer(buff,800,600);
renderer.drawType1(arr,ind,*shader);



window.GLswap();
}

  return 0;
}
