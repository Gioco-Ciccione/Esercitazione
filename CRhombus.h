/*! \file CRhombus.h
    \brief Declaration of the class Rhombus
    \author Paolo Gastaldo
*/

#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "CShape.h"

/// @class Rhombus
/// @brief to manage an object with the shape of a rhombus
class Rhombus : public Shape
{
public:

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    Rhombus();
    Rhombus(float px, float py, float w, float h);
    Rhombus(const Rhombus &r);

    ~Rhombus() override;
    /// @}

    /// @name OPERATORS
    /// @{
    Rhombus& operator=(const Rhombus &r);
    /// @}

    /// @name BASIC HANDLING
    /// @{
    void Init();
    void Init(const Rhombus &r);
    void Reset();
    /// @}

    /// @name GETTERS
    /// @{
    float GetArea() const override;
    float GetPerimeter() const override;
    float GetHDiagonal() const;
    float GetVDiagonal() const;
	float GetSide() const;
    /// @}

    /// @name DEBUG and SERIALIZATION
    /// @{
    void Dump() const override;
    /// @}
};

#endif