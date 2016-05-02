// Class that represents a circle in two-dimensional space
// Author: Edson Alves
// Date: 13/04/2015
// Licence: LGPL. Sem copyright

#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"

class Circle {
public:
    Circle(const Point& center = Point(), double radius = 0);

    Point center() const;
    double radius() const;

    void set_center(const Point& center);
    void set_radius(double radius);
    void set(const Point& center, double radius);

private:
    Point m_center;
    double m_r;
};

#endif
