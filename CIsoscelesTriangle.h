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
    /// @enum Orientation
    /// @brief Possible orientations of the isosceles triangle
    enum class Orientation
    {
        Up,    ///< Vertex pointing upward
        Down,  ///< Vertex pointing downward
    };

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    IsoscelesTriangle();
    IsoscelesTriangle(float px, float py, float w, float h, Orientation o = Orientation::Up);
    IsoscelesTriangle(const IsoscelesTriangle&r);

    ~IsoscelesTriangle() override;
    /// @}

    /// @name OPERATORS
    /// @{
    IsoscelesTriangle& operator=(const IsoscelesTriangle&r);
    /// @}

    /// @name BASIC HANDLING
    /// @{
    void Init();
    void Init(const IsoscelesTriangle&r);
    void Reset();
    bool IsEqual(const Shape& r) const override;
    /// @}

    /// @name GETTERS
    /// @{
    float GetArea() const override;
    float GetPerimeter() const override;
	float GetObliqueSide() const;
    Orientation GetOrientation() const;
    /// @}

    /// @name SETTERS
    /// @{
    void SetOrientation(Orientation o);
    /// @}
    

    /// @name DEBUG and SERIALIZATION
    /// @{
    void Dump() const override;
    /// @}

private:
    Orientation orientation;
};

#endif