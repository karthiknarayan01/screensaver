#include "Circle.h"

Circle::Circle()
{
    int minDim   = (WINDOW_MAXX <= WINDOW_MAXY) ? WINDOW_MAXX : WINDOW_MAXY;
    center.x     = minDim / 2;
    center.y     = minDim / 2;
    radius       = minDim / 10;
}

bool Circle::isValidPlacement(int r, POINT p)
{
    int bound = (GetWindowWidth() <= GetWindowHeight()) ? GetWindowWidth() : GetWindowHeight();
    return (p.x + r < bound) && (p.x - r > 0) &&
           (p.y + r < bound) && (p.y - r > 0);
}

bool Circle::SetPosition(POINT& point)
{
    if (isValidPlacement(radius, point)) {
        center   = point;
        position = point;
        return true;
    }
    return false;
}

bool Circle::SetRadius(int r)
{
    if (isValidPlacement(r, position)) {
        radius = r;
        return true;
    }
    return false;
}

bool Circle::Draw()
{
    renderer.SetPenColor(borderColor);
    renderer.SetBrushColor(fillColor);
    renderer.FilledCircle(center, radius);
    return true;
}

int   Circle::GetRadius() { return radius; }
POINT Circle::GetCenter() { return center; }
