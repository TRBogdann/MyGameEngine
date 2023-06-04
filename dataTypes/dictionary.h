
template <class IDtype,class DataType>
class Dictionary
{
public:
Dictionary();
~Dictionary();
DataType &operator[](IDtype iD);
void deleteKey(IDtype iD);
void createKey(IDtype iD, DataType element);
void applyHashFunction(void *(funct)(IDtype target));
private:
IDtype id;
DataType *data;
};




