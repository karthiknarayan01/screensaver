#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle();

    virtual bool Draw() override;
    virtual bool SetPosition(POINT& point) override;

    bool         SetSideLength(unsigned int length);
    unsigned int GetSideLength();

private:
    unsigned int sideLength;
};

#endif // TRIANGLE_H
