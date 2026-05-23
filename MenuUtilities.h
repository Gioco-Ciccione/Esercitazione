#pragma once

#include <memory>
#include <string>
#include <functional>

using namespace std;

class MenuNode;
struct MenuContext;
class MenuNavigator;
class Shape;
class Grid;
enum class EndActionBehaviour;

string GetShapeType(weak_ptr<Shape> shape_ptr);
shared_ptr<MenuNode> BuildShapeSelectionMenu(Grid& grid, const string& text, function<EndActionBehaviour(MenuContext&, int)> action);
EndActionBehaviour ReadFloatFromTerminal(float& outValue, bool allowOnlyPositive = false);
EndActionBehaviour ReadStringFromTerminal(string& outValue, bool allowEmpty);
shared_ptr<MenuNode> BuildShapeSelectionMenuWithChild(Grid& grid, const string& text, function<EndActionBehaviour(MenuContext&, int)> action, vector<shared_ptr<MenuNode>> children);
void PrintAndWait(const string& message);
EndActionBehaviour HasShapes(MenuContext& ctx, MenuNavigator& nav, function<void()> fn);
EndActionBehaviour ShowShapesList(MenuContext& ctx, MenuNavigator& nav, const string& text, vector<shared_ptr<MenuNode>> children, const string& title = "");
EndActionBehaviour ShowShapesListWithFunction(MenuContext& ctx, MenuNavigator& nav, const string& text, function<EndActionBehaviour(MenuContext&, int)> fn);
bool ModifyAndValidate(Grid& grid, shared_ptr<Shape> shape, function<void(Shape&)> modifyFunc);