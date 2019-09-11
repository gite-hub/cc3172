#pragma once
#include "sPet.h"
#include "sObject.h"
#include "sStone.h"

// 人物属性
struct sRole : public sProperty, public sObject
{
	// 钱
	sExp money;
	// 技能
	std::vector<int> skilvs;
	// 宝石(装备加成)
	sStone stone;
	// 宝宝修
	sXl xlbb;
	// 行囊(装备)
	sItems items;
	// 仓库(兽决)
	sItems stores;
	// 宝宝(指针?)
	sPets pets;
	// 参战索引
	int fight = cc::_1;

	int teamIdx;

	sRole();
	// 门派技能等级
	int getSkiLv(eSki eski = eSki::eNone) const;
	// 
	bool addPet(sPet* pet);
	// 休息
	void unPet();
	// 放生
	bool removePet(int index, bool del);
	// 
	sPet* getPet(int index);
	sPet* getPet();
	// 参战
	bool setPet(int fight, bool onlyCheck);

	bool isControllabel() const;

	bool isTeam() const;

	void save()const;
	void load();
};