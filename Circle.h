#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
public:
    Circle();

    virtual bool Draw() override;
    virtual bool SetPosition(POINT& point) override;

    bool  SetRadius(int radius);
    int   GetRadius();
    POINT GetCenter();

private:
    POINT center;
    int   radius;

    bool isValidPlacement(int r, POINT p);
};

#endif // CIRCLE_H
