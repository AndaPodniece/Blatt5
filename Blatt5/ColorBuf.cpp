#pragma once
#include "ColorBuf.h"
#include "Color.h"
#include "ViewPortGL.h"

//2.a: Konstruktor
ColorBuf::ColorBuf(unsigned int widthP, unsigned int heightP) :width{ widthP }, height{ heightP }
{
	colorState = new Color * [width];
	for (unsigned int i = 0; i < width; i++)
	{
		colorState[i] = new Color[height];
	}
};
//2.a: Destruktor
ColorBuf::~ColorBuf()
{
	for (unsigned int i = 0; i < width; i++)
	{
		delete[] colorState[i];
	}
	delete[] colorState;
};
//2.b: Getter Methode
Color& ColorBuf::get(unsigned int x, unsigned int y)
{
	return colorState[x][y];
};
//2.b: Setter Methode
void ColorBuf::set(unsigned int x, unsigned int y, const Color& c)
{
	colorState[x][y] = c;
};
//2.c: clear() Methode
void ColorBuf::clear()
{
	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			colorState[i][j] = Color::nullColor;
		}
	}
}


//2.d: Draw-To Methode
void ColorBuf::drawTo(ViewPortGL& vp)
{
	if (vp.getXSize() != width || vp.getYSize() != height) {
		string error = "selected viewport has a different size than the color buffer: \n";
		error += "viewport size width:" + to_string(vp.getXSize()) + ", height:" + to_string(vp.getYSize()) + "\n";
		error += "buffer size width:" + to_string(width) + ", height:" + to_string(height);
		throw std::logic_error(error);
	}

	int maxPixelsDrawn = ViewPortGL::getMaxNumberOfPreparedPixels();
	int countPixelsDrawn = 0;
	vp.sendPixels(); // clears View Port Pixel Buffer !important, will result in a buffer overflow, if deleted

	for (unsigned int x = 0; x < width; x++)
	{
		for (unsigned int y = 0; y < height; y++)
		{
			if (countPixelsDrawn >= maxPixelsDrawn) {
				countPixelsDrawn = 0;
				vp.sendPixels();
			}

			Color c = colorState[x][y];
			vp.preparePix(x, y, c.getRed(), c.getGreen(), c.getBlue());
			countPixelsDrawn++;

		}
	}
}
