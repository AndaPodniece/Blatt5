#pragma once
#include "ViewPortGL.h"
#include "ColorBuf.h"
#include "Color.h"
#include <time.h>
#include <math.h>

void buildColorPic(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, ColorBuf& cBuf)
{
	//Wie breit ist der Berreich
	int width_x = x2 - x1;
	//Wie hoch ist der Bereich
	int height_y = y2 - y1;
	//Wenn der Ausschnitt zu klein ist, soll man aufhören es weiter zu unterteilen
	if (abs(width_x) <= 1 && abs(height_y) <= 1) return;
	int middle_x = (x1 + x2)/2;
	int middle_y = (y1 + y2) / 2;
	int random = (width_x + height_y) / 4;

	Color topLeft = cBuf.get(x1, y1);
	Color topRight = cBuf.get(x2, y1);
	Color bottomLeft = cBuf.get(x1, y2);
	Color bottomRight = cBuf.get(x2, y2);

	Color topMiddle = cBuf.get(middle_x, y1);
	Color leftMiddle = cBuf.get(x1, middle_y);
	Color rightMiddle = cBuf.get(x2, middle_y);
	Color bottomMiddle = cBuf.get(middle_x, y2);
	Color middle = cBuf.get(middle_x, middle_y);

	//top middle:
	if (topMiddle.equals(Color::nullColor))
	{
		cBuf.set(middle_x, y1, topLeft.averageWith(topRight).randomlyChange(random));
	}
	//left middle:
	if (leftMiddle.equals(Color::nullColor))
	{
		cBuf.set(x1, middle_y, topLeft.averageWith(bottomLeft).randomlyChange(random));
	}
	//bottom middle:
	if (bottomMiddle.equals(Color::nullColor))
	{
		cBuf.set(middle_x, y2, bottomLeft.averageWith(bottomRight).randomlyChange(random));
	}
	//right middle:
	if (rightMiddle.equals(Color::nullColor))
	{
		cBuf.set(x2, middle_y, topRight.averageWith(bottomRight).randomlyChange(random));
	}
	//middle:
	if (middle.equals(Color::nullColor))
	{
		cBuf.set(middle_x, middle_y, topLeft.averageWith(topRight, bottomRight, bottomLeft).randomlyChange(random));
	}

	//Berreich in 4 unter teilt 
	buildColorPic(x1, y1, middle_x, middle_y, cBuf);
	buildColorPic(middle_x, y1, x2, middle_y, cBuf);
	buildColorPic(x1, middle_y, middle_x, y2, cBuf);
	buildColorPic(middle_x, middle_y, x2, y2, cBuf);
}

int main()
{
	srand(time(NULL));
	int width = 800;
	int height = 800;
	ViewPortGL vp = ViewPortGL("Generate Image: ", width, height);
	ColorBuf buf = ColorBuf(width, height);
	buf.clear();

	buf.set(0, 0, Color().randomlyChange(255));
	buf.set(0, height - 1, Color().randomlyChange(255));
	buf.set(width - 1, 0, Color().randomlyChange(255));
	buf.set(width - 1, width - 1, Color().randomlyChange(255));
	buildColorPic(0, 0, width - 1, height - 1, buf);

	bool isRunnin = true;
	while (isRunnin)
	{
		isRunnin = !vp.windowShouldClose();
		buf.drawTo(vp);
		vp.swapBuffers();
	}

}
