#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Shape {
public:
    virtual double area() const { return 0; };
};

class Rectangle: public Shape {
private:
    double width, height;
public:
    Rectangle(double width, double height): width{width}, height{height} {}
    double area() const override { return width * height; };
};

class Circle: public Shape {
private:
    double radius;
public:
    Circle(double radius) : radius{radius} {}
    double area() const override { return radius * radius * M_PI; }
};

int main()
{
    vector<Shape*> shapes;
    shapes.push_back(new Rectangle(5.5, 7.2));
    shapes.push_back(new Rectangle(0.2, 1.5));
    shapes.push_back(new Rectangle(8.9, 9.8));
    shapes.push_back(new Circle(1.5));
    shapes.push_back(new Circle(2.6));
    shapes.push_back(new Circle(2.7));
    double sum = 0;
    for(auto& shape : shapes) sum += shape->area();
    cout << sum << endl;
    for(auto& shape : shapes) delete shape;
    return 0;
}