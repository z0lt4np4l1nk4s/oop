#include<iostream>

using namespace std;

class MyVector {
private:
    int *P;
    unsigned int _size;
    unsigned int _capacity;
public:
    MyVector();
    MyVector(const MyVector&);
    ~MyVector();

    void pushBack(int);
    int popBack();

    unsigned int getSize() const;
    unsigned int getCapacity() const;

    void print() const;

    bool empty() const;
    bool halved() const;
    bool full() const;

    int& at(unsigned int pos);
    int& front();
    int& back();

    /*
    početak i kraj vektora
    (obratite pažnju što treba vraćati end)
    */
    int* begin() const;
    int* end() const;
};

MyVector::MyVector(): _size{0}, _capacity{0}, P{nullptr} {}

MyVector::MyVector(const MyVector &v) {
    P = new int[v._capacity];
    for (int i=0; i<v._size;i++)
        P[i] = v.P[i];

    _size = v._size;
    _capacity = v._capacity;
}

MyVector::~MyVector() {
    delete []P;
}

unsigned int MyVector::getSize() const {
    return _size;
}

unsigned int MyVector::getCapacity() const {
    return _capacity;
}

void MyVector::print() const {
    cout << "Size: " << _size << "\tCapacity:" << _capacity << "\n";

    if(!empty()){
        for(unsigned int i=0; i<_size;i++)
            cout << P[i] << "\t";
    }

    cout << "\n\n";
}

bool MyVector::empty() const {
    return _size==0;
}

bool MyVector::halved() const {
    return _size == _capacity/2;
}

bool MyVector::full() const {
    return _size == _capacity;
}

int & MyVector::at(unsigned int pos) {
    return P[pos];
}

int & MyVector::front() {
    return at(0);
}

int & MyVector::back() {
    return at(_size-1);
}

void MyVector::pushBack(int val) {
    if(empty()){
        _capacity++;
        P = new int[_capacity];
    }

    if(full()){
        _capacity *=2;
        int* P_new = new int[_capacity];

        for(unsigned int i=0; i<_size; i++)
            P_new[i] = P[i];

        delete[] P;
        P = P_new;
    }

    P[_size++] = val;
}

int MyVector::popBack() {
    if(!empty()){
        int to_return = P[--_size];

        if(halved()){
            _capacity/=2;
            int* P_new = new int[_capacity];

            for(unsigned int i=0; i<_size; i++)
                P_new[i] = P[i];
            delete[] P;
            P = P_new;
        }

        return to_return;
    }
}

int *MyVector::begin() const {
    return P;
}

int *MyVector::end() const {
    return &P[_size];
}

int main()
{

    MyVector *mv = new MyVector();

    for(unsigned int i=1; i<=10; i++)
        mv->pushBack(i);

    mv->print();

    MyVector *mv2 = new MyVector(*mv);

    while(!(*mv2).empty())
        cout << mv2->popBack() << "\t";

    cout << "\n\n";

    mv->print();
    mv2->print();

    for(auto it=mv->begin(); it!=mv->end(); it++)
        cout << *it << " ";

    cout << endl;

    for( auto k : *mv)
        cout << k << " ";

    cout << endl;

    delete mv, mv2;

}