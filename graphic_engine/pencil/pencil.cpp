#include "pencil.h"
#include "../transformations/transformations.h"

Pencil::Pencil(unsigned int SCREEN_WIDTH, unsigned int SCREEN_HEIGHT)
{
  width=SCREEN_WIDTH;
  height=SCREEN_HEIGHT;
  inUse=0;
  texAtrib=TexAtrib();
  colAtrib=ColAtrib();
  texShader=TexShader();
  colShader=ColShader();
}

Pencil::~Pencil()
{

}

void Pencil::erase(Texture *texture)
{
arr->unbind();
buff->unbind();
ind->unbind();

delete arr;
delete buff;
delete ind;



if(inUse==2){
texShader->unbind();
texture->unbind();

}

inUse=0;
}

void Pencil::clear()
{
    renderer.clear();

}

void Pencil::draw(Shape2::Triangle shape)
{


unsigned int indexData[]={0,1,2};

Math::vec3f coord[3]=
{
utils::convertToGlCoords({shape.coord[0].x,shape.coord[0].y,0.0f}, width, height),
utils::convertToGlCoords({shape.coord[1].x,shape.coord[1].y,0.0f}, width, height),
utils::convertToGlCoords({shape.coord[2].x,shape.coord[2].y,0.0f}, width, height),
};

if(shape.getRenderMode()==COLOR_MODE){
inUse=1;
float data[]
{
   coord[0].x,coord[0].y,1.0f,float(shape.fill[0].x)/255.0f,float(shape.fill[0].y)/255.0f,float(shape.fill[0].z)/255.0f,float(shape.getOpacity())/255.0f,
    coord[1].x,coord[1].y,1.0f,float(shape.fill[1].x)/255.0f,float(shape.fill[1].y)/255.0f,float(shape.fill[1].z)/255.0f,float(shape.getOpacity())/255.0f,
    coord[2].x,coord[2].y,1.0f,float(shape.fill[2].x)/255.0f,float(shape.fill[2].y)/255.0f,float(shape.fill[2].z)/255.0f,float(shape.getOpacity())/255.0f,
};
arr=new VertexArray((7*sizeof(float)));
arr->bind();
buff=new VertexBuffer(data,21*sizeof(float));
arr->addData(*buff,colAtrib,2);
ind=new IndexBuffer(indexData,3);
colShader->bind();
renderer.drawType1(*arr,*ind,*colShader);
}

else{
inUse=2;
float data[]
{
    coord[0].x,coord[0].y,1.0f,shape.texCoords[0].x,shape.texCoords[0].y,
    coord[1].x,coord[1].y,1.0f,shape.texCoords[1].x,shape.texCoords[1].y,
    coord[2].x,coord[2].y,1.0f,shape.texCoords[2].x,shape.texCoords[2].y
};

arr=new VertexArray(5*sizeof(float));
arr->bind();
buff=new VertexBuffer(data,15*sizeof(float));
arr->addData(*buff,texAtrib,2);
ind=new IndexBuffer(indexData,3);
shape.texture->bind();
texShader->bind();
texShader->setUniform1i("textureSampler",0);

renderer.drawType1(*arr,*ind,*texShader);


}

erase(shape.texture);

}

void Pencil::draw(Shape2::Rectangle shape)
{


unsigned int indexData[]={
0,2,1,
2,3,1
};

Math::vec3f coord[4]=
{
utils::convertToGlCoords({shape.coord[0].x,shape.coord[0].y,0.0f}, width, height),
utils::convertToGlCoords({shape.coord[1].x,shape.coord[1].y,0.0f}, width, height),
utils::convertToGlCoords({shape.coord[2].x,shape.coord[2].y,0.0f}, width, height),
utils::convertToGlCoords({shape.coord[3].x,shape.coord[3].y,0.0f}, width, height),
};

if(shape.getRenderMode()==COLOR_MODE){
inUse=1;
float data[]
{
   coord[0].x,coord[0].y,1.0f,float(shape.fill[0].x)/255.0f,float(shape.fill[0].y)/255.0f,float(shape.fill[0].z)/255.0f,float(shape.getOpacity())/255.0f,
    coord[1].x,coord[1].y,1.0f,float(shape.fill[1].x)/255.0f,float(shape.fill[1].y)/255.0f,float(shape.fill[1].z)/255.0f,float(shape.getOpacity())/255.0f,
    coord[2].x,coord[2].y,1.0f,float(shape.fill[2].x)/255.0f,float(shape.fill[2].y)/255.0f,float(shape.fill[2].z)/255.0f,float(shape.getOpacity())/255.0f,
    coord[3].x,coord[3].y,1.0f,float(shape.fill[3].x)/255.0f,float(shape.fill[3].y)/255.0f,float(shape.fill[3].z)/255.0f,float(shape.getOpacity())/255.0f
};
arr=new VertexArray((7*sizeof(float)));
arr->bind();
buff=new VertexBuffer(data,28*sizeof(float));
arr->addData(*buff,colAtrib,2);
ind=new IndexBuffer(indexData,6);
colShader->bind();
renderer.drawType1(*arr,*ind,*colShader);
}

else{
inUse=2;
float data[]
{
    coord[0].x,coord[0].y,1.0f,shape.texCoords[0].x,shape.texCoords[0].y,
    coord[1].x,coord[1].y,1.0f,shape.texCoords[1].x,shape.texCoords[1].y,
    coord[2].x,coord[2].y,1.0f,shape.texCoords[2].x,shape.texCoords[2].y,
    coord[3].x,coord[3].y,1.0f,shape.texCoords[3].x,shape.texCoords[3].y
};

arr=new VertexArray(5*sizeof(float));
arr->bind();
buff=new VertexBuffer(data,20*sizeof(float));
arr->addData(*buff,texAtrib,2);
ind=new IndexBuffer(indexData,6);
shape.texture->bind();
texShader->bind();
texShader->setUniform1i("textureSampler",0);

renderer.drawType1(*arr,*ind,*texShader);

}

erase(shape.texture);
}