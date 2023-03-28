#include <iostream>

using namespace std;

class MyVector {
private:
    unsigned int _size, _capacity;
    int* P;

public:
    MyVector();
    MyVector(const MyVector&);
    ~MyVector();

    void pushBack(int);
    int popBack();
    unsigned int getSize();
    unsigned int getCapacity();
    void print();
    bool empty();
    bool full();
    
    int& at(unsigned int pos);
    int& front();
    int& back();

    int* begin();
    int* end();
};

MyVector::MyVector() 
{ 
    _size = 0;
    _capacity = 0;
}

MyVector::MyVector(const MyVector& vector)
{
    _size = vector._size;
    _capacity = vector._capacity;
    P = new int[_capacity];
    for(int i = 0; i < _size; i++) P[i] = vector.P[i];
}

MyVector::~MyVector()
{
    delete [] P;
}

void MyVector::pushBack(int x)
{
    if(_size == _capacity)
    {
        if(_capacity == 0) _capacity = 1;
        else _capacity *= 2;
        int* newP = new int[_capacity];
        for(int i = 0; i < _size; i++) newP[i] = P[i];
        //Program zapne na ovom dijelu ako ovo nije iskomentirano
        //delete [] P;
        P = newP;
    }
    P[_size] = x;
    _size++;
}

int MyVector::popBack()
{
    if(_size == 0) throw out_of_range("MyVector::popBack() - no elements");
    _size--;
    int val = P[_size];
    if(_size != 0)
    {
        if(_size == 1 || _size * 2 == _capacity)
        {
            _capacity = _size;
            int* newP = new int[_size];
            for(int i = 0; i < _size; i++) newP[i] = P[i];
            //Program zapne na ovom dijelu ako ovo nije iskomentirano
            //delete [] P;
            P = newP;
        }
    }
    else _capacity = 0;
    return val;
}

unsigned int MyVector::getSize()
{
    return _size;
}

unsigned int MyVector::getCapacity()
{
    return _capacity;
}
    
void MyVector::print()
{
    cout << endl << "Memory location: " << this << "; Size: " << _size << "; Capacity: " << _capacity << endl;
    if(_size == 0) cout << "No elements...";
    else
    {
        cout << "Front: " << front() << "; Back: " << back() << endl;
        cout << "Elements: " << endl;
        for(int i = 0; i < _size; i++) cout << P[i] << " ";
    }
    cout << endl;
}

bool MyVector::empty()
{
    return _size == 0;
}

bool MyVector::full()
{
    return _capacity == _size;
}
    
int& MyVector::at(unsigned int pos)
{
    if(pos >= _size) throw out_of_range("MyVector::at() - index out of range");
    return P[pos];
}
    
int& MyVector::front()
{
    if(_size == 0) throw out_of_range("MyVector::front() - no elements");
    return P[0];
}

int& MyVector::back()
{
    if(_size == 0) throw out_of_range("MyVector::back() - no elements");
    return P[_size - 1];
}

int* MyVector::begin()
{
    if(empty()) return nullptr;
    return P;
}

int* MyVector::end()
{
    if(empty()) return nullptr;
    return P + _size;
}

int main()
{
    MyVector V;
    for(int i = 1; i <= 10; i++) V.pushBack(i);
    V.print();
    cout << endl << "Range-based for: " << endl;
    for(auto x: V) cout << x << " ";
    cout << endl;
    return 0;
}