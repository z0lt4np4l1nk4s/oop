class MyVector {
protected:
    unsigned int _size, _capacity;
    int* P;
public:
    MyVector();
    MyVector(const MyVector&);
    ~MyVector();

    void pushBack(int);
    void popBack();

    int getCapacity() const;
    int getSize() const;

    bool empty();
    bool full();

    int& at(int pos);
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
