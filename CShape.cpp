/*! \file CShape.h
    \brief implementation of class Shape
	\author Paolo Gastaldo
*/

#include "CShape.h"
#include<iostream>
#include<cstring>    
#include<new>        
#include<cmath>      

using namespace std;

/// @brief helper: safe copy with null checks and guaranteed termination
static void SafeStrCopy(char* dest, const char* src, size_t destSize) {
    if (!dest) return;
    if (!src) {
        dest[0] = '\0';
        return;
    }
    //strncpy(dest, src, destSize - 1);
    strncpy_s(dest, destSize, src, _TRUNCATE);
    dest[destSize - 1] = '\0';
}

/* ----------------------------
   CONSTRUCTORS / DESTRUCTOR
   ---------------------------- */
/// @brief default constructor 
Shape::Shape()
{
	
	cout << "Shape - default constructor" << endl;
	
	text = nullptr;
    Init();
}

/// @brief constructor 
/// @param px position in the grid (x)
/// @param py position in the grid (y)
/// @param w width of the bounding box
/// @param h height of the bounding box
Shape::Shape(float px, float py, float w, float h)
{
	cout << "Shape - constructor" << endl;
	
	text = nullptr;
    Init();
	
	SetPosition(px,py);
	
    SetWidth(w);
    SetHeight(h);
}

/// @brief copy constructor
/// @param r reference to the object to be copied
Shape::Shape(const Shape &r)
{
	cout << "Shape - copy constructor" << endl;
	
    text = nullptr;
	Init(r);
}

/// @brief destructor
Shape::~Shape()
{
	cout << "Shape - destructor" << endl;
    Reset();
}

/* ----------------------------
   OPERATORS
   ---------------------------- */

/// @brief overload of operator = 
/// @param r reference to the object on the right side of the operator 
/// @return reference to the object on the left side of the operator
Shape& Shape::operator=(const Shape &r)
{
    if (this == &r) return *this;

    // copy simple members
    x = r.x;
    y = r.y;
    width  = r.width;
    height = r.height;

    // ensure we have a buffer
    if (text == nullptr) {
        text = new char[TEXTSIZE];
        if (text == nullptr) {
            ErrorMessage("operator=: memory allocation for text failed");
            return *this;
        }
    }

    SafeStrCopy(text, r.text, TEXTSIZE);
    return *this;
}

/// @brief overload of operator == 
/// @param r reference to the object on the right side of the operator 
/// @return true if the two objects have the same width and the same length  
bool Shape::operator==(const Shape &r)
{
    return IsEqual(r);
}

/* ----------------------------
   BASIC HANDLING
   ---------------------------- */
   
/// @brief default initialization of the object
void Shape::Init()
{
    x = 0.0;
    y = 0.0;
    width = 0.0;
    height = 0.0;

    if (text == nullptr) {
        text = new char[TEXTSIZE];
        if (text == nullptr) {
            ErrorMessage("Init: memory allocation for text failed");
            return;
        }
    }
    text[0] = '\0';
}

/// @brief initialization of the object as a copy of an object 
/// @param r reference to the object to check the equality
/// @return if r is equal to this
void Shape::Init(const Shape &r)
{
    x = r.x;
    y = r.y;
    width = r.width;
    height = r.height;

    if (text == nullptr) {
        text = new char[TEXTSIZE];
        if (text == nullptr) {
            ErrorMessage("Init(copy): memory allocation for text failed");
            return;
        }
    }
    SafeStrCopy(text, r.text, TEXTSIZE);
}

/// @brief total reset of the object  
void Shape::Reset()
{
    if (text != nullptr) {
        delete [] text;
        text = nullptr;
    }
    width = 0.0;
    height = 0.0;
    x = 0.0;
    y = 0.0;
}

/// @brief check if r is equal to this
/// @param r 
bool Shape::IsEqual(const Shape& r) const
{
    const float eps = 1e-6f;
    bool posEqual = (fabs(x - r.x) < eps) && (fabs(y - r.y) < eps);
    bool dimsEqual = (fabs(width - r.width) < eps) &&
        (fabs(height - r.height) < eps);

    bool sameShape = typeid(*this) == typeid(r);

    /* optional
    const char* t1 = text;
    const char* t2 = r.text;

    bool textEqual = (strcmp(t1, t2) == 0);
    */

    return posEqual && dimsEqual && sameShape;
}

