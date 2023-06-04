#pragma once
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <ostream>

namespace Shader {

std::string FileToString(const std::ifstream &file);
 unsigned int ShaderCompiler(const std::string &source , unsigned int type );
 unsigned int CreateShader(const std::string &vertexShader ,const std::string &fragmentShader);
 void ShaderInit();
}