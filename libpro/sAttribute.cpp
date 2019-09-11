#include "sAttribute.h"
#include "_inc.h"

int3::int3()
{
	reset();
}

int3::operator int()
{
	return std::max(0, ori) * std::max(0, per) / 100 + std::max(0, add);
}

int3::operator const int() const
{
	return std::max(0, ori) * std::max(0, per) / 100 + std::max(0, add);
}

void int3::reset()
{
	ori = add = 0;
	per = 100;
}

void int3::reset(int _add)
{
	add = _add;
	ori = 0;
}



//////////////////////////////////////////////////////////////////////////
// const int sAttribute::cHp = 100;
// const int sAttribute::cMp = 200;
const int sAttribute::cAp = 150;
// const int sAttribute::cHit = 40;
// const int sAttribute::cAtk = 30;
sAttribute::sAttribute()
{
	reset();
}

void sAttribute::reset()
{
	hpMax.reset();
	mpMax.reset();

	// 面板 命中
	hit.reset();
	// 面板 伤害
	atk.reset();
	// 面板 防御
	def.reset();
	// 面板 法术伤害
	mtk.reset();
	// 面板 法术防御
	mef.reset();
	// 面板 速度
	speed.reset();
	// 面板 躲避
	avoid.reset();

	hpMax.ori = 256;
	mpMax.ori = 256;
	hit.ori = 64;
	atk.ori = 16;
	def.ori = 16;
	mtk.ori = 16;
	mef.ori = 16;
	speed.ori = 8;
	avoid.ori = 16;
}
