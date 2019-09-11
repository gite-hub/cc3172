#pragma once
#include "_cpp.h"

struct s888
{
	uchar b, g, r;

	s888();
	s888(uchar red, uchar green, uchar blue);

	bool operator==(const s888& color)const;

	static const s888 WHITE;
	static const s888 YELLOW;
	static const s888 GREEN;
	static const s888 BLUE;
	static const s888 RED;
	static const s888 MAGENTA;
	static const s888 BLACK;
	static const s888 ORANGE;
	static const s888 GRAY;
};
