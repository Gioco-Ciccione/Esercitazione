/*! \file CRectangle.cpp
    \brief implementation of class Rectangle
    \author Paolo Gastaldo
*/

#include "CRectangle.h"
#include <iostream>

using namespace std;

/* ----------------------------
   CONSTRUCTORS / DESTRUCTOR
   ---------------------------- */

/// @brief default constructor
Rectangle::Rectangle() : Shape()
{
    cout << "Rectangle - default constructor" << endl;
}

/// @brief constructor 
/// @param px position in the grid (x)
/// @param py position in the grid (y)
/// @param w width of the bounding box
/// @param h height of the bounding box
Rectangle::Rectangle(float px, float py, float w, float h) : Shape(px, py, w, h)
{
    cout << "Rectangle - constructor" << endl;
}

/// @brief copy constructor
/// @param r reference to the object to be copied
Rectangle::Rectangle(const Rectangle &r) : Shape(r)
{
    cout << "Rectangle - copy constructor" << endl;
}

/// @brief destructor
Rectangle::~Rectangle()
{
    cout << "Rectangle - destructor" << endl;
}

/* ----------------------------
   OPERATORS
   ---------------------------- */

/// @brief overload of operator = 
/// @param r reference to the object on the right side of the operator 
/// @return reference to the object on the left side of the operator
Rectangle& Rectangle::operator=(const Rectangle &r)
{
    if (this != &r) 
        Shape::operator=(r);

    return *this;
}


/* ----------------------------
   BASIC HANDLING
   ---------------------------- */

/// @brief default initialization of the object
void Rectangle::Init()
{
    Shape::Init();
}

/// @brief initialization of the object as a copy of an object 
/// @param r reference to the object that should be copied 
void Rectangle::Init(const Rectangle &r)
{
    Shape::Init(r);
}

/// @brief total reset of the object  
void Rectangle::Reset()
{
    Shape::Reset();
}


/* ----------------------------
   GETTERS
   ---------------------------- */
   
/// @brief to get the height of the rectangle
/// @return height
float Rectangle::GetVSide() const
{
	return height;
    
}

/// @brief to get the width of the rectangle
/// @return width
float Rectangle::GetHSide() const
{
    return width;
}

/// @brief computes the area of the rectangle
/// @return area 
float Rectangle::GetArea() const
{
    return width * height;
}

/// @brief computes the perimeter of the rectangle
/// @return perimeter 
float Rectangle::GetPerimeter() const
{
    return 2.0 * (width + height);
}

/* ----------------------------
   DEBUG and SERIALIZATION
   ---------------------------- */

/// @brief for debugging: all infos about the object
void Rectangle::Dump() const
{
	cout << endl <<  "----------------------" << endl;
    cout << "Rectangle Dump:" << endl << endl;
	
	Shape::Dump();
	cout << endl;
}