#pragma once

#define MAX_CONTAINER_SIZE 100000000000

#include <cstddef>
#include <iostream>

#ifndef DICTIONARY_H
#define DICTIONARY_H

template <class type1,class type2>
class Pair
{
public:

Pair(type1 firstElement, type2 secondElement)
{
first=firstElement;
second=secondElement;
};

Pair()
{

};

~Pair()
{

};

type1 first;
type2 second;

private:

};

template <class IDtype,class DataType>
class Dictionary
{
public:

Dictionary(unsigned long maxSize);
~Dictionary();

DataType &operator[](IDtype iD); //not now
unsigned int resize(unsigned long newCapacity); //not now

bool is_empty();
bool is_full();
bool id_exists(IDtype iD);

void deleteKey(IDtype iD); 
void createKey(IDtype iD, DataType element);

void swap(IDtype iD1,IDtype iD2);

IDtype find(DataType element);
IDtype findLast(DataType element);
IDtype end();
IDtype begin();

unsigned long NrOfOccurrences(DataType element);

unsigned long getCapacity();
unsigned long getSize();

void applyHashFunction(DataType (*funct)(IDtype target)); 
void applyHashFunctionToID(IDtype iD,DataType (*funct)(IDtype target)); 

private:

unsigned int capacity;
unsigned int size;

Pair<IDtype,DataType> *data;
Pair<IDtype,DataType> *garbageValue;

};

template <class IDtype,class DataType> 
Dictionary<IDtype,DataType>::Dictionary(unsigned long maxSize):
capacity(maxSize)
{
if(maxSize<MAX_CONTAINER_SIZE)
{
size=0;
data=new Pair<IDtype,DataType>[capacity];
garbageValue=new Pair<IDtype,DataType>;
}

else 
{
    std::cerr<<"\n[ERROR]:maxSize exeeds the maximum size allowed\n";
    exit(1);
}
};

template <class IDtype,class DataType> 
Dictionary<IDtype,DataType>::~Dictionary()
{
    if(data!=NULL)
    {
        delete[] data;
        data=NULL;
    }

};

template <class IDtype,class DataType> 
void Dictionary<IDtype,DataType>::createKey(IDtype iD, DataType element)
{
    bool k=0;

if(data==NULL)
{
  std::cerr<<"\n[ERROR]: insert()/create() into nullptr\n";
  exit(3);
}
if(size>=capacity)
{
  std::cerr<<"\n[ERROR]:Container Overflow.Container's size exeeds its capacity\n";
  exit(2);
}

    for(unsigned long i=0;i<size;i++)
    {
        if(data[i].first==iD)
        {
         
            k=1;
            data[i].second=element;
            break;
        }
    }

if(!k)
    {   
        data[size++].first=iD;
        data[size-1].second=element;
        
    }


}

template <class IDtype,class DataType> 
void Dictionary<IDtype,DataType>::deleteKey(IDtype iD)
{
    long pos=-1;
     if(size==0)
    {
        std::cerr<<"\n Trying to use delete()/remove() on empty container";
        exit(5);
    }

    for(unsigned long i=0;i<size;i++)
    {
        if(data[i].first==iD)
        {
            pos=i;
            break;
        }
    }

    for(unsigned long i=pos;i<size-1;i++ )
    {
        data[i].first=data[i+1].first;
        data[i].second=data[i+1].second;
    }

    size--;
}

template <class IDtype,class DataType> 
IDtype Dictionary<IDtype,DataType>::begin()
{
    if(size>0)  
        return data[0].first;

    else
    {
        std::cerr<<"[ERROR]: Using .begin() on empty container";
        exit(9);
    }
}

template <class IDtype,class DataType> 
IDtype Dictionary<IDtype,DataType>::end()
{   
    if(size>0)
        return data[size-1].first;
   
    else
    {
         std::cerr<<"[ERROR]: Using .begin() on empty container";
         exit(10);
    };
}


