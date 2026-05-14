/*! \file CIsoscelesTriangle.h
    \brief Declaration of the class IsoscelesTriangle
    \author Sebastiano Valente
*/

#ifndef ISOSCELESTRIANGLE_H
#define ISOSCELESTRIANGLE_H

#include "CShape.h"

/// @class IsoscelesTriangle
/// @brief to manage an object with the shape of a isosceles triangle
class IsoscelesTriangle : public Shape
{
public:

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    IsoscelesTriangle();
    IsoscelesTriangle(float px, float py, float w, float h);
    IsoscelesTriangle(const IsoscelesTriangle&r);

    ~IsoscelesTriangle();
    /// @}

    /// @name OPERATORS
    /// @{
    IsoscelesTriangle& operator=(const IsoscelesTriangle&r);
    bool operator==(const IsoscelesTriangle&r);
    /// @}

    /// @name BASIC HANDLING
    /// @{
    void Init();
    void Init(const IsoscelesTriangle&r);
    void Reset();
    /// @}

    /// @name GETTERS
    /// @{
    float GetArea();
    float GetPerimeter();
	float GetObliqueSide();
    /// @}

    /// @name DEBUG and SERIALIZATION
    /// @{
    void Dump();
    /// @}
};

#endif