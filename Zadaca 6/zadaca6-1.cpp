#include <iostream>

using namespace std;

class MyVector {
protected:
    unsigned int _size, _capacity;
    int* P;
public:
    MyVector();
    MyVector(const MyVector&);
    ~MyVector();

    void pushBack(int);
    int popBack();

    unsigned int getCapacity() const;
    unsigned int getSize() const;

    void print();
    bool empty() const;
    bool full();

    int& at(unsigned int pos);
    int& front();
    int& back();

    //operator pridruživanja
    MyVector& operator=(const MyVector&);

    /*
    Povećaj element na itom mjestu za vrijednost 
    koja se nalazi na itom mjestu vektora
    prosljeđenog po referenci
    */
    MyVector& operator+=(const MyVector&);

    //zbroj vektora
    MyVector operator+(const MyVector&) const;

    //skalarni produkt vektora
    int operator*(const MyVector&) const;

    //provjera jesu li dva vektora jednaki po elementima
    bool operator==(const MyVector&) const;

    //provjera jesu li dva vektora različiti po elementima
    bool operator!=(const MyVector&) const;

    //operatori dohvaćanja
    const int& operator[](int) const;
    int& operator[](int);

    int* begin() const;
    int* end() const;
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
    P = new int[_capacity]{};
    for(int i = 0; i < _size; i++) P[i] = vector.P[i];
}

MyVector::~MyVector()
{
    delete [] P;
}

void MyVector::pushBack(int x)
{
    if(full())
    {
        if(_capacity == 0) _capacity = 1;
        else _capacity *= 2;
        int* newP = new int[_capacity]{};
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
            int* newP = new int[_size]{};
            for(int i = 0; i < _size; i++) newP[i] = P[i];
            //Program zapne na ovom dijelu ako ovo nije iskomentirano
            //delete [] P;
            P = newP;
        }
    }
    else _capacity = 0;
    return val;
}

unsigned int MyVector::getSize() const
{
    return _size;
}

unsigned int MyVector::getCapacity() const 
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

bool MyVector::empty() const
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

int* MyVector::begin() const
{
    if(empty()) return nullptr;
    return P;
}

int* MyVector::end() const
{
    if(empty()) return nullptr;
    return P + _size;
}

MyVector& MyVector::operator=(const MyVector& vector)
{
    _size = vector._size;
    _capacity = vector._capacity;
    delete [] P;
    P = new int[_capacity]{};
    for(int i = 0; i < _size; i++) P[i] = vector.P[i];
    return *this;
}

// /*
// Povećaj element na itom mjestu za vrijednost 
// koja se nalazi na itom mjestu vektora
// prosljeđenog po referenci
// */
MyVector& MyVector::operator+=(const MyVector& vector)
{
    if(_size == 0) return *this;
    for(int i = 0; i < vector._size; i++) 
    {
        if(i < _size) P[i] += vector.P[i];
        else pushBack(vector.P[i]);
    }
    return *this;
}

//zbroj vektora
MyVector MyVector::operator+(const MyVector& vector) const
{
    MyVector result{};
    for(int i = 0; i < max(_size, vector._size); i++)
    {
        int res = 0;
        res += i >= _size ? 0 : P[i];
        res += i >= vector._size ? 0 : vector.P[i];
        result.pushBack(res);
    }
    return result;
}

//skalarni produkt vektora
int MyVector::operator*(const MyVector& vector) const
{
    int res = 0;
    for(int i = 0; i < min(_size, vector._size); i++) res += P[i] * vector.P[i];
    return res;
}

//provjera jesu li dva vektora jednaki po elementima
bool MyVector::operator==(const MyVector& vector) const
{
    if(_size != vector._size) return false;
    for(int i = 0; i < _size; i++) if(P[i] != vector[i]) return false;
    return true;
}

//provjera jesu li dva vektora različiti po elementima
bool MyVector::operator!=(const MyVector& vector) const
{
    return !(*this == vector);
}

//operatori dohvaćanja
const int& MyVector::operator[](int index) const
{
    if(index < 0 || index >= _size) throw out_of_range("const int& MyVector::operator[](int index) - index out of range");
    return P[index];
}

int& MyVector::operator[](int index)
{
    if(index < 0 || index >= _size) throw out_of_range("const int& MyVector::operator[](int index) - index out of range");
    return P[index];
}

int main()
{
    MyVector A, B;
    for(int i = 1; i <= 10; i++) A.pushBack(i);
    for(int i = 1; i <= 4; i++) B.pushBack(i);
    B += A;
    B.print();
    MyVector C = A + B;
    C.print();
    cout << C[3] << endl;
    MyVector D;
    D = A;
    cout << "Skalarni produkt vektora D i C: " << (D * C) << endl;
    cout << "Jesu li vektori D i A isti? " << (D == A) << endl;
    cout << "Jesu li vektori D i A razliciti? " << (D != A) << endl;
    cout << endl << "Vektor D:" << endl;
    for(int i = 0; i < D.getSize(); i++) cout << D[i] << " ";
    cout << endl;
    return 0;
}