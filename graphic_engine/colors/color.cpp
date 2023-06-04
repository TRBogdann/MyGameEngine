#include "color.h"

Color::Color(int _r ,int _g ,int _b):r(_r),g(_g),b(_b){};

Color::Color():r(255),g(255),b(255){};

Color::~Color(){};

Color& Color::operator=(const Color &c)
{
r=c.r;
b=c.b;
g=c.g;
return *this;

}





