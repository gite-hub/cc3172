#pragma once
#include "_inc.h"
#include "eSki.h"
#include "eMenpai.h"

class txtSki
{
public:
	// 消耗
	struct sCost
	{
		// 最大气血%
		int hpper = 0;
		// 魔法每人
		int mps = 0;
		// 魔法: 等级 / lv + mp
		int lv = 0;
		// 魔法
		int mp = 0;
		// 愤怒
		int ap = 0;

		sSkiCost getCost(int hpMax, int ulv, int targetsCount);
	};
	struct sSki
	{
		ulong act;
		ulong state;
		ulong sound;
		eSkiSelect select;
		eSkiBuff buff;
		eSkiPos pos, buffpos;
		sCost cost;
		std::string descCost;
		int count;
	};
	txtSki();

	static std::string getName(eMenpai mp);
	static eSki get0(eMenpai mp);
	static eSki getEnd(eMenpai mp);
	// 被动
	static bool isEd(eSki e);
	// 门派技能
	static bool isMenpai(eSki e);
	// 门派技能
	static bool isMenpai(eSki e, eMenpai mp);
	// 宝宝技能(仅仅是主动技能)
	static bool isPet(eSki e);
	// 特技
	static bool isSpecial(eSki e);

private:
	void init(ulong act, ulong state, ulong sound, eSki ski, int count = 1);
	void insert(eSkiSelect select, eSkiPos pos);
	void insert(eSkiSelect select, eSkiPos pos, eSkiBuff buff, eSkiPos buffpos);
	void insert(int ap_per, int mps, int lv = 0, int mp = 0);

	eSki _e;
	sSki* _ski;
protected:
	std::map<eSki, sSki> _skis;
public:
	static const std::map<eSki, sSki>& getSkis();
	static const int cTargetMax;
};