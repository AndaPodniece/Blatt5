#include "Color.h"
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Utils.h"

using namespace std;
Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
}
Color::Color(int r, int g, int b)
{
	if (r < 0 || r>255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		throw logic_error("value is outside of range");
	}
	red = r;
	green = g;
	blue = b;
}
int Color::getRed()
{
	return red;
}
int Color::getGreen()
{
	return green;
}
int Color::getBlue()
{
	return blue;
}
void Color::setRed(int r)
{
	if (r < 0 || r > 255)
		throw logic_error("value is out  of range");
	red = r;
}
void Color::setGreen(int g)
{
	if (g< 0 || g> 255)
		throw logic_error("value is out  of range");
	green = g;
}
void Color::setBlue(int b)
{
	if (b< 0 ||b> 255)
		throw logic_error("value is out  of range");
	blue = b;
}
const Color Color::nullColor = Color(false);

Color::Color(bool isValidColor)
{
	if (isValidColor)
	{
		this->red = 0;
		this->green = 0;
		this->blue = 0;
		return;
	}
	this->red = -1;
	this->green = -1;
	this->blue = -1;
}

Color Color::darken(int amount)
{
	if (amount < 0)
		amount = 0;
	red -= amount;
	red = red < 0 ? 0 : red;

	green -= amount;
	green = green < 0 ? 0 : green;

	blue -= amount;
	blue = blue < 0 ? 0 : blue;

	Color color(red, green, blue);

	return color;

}

Color Color::lighten(int amount)
{
	if(amount < 0)
		amount = 0;

	red += amount;
	red = red > 255 ? 255 : red;

	green += amount;
	green = green > 255 ? 255 : green;

	blue += amount;
	blue = blue > 255 ? 255 : blue;

	Color color(red, green, blue);
	return color;
}

Color Color::averageWith(const Color& other) const
{
	int newRed = (this->red + other.red) / 2;
	int newGreen = (this->green + other.green) / 2;
	int newBlue = (this->blue + other.blue) / 2;

	return Color(newRed, newGreen, newBlue);
}

Color Color::averageWith(const Color& other1, const Color& other2, const Color& other3) const
{
	int newRed = (this->red + other1.red + other2.red + other3.red) / 4;
	int newGreen = (this->green + other1.green + other2.green + other3.green) / 4;
	int newBlue = (this->blue + other1.blue + other2.blue + other3.blue) / 4;

	return Color(newRed, newGreen, newBlue);
}

Color Color::randomlyChange(int maxAmount) const
{
	int upper = abs(maxAmount);
	int lower = -abs(maxAmount);

	int newRed = limit(0, 255, this->red + randomNumber(lower, upper));
	int newGreen = limit(0, 255, this->green + randomNumber(lower, upper));
	int newBlue = limit(0, 255, this->blue + randomNumber(lower, upper));
	return Color(newRed, newGreen, newBlue);
}

bool Color::equals(const Color& other) const
{
	if ((this->red == other.red) && (this->green == other.green) && (this->blue == other.blue))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
