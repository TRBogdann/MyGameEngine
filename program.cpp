#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/colors/color.h"
#include "graphic_engine/geometry/geometry.h"
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


bool A_isPressed=0,W_isPressed=0,S_isPressed=0,D_isPressed=0;
bool Left_isPressed=0,Right_isPressed=0;
bool Space_isPressed=0;
float oHeight=1024;
float angle=0.07f;
float distance=0.3f;
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
if(player.angle[i]<0.0f)player.angle[i]=359.99f;
player.pov[i].x=camera.x;
player.pov[i].y=camera.y;

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

player.angle[i]+=angle;
if(player.angle[i]>360.0f)player.angle[i]=0.01f;
player.pov[i].x=camera.x;
player.pov[i].y=camera.y;
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

void drawWalls(Player &player, Window &window)
{
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
Shape::Rectangle shape(Math::vec2f(mx,my),w,h);

shape.setFill(green);
if(rays[i].type)shape.setFill(dark_green);

if(i==90 && Space_isPressed)shape.setFill(orange);

window.drawShape(shape);
mx+=window.getWidth()/181.0f;
}

}

void drawCrossHair(Window &window)
{
Shape::Rectangle leftCR(Math::vec2f(window.getWidth()/2,window.getHeight()/2),window.getWidth()/160,
window.getHeight()/40);
Shape::Rectangle rightCR(Math::vec2f(window.getWidth()/2,window.getHeight()/2),window.getWidth()/40,
window.getHeight()/160);
leftCR.setFill(red);
rightCR.setFill(red);
window.drawShape(leftCR);
window.drawShape(rightCR);
}

void drawCeiling(Window &window)
{
Shape::Rectangle ceiling(Math::vec2f(window.getWidth()/2,window.getHeight()/4)
,window.getWidth(),window.getHeight()/2);


window.drawShape(ceiling);
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
SDL_Event event;

glClearColor(1, 0, 0, 0);

while(!window.isClosed())
{




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

drawCeiling(window);
drawWalls(player,window);
drawCrossHair(window);





window.GLswap();
window.clear();
}

  return 0;
}
