#pragma once
#include "_inc.h"

struct sZz
{
	// 攻击资质
	int atk;
	// 防御资质
	int def;
	// 体力资质
	int hp;
	// 法力资质
	int mana;
	// 速度资质
	int speed;
	// 躲闪资质
	int avoid;
	// 成长
	int grow;

	sZz();

	void reset();

	bool isValid();

	void correct();


	void operator=(const txtZz::sZz& zz);

	void save()const;
	void load();
};


