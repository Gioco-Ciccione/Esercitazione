/*! \file MenuUtilities.cpp
    \brief utility functions for menu handling
    \author Sebastiano Valente
*/

#include "MenuUtilities.h"
#include <memory>
#include <string>

#include "CShape.h"
#include "CRectangle.h"
#include "CRhombus.h"
#include "CIsoscelesTriangle.h"
#include "ShapeTester.h"
#include "Grid.h"
#include "MenuNode.h"
#include "MenuNavigator.h"
#include "MenuContext.h"
#include "macros.h"

using namespace std;

/* ----------------------------
   INPUT UTILITIES
   ---------------------------- */

/// @brief safely reads a float value from terminal
/// @param outValue variable where the value will be stored
/// @param allowOnlyPositive if true only positive values are accepted
/// @return action behaviour after input
EndActionBehaviour ReadFloatFromTerminal(float& outValue, bool allowOnlyPositive) {
    cin >> outValue;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input non valido" << endl;
        return EndActionBehaviour::Repeat;
    }

    if (allowOnlyPositive && outValue < 0) {
        cout << "Non sono ammessi valori negativi" << endl;
        return EndActionBehaviour::Repeat;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return EndActionBehaviour::ExecuteSelectedChild;
}

/// @brief safely reads a string from terminal
/// @param outValue variable where the string will be stored
/// @param allowEmpty if true empty strings are accepted
/// @return action behaviour after input
EndActionBehaviour ReadStringFromTerminal(string& outValue, bool allowEmpty) {
    cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, outValue);

    if (cin.fail()) {
        cin.clear();
        cout << "Input non valido" << endl;
        return EndActionBehaviour::Repeat;
    }

    if (!allowEmpty && outValue.empty()) {
        cout << "La stringa non puo' essere vuota" << endl;
        return EndActionBehaviour::Repeat;
    }

    return EndActionBehaviour::ExecuteSelectedChild;
}

/* ----------------------------
   MENU BUILDING
   ---------------------------- */

/// @brief builds a menu containing all shapes in the grid
/// @param grid reference to the grid
/// @param text menu title
/// @param action callback executed when selecting a shape
/// @return generated menu node
shared_ptr<MenuNode> BuildShapeSelectionMenu(Grid& grid, const string& text, function<EndActionBehaviour(MenuContext&, int)> action) {
    auto root = NODE(text);
    auto shapes = grid.GetShapes();

    for (int i = 0; i < shapes.size(); ++i) {
        auto shape = shapes[i].lock();
        if (!shape) continue;

        float pos_x, pos_y, width, height;
        shape->GetPosition(pos_x, pos_y);
        shape->GetDim(width, height);

        string shape_name = GetShapeType(shapes[i]) +
            ": Location=[" + to_string(pos_x) + "," + to_string(pos_y) + "]" +
            ", Size=[" + to_string(width) + "," + to_string(height) + "]";

        auto child = NODE(
            "[ index:" + to_string(i) + " ] " + shape_name,
            [action, i](MenuContext& ctx, MenuNavigator& nav) {
                ctx.selectedShapeIndex = i;
                return action(ctx, i);
            }
        )->SetBackOptionVisibility(true)->MarkAsRuntimeGenerated();

        root->AddChild(child)->SetBackOptionVisibility(true);
    }

    return root;
}

/// @brief builds a shape selection menu with additional child nodes
/// @param grid reference to the grid
/// @param text menu title
/// @param action callback executed when selecting a shape
/// @param children child nodes added to each shape node
/// @return generated menu node
shared_ptr<MenuNode> BuildShapeSelectionMenuWithChild(Grid& grid, const string& text, function<EndActionBehaviour(MenuContext&, int)> action, vector<shared_ptr<MenuNode>> children) {
    auto ret = BuildShapeSelectionMenu(grid, text, action);
    for (auto node : ret->GetChildren()) {
        for (auto child : children) {
            node->AddChild(child);
        }
    }
    return ret;
}

