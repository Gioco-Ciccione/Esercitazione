#include <iostream>
#include <cmath>

#include "CShape.h"
#include "CRectangle.h"
#include "CRhombus.h"
#include "CIsoscelesTriangle.h"
#include <memory.h>

using namespace std;

#define MAX_SHAPES 3

int main()
{
    unique_ptr<Shape> figures[MAX_SHAPES];

    figures[0] = make_unique<Rectangle>(0,0,10,30);
    figures[1] = make_unique<Rectangle>(0,0,10,30);
    figures[2] = make_unique<IsoscelesTriangle>(12, 67, 67, 67);

    cout << (*figures[0] == *figures[1]) << endl;
    
    return 0;
}