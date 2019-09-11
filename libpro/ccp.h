#pragma once
#include "cEquip.h"
#include "sPropertyInfo.h"
#include "sAttribute.h"
#include "sPet.h"
#include "sRole.h"

namespace ccp
{
	struct sZhuijia 
	{ 
		eSki e = eSki::eNone; 
		int rate = 0, lvGap;
		operator bool()const 
		{
			return e != eSki::eNone && rate > 0;
		}
	};
	typedef std::vector<sZhuijia> sZhuijias;
}
struct sPropertys
{
	int spurting = 0, zhuiji = 0;
	sPropertyInfo info;
	sAttribute attr;
	ccp::sZhuijias zhuijias;
	eSkis specials;
};
// 属性计算
namespace ccp
{
	static const int cFF = 0xFF;
	// 面板属性 
	void apply(sAttribute& attr, cEquip::eProPerty epro, int skilv);
	void apply(sAttribute& attr, const sPoint& point);
	void apply(sAttribute& attr, const sPoint& point, const sZz& zz, int lv);
	void apply(sAttribute& attr, const cEquip::sPropertys& pros);
	// 内置属性
	void apply(sPropertyInfo& info, eMenpai menpai);
	void apply(sPropertyInfo& info, const sXl& xl);
	// 装备
	void apply(sPropertys& pr, const sItems& equips, sStone* stone);
	// 被动技能
	void apply(sPropertyInfo& info, sAttribute& attr, eSki eski);
	// 互斥技能
	void apply(std::set<eSki>& mutexs, const eSkis& eskis);
	// 主属性
	void apply(sPropertys& pros, const sProperty* pro);
	// 酒肆
	void fillHpMp(sProperty* pro);
	// 升级
	bool lvup(sProperty* pro, bool onlyCheck);
	// 降级
	bool lvdown(sProperty* pro, bool onlyCheck);
	// 这个先不要用 逻辑还是旧的
	bool lvdown(sRole* role);
	// 门派技能
	bool addSki(eSkis& eskis, eMenpai mp);
	// 添加技能
	bool addSki(eSkis& eskis, eSki eski, int idx = cFF);
	// 合宝宝
	sPet* compose(const sPet* pet1, const sPet* pet2);
};