#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "FilledShapes.h"

#define WINDOW_MAXX 800
#define WINDOW_MAXY 600
#define DEFAULT_BORDER_WIDTH 5

class Shape {
public:
    Shape();

    virtual bool Draw() = 0;
    virtual bool SetPosition(POINT& point) = 0;

    POINT        GetPosition();
    unsigned int GetBorderWidth();
    unsigned int GetMaxBorderWidth();
    unsigned int GetWindowWidth();
    unsigned int GetWindowHeight();

    bool SetBorderColor(SHAPE_COLOR color);
    bool SetFillColor(SHAPE_COLOR color);
    bool ClearScreen();

protected:
    SHAPE_COLOR  borderColor;
    SHAPE_COLOR  fillColor;
    unsigned int borderWidth;
    POINT        position;
    FilledShapes renderer;
};

#endif // SHAPE_H
