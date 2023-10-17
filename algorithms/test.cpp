#include "algorithms.h"

int main()
{
int v[8]={0,3,1,6,7,9,4,2};

utils::quickSort(0,7, v,1);

for(unsigned int i=0; i<7; i++)
    {
        std::cout<<v[i]<<'\n';
    }

}