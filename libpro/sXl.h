#pragma once
#include <vector>


enum class eXl { atk, def, mtk, mef };
// 不用联合体,存档会自己截断
struct sXl
{
	static const int c4;
	std::vector<int> lvs;

	sXl();

	void reset();
	// 升级
	bool lvup(int idx);
	bool lvup(eXl exl);
	// 降级, 退还经验
	bool lvdown(int idx, bool onlyCheck);
	// 
	void set(int atk, int def, int mtk, int mef);
		
	void set(int a, int d);

	void set(int v);

	void setA(int a);
	void setA(int atk, int mtk);

	void setD(int d);
	void setD(int def, int mef);

	int get(int idx) const;
	int get(eXl exl) const;

	void operator+=(const sXl& xl);
	sXl operator+(const sXl& xl) const;

	void operator-=(const sXl& xl);
	sXl operator-(const sXl& xl) const;

	void save()const;
	void load();

	static int getExp(int lv);
	// 取当前人物等级的修炼上限
	static int getLv(int lv);
	static const int c25, c2000;
};

