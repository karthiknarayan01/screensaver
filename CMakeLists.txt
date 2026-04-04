cmake_minimum_required(VERSION 3.16)
project(screensaver CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Common source files
# ---------------------------------------------------------------------------
set(SOURCES
    main.cpp
    Shape.cpp
    Rectangle.cpp
    Triangle.cpp
    Circle.cpp
)

add_executable(screensaver ${SOURCES})

# ---------------------------------------------------------------------------
# Platform-specific rendering backend
# ---------------------------------------------------------------------------
if(WIN32)
    # Windows: use the prebuilt GDI-based FilledShapes library
    target_include_directories(screensaver PRIVATE ${CMAKE_SOURCE_DIR}/platform/win)
    target_link_libraries(screensaver PRIVATE
        ${CMAKE_SOURCE_DIR}/FilledShapes_Lib.lib
    )
else()
    # macOS / Linux: SDL2-based renderer
    target_include_directories(screensaver PRIVATE ${CMAKE_SOURCE_DIR}/platform/mac)
    target_sources(screensaver PRIVATE platform/mac/FilledShapes.cpp)

    find_package(SDL2 REQUIRED)
    if(TARGET SDL2::SDL2)
        target_link_libraries(screensaver PRIVATE SDL2::SDL2)
    else()
        # Fallback for older FindSDL2 modules that expose variables instead of targets
        target_include_directories(screensaver PRIVATE ${SDL2_INCLUDE_DIRS})
        target_link_libraries(screensaver PRIVATE ${SDL2_LIBRARIES})
    endif()
endif()
