/*! \file CRectangle.h
    \brief Declaration of the class Rectangle
    \author Paolo Gastaldo
*/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "CShape.h"

/// @class Rectangle
/// @brief to manage an object with the shape of a rectangle
class Rectangle : public Shape
{
public:

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    Rectangle();
    Rectangle(float px, float py, float w, float h);
    Rectangle(const Rectangle &r);

    ~Rectangle();
    /// @}

    /// @name OPERATORS
    /// @{
    Rectangle& operator=(const Rectangle &r);
    bool operator==(const Rectangle &r);
    /// @}

    /// @name BASIC HANDLING
    /// @{
    void Init();
    void Init(const Rectangle &r);
    void Reset();
    /// @}
	
	/// @name GETTERS
    /// @{
	float GetVSide();
	float GetHSide();
    float GetArea();
    float GetPerimeter();
    /// @}

    /// @name DEBUG and SERIALIZATION
    /// @{
    virtual void Dump();
    /// @}
};

#endif