#ifndef FILLED_SHAPES_H
#define FILLED_SHAPES_H

#include <exception>
#include <iostream>
#include <cstdlib>
#include <string>

// Cross-platform 2D point
struct POINT { long x; long y; };

// Default window dimensions
#define MAXX 600
#define MAXY 400

// Available shape colors
enum SHAPE_COLOR { RED=1, ORANGE=2, YELLOW=3, GREEN=4, BLUE=5, PURPLE=6, BLACK=7, BROWN=8 };

#define PEN_WIDTH_MIN 1
#define PEN_WIDTH_MAX 20

class FilledShapes {
public:
    FilledShapes(int width = MAXX, int height = MAXY);
    ~FilledShapes();

    bool FilledRectangle(POINT& origin, int height, int width, std::string text = "");
    bool FilledCircle(POINT& center, int radius);
    bool FilledEllipse(POINT& center, int radiusX, int radiusY);
    bool FilledTriangle(POINT& apex, int sideLength);
    bool Line(POINT& start, POINT& end);

    bool         SetPenColor(SHAPE_COLOR color);
    SHAPE_COLOR  GetPenColor();
    bool         SetBrushColor(SHAPE_COLOR color);
    SHAPE_COLOR  GetBrushColor();
    bool         SetPenWidth(unsigned int width);
    unsigned int GetPenWidth();

    void         ClearScreen();
    unsigned int GetMaxX();
    unsigned int GetMaxY();

    std::exception out_of_bounds;
    static void TerminateHandler() {}

private:
    static int   instanceCount;
    int          currentPenWidth;
    unsigned int currentPenColor;
    unsigned int currentBrushColor;
    int          windowWidth;
    int          windowHeight;

    SHAPE_COLOR GetColor(unsigned int& slot);
    bool        SetColor(unsigned int& slot, SHAPE_COLOR color);
};

#endif // FILLED_SHAPES_H
