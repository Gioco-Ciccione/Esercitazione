/*! \file CShape.h
    \brief Declaration of the base class Shape
	\author Paolo Gastaldo
*/

#ifndef SHAPE_H
#define SHAPE_H

#define TEXTSIZE 1000


/// @class Shape
/// @brief to manage a generic object with a shape
class Shape
{
protected:

    /// position of the shape in the page/grid
    float x;
    float y;

    /// dimensions of the bounding box
    float height;
    float width;

    /// optional text inside the shape
    char* text;

public:

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    Shape();
    Shape(float px, float py, float w, float h);
    Shape(const Shape &r);

    virtual ~Shape();
    /// @}


    /// @name OPERATORS
    /// @{
    Shape& operator=(const Shape &r);
    bool operator==(const Shape &r);
    /// @}


    /// @name BASIC HANDLING
    /// @{
    void Init();
    void Init(const Shape &r);
    void Reset();

    virtual bool IsEqual(const Shape& r) const;
    /// @}
	
	/// @name FOMATTING
    /// @{
	virtual void Scale(float sf);
	/// @}

    /// @name GETTERS / SETTERS
    /// @{

    void SetPosition(float px, float py);
    void SetHeight(float h);
    void SetWidth(float w);
    void SetDim(float w, float h);

    void SetText(const char* string);

    void GetPosition(float &px, float &py) const;
    void GetDim(float &w, float &h) const;

    float GetX() const;
    float GetY() const;
    float GetHeight() const;
    float GetWidth() const;

    float GetBoundingBoxArea() const;

    void GetText(char* string) const;
	
	virtual float GetPerimeter() const = 0;
	virtual float GetArea() const = 0;

    /// @}


    /// @name DEBUG and SERIALIZATION
    /// @{
    void ErrorMessage(const char *string) const;
    void WarningMessage(const char *string) const;
    virtual void Dump() const;
    /// @}

};

#endif