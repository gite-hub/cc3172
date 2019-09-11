#pragma once

// 三相数据
struct int3
{
	// 原始
	int ori;
	// 百分比 (比如:强身/冥思)
	int per;
	// 附加 (比如: 强壮)
	int add;

	int3();
	operator int();
	operator const int() const;

	void reset();
	// per不变
	void reset(int add);
};

// 基本属性
struct sAttribute
{
	// 气血上限
	int3 hpMax;
	// 魔法上限
	int3 mpMax;

	// 面板 命中
	int3 hit;
	// 面板 伤害
	int3 atk;
	// 面板 防御
	int3 def;
	// 面板 法术伤害
	int3 mtk;
	// 面板 法术防御
	int3 mef;
	// 面板 速度
	int3 speed;
	// 面板 躲避
	int3 avoid;

	sAttribute();

	void reset();

	static const int /*cHp, cMp, */cAp/*, cHit, cAtk*/;
};


