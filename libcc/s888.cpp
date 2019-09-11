#include "s888.h"
s888::s888() : r(0xFF), g(0xFF), b(0xFF)
{

}

s888::s888(uchar red, uchar green, uchar blue) : r(red), g(green), b(blue)
{

}


bool s888::operator==(const s888& color)const
{
	return r == color.r && g == color.g && b == color.b;
}

const s888 s888::WHITE(0xFF, 0xFF, 0xFF);
const s888 s888::YELLOW(0xFF, 0xFF, 0);
const s888 s888::GREEN(0, 0xFF, 0);
const s888 s888::BLUE(0, 0, 0xFF);
const s888 s888::RED(0xFF, 0, 0);
const s888 s888::MAGENTA(0xFF, 0, 0xFF);
const s888 s888::BLACK(0, 0, 0);
const s888 s888::ORANGE(0xFF, 127, 0);
const s888 s888::GRAY(166, 166, 166);