# Screensaver

Draws randomly sized and colored rectangles, triangles, and circles in a window.

## Building

### macOS / Linux (SDL2)

```bash
brew install sdl2          # macOS
# apt install libsdl2-dev  # Ubuntu / Debian

cmake -B build
cmake --build build
./build/screensaver
```

### Windows (Visual Studio)

```powershell
cmake -B build
cmake --build build --config Release
.\build\Release\screensaver.exe
```

The Windows build links against the prebuilt `FilledShapes_Lib.lib` (GDI-based renderer).
The macOS / Linux build compiles `platform/mac/FilledShapes.cpp` using SDL2.

## Project structure

```
screensaver/
├── main.cpp            # Entry point – shape allocation, randomization, draw loop
├── Shape.h / .cpp      # Abstract base class for all shapes
├── Rectangle.h / .cpp  # Filled rectangle
├── Triangle.h  / .cpp  # Filled equilateral triangle
├── Circle.h    / .cpp  # Filled circle
├── platform/
│   ├── win/FilledShapes.h          # Windows GDI renderer header (used with .lib)
│   └── mac/FilledShapes.h / .cpp   # SDL2 renderer for macOS and Linux
├── FilledShapes_Lib.lib            # Prebuilt Windows GDI renderer
└── CMakeLists.txt
```
