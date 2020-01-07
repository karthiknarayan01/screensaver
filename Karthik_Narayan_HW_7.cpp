/////////////////////////////////////////////////////////////////////
// screensaver.cpp
// Author: Karthik Narayan
// Description: Assignment 7
/////////////////////////////////////////////////////////////////////
#include "MyRect.h"
#include "MyTriangle.h"
#include <stdlib.h> // rand and srand
#include <time.h> // time funciton
#include <windows.h>  // POINT object
#include "MyCircle.h"
#include <map>
#include<vector>


// how many times will the program cycle
#define PROGRAM_RUN 20

// small delay between drawing rectangles during each run
#define DRAW_DELAY 100

// small delay between each iteration of drawing rectangles
#define ITERATION_DELAY 250

#define NUM_SHAPES 20

#define TOTAL_SHAPES 150

// function prototypes
void RandomAttributesRect(MyRect&);
void RandomAttributesTriangle(MyTriangle&);
void RandomAttributesCircle(MyCircle&);
void RandomAttributes(Shape*);

void main()
{
	int shapes; // loop index

	// seed the random number generator
	srand((unsigned int)time(0));

	// allow the user time to move the console window away
	// from the FilledShapes window are
	cout << "Move this window to the lower right of the screen, and press ENTER to continue:\n";
	cin.get();


	vector<Shape *> R;
	vector<Shape *> T;
	vector<Shape *> C;

	map<string, vector<Shape*>> storeShapes;

	int rSize = 0, tSize = 0, cSize = 0, totalSize = 0;

	// loop until we get atleast 20 of each shape and 150 total shapes
	while (rSize < NUM_SHAPES || tSize < NUM_SHAPES || cSize < NUM_SHAPES || totalSize < TOTAL_SHAPES) {
		switch (rand() % 3) {
			case 0:
				R.push_back(new MyRect);
				rSize += 1;
				break;
			case 1:
				T.push_back(new MyTriangle);
				tSize += 1;
				break;
			default:
				C.push_back(new MyCircle);
				cSize += 1;
				break;
		}

		totalSize += 1;
	}
	// key of the map will be either rectangles or triangles or circles and it will store a list of shape pointers
	storeShapes["rectangles"] = R;

	storeShapes["triangles"] = T;

	storeShapes["circles"] = C;

	// for each of the shape created call RandomAttributes, which will take a shape pointer, downcast it and then call the appropriate method for the shape
		for (int i = 0, j = 0, k = 0; i < rSize || j < tSize || k < cSize; )
		{
			
			if (i < rSize) {
				RandomAttributes(R[i]);
				i += 1;
			}
			if (j < tSize) {
				RandomAttributes(T[j]);
				j += 1;
			}
			if (k < cSize) {
				RandomAttributes(C[k]);
				
				k += 1;
				
			}
			
		}

		// draw the shapes by calling draw method. based on the type of the object either rectangle, triangle or circle's draw method will be invoked during runtime.
	for (int i = 0; i < totalSize; )
	{
		

		(*storeShapes["rectangles"][0]).ClearScreen();

		if (rSize > 0) {
			(*storeShapes["rectangles"][rSize - 1]).Draw();
			i += 1;
		}

		if (tSize > 0)
		{
			(*storeShapes["triangles"][tSize - 1]).Draw();
			i += 1;
		}
		
		if (cSize > 0)
		{
			(*storeShapes["circles"][cSize - 1]).Draw();
			i += 1;
		}

		rSize -= 1;
		cSize -= 1;
		tSize -= 1;

		if (DRAW_DELAY > 0)
			Sleep(DRAW_DELAY);


		// wait for a little while 
		if (ITERATION_DELAY > 0)
			Sleep(ITERATION_DELAY);
	}

}

void RandomAttributes(Shape* s) {
	MyRect* r = dynamic_cast<MyRect *>(s);
	MyTriangle* t = dynamic_cast<MyTriangle*>(s);
	MyCircle* c = dynamic_cast<MyCircle*>(s);
	
	if (r != NULL)
		RandomAttributesRect(*r);
	else if (t != NULL)
		RandomAttributesTriangle(*t);
	else
	{
		RandomAttributesCircle(*c);
	}
}

