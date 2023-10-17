#pragma once
#include <iostream>

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

namespace utils {

namespace  {


template <class type> 
unsigned int pivot(unsigned int left , unsigned int right, type *array,int order)
{
    int dl=0;
    int dr=-1;
    type aux;
    if(order==-1)order=0;

    while(left<right)
    {
        if(array[left]>array[right]==order)
        {
            aux=array[left];
            array[left]=array[right];
            array[right]=aux;
            dl=-dr;
            dr=dl-1;
        }
        left+=dl;
        right+=dr;
    }

    return left;
    
}


template <class type>
void mergeFunc(int left1, int right1, int left2, int right2 , type *array, int order)
{

unsigned int k=0;
unsigned int len1=right1-left1+1;
unsigned int len2=right2-left2+1;

if(order==-1)order=0;

type *aux=new type[len1+len2];

unsigned int i=left1;
unsigned int j=left2;

while(i<=right1 && j<=right2)
{
    if(array[i]>array[j]==order)
         aux[k++]=array[j++];
    
    else 
        aux[k++]=array[i++];
        
}


while(i<=right1)
    aux[k++]=array[i++];

while(j<=right2)
    aux[k++]=array[j++];


for(i=0;i<k;i++)
{
   array[left1+i]=aux[i];
}

delete[] aux;

}
}

//left-fist element in subarray , right-last element in subarray , order -1 for descending 1 for ascending
template <class type>
void quickSort(unsigned int left , unsigned int right , type *array,int order) 
{
    
    if(left<right)
    {
        unsigned int middle=pivot(left,right,array,order);
        quickSort(left,middle,array,order);
        quickSort(middle+1,right,array,order);
    }
}




//left-fist element in subarray , right-last element in subarray , order -1 for descending 1 for ascending
template <class type>
void mergeSort(unsigned int left , unsigned int right, type *array, int order)
{

if(left<right){

unsigned int middle=(left+right)/2;
mergeSort(left,middle,array,order);
mergeSort(middle+1,right,array,order);
mergeFunc(left,middle,middle+1,right,array,order);

}

}

}





#endif