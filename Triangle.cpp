#include "Triangle.h"

Triangle::Triangle()
    : sideLength(WINDOW_MAXY / 4)
{}

bool Triangle::Draw()
{
    renderer.SetPenColor(borderColor);
    renderer.SetBrushColor(fillColor);
    renderer.FilledTriangle(position, sideLength - 2 * borderWidth);
    return true;
}

bool Triangle::SetSideLength(unsigned int length)
{
    if (length <= 2 * borderWidth) return false;
    if (length < (GetWindowHeight() - position.y) &&
        length < (GetWindowWidth()  - position.x))
    {
        sideLength = length;
        return true;
    }
    return false;
}

bool Triangle::SetPosition(POINT& p)
{
    if ((p.x + sideLength / 2 + borderWidth) < GetWindowWidth()  &&
        (p.x > (sideLength / 2 + borderWidth))                   &&
        (p.y + sideLength     + borderWidth)  < GetWindowHeight() &&
        (p.y > borderWidth))
    {
        position.x = p.x;
        position.y = p.y;
        return true;
    }
    return false;
}

unsigned int Triangle::GetSideLength() { return sideLength; }
