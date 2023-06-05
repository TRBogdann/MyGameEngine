#pragma once
#include <GL/glew.h>
#include "../buffers/buffers.h"
#include "../shaders/Shader.h"

class Renderer
{

public:
Renderer();
~Renderer();

void drawType1(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader );
void drawType2(VertexArray& vertexArray, Shader& shader );
void clear();

private:

};

