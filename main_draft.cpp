#include <iostream>
#include <cmath>

#include "CShape.h"
#include "CRectangle.h"
#include "CRhombus.h"
#include "CIsoscelesTriangle.h"
#include <memory.h>
#include "ShapeTester.h"
#include "main_draft.h"
#include "Grid.h"
#include <string>

using namespace std;

#define MAX_SHAPES 10
#define GRID_SIZE 100

static void MainMenu(Grid* grid);

static string GetShapeType(weak_ptr<Shape> shape_ptr);

int main()
{
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

    MainMenu(&grid);
    
    return 0;
}

static void MainMenu(Grid* grid)
{
    int input;
    cout << endl << "=================================" << endl <<
                    "               MENU              " << endl <<
                    "=================================" << endl;
    cout << "Seleziona un opzione: " << endl <<
        "1) Visulizza tutti i poligoni" << endl <<
        "2) Modifica proprietà di un poligono" << endl <<
        "3) Sposta un poligono sulla griglia" << endl <<
        "4) Inserisci un nuovo poligono" << endl <<
        "5) Cancella un poligono" << endl <<
        "6) Cancella tutti i poligoni" << endl <<
        "0) Esci" << endl;

    if (cin >> input) {
        switch (input) {
            case 0:
                cout << "Termine programma" << endl;
                return;
            case 1:
                cout << "Elenco Poligoni: " << endl;
                vector<weak_ptr<Shape>> _shapes = grid->GetShapes();
                float _pos_x, _pos_y, _width, _height;
                string _shape_type;

                for (int i = 0; i < _shapes.size(); i++) {
                    _shape_type = GetShapeType(_shapes[i]);
                    _shapes[i].lock()->GetPosition(_pos_x, _pos_y);
                    _shapes[i].lock()->GetDim(_width, _height);

                    cout << "[" << i << "]: " << _shape_type << " Coord:[" << _pos_x << "," << _pos_y << "]" << " Dim:[" << _width << "," << _height << "]" << endl;
                }

                string _decision;
                cout << "Desideri mostrare ulteriori informazioni su uno specifico poligono? (S/N)" << endl;
                if (cin >> _decision) {
                    if (_decision == "S") {
                        int _index;
                        cout << "Selezionare l'indice di interesse: ";
                        if (cin >> _index) {
                            if (_index < _shapes.size()) {

                            }
                            else {
                                cout << "Indice non valido" << endl;
                            }
                        }
                        else {
                            cout << "Indice non valido" << endl;
                        }
                    }
                }

                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
            {
                int shapes_count = grid->ClearGrid();
                cout << "Eliminazione poligoni: " << shapes_count << " poligoni eliminati" << endl;
            }
            break;
            default:
                cout << "Input non valido" << endl;
        }
    }
    else {
        cout << "Input non valido" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    MainMenu(grid);
}

string GetShapeType(weak_ptr<Shape> shape_ptr)
{
    const std::type_info& type = typeid(*shape_ptr.lock());
    if (type == typeid(Rectangle)) return "Rettangolo";
    if (type == typeid(Rhombus)) return "Rombo";
    if (type == typeid(IsoscelesTriangle)) return "Triangolo Isoscele";

    return "Undefined";
}



