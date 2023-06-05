#include "texture.h"
#include <cstddef>

Texture::Texture(const std::string filename,bool keepLocalData)
:rendererId(0),filePath(filename),pixelBuffer(nullptr),width(0),height(0),density(0)
{  
    SDL_Surface *surface=IMG_Load(filePath.c_str());
    if(keepLocalData)pixelBuffer=surface->pixels;
   
    glGenTextures(1,&rendererId);
    glBindTexture(GL_TEXTURE_2D,rendererId);
    
    density=surface->format->BitsPerPixel;
    width=surface->w;
    height=surface->h;
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB ,width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,surface->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(surface );

}

Texture::~Texture()
{
    glDeleteTextures(1,&rendererId);
}

void Texture::bind(unsigned int slot)
{   
    glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D,rendererId);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getDensity()
{
    return density;
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}