#include "renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::drawType1(VertexArray &vertexArray,IndexBuffer &indexBuffer,Shader &shader)
{
  shader.bind();
  vertexArray.bind();
  indexBuffer.bind();
  glDrawElements(GL_TRIANGLES,indexBuffer.getCount(),GL_UNSIGNED_INT,nullptr);
}

void Renderer::drawType2(VertexArray &vertexArray, Shader &shader)
{
    
}

void Renderer::clear()
{
  glClear(GL_COLOR_BUFFER_BIT);
}