/* ----------------------------
   FORMATTING
   ---------------------------- */

/// @brief to rescale the shape without changing the aspect ratio
/// @param sf scale factor (1.0 = 100%, no changes)
void Shape::Scale(float sf) 
{
    if (sf < 0.0f) {
        WarningMessage("Scale: negative value, clamped to 0");
        sf = 0.0;
    }
    width = width * sf;
    height = height * sf;
}

/* ----------------------------
   GETTERS / SETTERS
   ---------------------------- */

/// @brief set position of the object
/// @param px position on x
/// @param py position on y
void Shape::SetPosition(float px, float py)
{
	if (px < 0.) {
		WarningMessage("SetPosition: the position in the grid cannot be a negative value; clamped to 0");
		x = 0;
	}		
	else 
		x = px;
	
	if (py < 0.) {
		WarningMessage("SetPosition: the position in the grid cannot be a negative value; clamped to 0");
		y = 0;
	}		
	else 
		y = py;

}

/// @brief set height of the object
/// @param h height 
void Shape::SetHeight(float h)
{
    if (h < 0.0) {
        WarningMessage("SetHeight: negative value, clamped to 0");
        h = 0.0;
    }
    height = h;
}

/// @brief set width of the object
/// @param w width 
void Shape::SetWidth(float w)
{
    if (w < 0.0) {
        WarningMessage("SetWidth: negative value, clamped to 0");
        w = 0.0;
    }
    width = w;
}

/// @brief set width and length of the object
/// @param w width 
/// @param h height
void Shape::SetDim(float w, float h)
{
    SetWidth(w);
    SetHeight(h);
}

/// @brief set the text area of the object
/// @param string the text 
void Shape::SetText(const char* string)
{
    if (string == nullptr) {
        // clear existing text if buffer exists, else do nothing
        if (text) text[0] = '\0';
        return;
    }

    if (text == nullptr) {
        text = new char[TEXTSIZE];
        if (text == nullptr) {
            ErrorMessage("SetText: memory allocation for text failed");
            return;
        }
    }

    SafeStrCopy(text, string, TEXTSIZE);
}

/// @brief get position of the object
/// @param px (reference to) position on x
/// @param py (reference to) position on y
void Shape::GetPosition(float &px, float &py) const
{
    px = x;
    py = y;
}

/// @brief get width and length of the object
/// @param w (reference to) width 
/// @param h (reference to) height
void Shape::GetDim(float &w, float &h) const
{
    w = width;
    h = height;
}

/// @brief get position on x of the object
/// @return position on x
float Shape::GetX() const
{
    return x;
}

/// @brief get position on y of the object
/// @return position on y
float Shape::GetY() const
{
    return y;
}

/// @brief get height of the object
/// @return height
float Shape::GetHeight() const
{
    return height;
}

/// @brief get width of the object
/// @return width
float Shape::GetWidth() const
{
    return width;
}


/// @brief computes the area of the object
/// @return area 
float Shape::GetBoundingBoxArea() const
{
    return width * height;
}

/// @brief returns text in the text area 
/// @param string pointer to a string 
void Shape::GetText(char* string) const
{
    if (!string) return;
    if (!text) {
        string[0] = '\0';
        return;
    }
    SafeStrCopy(string, text, TEXTSIZE);
}

/* ----------------------------
   DEBUG and SERIALIZATION
   ---------------------------- */

/// @brief write an error message 
/// @param string message to be printed
void Shape::ErrorMessage(const char *string) const
{
    std::cerr << "[Shape - ERROR] " << (string ? string : "(null)") << std::endl;
}

/// @brief write an warning message 
/// @param string message to be printed
void Shape::WarningMessage(const char *string) const
{
    std::cerr << "[Shape - WARNING] " << (string ? string : "(null)") << std::endl;
}

/// @brief for debugging: all infos about the object
void Shape::Dump() const
{
    std::cout << "Shape Dump:" << std::endl;
    std::cout << "  Position: (" << x << ", " << y << ")" << std::endl;
    std::cout << "  Width:  " << width << std::endl;
    std::cout << "  Height: " << height << std::endl;
    std::cout << "  Bounding Box Area:   " << GetBoundingBoxArea() << std::endl;
 	
	cout << endl;
}