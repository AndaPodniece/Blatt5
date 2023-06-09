#pragma once
#include <stdexcept>

class Color
{
public:
	Color();
	Color(int r, int g, int b);
	Color(bool isValidColor);
	int getRed();
	int getGreen();
	int getBlue();
	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);

	Color darken(int amount);
	Color lighten(int amount);

	Color averageWith(const Color& other) const;
	Color averageWith(const Color& other1, const Color& other2, const Color& other3) const;

	Color randomlyChange(int maxAmount) const;
	bool equals(const Color& other) const;

	static const Color nullColor;

private:
	int red, green, blue;
};