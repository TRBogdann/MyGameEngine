#include "buffers.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void *data, unsigned int byteSize)
{


    glGenBuffers(1,&rendererId);  
    glBindBuffer(GL_ARRAY_BUFFER,rendererId);
    glBufferData(GL_ARRAY_BUFFER,byteSize,data,GL_DYNAMIC_DRAW); 

}

VertexBuffer::VertexBuffer(std::string fileName, unsigned int byteSize)
{

}

void VertexBuffer::update(const void *data,unsigned int byteSize,unsigned int offset)
{
    glBindBuffer(GL_ARRAY_BUFFER,rendererId);
    glBufferSubData(GL_ARRAY_BUFFER,offset,byteSize,data);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&rendererId );
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER,rendererId);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}




IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int elementCount)
{
    
    glGenBuffers(2,&rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rendererId); //buffer ul ales va fi utilizat 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,elementCount*sizeof(unsigned int),data,GL_STATIC_DRAW);
    count=elementCount;
    
}

/*
IndexBuffer::IndexBuffer(std::string fileName, unsigned int elementCount)
{

}
*/

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(2,&rendererId );
}

void IndexBuffer::bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rendererId);
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

unsigned int IndexBuffer::getCount()
{
    return count;
}


VertexArray::VertexArray(unsigned int dataBlockByteSize):
dataSize(dataBlockByteSize)
{

   glGenVertexArrays(1,&rendererId);

}

void VertexArray::bind()
{
    glBindVertexArray(rendererId);
}


void VertexArray::unbind()
{
    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{

 glDeleteVertexArrays(1,&rendererId);

}

void VertexArray::addData(VertexBuffer &buffer, graphicalAtribute *atributes, unsigned int atribCount)
{
    buffer.bind();
    unsigned int offset=0;
    for(int i=0;i<atribCount;i++)
    {  
       glEnableVertexAttribArray(i);
       glVertexAttribPointer(i,atributes[i].size,GL_FLOAT,GL_FALSE,dataSize,(GLvoid*)(offset*sizeof(float))); 
       offset+=atributes[i].size;
    }
}

graphicalAtribute* ColAtrib()
{
graphicalAtribute *atrib=new graphicalAtribute[2];

atrib[0].name="Vertecies";
atrib[0].size=3;

atrib[1].name="Color";
atrib[1].size=4;

return atrib;

};

graphicalAtribute* TexAtrib()
{
    
graphicalAtribute *atrib=new graphicalAtribute[2];

atrib[0].name="Vertecies";
atrib[0].size=3;

atrib[1].name="Tex";
atrib[1].size=2;

return atrib;

};