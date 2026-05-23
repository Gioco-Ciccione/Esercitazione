#include <iostream>
#include <cmath>
#include <memory>
#include <string>

#include "CShape.h"
#include "CRectangle.h"
#include "CRhombus.h"
#include "CIsoscelesTriangle.h"
#include "ShapeTester.h"
#include "Grid.h"
#include "MenuNavigator.h"
#include "MenuContext.h"
#include "MenuBuild.h"

using namespace std;
using enum EndActionBehaviour;

#define GRID_SIZE 100

int main() {

    /*array<unique_ptr<Shape>, MAX_SHAPES> figures;

    cout << "===== TEST GERARCHIA SHAPE =====" << endl;

    // Creazione figure
    figures[0] = make_unique<Rectangle>(0 ,0 ,10 ,30);
    figures[1] = make_unique<Rhombus>(12, 67, 67, 67);
    figures[2] = make_unique<IsoscelesTriangle>(12, 67, 67, 67, IsoscelesTriangle::Orientation::Down);
    figures[3] = make_unique<Rectangle>(2, 7, 10, 30);
    figures[4] = make_unique<IsoscelesTriangle>(0, 0, 4, 8);
    figures[5] = make_unique<IsoscelesTriangle>(0, 0, 4, 8, IsoscelesTriangle::Orientation::Down);
    figures[6] = make_unique<Rectangle>(0, 0, 10, 30);
    figures[7] = make_unique<Rhombus>(12, 34, 10, 20);
    figures[8] = make_unique<Rhombus>(12, 37, 10, 20);
    figures[9] = make_unique<IsoscelesTriangle>(12, 67, 13, 45, IsoscelesTriangle::Orientation::Down);

    // Impostazione testo
    figures[0]->SetText("rettangolo_0");
    figures[1]->SetText("rombo");
    figures[3]->SetText("rettangolo_1");
    figures[5]->SetText("isoscele_0");
    figures[6]->SetText("rettangolo_0");
    figures[7]->SetText("rombo");
    figures[9]->SetText("isoscele_1");

    // Execute routine
    ShapeTester::ExecuteTestRoutine(figures);

    // Destructors call (automatically called by smart ptrs)
    cout << endl << "===== DESTRUCTORS =====" << endl << endl;*/

    Grid grid(GRID_SIZE, GRID_SIZE);
    MenuContext context(grid);

    auto root = BuildMenu();

    MenuNavigator nav(root, context);
    nav.Execute(root);

    return 0;
}

