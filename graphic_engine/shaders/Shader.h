#pragma once
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <ostream>
#include <string>

unsigned int ShaderCompiler(const std::string &source , unsigned int type );

class Shader
{

public:

Shader(const std::string &vertexShader ,const std::string &fragmentShader);
~Shader();


void bind();
void unbind();

void setUniform4f(std::string name, float r , float g , float b, float a);
void setUniform1i(std::string name, int slot);
void setUniform1f(std::string name, float slot);


private:

unsigned int findUniform(std::string name);

unsigned int rendererId;
std::string _fragmentShader;
std::string _vertexShader;

};

std::string FileToString(const std::ifstream &file);

