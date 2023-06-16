#include "transformations.h"

namespace Utils {

Math::vec3f convertToGlCoords(Math::vec3f point,float width,float height)
{
float ar=width/height;
point.x=point.x/width;
point.y=point.y/height;
point.x=(2*point.x-1);
point.y=(1-2*point.y);
return {point.x,point.y,point.z};
}

}