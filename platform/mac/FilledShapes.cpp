// SDL2-based implementation of FilledShapes for macOS / Linux.
// Provides the same drawing interface as the Windows GDI version.
//
// Dependencies: SDL2  (brew install sdl2  /  apt install libsdl2-dev)

#include "FilledShapes.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

// ---------------------------------------------------------------------------
// Module-level SDL state (shared across all FilledShapes instances)
// ---------------------------------------------------------------------------
static SDL_Window*   gWindow    = nullptr;
static SDL_Renderer* gRenderer  = nullptr;
int FilledShapes::instanceCount = 0;

// ---------------------------------------------------------------------------
// Color helpers
// ---------------------------------------------------------------------------
struct RGBAColor { Uint8 r, g, b, a; };

static RGBAColor toRGBA(SHAPE_COLOR c)
{
    switch (c) {
        case RED:    return {220,  30,  30, 255};
        case ORANGE: return {255, 140,   0, 255};
        case YELLOW: return {230, 210,   0, 255};
        case GREEN:  return {  0, 180,   0, 255};
        case BLUE:   return {  0,  80, 220, 255};
        case PURPLE: return {130,   0, 160, 255};
        case BLACK:  return {  0,   0,   0, 255};
        case BROWN:  return {139,  69,  19, 255};
        default:     return {255, 255, 255, 255};
    }
}

static void applyColor(SDL_Renderer* r, SHAPE_COLOR c)
{
    RGBAColor col = toRGBA(c);
    SDL_SetRenderDrawColor(r, col.r, col.g, col.b, col.a);
}

// ---------------------------------------------------------------------------
// Primitive drawing helpers
// ---------------------------------------------------------------------------
static void drawFilledCircle(SDL_Renderer* r, int cx, int cy, int radius)
{
    for (int dy = -radius; dy <= radius; dy++) {
        int dx = static_cast<int>(std::sqrt(static_cast<double>(radius * radius - dy * dy)));
        SDL_RenderDrawLine(r, cx - dx, cy + dy, cx + dx, cy + dy);
    }
}

static void drawCircleOutline(SDL_Renderer* r, int cx, int cy, int radius)
{
    int x = radius, y = 0, err = 0;
    while (x >= y) {
        SDL_RenderDrawPoint(r, cx + x, cy + y);
        SDL_RenderDrawPoint(r, cx + y, cy + x);
        SDL_RenderDrawPoint(r, cx - y, cy + x);
        SDL_RenderDrawPoint(r, cx - x, cy + y);
        SDL_RenderDrawPoint(r, cx - x, cy - y);
        SDL_RenderDrawPoint(r, cx - y, cy - x);
        SDL_RenderDrawPoint(r, cx + y, cy - x);
        SDL_RenderDrawPoint(r, cx + x, cy - y);
        y++;
        err += 1 + 2 * y;
        if (2 * (err - x) + 1 > 0) { x--; err += 1 - 2 * x; }
    }
}

// Equilateral triangle: apex at (tx, ty), side length given
static void triangleVertices(int tx, int ty, int side,
                             int& x1, int& y1,
                             int& x2, int& y2,
                             int& x3, int& y3)
{
    int h = static_cast<int>(side * std::sqrt(3.0) / 2.0);
    x1 = tx;           y1 = ty;
    x2 = tx - side/2;  y2 = ty + h;
    x3 = tx + side/2;  y3 = ty + h;
}

static void drawFilledTriangle(SDL_Renderer* r,
                               int x1, int y1,
                               int x2, int y2,
                               int x3, int y3)
{
    int minY = std::min({y1, y2, y3});
    int maxY = std::max({y1, y2, y3});

    for (int y = minY; y <= maxY; y++) {
        std::vector<int> xs;
        auto addIntersect = [&](int ax, int ay, int bx, int by) {
            if ((ay <= y && by > y) || (by <= y && ay > y)) {
                float t = static_cast<float>(y - ay) / (by - ay);
                xs.push_back(static_cast<int>(ax + t * (bx - ax)));
            }
        };
        addIntersect(x1, y1, x2, y2);
        addIntersect(x2, y2, x3, y3);
        addIntersect(x3, y3, x1, y1);
        if (xs.size() >= 2) {
            std::sort(xs.begin(), xs.end());
            SDL_RenderDrawLine(r, xs.front(), y, xs.back(), y);
        }
    }
}

// Pump the SDL event queue to keep the window responsive
static void pumpEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            std::cout << "Window closed.\n";
        }
    }
}

