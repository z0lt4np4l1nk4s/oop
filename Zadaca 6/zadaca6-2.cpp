#include <iostream>

using namespace std;

class SquareMatrix {
public:
    /*
     * pokazivač na dimanički alocirano polje duljine M čiji su elementi
     * pokazivači na dinamički alocirana polja duljine M (retci u matrici)
    */
    double** container;
    unsigned int M;

    // inicijaliziraj sve ćelije na 0.0
    SquareMatrix(unsigned int);
    SquareMatrix(const SquareMatrix&);
    ~SquareMatrix();
	
    void print() const; // ispis matrice

    double* operator[](unsigned int);
    const double* operator[](unsigned int) const;

    SquareMatrix& operator=(const SquareMatrix&);
    SquareMatrix& operator+=(const SquareMatrix&);
    SquareMatrix& operator-=(const SquareMatrix&);
    SquareMatrix& operator*=(const SquareMatrix&);

    // postavi sve ćelije na isti skalar
    SquareMatrix& operator=(double);
    //svim ćelijama nadodaj isti skalar
    SquareMatrix& operator+=(double);
    // od svih ćelija oduzmi isti skalar
    SquareMatrix& operator-=(double);
    // svaku ćeliju pomnoži sa skalarom
    SquareMatrix& operator*=(double);
    // svaku ćeliju podijeli sa skalarom
    SquareMatrix& operator/=(double);

    SquareMatrix operator+(const SquareMatrix&) const;
    SquareMatrix operator-(const SquareMatrix&) const;
    SquareMatrix operator*(const SquareMatrix&) const;


    SquareMatrix operator+(double) const;
    SquareMatrix operator-(double) const;
    SquareMatrix operator*(double) const;
    SquareMatrix operator/(double) const;

    bool operator==(const SquareMatrix&) const;
    bool operator!=(const SquareMatrix&) const;
};

SquareMatrix::SquareMatrix(unsigned int m) : M{m}
{
    container = new double*[m];
    for(int i = 0; i < m; i++) container[i] = new double[m]{0.0};
}

SquareMatrix::SquareMatrix(const SquareMatrix& matrix)
{
    M = matrix.M;
    container = new double*[M];
    for(int i = 0; i < M; i++) 
    {
        container[i] = new double[M]{0.0};
        for(int j = 0; j < M; j++) container[i][j] = matrix.container[i][j];
    }
}

SquareMatrix::~SquareMatrix()
{
    for(int i = 0; i < M; i++) delete [] container[i];
    delete [] container;
}

void SquareMatrix::print() const
{
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++) cout << container[i][j] << "\t";
        cout << endl;
    }
}

double* SquareMatrix::operator[](unsigned int index)
{
    if(index < 0 || index >= M) throw out_of_range("double* SquareMatrix::operator[](unsigned int) - index out of range");
    return container[index];
}

const double* SquareMatrix::operator[](unsigned int index) const
{
    if(index < 0 || index >= M) throw out_of_range("const double* SquareMatrix::operator[](unsigned int) - index out of range");
    return container[index];
}

SquareMatrix& SquareMatrix::operator=(const SquareMatrix& matrix)
{
    M = matrix.M;
    for(int i = 0; i < M; i++) delete [] container[i];
    delete [] container;
    container = new double*[M];
    for(int i = 0; i < M; i++) 
    {
        container[i] = new double[M];
        for(int j = 0; j < M; j++) container[i][j] = matrix.container[i][j];
    }
    return *this;
}

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& matrix)
{
    if(M != matrix.M) throw out_of_range("SquareMatrix& SquareMatrix::operator+=(const SquareMatrix&) - two matrices are not the same size");
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++) container[i][j] += matrix.container[i][j];
    }
    return *this;
}

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& matrix)
{
    if(M != matrix.M) throw out_of_range("SquareMatrix& SquareMatrix::operator-=(const SquareMatrix&) - two matrices are not the same size");
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++) container[i][j] -= matrix.container[i][j];
    }
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& matrix)
{
    if(M != matrix.M) throw out_of_range("SquareMatrix& SquareMatrix::operator-=(const SquareMatrix&) - two matrices are not the same size");
    double** temp = new double*[M];
    for(int i = 0; i < M; i++)
    {
        temp[i] = new double[M]{0.0};
        for(int j = 0; j < M; j++)
        {
            for (int k = 0; k < M; k++) temp[i][j] += container[i][k] * matrix.container[k][j];
        }
    }
    for(int i = 0; i < M; i++) 
    {
        for(int j = 0; j < M; j++) container[i][j] = temp[i][j];
        delete [] temp[i];
    }
    delete [] temp;
    return *this;
}

// postavi sve ćelije na isti skalar
SquareMatrix& SquareMatrix::operator=(double x)
{
    for(int i = 0; i < M; i++) for(int j = 0; j < M; j++) container[i][j] = x;
    return *this;
}

//svim ćelijama nadodaj isti skalar
SquareMatrix& SquareMatrix::operator+=(double x)
{
    for(int i = 0; i < M; i++) for(int j = 0; j < M; j++) container[i][j] += x;
    return *this;
}

// od svih ćelija oduzmi isti skalar
SquareMatrix& SquareMatrix::operator-=(double x)
{
    for(int i = 0; i < M; i++) for(int j = 0; j < M; j++) container[i][j] -= x;
    return *this;
}

// svaku ćeliju pomnoži sa skalarom
SquareMatrix& SquareMatrix::operator*=(double x)
{
    for(int i = 0; i < M; i++) for(int j = 0; j < M; j++) container[i][j] *= x;
    return *this;
}

// svaku ćeliju podijeli sa skalarom
SquareMatrix& SquareMatrix::operator/=(double x)
{
    if(x == 0) throw out_of_range("SquareMatrix& SquareMatrix::operator/=(double) - you can't divide with 0");
    for(int i = 0; i < M; i++) for(int j = 0; j < M; j++) container[i][j] /= x;
    return *this;
}

SquareMatrix SquareMatrix::operator+(const SquareMatrix& matrix) const
{
    if(M != matrix.M) throw out_of_range("SquareMatrix SquareMatrix::operator+(const SquareMatrix&) const - two matrices are not the same size");
    SquareMatrix result{M};
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++) result[i][j] = container[i][j] + matrix.container[i][j];
    }
    return result;
}

SquareMatrix SquareMatrix::operator-(const SquareMatrix& matrix) const
{
    if(M != matrix.M) throw out_of_range("SquareMatrix SquareMatrix::operator-(const SquareMatrix&) const - two matrices are not the same size");
    SquareMatrix result{M};
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++) result[i][j] = container[i][j] - matrix.container[i][j];
    }
    return result;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& matrix) const
{
    if(M != matrix.M) throw out_of_range("SquareMatrix SquareMatrix::operator*(const SquareMatrix&) const - two matrices are not the same size");
    SquareMatrix result{M};
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++)
        {
            for (int k = 0; k < M; k++) result.container[i][j] += container[i][k] * matrix.container[k][j];
        }
    }
    return result;
}

int main()
{
    SquareMatrix a{10}, b{10};
    for(int i = 0; i < 10; i++) a[i][i] = i+1;
    b = 1;
    a += b;
    a.print();
    cout << endl;
    SquareMatrix c{10};
    c = a;
    c /= 10;
    c.print();
    return 0;
}