#pragma once
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <string>

class Texture 
{

public:
    Texture(const std::string filename,bool keepLocalData,bool useOpacity=0);  
    ~Texture();

    void bind(unsigned int slot=0);
    void unbind();

    int getWidth();
    int getHeight();
    int getDensity();

    void enableOpacity();
    void disableOpacity();

private:
    unsigned int rendererId;
    std::string filePath;
    void *pixelBuffer;
    int width;
    int height;
    int density;
    bool opacity;
};