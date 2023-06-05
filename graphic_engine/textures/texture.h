#pragma once
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <string>

class Texture 
{

public:
    Texture(const std::string filename,bool keepLocalData);  
    ~Texture();

    void bind(unsigned int slot=0);
    void unbind();

    int getWidth();
    int getHeight();
    int getDensity();

private:
    unsigned int rendererId;
    std::string filePath;
    void *pixelBuffer;
    int width;
    int height;
    int density;
};