#pragma once

class cDirection
{
public:
	static int getDirection4(int direction8);
	static int getDirection4(float x, float y);
	static int getDirection8(int pred, float x, float y);
	// 取反(对面)方向(比如战斗时候,站对面)
	static int getDirectionR(int direction);
	// 取下一个方向(顺时针/逆时针)
	static int getDirectionRound8(int directionLast, bool isNextOrPre);
	// 取下一个方向(顺时针/逆时针)
	static int getDirectionRound4(int directionLast, bool isNextOrPre);
};