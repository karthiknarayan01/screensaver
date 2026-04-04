#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle();

    virtual bool Draw() override;
    virtual bool SetPosition(POINT& point) override;

    bool         SetHeight(unsigned int height);
    unsigned int GetHeight();
    bool         SetWidth(unsigned int width);
    unsigned int GetWidth();

private:
    unsigned int height;
    unsigned int width;
};

#endif // RECTANGLE_H
