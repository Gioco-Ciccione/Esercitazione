/*! \file Grid.h
    \brief Declaration of the base class Grid
    \author Valente Sebastiano
*/

#pragma once

#include <memory>
#include <vector>

using namespace std;

class Shape;

/// @class Grid
/// @brief to store all the shapes
class Grid final
{
private:

    /// grid size
    pair<int,int> size;

    /// vector of shapes contained in the grid
    vector<shared_ptr<Shape>> shapes = {};

public:

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    Grid() = default;
    Grid(float size_x, float size_y);

    ~Grid() = default;
    /// @}

    /// @name GETTERS / SETTERS
    /// @{
    pair<int,int> GetSize() const;
    vector<weak_ptr<Shape>> GetShapes() const;
    weak_ptr<Shape> GetShapeAt(int index) const;
    
    void SetSize(pair<int,int> size);
    ///  @}

    /// @name BASIC HANDLING
    /// @{
    bool AddShape(weak_ptr<Shape> shape_ptr);
    bool RemoveShapeAt(int index);
    bool RemoveShape(weak_ptr<Shape> shape_ptr);

    bool IsShapeInGrid(weak_ptr<Shape> shape_ptr);

    int ClearGrid();
    /// @}
};