/////////////////////////////////////////////////////////////////////
// RandomAttributes
// Description: This routine will randomy choose parameters for 
//              a MyRect object, and draw it.
// 
// Inputs: MyRect object
// Outputs: None
// Returns: None
/////////////////////////////////////////////////////////////////////
void RandomAttributesRect(MyRect& S)
{
	// needed to draw a filled shape
	POINT p;
	p.x = 50;
	p.y = 50;

	// define variables that will hold he parameters
	// for the rectangle
	SHAPE_COLOR firstColor = RED;
	SHAPE_COLOR lastColor = PURPLE;
	unsigned int myPen;
	unsigned int myBrush;
	unsigned int length;
	unsigned int width;

	// reset the rectangle object to some known, legal values
	S.SetPosition(p);
	S.SetLength(S.GetWindowHeight() / 10);
	S.SetWidth(S.GetWindowWidth() / 10);

	// generate random values for our parameters, within
	// allowable limits
	myPen = (unsigned int)firstColor + rand() % (unsigned int)lastColor;

	// make sure the pen and brush colors are not the same
	do {
		myBrush = (unsigned int)firstColor + rand() % (unsigned int)lastColor;
	} while (myBrush == myPen);

	// set up the parameters of the filled shape
	// object per the random data
	S.SetBorderColor((SHAPE_COLOR)myPen);
	S.SetFillColor((SHAPE_COLOR)myBrush);

	// stay in each loop until you have chosen random
	// parameters which draw a rectangle within the legal
	// limits of the window.

	// length
	do {
		length = 1 + rand() % S.GetWindowHeight();
	} while (!S.SetLength(length));

	// width
	do {
		width = 1 + rand() % S.GetWindowWidth();
	} while (!S.SetWidth(width));

	// position
	do {
		p.x = 1 + rand() % S.GetWindowWidth();
		p.y = 1 + rand() % S.GetWindowHeight();
	} while (!S.SetPosition(p));
}

/////////////////////////////////////////////////////////////////////
// RandomAttributes
// Description: This routine will randomy choose parameters for 
//              a MyTriangle object, and draw it.
// 
// Inputs: MyTriangle object
// Outputs: None
// Returns: None
/////////////////////////////////////////////////////////////////////
void RandomAttributesTriangle(MyTriangle& S)
{
	// needed to draw a filled shape
	POINT p;
	p.x = 50;
	p.y = 50;

	// define variables that will hold he parameters
	// for the rectangle
	SHAPE_COLOR firstColor = RED;
	SHAPE_COLOR lastColor = PURPLE;
	unsigned int myPen;
	unsigned int myBrush;
	unsigned int length;

	// reset the rectangle object to some known, legal values
	S.SetPosition(p);
	S.SetLength(S.GetWindowHeight() / 10);

	// generate random values for our parameters, within
	// allowable limits
	myPen = (unsigned int)firstColor + rand() % (unsigned int)lastColor;

	// make sure the pen and brush colors are not the same
	do {
		myBrush = (unsigned int)firstColor + rand() % (unsigned int)lastColor;
	} while (myBrush == myPen);

	// set up the parameters of the filled shape
	// object per the random data
	S.SetBorderColor((SHAPE_COLOR)myPen);
	S.SetFillColor((SHAPE_COLOR)myBrush);

	// stay in each loop until you have chosen random
	// parameters which draw a rectangle within the legal
	// limits of the window.

	// length
	do {
		length = 1 + rand() % S.GetWindowHeight();
	} while (!S.SetLength(length));

	// position
	do {
		p.x = 1 + rand() % S.GetWindowWidth();
		p.y = 1 + rand() % S.GetWindowHeight();
	} while (!S.SetPosition(p));
}

void RandomAttributesCircle(MyCircle& S)
{
	// needed to draw a filled shape
	POINT p;
	p.x = 50;
	p.y = 50;

	// define variables that will hold he parameters
	// for the circle
	SHAPE_COLOR firstColor = RED;
	SHAPE_COLOR lastColor = PURPLE;
	unsigned int myPen;
	unsigned int myBrush;
	unsigned int length;

	

	// generate random values for our parameters, within
	// allowable limits
	myPen = (unsigned int)firstColor + rand() % (unsigned int)lastColor;

	
	S.SetPosition(p);
	S.setRadius(10);

	// make sure the pen and brush colors are not the same
	do {
		myBrush = (unsigned int)firstColor + rand() % (unsigned int)lastColor;
	} while (myBrush == myPen);

	// set up the parameters of the filled shape
	// object per the random data
	S.SetBorderColor((SHAPE_COLOR)myPen);
	S.SetFillColor((SHAPE_COLOR)myBrush);

	// stay in each loop until you have chosen random
	// parameters which draw a rectangle within the legal
	// limits of the window.

	// length

	do {
		length = 1 + rand() % (S.GetWindowHeight() <= S.GetWindowWidth()? S.GetWindowHeight(): S.GetWindowWidth());
		
	} while (!S.setRadius(length));

	
	do {
		p.x = 1 + rand() % S.GetWindowWidth();
		p.y = 1 + rand() % S.GetWindowHeight();
	} while (!S.SetPosition(p));



	

	// position
	
}
