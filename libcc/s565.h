#pragma once
#include "_cpp.h"

union s565 
{ 
	ushort color; 
	struct 
	{ 
		ushort b : 5, g : 6, r : 5;
	};

	s565();
	s565(uchar red, uchar green, uchar blue);

	void toBlick();

	void toLight();

	void toAlpha(uchar Ox20);

	void toOpacity(s565& src2des, uchar opacity)const;

	ulong to8888(uchar Ox20) const;

	ushort to4444(uchar Ox20) const;

	static const s565 WHITE;
	static const s565 YELLOW;
	static const s565 GREEN;
	static const s565 BLUE;
	static const s565 RED;
	static const s565 MAGENTA;
	static const s565 BLACK;
	static const s565 ORANGE;
	static const s565 GRAY;
};
