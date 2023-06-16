#include "dictionary.h"
#include "queue.h"
#include <string>

float f( int id )
{
return float(id)/10.0f;
}

int main()
{
Dictionary<int,float> map(4);
Queue<int>q(2);
for(unsigned int i=0;i<4;i++)
{
    map.createKey(i,0.0f);
}
map.applyHashFunction(f);
map[3]=1;
map.resize(5);
map.createKey(5,0.5f);
std::cout<<map[3];

return 0;
}