#pragma once
#include "cIndexCounter.h"
#include "sMod.h"
#include "sPoint.h"
#include "sXl.h"
#include "sItem.h"
#include "cSki.h"
#include "sExp.h"
#include "sZz.h"

// 主属性
struct sProperty : public sUnique
{
	// 是否宝宝
	bool ispet;
	// 模型
	sMod mod;
	// 门派
	eMenpai menpai = eMenpai::eNone;
	// 名字
	std::string name;
	// 等级
	int lv = 0;
	// 气血
	int hp;
	// 魔法
	int mp;
	// 愤怒
	int ap = 0;
	// 属性点
	sPoint point;
	// 装备
	sItems equips;
	// 修炼
	sXl xl;
	// 技能
	eSkis eskis;
	// 经验
	sExp exp;
	// 资质
	sZz zz;

	// 构造
	sProperty();
protected:
	sProperty(bool ispet);
public:
	void reset(bool ispet);
	// 判断技能
	bool isSki(eSki e);
	// 技能等级
	virtual int getSkiLv(eSki eski = eSki::eNone) const;
	// 升级
	bool lvup(bool onlyCheck);

	void lvupEasy(int lv);

	// 修炼不存
	virtual void save()const;
	virtual void load();
};