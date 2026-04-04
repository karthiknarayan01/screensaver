#include "Rectangle.h"

Rectangle::Rectangle()
    : height(WINDOW_MAXY / 4),
      width(WINDOW_MAXX / 4)
{}

bool Rectangle::Draw()
{
    renderer.SetPenColor(borderColor);
    renderer.SetBrushColor(fillColor);
    // Subtract border width so the total bounding box matches the stated dimensions
    renderer.FilledRectangle(position, height - 2 * borderWidth, width - 2 * borderWidth);
    return true;
}

bool Rectangle::SetHeight(unsigned int h)
{
    if (h <= 2 * borderWidth) return false;
    if (h < (GetWindowHeight() - position.y)) {
        height = h;
        return true;
    }
    return false;
}

bool Rectangle::SetWidth(unsigned int w)
{
    if (w <= 2 * borderWidth) return false;
    if (w < (GetWindowWidth() - position.x)) {
        width = w;
        return true;
    }
    return false;
}

bool Rectangle::SetPosition(POINT& p)
{
    if ((width  + borderWidth < (GetWindowWidth()  - p.x)) &&
        (height + borderWidth < (GetWindowHeight() - p.y)))
    {
        position.x = p.x;
        position.y = p.y;
        return true;
    }
    return false;
}

unsigned int Rectangle::GetWidth()  { return width; }
unsigned int Rectangle::GetHeight() { return height; }
