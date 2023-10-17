#include "GL/glew.h"
#include "Shader.h"
#include <iostream>
#include <sstream>



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


 Shader::Shader(const std::string &vertexShader ,const std::string &fragmentShader)
{

 rendererId=glCreateProgram();

_vertexShader=vertexShader;
_fragmentShader=fragmentShader;

 unsigned int vshader= ShaderCompiler(vertexShader, GL_VERTEX_SHADER);
 unsigned int fshader= ShaderCompiler(fragmentShader, GL_FRAGMENT_SHADER);

 glAttachShader(rendererId,vshader);
 glAttachShader(rendererId,fshader);

 glLinkProgram(rendererId);
 glValidateProgram(rendererId);

 glDeleteShader(vshader);
 glDeleteShader(fshader);

};

Shader::~Shader()
{
 
}

void Shader::bind()
{
  glUseProgram(rendererId);
}

void Shader::unbind()
{
  glUseProgram(0);
}

void Shader::setUniform4f(std::string name,float r , float g, float b, float a)
{
    glUniform4f((findUniform(name)),r,g,b,a);
}

void Shader::setUniform1f(std::string name,float slot)
{
    glUniform1f((findUniform(name)),slot);
}

void Shader::setUniform1i(std::string name,int slot)
{
    glUniform1i((findUniform(name)),slot);
}

unsigned int Shader::findUniform(std::string name)
{
   int location = glGetUniformLocation(rendererId,name.c_str());
   if(location==-1)
   {
    std::cerr<<"\n[ERROR]: Invalid uniform location";
   }

   return location;

}

Shader* ColShader()
{

std::string vertexShader=" #version 450 core \n layout(location = 0) in vec4 aPos; \n layout (location = 1) in vec4 aColor; \n out vec4 ourColor; \n void main() \n { \n  gl_Position = aPos; \n ourColor = aColor; \n } ";
std::string fragmentShader=" #version 450 core \n out vec4 FragColor; \n in vec4 ourColor; \n void main() \n { \n FragColor = ourColor; \n } ";

Shader *sh = new Shader(vertexShader,fragmentShader);

return sh;

}

Shader* TexShader()
{
  

std::string vertexShader=" #version 450 core \n layout(location = 0)  in vec4 aPos; \n  layout (location = 1) in vec2 texCoord; \n out vec2 fragTexCoord;\n void main()\n { \n gl_Position = aPos; \n fragTexCoord = texCoord; \n } ";
std::string fragmentShader=" #version 450 core \n uniform sampler2D textureSampler;\n in vec2 fragTexCoord; \n out vec4 FragColor; \n void main() \n { \n FragColor = texture(textureSampler, fragTexCoord); \n } ";

Shader *sh = new Shader(vertexShader,fragmentShader);

return sh;

}


