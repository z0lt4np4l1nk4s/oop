#include <iostream>

using namespace std;

const double pi = 3.14159265;

//Klasu Point bez tijela sam deklarirao prije, jer u suprotnom se kod ne bi kompajlirao
//Ako je klasa Point prva onda ona ne vidi klasu Circle koju zahtijeva njena funkcija isInsideCircle,
//a ako je klasa Circle iznad onda ona ne vidi klasu Point, koja se u njoj koristi kao atribut
//u koji su spremljene koordinate središta
//Ovako se problem rijesio, a tijelo klase Point je napisano nakon klase Circle
class Point;

class Circle
{
public:
    //Postavio sam varijablu kao pokazivac, jer u suprotnom ona vidi samo 
    //deklaraciju klase Point bez tijela, pa se zbog toga kod ne bi kompajlirao
    Point* S;
    double r;

    Circle(Point&, double);

    ~Circle();

    void print();
    double circleArea();
    double circleCircumference();
    double sectorArea(double);
};

class Point
{
public:
    double x, y;

    Point();

    Point(double, double);

    ~Point();

    //Posto je klasa Circle definirana iznad, zato ovdje kompajler 
    //nema nikakvih problema sa kodom i ne baca error
    bool isInsideCircle(Circle&);
    void print();
};

Point::Point() { x = 0; y = 0; }

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

Point::~Point(){}

void Point::print()
{
    cout << "Point: (" << x << ", " << y << ")" << endl;
}

bool Point::isInsideCircle(Circle& circle)
{
    double a = x - (*circle.S).x;
    double b = y - (*circle.S).y;
    return a * a + b * b <= circle.r * circle.r;
}

Circle::Circle(Point& center, double radius)
{
    this->S = &center;
    this->r = radius;
}

Circle::~Circle() {
    delete S;
}

void Circle::print()
{
    cout << "Center: " << "(" << (*S).x << ", " << (*S).y << "), " << "Radius: " << r << endl;
}

double Circle::circleArea()
{
    return r * r * pi;
}

double Circle::circleCircumference()
{
    return 2 * r * pi;
}

double Circle::sectorArea(double angle)
{
    return r * r * pi * angle / 360;
}

void printIsInsideMessage(Circle* circle, Point* A)
{
    cout << "The point (" << A->x << ", " << A->y << ") is" << (A->isInsideCircle(*circle) ? "" : " not") << " inside the circle" << endl;
}

void printCircleInfo(Circle* circle, Point* A, Point* B)
{
    circle->print();
    cout << "Circle area: " << circle->circleArea() << endl;
    cout << "Circle circumference: " << circle->circleCircumference() << endl;
    cout << "Sector area (100 deg): " << circle->sectorArea(100) << endl;
    printIsInsideMessage(circle, A);
    printIsInsideMessage(circle, B);
}

int main()
{
    Point* pointA = new Point{0, 0};
    Point* pointB = new Point{5, 5};
    Circle* circleA = new Circle{*pointA, 10};
    Circle* circleB = new Circle{*pointB, 3};
    //Ispis podataka tocaka
    pointA->print();
    pointB->print();
    //Ispis podataka krugova
    printCircleInfo(circleA, pointA, pointB);
    printCircleInfo(circleB, pointA, pointB);

    delete pointA, delete pointB;
    delete circleA, delete circleB;
}