// ---------------------------------------------------------------------------
// FilledShapes implementation
// ---------------------------------------------------------------------------
FilledShapes::FilledShapes(int width, int height)
    : currentPenWidth(1),
      currentPenColor(static_cast<unsigned int>(BLUE)),
      currentBrushColor(static_cast<unsigned int>(RED)),
      windowWidth(width),
      windowHeight(height)
{
    if (instanceCount == 0) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
            return;
        }
        gWindow = SDL_CreateWindow(
            "Screensaver",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN
        );
        if (!gWindow) {
            std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
            return;
        }
        gRenderer = SDL_CreateRenderer(gWindow, -1,
                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!gRenderer) {
            std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
            return;
        }
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);
    }
    instanceCount++;
}

FilledShapes::~FilledShapes()
{
    instanceCount--;
    if (instanceCount == 0 && gRenderer) {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        gRenderer = nullptr;
        gWindow   = nullptr;
    }
}

bool FilledShapes::SetPenColor(SHAPE_COLOR color)   { return SetColor(currentPenColor,   color); }
bool FilledShapes::SetBrushColor(SHAPE_COLOR color) { return SetColor(currentBrushColor, color); }
SHAPE_COLOR FilledShapes::GetPenColor()   { return GetColor(currentPenColor);   }
SHAPE_COLOR FilledShapes::GetBrushColor() { return GetColor(currentBrushColor); }

bool FilledShapes::SetPenWidth(unsigned int w)
{
    if (w < PEN_WIDTH_MIN || w > PEN_WIDTH_MAX) return false;
    currentPenWidth = static_cast<int>(w);
    return true;
}

unsigned int FilledShapes::GetPenWidth() { return static_cast<unsigned int>(currentPenWidth); }

void FilledShapes::ClearScreen()
{
    if (!gRenderer) return;
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);
    pumpEvents();
}

unsigned int FilledShapes::GetMaxX() { return static_cast<unsigned int>(windowWidth);  }
unsigned int FilledShapes::GetMaxY() { return static_cast<unsigned int>(windowHeight); }

bool FilledShapes::FilledRectangle(POINT& origin, int height, int width, std::string /*text*/)
{
    if (!gRenderer) return false;

    SDL_Rect rect = { static_cast<int>(origin.x), static_cast<int>(origin.y), width, height };

    applyColor(gRenderer, GetColor(currentBrushColor));
    SDL_RenderFillRect(gRenderer, &rect);

    applyColor(gRenderer, GetColor(currentPenColor));
    SDL_RenderDrawRect(gRenderer, &rect);

    SDL_RenderPresent(gRenderer);
    pumpEvents();
    return true;
}

bool FilledShapes::FilledCircle(POINT& center, int radius)
{
    if (!gRenderer) return false;

    applyColor(gRenderer, GetColor(currentBrushColor));
    drawFilledCircle(gRenderer, static_cast<int>(center.x), static_cast<int>(center.y), radius);

    applyColor(gRenderer, GetColor(currentPenColor));
    drawCircleOutline(gRenderer, static_cast<int>(center.x), static_cast<int>(center.y), radius);

    SDL_RenderPresent(gRenderer);
    pumpEvents();
    return true;
}

bool FilledShapes::FilledTriangle(POINT& apex, int sideLength)
{
    if (!gRenderer) return false;

    int x1, y1, x2, y2, x3, y3;
    triangleVertices(static_cast<int>(apex.x), static_cast<int>(apex.y), sideLength,
                     x1, y1, x2, y2, x3, y3);

    applyColor(gRenderer, GetColor(currentBrushColor));
    drawFilledTriangle(gRenderer, x1, y1, x2, y2, x3, y3);

    applyColor(gRenderer, GetColor(currentPenColor));
    SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(gRenderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(gRenderer, x3, y3, x1, y1);

    SDL_RenderPresent(gRenderer);
    pumpEvents();
    return true;
}

bool FilledShapes::FilledEllipse(POINT& center, int radiusX, int radiusY)
{
    // Approximate as a circle using the average radius
    int avgRadius = (radiusX + radiusY) / 2;
    return FilledCircle(center, avgRadius);
}

bool FilledShapes::Line(POINT& start, POINT& end)
{
    if (!gRenderer) return false;
    applyColor(gRenderer, GetColor(currentPenColor));
    SDL_RenderDrawLine(gRenderer,
                       static_cast<int>(start.x), static_cast<int>(start.y),
                       static_cast<int>(end.x),   static_cast<int>(end.y));
    SDL_RenderPresent(gRenderer);
    pumpEvents();
    return true;
}

SHAPE_COLOR FilledShapes::GetColor(unsigned int& slot)
{
    return static_cast<SHAPE_COLOR>(slot);
}

bool FilledShapes::SetColor(unsigned int& slot, SHAPE_COLOR color)
{
    slot = static_cast<unsigned int>(color);
    return true;
}
