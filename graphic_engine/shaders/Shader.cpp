#include "GL/glew.h"
#include "Shader.h"
#include <iostream>
#include <sstream>
//III(B)  VERTEX SHADER && FRAGMENT SHADER
namespace Shader {

 std::string FileToString(const std::ifstream &file)
{ 
  std::stringstream buffer;

  buffer << file.rdbuf();

  std::string str = buffer.str();

  return str;
  
}


 unsigned int ShaderCompiler(const std::string &source , unsigned int type )
{
   unsigned int id =glCreateShader(type);
   const char* src=source.c_str();
   glShaderSource(id,1,&src,nullptr);
   glCompileShader(id);


    //Verificare erori
  int status;
  glGetShaderiv(id,GL_COMPILE_STATUS,&status);
    if(status == GL_FALSE)
    {
    
        int message_lenght;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH, &message_lenght);
        char* message = (char*)alloca(message_lenght * sizeof(char)); 
        std::cout<<"Failed to compile shader"<<'\n'; 
        std::cout<<message<<'\n';
        std::cout<<source;
        glDeleteShader(id);
        
        return 0;
    }


   return id;
}

 unsigned int CreateShader(const std::string &vertexShader ,const std::string &fragmentShader)
{
 unsigned int program=glCreateProgram();
 unsigned int vshader= ShaderCompiler(vertexShader, GL_VERTEX_SHADER);
 unsigned int fshader= ShaderCompiler(fragmentShader, GL_FRAGMENT_SHADER);

//Salvarea si Conectarea shaderlor
 glAttachShader(program,vshader);
 glAttachShader(program,fshader);
 glLinkProgram(program);
 glValidateProgram(program);



   //Stergere sau detasare shadere originale

/* 1. Pt debugging
      glDetachShader(vshader);
      glDetachShader(fshader);
*/

// 2.

 glDeleteShader(vshader);
 glDeleteShader(fshader);

 return program;
}

void ShaderInit()
{
std::ifstream fs("graphic_engine/shaders/fragmentShader.shader");
std::ifstream vs("graphic_engine/shaders/vertexShader.shader");
std::string vertexShader=Shader::FileToString(vs);
std::string fragmentShader=Shader::FileToString(fs);
unsigned int shader=Shader::CreateShader(vertexShader, fragmentShader);
glUseProgram(shader);
}

}