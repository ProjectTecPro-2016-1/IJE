// Implementation of the class that represents a circle in two-dimensional space
// Author: Edson Alves
// Date: 13/04/2015
// Licence: LGPL. Sem copyright

#include "core/circle.h"

// -------------------------------------------------------------
// Function: Circle()
// Description: Circle class builder where the initializations of the variables happen.
// Parameters:
//      const Point& center;        Description
//      double radius;
//
// Return: void
// -------------------------------------------------------------
Circle::Circle(const Point& center, double radius)
    : m_center(center), m_r(radius) {
}

// -------------------------------------------------------------
// Function: center();
// Description:
//
// Return: void
// -------------------------------------------------------------
Point Circle::center() const {
    return m_center;
}

// -------------------------------------------------------------
// Function: radius();
// Description:
//
// Return: double
// -------------------------------------------------------------
double Circle::radius() const {
    return m_r;
}

// -------------------------------------------------------------
// Function: set_center();
// Description:
// Parameters:
//      const Point& center;        Description
//
// Return: void
// -------------------------------------------------------------
void Circle::set_center(const Point& center) {
    m_center = center;
}

// -------------------------------------------------------------
// Function: set_radius();
// Description:
// Parameters:
//      double radius        Description
//
// Return: void
// -------------------------------------------------------------
void Circle::set_radius(double radius) {
    m_r = radius;
}

// -------------------------------------------------------------
// Function: set();
// Description:
// Parameters:
//      const Point& center;        Description
//      double radius;
//
// Return: void
// -------------------------------------------------------------
void Circle::set(const Point& center, double radius) {
    m_center = center;
    m_r = radius;
}
