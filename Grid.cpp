/*! \file Grid.cpp
	\brief implementation of class Grid
	\author Sebastiano Valente
*/

#include "Grid.h"
#include "CShape.h"

/* ----------------------------
   CONSTRUCTORS
   ---------------------------- */

/// @brief constructor
/// @param size_x width of the grid
/// @param size_y height of the grid
Grid::Grid(float size_x, float size_y)
{
	size = { size_x,size_y };
}

/* ----------------------------
   GETTERS
   ---------------------------- */

/// @brief getter for grid size
/// @return pair containing width and height
pair<int, int> Grid::GetSize() const {
	return size;
}

/// @brief getter for all shapes in the grid
/// @return vector of weak pointers to shapes
std::vector<std::weak_ptr<Shape>> Grid::GetShapes() const {
	std::vector<std::weak_ptr<Shape>> result;

	result.reserve(shapes.size());

	for (const auto& shape : shapes) {
		result.push_back(shape);
	}

	return result;
}

/// @brief getter for shape at specified index
/// @param index index of the shape
/// @return weak pointer to the selected shape
weak_ptr<Shape> Grid::GetShapeAt(int index) const {
	if (index >= shapes.size()) return {};
	return shapes[index];
}

/* ----------------------------
   SETTERS
   ---------------------------- */

/// @brief setter for grid size
/// @param size pair containing width and height
void Grid::SetSize(pair<int, int> size)
{
	this->size.first = size.first;
	this->size.second = size.second;
}


/* ----------------------------
   BASIC HANDLING
   ---------------------------- */

/// @brief adds a shape to the grid
/// @param shape_ptr weak pointer to the shape
/// @return true if insertion succeeded
bool Grid::AddShape(weak_ptr<Shape> shape_ptr) {
	if (shape_ptr.expired()) return false;

	shapes.push_back(shape_ptr.lock());
	return true;
}

/// @brief removes a shape at a given index
/// @param index index of the shape
/// @return true if removal succeeded
bool Grid::RemoveShapeAt(int index) {
	if (index >= shapes.size()) return false;
	shapes.erase(shapes.begin() + index);
	return true;
}	

/// @brief checks if a shape is completely inside the grid
/// @param shape_ptr weak pointer to the shape
/// @return true if the shape bounding box is inside the grid
bool Grid::IsShapeInGrid(weak_ptr<Shape> shape_ptr)
{
	if (shape_ptr.expired()) return false;
	float _pos_x;
	float _pos_y;
	float _width;
	float _heigth;

	shape_ptr.lock()->GetPosition(_pos_x, _pos_y);
	shape_ptr.lock()->GetDim(_width, _heigth);

	return _pos_x >= 0 && _pos_y >= 0 && _pos_x + _width <= size.first && _pos_y + _heigth <= size.second;
}

/// @brief removes all shapes from the grid
/// @return number of removed shapes
int Grid::ClearGrid()
{
	int shapes_count = shapes.size();
	shapes.clear();
	return shapes_count;
}

/// @brief removes a specific shape from the grid
/// @param shape_ptr shared pointer to the shape
/// @return true if the shape was removed
bool Grid::RemoveShape(const std::shared_ptr<Shape>& shape_ptr) {

	auto oldSize = shapes.size();

	shapes.erase(
		std::remove_if(shapes.begin(), shapes.end(),
			[&](const shared_ptr<Shape>& s)
			{
				return s.get() == shape_ptr.get();
			}),
		shapes.end());

	return shapes.size() != oldSize;
}
