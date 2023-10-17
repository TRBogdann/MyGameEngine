#include "../renderer/renderer.h"
#include "../../dataTypes/dataTypes.h"
#include "../textures/texture.h"
#include "../mesh/mesh.h"
#include "../geometry/geometry2.h"



class Pencil
{
    public:
    Pencil(unsigned int SCREEN_WIDTH,unsigned int SREEN_HEIGHT );
    ~Pencil();

    void update();
    void draw(Shape2::Triangle shape);
    void draw(Shape2::Rectangle shape);
    void clear();

private:

void erase(Texture *texture);

Renderer renderer;
unsigned width,height;
Shader *texShader;
Shader *colShader;
VertexArray *arr;
VertexBuffer *buff;
IndexBuffer *ind;
graphicalAtribute *colAtrib;
graphicalAtribute *texAtrib;
unsigned int inUse=0;
};