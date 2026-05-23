#include "Grid.h"
#include "CShape.h"

Grid::Grid(float size_x, float size_y)
{
	size = { size_x,size_y };
}

pair<int, int> Grid::GetSize() const {
	return size;
}

std::vector<std::weak_ptr<Shape>> Grid::GetShapes() const {
	std::vector<std::weak_ptr<Shape>> result;

	result.reserve(shapes.size());

	for (const auto& shape : shapes) {
		result.push_back(shape);
	}

	return result;
}

weak_ptr<Shape> Grid::GetShapeAt(int index) const {
	if (index >= shapes.size()) return {};
	return shapes[index];
}

void Grid::SetSize(pair<int, int> size)
{
	this->size.first = size.first;
	this->size.second = size.second;
}


bool Grid::AddShape(weak_ptr<Shape> shape_ptr) {
	if (shape_ptr.expired()) return false;

	shapes.push_back(shape_ptr.lock());
	return true;
}

bool Grid::RemoveShapeAt(int index) {
	if (index >= shapes.size()) return false;
	shapes.erase(shapes.begin() + index);
	return true;
}	

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

int Grid::ClearGrid()
{
	int shapes_count = shapes.size();
	shapes.clear();
	return shapes_count;
}

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