template <class IDtype,class DataType> 
IDtype Dictionary<IDtype,DataType>::find(DataType element)
{
    for(unsigned long i=0;i<size;i++)
    {
        if(data[i].second==element)
            return data[i].first;
    }
    return garbageValue->first;
}

template <class IDtype,class DataType> 
IDtype Dictionary<IDtype,DataType>::findLast(DataType element)
{
 long pos=-1;
    for(unsigned long i=0;i<size;i++)
    {
        if(data[i].second==element)
        pos=i;
            
    }

    if(pos>-1)
        return data[pos].first;

    return garbageValue->first;
}

template <class IDtype,class DataType> 
unsigned long  Dictionary<IDtype,DataType>::NrOfOccurrences(DataType element)
{
 unsigned long count=0;
    for(unsigned long i=0;i<size;i++)
    {
        if(data[i].second==element)
        count++;      
    }

    return count;
}

template <class IDtype,class DataType> 
unsigned long Dictionary<IDtype,DataType>::getCapacity()
{
    return capacity;
}

template <class IDtype,class DataType> 
unsigned long Dictionary<IDtype,DataType>::getSize()
{
    return size;
}

template <class IDtype,class DataType> 
bool Dictionary<IDtype,DataType>::is_empty()
{
    return size==0;
}

template <class IDtype,class DataType> 
bool Dictionary<IDtype,DataType>::is_full()
{
    return size>=capacity;
}

template <class IDtype,class DataType> 
bool Dictionary<IDtype,DataType>::id_exists(IDtype iD)
{
    for(unsigned long i=0 ; i<size ; i++)
    {
        if(data[i].first==iD)return 1;
    }
    return 0;
}

template <class IDtype,class DataType> 
void Dictionary<IDtype,DataType>::swap(IDtype iD1, IDtype iD2)
{
long  pos1=-1,pos2=-1;
Pair<IDtype,DataType> aux;

    for(unsigned long i=0;i<size;i++)
    {
        if(iD1==data[i].first)pos1=i;
        if(iD2==data[i].first)pos2=i;
        if(pos1>=0 && pos2>=0)break;
    }

    if(pos1>=0 && pos2>=0)
    {
        aux.second=data[pos1].second;
        data[pos1].second=data[pos2].second;
        data[pos2].second=data[pos1].second;
    }

}

template <class IDtype,class DataType> 
void Dictionary<IDtype,DataType>::applyHashFunctionToID(IDtype iD, DataType (*funct)(IDtype))
{
    for(unsigned long i=0;i<size;i++)
    {
        if(data[i].first==iD)
        {
            data[i].second=funct(data[i].first);
        }
    }
}

template <class IDtype,class DataType> 
void Dictionary<IDtype,DataType>::applyHashFunction(DataType (*funct)(IDtype))
{
      for(unsigned long i=0;i<size;i++)
    {
            data[i].second=funct(data[i].first);
    }
}

template <class IDtype,class DataType> 
unsigned int  Dictionary<IDtype,DataType>::resize(unsigned long newCapacity)
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

Pair<IDtype,DataType> *temp=new Pair<IDtype,DataType>[capacity];

for(long i=0;i<size;i++)
{
    temp[i].first=data[i].first;
    temp[i].second=data[i].second;
}


delete[] data;
data=new Pair<IDtype,DataType>[capacity];
for(long i=0;i<size;i++)

{   
    data[i].first=temp[i].first;
    data[i].second=temp[i].second;
}

delete[] temp;
temp=NULL;

return 0;

}

template <class IDtype,class DataType> 
DataType& Dictionary<IDtype,DataType>::operator[](IDtype iD)
{
 long pos=-1;
 for(unsigned long i=0; i<size;i++)
 {
    if(data[i].first==iD)
    {
        pos=i;
        break;
    }
 }
 if(pos>=0)return data[pos].second;

 else return garbageValue->second;
}


#endif


