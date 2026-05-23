#include "MenuBuild.h"
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
#include "Macros.h"
#include "MenuUtilities.h"

using namespace std;
using enum EndActionBehaviour;

shared_ptr<MenuNode> BuildMenu() {
    // Root menu
    auto root = NODE("Main Menu");

    // Visualize Menu
    auto perimeterShow = NODE("Perimetro", LAMBDA() {
        cout << "Perimetro = " << context.grid.GetShapeAt(context.selectedShapeIndex).lock()->GetPerimeter() << endl;
        return JumpToStart;
    });
    auto areaShow = NODE("Area", LAMBDA() {
        cout << "Area = " << context.grid.GetShapeAt(context.selectedShapeIndex).lock()->GetArea() << endl;
        return JumpToStart;
    });
    auto dumpShow = NODE("Dump completo", LAMBDA() {
        context.grid.GetShapeAt(context.selectedShapeIndex).lock()->Dump();
        return JumpToStart;
    });


    auto visualizePolygons = NODE("Visualizza tutti i poligoni", LAMBDA_CAPTURE(perimeterShow, areaShow, dumpShow) {
        return ShowShapesList(context, nav, "Scegli la figura da analizzare:", { perimeterShow, areaShow, dumpShow }, "Cosa desideri visualizzare?");
    });

    // Modify menu
    auto modifyHeightInput = NODE("Inserisci nuova height: ", LAMBDA() {
        switch (ReadFloatFromTerminal(context.height, true)) {
        case ExecuteSelectedChild:
        {
            auto selectedShape = context.grid.GetShapeAt(context.selectedShapeIndex).lock();
            bool success = ModifyAndValidate(context.grid, selectedShape, [&](Shape& s) {s.SetHeight(context.height); });
            if (success) PrintAndWait("Height modificata");
            else PrintAndWait("Impossibile modificare la height (bounding box non contenuta nella griglia)");

            return JumpToStart;
        }
        default: return ExecuteSelectedChild;
        }
    })->MarkAsInputNode();

    auto modifyWidthInput = NODE("Inserisci nuova width: ", LAMBDA() {
        switch (ReadFloatFromTerminal(context.width, true)) {
        case ExecuteSelectedChild:
        {
            auto selectedShape = context.grid.GetShapeAt(context.selectedShapeIndex).lock();
            bool success = ModifyAndValidate(context.grid, selectedShape, [&](Shape& s) {s.SetWidth(context.width); });
            if (success) PrintAndWait("Width modificata");
            else PrintAndWait("Impossibile modificare la width (bounding box non contenuta nella griglia)");

            return JumpToStart;
        }
        default: return ExecuteSelectedChild;
        }
    })->MarkAsInputNode();

    auto modifyScaleInput = NODE("Inserisci fattore di scale (1 = 100%): ", LAMBDA() {
        switch (ReadFloatFromTerminal(context.scale, true)) {
        case ExecuteSelectedChild:
        {
            auto selectedShape = context.grid.GetShapeAt(context.selectedShapeIndex).lock();
            bool success = ModifyAndValidate(context.grid, selectedShape, [&](Shape& s) {s.Scale(context.scale); });
            if (success) PrintAndWait("Figura scalata di un fattore " + to_string(context.scale));
            else PrintAndWait("Impossibile scalare la figura (bounding box non contenuta nella griglia)");

            return JumpToStart;
        }
        default: return ExecuteSelectedChild;
        }
    })->MarkAsInputNode();

    auto modifyTextInput = NODE("Inserisci nuovo testo: ", LAMBDA() {
        switch (ReadStringFromTerminal(context.text, true)) {
        case ExecuteSelectedChild:
        {
            weak_ptr<Shape> selectedShape = context.grid.GetShapeAt(context.selectedShapeIndex);
            selectedShape.lock()->SetText(context.text.c_str());
            PrintAndWait("Testo figura aggiornato");

            return JumpToStart;
        }
        default: return ExecuteSelectedChild;
        }
    })->MarkAsInputNode();

    auto modifyWidth = NODE("Width")->AddChild(modifyWidthInput);
    auto modifyHeight = NODE("Height")->AddChild(modifyHeightInput);
    auto modifyScale = NODE("Scale")->AddChild(modifyScaleInput);
    auto modifyText = NODE("Text")->AddChild(modifyTextInput);

    auto modifyPolygons = NODE("Modifica le proprietà di un poligono", LAMBDA_CAPTURE(modifyScale, modifyText, modifyWidth, modifyHeight) {
        return ShowShapesList(context, nav, "Scegli la figura da modificare:", { modifyScale, modifyText, modifyWidth, modifyHeight }, "Cosa desideri modificare?");
    });

    // Move menu
    auto movePosyInput = NODE("Inserisci nuova posizione y: ", LAMBDA() {
        switch (ReadFloatFromTerminal(context.pos_y, true)) {
        case ExecuteSelectedChild:
        {
            auto selectedShape = context.grid.GetShapeAt(context.selectedShapeIndex).lock();
            bool success = ModifyAndValidate(context.grid, selectedShape, [&](Shape& s) { s.SetPosition(context.pos_x, context.pos_y); });
            if (success) PrintAndWait("Figura spostata nella nuova posizione [" + to_string(context.pos_x) + "," + to_string(context.pos_y) + "]");
            else PrintAndWait("Impossibile spostare nella posizione (bounding box non contenuta nella griglia)");

            return JumpToStart;
        }
        default: return ExecuteSelectedChild;
        }
    })->MarkAsInputNode();

    auto movePosxInput = NODE("Inserisci nuova posizione x: ", LAMBDA() {
        return ReadFloatFromTerminal(context.pos_x, true);
    })->MarkAsInputNode()->AddChild(movePosyInput);


    auto movePolygon = NODE("Sposta un poligono sulla griglia", LAMBDA_CAPTURE(movePosxInput) {
        return ShowShapesList(context, nav, "Scegli la figura da muovere:", { movePosxInput });
    });


    // Input nodes per proprietà delle forme
    auto heightInput = NODE("Inserisci height: ", LAMBDA() {
        switch (ReadFloatFromTerminal(context.height, true)) {
        case EndActionBehaviour::ExecuteSelectedChild: {
            shared_ptr<Shape> newShape;
            switch (context.selectedType) {
            case ShapeType::Rectangle:
                newShape = make_shared<Rectangle>(context.pos_x, context.pos_y, context.width, context.height);
                break;
            case ShapeType::Rhombus:
                newShape = make_shared<Rhombus>(context.pos_x, context.pos_y, context.width, context.height);
                break;
            case ShapeType::IsoscelesTriangle:
                newShape = make_shared<IsoscelesTriangle>(context.pos_x, context.pos_y, context.width, context.height, context.orientation);
                break;
            }
            if (context.grid.IsShapeInGrid(newShape)) {
                context.grid.AddShape(newShape);
                PrintAndWait("Aggiunta la nuova shape");
            }
            else {
                PrintAndWait("La figura creata non ha il bounding box contenuto completamente nella griglia.\nNon verrà aggiunta.");
            }
            return EndActionBehaviour::JumpToStart;
        }
        default:
            return EndActionBehaviour::Repeat;
        }
    })->MarkAsInputNode();

    auto widthInput = NODE("Inserisci width: ", LAMBDA() {
        return ReadFloatFromTerminal(context.width, true);
    })->MarkAsInputNode()->AddChild(heightInput);

    auto newPosyInput = NODE("Inserisci y: ", LAMBDA() {
        return ReadFloatFromTerminal(context.pos_y, true);
    })->MarkAsInputNode()->AddChild(widthInput);

    auto newPosxInput = NODE("Inserisci x: ", LAMBDA() {
        return ReadFloatFromTerminal(context.pos_x, true);
    })->MarkAsInputNode()->AddChild(newPosyInput);

    // Sotto-menu aggiunta poligoni
    auto isoscUp = NODE("Vertice in alto", [](MenuContext& context) { context.orientation = IsoscelesTriangle::Orientation::Up; })->AddChild(newPosxInput);
    auto isoscDown = NODE("Vertice in basso", [](MenuContext& context) { context.orientation = IsoscelesTriangle::Orientation::Down; })->AddChild(newPosxInput);

    auto rect = NODE("Rettangolo", [](MenuContext& context) { context.selectedType = ShapeType::Rectangle; })->AddChild(newPosxInput);;
    auto rhomb = NODE("Rombo", [](MenuContext& context) { context.selectedType = ShapeType::Rhombus; })->AddChild(newPosxInput);
    auto isoscTrian = NODE("Triangolo Isoscele", [](MenuContext& context) { context.selectedType = ShapeType::IsoscelesTriangle; })
        ->AddChildren(isoscUp, isoscDown)
        ->SetBackOptionVisibility(true);


    auto addPolygon = NODE("Inserisci un nuovo poligono", []() {})
        ->AddChildren(rect, rhomb, isoscTrian)
        ->SetBackOptionVisibility(true);

    // Menu cancella poligono
    auto deletePolygon = NODE("Cancella un poligono", LAMBDA() {
        return ShowShapesListWithFunction(context, nav, "Scegli la figura da cancellare:", [](MenuContext& context, int i) {
            if (context.grid.RemoveShapeAt(i)) { PrintAndWait("Rimossa shape alla posizione: " + to_string(i)); }
            else { PrintAndWait("Errore"); }
            return JumpToStart;
            });
    });

    // Menu cancella tutti
    auto deleteAllPolygons = NODE("Cancella tutti i poligoni", [](MenuContext& context) {
        PrintAndWait("Eliminate " + to_string(context.grid.ClearGrid()) + " figure");
        });

    // Aggiunta menu principali al root
    root->AddChildren(visualizePolygons, modifyPolygons, movePolygon, addPolygon, deletePolygon, deleteAllPolygons)
        ->SetBackOptionVisibility(true)
        ->SetBackText("Esci");

    return root;
}