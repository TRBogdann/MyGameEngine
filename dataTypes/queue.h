
#include <iostream>
#define MAX_CONTAINER_SIZE 100000000000

#ifndef QUEUE_H
#define QUEUE_H

template <class type>
class Queue
{
public:
Queue(unsigned long  maxSize);
~Queue();
bool is_empty();
bool is_full();
unsigned long getCapacity();
unsigned long getSize();
unsigned int resize(unsigned long newCapacity);
void push(type element);
type pop();
type& operator[](long index);
private:
unsigned long size;
unsigned long capacity;
type *data;
};

template <class type>
Queue<type>::Queue(unsigned long maxSize):
capacity(maxSize)
{
if(maxSize<MAX_CONTAINER_SIZE)
{
size=0;
data=new type[capacity];
}

else 
{
    std::cerr<<"\n[ERROR]:maxSize exeeds the maximum size allowed\n";
    exit(1);
}
};

template <class type>
Queue<type>::~Queue()
{
    if(data!=NULL)
    {
        delete[] data;
        data=NULL;
    }
};

template <class type>
void Queue<type>::push(type element)
{
if(data==NULL)
{
  std::cerr<<"\n[ERROR]: Push into nullptr\n";
  exit(3);
}
if(size>=capacity)
{
  std::cerr<<"\n[ERROR]:Container Overflow.Container's size exeeds its capacity\n";
  exit(2);
}

data[size++]=element;

}

template <class type>
type Queue<type>::pop()
{
  if(data==NULL)
{
  std::cerr<<"\n[ERROR]: Pop() nullptr\n";
  exit(4);
}  

if(size==0)
{
    std::cerr<<"\n Trying to use pop() on empty container";
    exit(5);
}

type element=data[0];

for(long i=0;i<size-1;i++)
{
    data[i]=data[i+1];
}

data[(size--)-1]=0;

return element;

}

template <class type>
bool Queue<type>::is_empty()
{
    return size==0;
}

template <class type>
bool Queue<type>::is_full()
{
    return size==capacity;
}

template <class type>
unsigned int Queue<type>::resize(unsigned long newCapacity)
{
if(newCapacity==0 || newCapacity>MAX_CONTAINER_SIZE)
{
 std::cerr<<"\nInvalid size: Container was not resized.\n";
 return 7;
}

capacity=newCapacity;

if(size>capacity)
{
    size=capacity;
}

type *temp=new type[capacity];

for(long i=0;i<size;i++)
{
    temp[i]=data[i];
}

delete data;
data=new type[capacity];

type *temp2=data;
data=temp;
delete[] temp2;

temp2=NULL;
temp=NULL;

return 0;

}

template <class type>
type& Queue<type>::operator[](long index)
{
if(index>=size)
{
    std::cerr<<"[Error]:Index out of bounds\n";
    exit(8);
}
    return data[index];
}

template <class type>
unsigned long Queue<type>::getCapacity()
{
    return capacity;
}

template <class type>
unsigned long Queue<type>::getSize()
{
    return size;
}


#endif