#include <iostream>
#include <fstream>

#ifndef  TEMP_H
#define  TEMP_H

#define MAX_CONTAINER_SIZE 100000000000

template <class type>
class Temp
{
public:

Temp(std::string fileName,long size);
Temp(type *elements,long size);
~Temp();

void deleteData();
long getSize();

type& operator[](long index);

private:
long _size;
type *data; 

};

template <class type>
Temp<type>::Temp(std::string fileName,long size)
{

std::ifstream input(fileName);
_size=size;
type element;
data=new type[size];
for(long i=0;i<_size;i++)
{
input>>element;
data[i]=element;
}

}

template <class type>
Temp<type>::Temp(type *elements,long size)
{
_size=size;
data=new type[size];

for(long i=0;i<_size;i++)
    data[i]=elements[i];

}

template <class type>
Temp<type>::~Temp()
{

delete[] data;
data=NULL;

}

template <class type>
void Temp<type>::deleteData()
{

delete[] data;
data=NULL;
_size=0;

}

template <class type>
long Temp<type>::getSize()
{

return _size;

}

template <class type>
type& Temp<type>::operator[](long index)
{
if(index>=_size)
{
    std::cerr<<"[Error]:Index out of bounds\n";
    exit(8);
}
    return data[index];
}


#endif