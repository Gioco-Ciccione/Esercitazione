#pragma once

#include "CIsoscelesTriangle.h"
#include <string>

class Grid;

enum class ShapeType {
    Rectangle,
    Rhombus,
    IsoscelesTriangle,
};

struct MenuContext
{
    Grid& grid;
    ShapeType selectedType;
    IsoscelesTriangle::Orientation orientation;

    float pos_x, pos_y, width, height;
    float scale;
    int selectedShapeIndex;

    string text;

    MenuContext(Grid& grid)
        : grid(grid)
    {
    }
};