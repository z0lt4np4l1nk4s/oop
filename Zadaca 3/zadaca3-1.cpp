#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

struct PositionVector {
    double x, y;

    PositionVector();
    PositionVector(double, double);
    PositionVector(const PositionVector&);

    double norm() const;
    void print() const;
};

PositionVector::PositionVector(): x{0}, y{0} {}

PositionVector::PositionVector(double x, double y): x{x}, y{y} {}

PositionVector::PositionVector(const PositionVector& vector): x{vector.x}, y{vector.y} {}

double PositionVector::norm() const 
{
    return sqrt(x*x + y*y);
}

void PositionVector::print() const
{
    cout << "Koordinate: (" << x << ", " << y << ")" << ", norma: " << norm() << endl;
}

bool cmp(const PositionVector& first, const PositionVector& second)
{
    return first.norm() >= second.norm();
}

int main()
{
    PositionVector polje[5] = 
    {
        PositionVector(1.5, 2.7), 
        PositionVector(3.4, 5.1), 
        PositionVector(2.3, 6.3), 
        PositionVector(5.0, 0.8), 
        PositionVector(0.0, 0.0)
    };
    for(auto x: polje) x.print();
    cout << endl << endl;
    sort(begin(polje), end(polje), cmp);
    for(auto x: polje) x.print();
    return 0;
}