#pragma once
#include "sDyes.h"

struct sMod
{
	// 模型
	eMod e = eMod::eNone;
	// 染色方案
	sDyes dyes;
	// 形态
	int jdx = 0;

	void setMod(eMod emod);
	void setMod(eMod emod, int jdx);
	void setJdx(int jdx, int max);
	void setJdx(int jdx);

	typedef std::map<eAct, sSps> sActs;
	void apply(sActs& sps, bool onMap, bool shadow) const;
	void apply(txtAction::sAction& heads, bool sound) const;
	void apply()const;

	ulong get(eAct e) const;
	sSps get(eAct e, bool shadow) const;

	operator bool()const;

	void save(bool pet) const;
	void load(bool pet);
};