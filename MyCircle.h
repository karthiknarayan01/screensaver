#pragma once
///////////////////////////////////////////////////////////////////////////////
// Karthik Narayan
// CPS 400
// MyCircle
//
// Description: Interface file for a simple circle class. This class will 
//              clients to draw simple circles on the screen.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef __MY_CIRCLE__
#define __MY_CIRCLE__
#include "FilledShapes.h"
#include "Shape.h"
#include <windows.h>
class MyCircle : public Shape {
	
	public:
		// default constructor for circle class
		MyCircle();
		// getRadius() -> returns the radius of the circle
		int getRadius();
		// getCenter(0 -> returns the position of the center of the circle
		POINT getCenter();
		// SetPosition() -> sets the position where the circle is drawn
		virtual bool SetPosition(POINT& point);
		// setRadius(int) -> sets the radius
		bool setRadius(int r);
		// draws the circle shape on screen
		virtual bool Draw();
		// validates whether the provided radius and center coordinates are correct or not
		bool validateInput(int r, POINT point);
	private:
		POINT center;
		int radius;

};
#endif __MY_CIRCLE__