/* ----------------------------
   SHAPE UTILITIES
   ---------------------------- */

/// @brief returns shape type as string
/// @param shape_ptr weak pointer to the shape
/// @return shape type name
string GetShapeType(weak_ptr<Shape> shape_ptr) {
    auto s = shape_ptr.lock();
    if (!s) return "Invalid";

    const type_info& type = typeid(*s);
    if (type == typeid(Rectangle)) return "Rettangolo";
    if (type == typeid(Rhombus)) return "Rombo";
    if (type == typeid(IsoscelesTriangle)) return "Triangolo Isoscele";
    return "Undefined";
}

/// @brief prints a message and waits for ENTER
/// @param message message to print
void PrintAndWait(const string& message) {
    cout << message << endl;
    Wait();
}

/// @brief Waits for ENTER
void Wait() {
    cout << "Premi INVIO per continuare...";

    cin.clear();

    string str;
    getline(cin, str);
}

/* ----------------------------
   MENU HELPERS
   ---------------------------- */

/// @brief checks if grid contains shapes
/// @param ctx menu context
/// @param nav menu navigator
/// @param fn function executed if shapes exist
/// @return action behaviour
EndActionBehaviour HasShapes(MenuContext& ctx, MenuNavigator& nav, function<void()> fn) {
    if (ctx.grid.GetShapes().empty()) {
        PrintAndWait("Non sono presenti poligoni nella griglia");
        return EndActionBehaviour::JumpToStart;
    }
    fn();
    return EndActionBehaviour::ExecuteSelectedChild;
}

/// @brief shows shape list with child menus
/// @param ctx menu context
/// @param nav menu navigator
/// @param text menu title
/// @param children child nodes to attach
/// @param title optional child menu title
/// @return action behaviour
EndActionBehaviour ShowShapesList(MenuContext& ctx, MenuNavigator& nav, const string& text, vector<shared_ptr<MenuNode>> children, const string& title) {
    return HasShapes(ctx, nav, [&ctx, &text, &children, &title, &nav] {
        auto modifyMenu = BuildShapeSelectionMenuWithChild(ctx.grid, text, [&nav](MenuContext& context, int i) {
            return EndActionBehaviour::ExecuteSelectedChild;
            }, children);
        if (title != "") {
            for (auto option : modifyMenu->GetChildren()) {
                option->SetTitle(title);
            }
        }
        nav.Execute(modifyMenu);
        });
}

/// @brief shows shape list with custom callback
/// @param ctx menu context
/// @param nav menu navigator
/// @param text menu title
/// @param fn callback function
/// @return action behaviour
EndActionBehaviour ShowShapesListWithFunction(MenuContext& ctx, MenuNavigator& nav, const string& text, function<EndActionBehaviour(MenuContext&, int)> fn) {
    return HasShapes(ctx, nav, [&] {
        auto modifyMenu = BuildShapeSelectionMenuWithChild(ctx.grid, text, fn, {});
        nav.Execute(modifyMenu);
        });
}

/* ----------------------------
   SHAPE VALIDATION
   ---------------------------- */

/// @brief modifies a shape and validates grid constraints
/// @param grid reference to the grid
/// @param shape shape to modify
/// @param modifyFunc lambda containing modification logic
/// @return true if modification is valid
bool ModifyAndValidate(Grid& grid, shared_ptr<Shape> shape, function<void(Shape&)> modifyFunc)
{
    if (!shape)
        return false;

    // Backup completo della shape
    float pos_x, pos_y, width, height;
    shape->GetPosition(pos_x, pos_y);
    shape->GetDim(width, height);

    // Applica la modifica tramite lambda
    modifyFunc(*shape);

    // Controlla validità
    if (grid.IsShapeInGrid(shape))
        return true;

    // Rollback
    shape->SetPosition(pos_x, pos_y);
    shape->SetDim(width, height);

    return false;
}