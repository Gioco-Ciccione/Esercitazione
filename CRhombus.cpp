/*! \file CRhombus.cpp
    \brief implementation of class Rhombus
    \author Paolo Gastaldo
*/

#include "CRhombus.h"
#include <iostream>
#include <cmath>

using namespace std;

/* ----------------------------
   CONSTRUCTORS / DESTRUCTOR
   ---------------------------- */

/// @brief default constructor
Rhombus::Rhombus() : Shape()
{
    cout << "Rhombus - default constructor" << endl;
}

/// @brief constructor 
/// @param px position in the grid (x)
/// @param py position in the grid (y)
/// @param w width of the bounding box
/// @param h height of the bounding box
Rhombus::Rhombus(float px, float py, float w, float h) : Shape(px, py, w, h)
{
    cout << "Rhombus - constructor" << endl;
}

/// @brief copy constructor
/// @param r reference to the object to be copied
Rhombus::Rhombus(const Rhombus &r) : Shape(r)
{
    cout << "Rhombus - copy constructor" << endl;
}

/// @brief destructor
Rhombus::~Rhombus()
{
    cout << "Rhombus - destructor" << endl;
}

/* ----------------------------
   OPERATORS
   ---------------------------- */

/// @brief overload of operator = 
/// @param r reference to the object on the right side of the operator 
/// @return reference to the object on the left side of the operator
Rhombus& Rhombus::operator=(const Rhombus &r)
{
    if (this != &r) 
        Shape::operator=(r);

    return *this;
}

/// @brief overload of operator == 
/// @param r reference to the object on the right side of the operator 
/// @return true if the two bounding boxes have the same width and the same length  
bool Rhombus::operator==(const Rhombus &r)
{
    return Shape::operator==(r);
}

/* ----------------------------
   BASIC HANDLING
   ---------------------------- */

/// @brief default initialization of the object
void Rhombus::Init()
{
    Shape::Init();
}

/// @brief initialization of the object as a copy of an object 
/// @param r reference to the object that should be copied
void Rhombus::Init(const Rhombus &r)
{
    Shape::Init(r);
}

/// @brief total reset of the object
void Rhombus::Reset()
{
    Shape::Reset();
}

/* ----------------------------
   GETTERS
   ---------------------------- */

/// @brief to get the horizontal diagonal of the rhombus
/// @return horizontal diagonal
float Rhombus::GetHDiagonal()
{
    return width;
}

/// @brief to get the vertical diagonal of the rhombus
/// @return vertical diagonal
float Rhombus::GetVDiagonal()
{
    return height;
}

/// @brief computes the area of the rhombus
/// @return area
float Rhombus::GetArea()
{
    return (GetHDiagonal() * GetVDiagonal()) / 2.0;
}

/// @brief computes the perimeter of the rhombus
/// @return perimeter
float Rhombus::GetPerimeter()
{
    float side;

    side = GetSide();

    return 4.0 * side;
}

/// @brief computes the side of the rhombus
/// @return side
float Rhombus::GetSide()
{
    float d1, d2, side;

    d1 = GetHDiagonal();
    d2 = GetVDiagonal();

    side = sqrt((d1 / 2.0) * (d1 / 2.0) +
                (d2 / 2.0) * (d2 / 2.0));
	
	return side;
}

/* ----------------------------
   DEBUG and SERIALIZATION
   ---------------------------- */

/// @brief for debugging: all infos about the object
void Rhombus::Dump()
{
    cout << "Rhombus Dump:" << endl;

    Shape::Dump();

    cout << "  Horizontal diagonal:   " << GetHDiagonal() << endl;
    cout << "  Vertical diagonal:     " << GetVDiagonal() << endl;
    cout << "  Figure area:           " << GetArea() << endl;
    cout << "  Figure perimeter:      " << GetPerimeter() << endl;
    cout << "  Text:                  " << (text ? text : "(null)") << endl;
}