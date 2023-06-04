#include "stack.h"


int main()
{
Stack<int> stack(20);
for(long i=0;i<20;i++)
{
    stack.push(i);
}
std::cout<<stack.getSize()<<" ";
for(int i=0;i<20;i++)
{    
    std::cout<<stack.pop()<<"\n";
}

return 0;
}