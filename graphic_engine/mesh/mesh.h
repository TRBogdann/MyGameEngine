#pragma once

#include "../shaders/Shader.h"
#include "../textures/texture.h"
#include "../buffers/buffers.h"
#include "../colors/color.h"
#include <string>



namespace Models3D
{
    /*
    class Mesh
    {
        public:

        Mesh();

        Mesh(std::string VertBufferFile,int size, std::string IndexBuffer="",graphicalAtribute *atrib=0);
        Mesh(float *vertexBuffer,int size, std::string IndexBuffer="",graphicalAtribute *atrib=0);
        Mesh(std::string VertBufferFile,int size, float* indexBuffer=0,graphicalAtribute *atrib=0);
        Mesh(float *vertexBuffer,int size, float* indexBuffer=0,graphicalAtribute *atrib=0);

        bool readyToUse();
        
        void rotate(float angle,Math::vec3f axis);
        void translate(float x,float y,float z);
        void scale(float xSCALE, float ySCALE, float zSCALE);
    

        ~Mesh();
        
        
        private:
        Shader *_shader;
        Texture *_texture;
        VertexBuffer *buff;
        IndexBuffer *ind;
        VertexArray *arr;
        Color *colors;
        Texture *texCoords;
        VertexArray *Vertecies;
        graphicalAtribute *atrib;
        bool usable;

    };
*/
        class Quad
    {

        public:
        Quad();
        Quad(Math::vec3f p1,Math::vec3f p2,Math::vec3f p3, Math::vec3f p4);
        ~Quad();

        void changeCoordinates(Math::vec3f p1,Math::vec3f p2,Math::vec3f p3, Math::vec3f p4);
        void changeTextureCoordinates(Math::vec2f p1,Math::vec2f p2,Math::vec2f p3, Math::vec2f p4);
        void addTexture(std::string texture);
        void addUniformColor(Color color);
        void changeVertexColor(Color color, unsigned int index);

        bool readyToUse(); 
        void rotate(float angle,Math::vec3f axis);
        void translate(float x,float y,float z);
        void scale(float xSCALE, float ySCALE, float zSCALE);
        
        private:

        std::string _texture;
        Math::vec3f origin;
        Color colors[4];
        Math::vec3f vertecies[4];
        Math::vec2f texCoord[4];
        bool usable;
        

        
    };

}



