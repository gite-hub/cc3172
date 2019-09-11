#pragma once
#include "_inc.h"

typedef std::vector<eSki> eSkis;
// 包裹
class cSki
{
public:
	// 描述
	static bool toDescs(eSki eski, sDescs& descs);
	// 学习经验
	static int getExp(int lv);
	// 学习金钱
	static int getMoney(int lv);

	static const int cGap;
};