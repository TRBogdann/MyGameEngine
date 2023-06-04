
#include <GL/glew.h>
#include <iostream>

/*
clasa atribut
id 
nr elemente
marime data
*/

struct graphicalAtribute
{

unsigned int size;
std::string name;

};

class VertexBuffer
{
public:

VertexBuffer(const void* data, unsigned int byteSize);
VertexBuffer(std::string filename, unsigned int byteSize);
~VertexBuffer();

void bind();
void unbind();

private:

unsigned int rendererId;

};

class IndexBuffer
{
public:

IndexBuffer(const unsigned int* data, unsigned int elementCount);
IndexBuffer(std::string filename, unsigned int size);
~IndexBuffer();

void bind();
void unbind();

unsigned int getCount();

private:

unsigned int rendererId;
unsigned int count;

};

class VertexArray
{

public:

VertexArray(unsigned int dataBlockByteSize);
~VertexArray();

void addData(VertexBuffer &buffer, graphicalAtribute *atributes, unsigned int atribCount);

void bind();
void unbind();

private:

unsigned int dataSize;
unsigned int rendererId;
};


