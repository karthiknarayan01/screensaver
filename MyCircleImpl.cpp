///////////////////////////////////////////////////////////////////////////////
// Karthik Narayan
// CPS 400
// MyCircle
//
// Description: Implementation file for a simple circle class. This class will 
//              clients to draw simple circles on the screen.
//
///////////////////////////////////////////////////////////////////////////////

#include "MyCircle.h"

bool MyCircle::validateInput(int r, POINT point) {

	int xRightBoundary = point.x + r;
	int xLeftBoundary = point.x - r;
	int yRightBoundary = point.y + r;
	int yLeftBoundary = point.y - r;
	int border = (GetWindowWidth() <= GetWindowHeight()) ? GetWindowWidth() : GetWindowHeight();

	// the radius drawn from the center position should not flow outside the valid boundaries as obtained using the methods GetWindowHeight() and GetWindowWidth()
	
	if (xRightBoundary < border && xLeftBoundary > 0 && yRightBoundary < border && yLeftBoundary > 0)
	{
		
		return true;
	}
	return false;
}

MyCircle::MyCircle() {
	center.x = (WINDOW_MAXX <= WINDOW_MAXY)?WINDOW_MAXX / 2:WINDOW_MAXY/2;
	center.y = (WINDOW_MAXX <= WINDOW_MAXY) ? WINDOW_MAXX / 2 : WINDOW_MAXY / 2;
	radius = (WINDOW_MAXX <= WINDOW_MAXY) ? WINDOW_MAXX / 10 : WINDOW_MAXY / 10;
}
int MyCircle::getRadius() {
	return radius;
}
POINT MyCircle::getCenter() {
	return center;
}
bool MyCircle::SetPosition(POINT& point) {
	// validates whether the position provided is valid or not by invoking the validateInput method and then sets the position and center
	if (validateInput(radius, point)) {
		center = point;
		position = point;
		
		return true;
	}

	return false;
}
bool MyCircle::setRadius(int r) {
	// validates whether the radius provided is valid or not by invoking the validateInput method and then sets the position and center
	if (validateInput(r, position)) {
		radius = r;
		
		return true;
	}

	return false;
}
bool MyCircle::Draw() {

	// draws the shape by invoking FilledCircle method in FilledShapes class
	fs.SetPenColor(borderColor);
	fs.SetBrushColor(fillColor);


	fs.FilledCircle(center, radius);

	return true;
}