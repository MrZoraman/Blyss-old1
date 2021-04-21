#include "Rectangle.hpp"

Rectangle::Rectangle(int width, int height)
    : _width{width}
    , _height{height}
{
}

int Rectangle::area()
{
    return _width * _height;
}

