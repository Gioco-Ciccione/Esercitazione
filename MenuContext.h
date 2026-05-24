/*! \file MenuContext.h
    \brief Declaration of the struct MenuContext
    \author Sebastiano Valente
*/

#pragma once

#include "CIsoscelesTriangle.h"
#include <string>

class Grid;

/// @enum ShapeType
/// @brief Possible types of shapes managed by the application
enum class ShapeType {
    Rectangle,          ///< Rectangle shape
    Rhombus,            ///< Rhombus shape
    IsoscelesTriangle,  ///< Isosceles triangle shape
};

/// @struct MenuContext
/// @brief to manage the shared context used by menu actions
struct MenuContext
{
    Grid& grid;

    ShapeType selectedType;
    IsoscelesTriangle::Orientation orientation;

    float pos_x, pos_y, width, height;
    float scale;

    int selectedShapeIndex;

    string text;

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{

    /// @brief Constructs the menu context
    /// @param grid Reference to the grid instance
    MenuContext(Grid& grid)
        : grid(grid)
    {
    }

    /// @}
};