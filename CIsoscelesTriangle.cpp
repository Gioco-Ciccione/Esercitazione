/*! \file CIsoscelesTriangle.cpp
    \brief implementation of class IsoscelesTriangle
    \author Sebastiano Valente
*/

#include "CIsoscelesTriangle.h"
#include <iostream>
#include <cmath>

using namespace std;

static const char* OrientationToString(IsoscelesTriangle::Orientation o) {
    switch (o) {
        case IsoscelesTriangle::Orientation::Up:
            return "Up";
        case IsoscelesTriangle::Orientation::Down:
            return "Down";
        default:
            return "Invalid orientation";
    }
}

/* ----------------------------
   CONSTRUCTORS / DESTRUCTOR
   ---------------------------- */

/// @brief default constructor
IsoscelesTriangle::IsoscelesTriangle() : Shape(), orientation(Orientation::Up)
{
    cout << "IsoscelesTriangle - default constructor" << endl;
}

/// @brief constructor 
/// @param px position in the grid (x)
/// @param py position in the grid (y)
/// @param w width of the bounding box
/// @param h height of the bounding box
IsoscelesTriangle::IsoscelesTriangle(float px, float py, float w, float h, Orientation o) : Shape(px, py, w, h)
{
    orientation = o;
    cout << "IsoscelesTriangle - constructor" << endl;
}

/// @brief copy constructor
/// @param r reference to the object to be copied
IsoscelesTriangle::IsoscelesTriangle(const IsoscelesTriangle&r) : Shape(r), orientation(r.orientation)
{
    cout << "IsoscelesTriangle - copy constructor" << endl;
}

/// @brief destructor
IsoscelesTriangle::~IsoscelesTriangle()
{
    cout << "IsoscelesTriangle - destructor" << endl;
}

/* ----------------------------
   OPERATORS
   ---------------------------- */

/// @brief overload of operator = 
/// @param r reference to the object on the right side of the operator 
/// @return reference to the object on the left side of the operator
IsoscelesTriangle& IsoscelesTriangle::operator=(const IsoscelesTriangle&r)
{
    if (this != &r)
    {
        Shape::operator=(r);
        orientation = r.orientation;
    }

    return *this;
}


/* ----------------------------
   BASIC HANDLING
   ---------------------------- */

/// @brief default initialization of the object
void IsoscelesTriangle::Init()
{
    Shape::Init();
    orientation = Orientation::Up;
}

/// @brief initialization of the object as a copy of an object 
/// @param r reference to the object that should be copied
void IsoscelesTriangle::Init(const IsoscelesTriangle&r)
{
    Shape::Init(r);
    orientation = r.orientation;
}

/// @brief total reset of the object
void IsoscelesTriangle::Reset()
{
    Shape::Reset();
}

/// @brief override of function Shape::IsEqual()
/// @param r reference to the object to check the equality
/// @return if r is equal to this
bool IsoscelesTriangle::IsEqual(const Shape& r) const
{
    // check dynamic type
    const IsoscelesTriangle* p = dynamic_cast<const IsoscelesTriangle*>(&r);

    if (!p) return false;

    return Shape::IsEqual(r) && orientation == p->orientation;
}

/* ----------------------------
   GETTERS
   ---------------------------- */


/// @brief computes the area of the isosceles triangle
/// @return area
float IsoscelesTriangle::GetArea() const
{
    return (height * width) / 2.0;
}

/// @brief computes the perimeter of the isosceles triangle
/// @return perimeter
float IsoscelesTriangle::GetPerimeter() const
{
    return width + 2*GetObliqueSide();
}

/// @brief computes the oblique side lenght of the isosceles triangle
/// @return oblique side lenght
float IsoscelesTriangle::GetObliqueSide() const
{
    return sqrt(height*height + (width/2.0f)*(width/2.0f));
}

/// @brief getter for the triangle orientation
/// @return orientation
IsoscelesTriangle::Orientation IsoscelesTriangle::GetOrientation() const
{
    return orientation;
}

/* ----------------------------
   SETTERS
   ---------------------------- */

/// @brief set the triangle orientation
/// @param o value of the desired orientation
void IsoscelesTriangle::SetOrientation(Orientation o)
{
    orientation = o;
}


/* ----------------------------
   DEBUG and SERIALIZATION
   ---------------------------- */

/// @brief for debugging: all infos about the object
void IsoscelesTriangle::Dump() const
{
    cout << "IsoscelesTriangle Dump:" << endl;

    Shape::Dump();

    cout << "  Oblique side:          " << GetObliqueSide() << endl;
    cout << "  Orientation:           " << OrientationToString(GetOrientation()) << endl;
    cout << "  Figure area:           " << GetArea() << endl;
    cout << "  Figure perimeter:      " << GetPerimeter() << endl;
    cout << "  Text:                  " << (text ? text : "(null)") << endl;
}