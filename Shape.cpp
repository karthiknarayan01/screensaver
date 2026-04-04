#include "Shape.h"
#include <iostream>

using std::cout;
using std::cin;

Shape::Shape()
    : renderer(WINDOW_MAXX, WINDOW_MAXY),
      borderWidth(DEFAULT_BORDER_WIDTH),
      borderColor(BLUE),
      fillColor(RED)
{
    position.x = GetWindowWidth() / 2;
    position.y = GetWindowHeight() / 2;
}

bool Shape::SetBorderColor(SHAPE_COLOR color)
{
    borderColor = color;
    return true;
}

bool Shape::SetFillColor(SHAPE_COLOR color)
{
    fillColor = color;
    return true;
}

unsigned int Shape::GetWindowWidth()
{
    return WINDOW_MAXX - 4;   // account for window border
}

unsigned int Shape::GetWindowHeight()
{
    return WINDOW_MAXY - 28;  // account for title bar
}

POINT Shape::GetPosition()
{
    return position;
}

unsigned int Shape::GetBorderWidth()
{
    return borderWidth;
}

unsigned int Shape::GetMaxBorderWidth()
{
    return PEN_WIDTH_MAX;
}

bool Shape::ClearScreen()
{
    renderer.ClearScreen();
    return true;
}
