#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#ifdef _WIN32
#include <windows.h>  // Sleep()
#else
#include <unistd.h>
static void Sleep(unsigned int ms) { usleep(ms * 1000); }
#endif

static const int MIN_PER_TYPE    = 20;
static const int MIN_TOTAL       = 150;
static const int DRAW_DELAY_MS   = 100;
static const int CYCLE_DELAY_MS  = 250;

// Forward declarations
void randomizeShape(Shape* shape);
void randomizeRect(Rectangle& rect);
void randomizeTriangle(Triangle& tri);
void randomizeCircle(Circle& circle);

static SHAPE_COLOR randomColor()
{
    return static_cast<SHAPE_COLOR>(RED + rand() % static_cast<int>(PURPLE));
}

static SHAPE_COLOR randomDifferentColor(SHAPE_COLOR exclude)
{
    SHAPE_COLOR c;
    do { c = randomColor(); } while (c == exclude);
    return c;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "Move this window to the lower right of the screen, then press ENTER:\n";
    std::cin.get();

    std::vector<Shape*> rects;
    std::vector<Shape*> triangles;
    std::vector<Shape*> circles;

    int rectCount = 0, triCount = 0, circCount = 0, totalCount = 0;

    // Allocate shapes: at least MIN_PER_TYPE of each type, MIN_TOTAL overall
    while (rectCount < MIN_PER_TYPE || triCount < MIN_PER_TYPE ||
           circCount < MIN_PER_TYPE || totalCount < MIN_TOTAL)
    {
        switch (rand() % 3) {
            case 0:  rects.push_back(new Rectangle); rectCount++;  break;
            case 1:  triangles.push_back(new Triangle); triCount++; break;
            default: circles.push_back(new Circle);  circCount++; break;
        }
        totalCount++;
    }

    std::map<std::string, std::vector<Shape*>> shapeGroups;
    shapeGroups["rectangles"] = rects;
    shapeGroups["triangles"]  = triangles;
    shapeGroups["circles"]    = circles;

    // Assign random attributes to every shape
    for (int i = 0, j = 0, k = 0; i < rectCount || j < triCount || k < circCount; ) {
        if (i < rectCount)  randomizeShape(rects[i++]);
        if (j < triCount)   randomizeShape(triangles[j++]);
        if (k < circCount)  randomizeShape(circles[k++]);
    }

    // Draw shapes one-by-one, clearing before each trio
    for (int drawn = 0; drawn < totalCount; ) {
        shapeGroups["rectangles"][0]->ClearScreen();

        if (rectCount > 0) { shapeGroups["rectangles"][--rectCount]->Draw(); drawn++; }
        if (triCount  > 0) { shapeGroups["triangles"] [--triCount ]->Draw(); drawn++; }
        if (circCount > 0) { shapeGroups["circles"]   [--circCount]->Draw(); drawn++; }

        Sleep(DRAW_DELAY_MS);
        Sleep(CYCLE_DELAY_MS);
    }

    return 0;
}

void randomizeShape(Shape* shape)
{
    if (Rectangle* r = dynamic_cast<Rectangle*>(shape)) { randomizeRect(*r);     return; }
    if (Triangle*  t = dynamic_cast<Triangle*> (shape)) { randomizeTriangle(*t); return; }
    if (Circle*    c = dynamic_cast<Circle*>   (shape)) { randomizeCircle(*c);   return; }
}

void randomizeRect(Rectangle& rect)
{
    POINT p = {50, 50};
    rect.SetPosition(p);
    rect.SetHeight(rect.GetWindowHeight() / 10);
    rect.SetWidth(rect.GetWindowWidth() / 10);

    SHAPE_COLOR pen   = randomColor();
    SHAPE_COLOR brush = randomDifferentColor(pen);
    rect.SetBorderColor(pen);
    rect.SetFillColor(brush);

    unsigned int h, w;
    do { h = 1 + rand() % rect.GetWindowHeight(); } while (!rect.SetHeight(h));
    do { w = 1 + rand() % rect.GetWindowWidth();  } while (!rect.SetWidth(w));
    do {
        p.x = 1 + rand() % rect.GetWindowWidth();
        p.y = 1 + rand() % rect.GetWindowHeight();
    } while (!rect.SetPosition(p));
}

void randomizeTriangle(Triangle& tri)
{
    POINT p = {50, 50};
    tri.SetPosition(p);
    tri.SetSideLength(tri.GetWindowHeight() / 10);

    SHAPE_COLOR pen   = randomColor();
    SHAPE_COLOR brush = randomDifferentColor(pen);
    tri.SetBorderColor(pen);
    tri.SetFillColor(brush);

    unsigned int side;
    do { side = 1 + rand() % tri.GetWindowHeight(); } while (!tri.SetSideLength(side));
    do {
        p.x = 1 + rand() % tri.GetWindowWidth();
        p.y = 1 + rand() % tri.GetWindowHeight();
    } while (!tri.SetPosition(p));
}

void randomizeCircle(Circle& circle)
{
    POINT p = {50, 50};
    circle.SetPosition(p);
    circle.SetRadius(10);

    SHAPE_COLOR pen   = randomColor();
    SHAPE_COLOR brush = randomDifferentColor(pen);
    circle.SetBorderColor(pen);
    circle.SetFillColor(brush);

    unsigned int bound = std::min(circle.GetWindowHeight(), circle.GetWindowWidth());
    unsigned int r;
    do { r = 1 + rand() % bound; } while (!circle.SetRadius(r));
    do {
        p.x = 1 + rand() % circle.GetWindowWidth();
        p.y = 1 + rand() % circle.GetWindowHeight();
    } while (!circle.SetPosition(p));
}
