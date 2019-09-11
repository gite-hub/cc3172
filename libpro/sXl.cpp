#include "sXl.h"
#include "_inc.h"

const int sXl::c4 = 4;
const int sXl::c25 = 20;
const int sXl::c2000 = 20000;

sXl::sXl()
{
	lvs.resize(c4);
	reset();
}


void sXl::reset()
{
	std::fill(lvs.begin(), lvs.end(), 0);
}

bool sXl::lvup(int idx)
{
	if (idx < 0 || idx >= c4)
	{
		return false;
	}
	if (lvs[idx] >= c25)
	{
		return false;
	}
	++lvs[idx];
	return true;
}


bool sXl::lvup(eXl exl)
{
	return lvup((int)exl);
}

bool sXl::lvdown(int idx, bool onlyCheck)
{
	if (idx < 0 || idx >= c4)
	{
		return false;
	}
	if (lvs[idx] <= 0)
	{
		return false;
	}
	if (!onlyCheck)
	{
		--lvs[idx];
	}
	return true;
}


void sXl::set(int atk, int def, int mtk, int mef)
{
	setA(atk, mtk);
	setD(def, mef);
}

void sXl::setA(int a)
{
	setA(a, a);
}

void sXl::setA(int atk, int mtk)
{
	lvs[0] = atk;
	lvs[2] = mtk;
}

void sXl::setD(int d)
{
	setD(d, d);
}

void sXl::setD(int def, int mef)
{
	lvs[1] = def;
	lvs[3] = mef;
}

void sXl::set(int v)
{
	set(v, v);
}

void sXl::set(int a, int d)
{
	setA(a);
	setD(d);
}

int sXl::get(int idx) const
{
	return lvs.at(idx);
}

int sXl::get(eXl exl) const
{
	return get((int)exl);
}

void sXl::operator+=(const sXl& xl)
{
	forv(lvs, k)
	{
		lvs.at(k) += xl.lvs.at(k);
	}
}

sXl sXl::operator+(const sXl& xl) const
{
	sXl x;
	forv(lvs, k)
	{
		x.lvs.at(k) = lvs.at(k) + xl.lvs.at(k);
	}
	return x;
}

void sXl::operator-=(const sXl& xl)
{
	forv(lvs, k)
	{
		lvs.at(k) -= xl.lvs.at(k);
	}
}

sXl sXl::operator-(const sXl& xl) const
{
	sXl x;
	forv(lvs, k)
	{
		x.lvs.at(k) = lvs.at(k) - xl.lvs.at(k);
	}
	return x;
}

#pragma pack (push)
#pragma pack (1)
union sXlSaveLoad
{
	uint v;
	struct
	{
		uint temp : 12;
		uint lv1 : 5;
		uint lv2 : 5;
		uint lv3 : 5;
		uint lv4 : 5;
	};
};
#pragma pack (pop)



void sXl::save()const
{
	sXlSaveLoad xl;
	xl.lv1 = lvs[0];
	xl.lv2 = lvs[1];
	xl.lv3 = lvs[2];
	xl.lv4 = lvs[3];
	sStream& sav = *cSave::getSave();
	sav << xl.v << s_space;
}

void sXl::load()
{
	sStream& sav = *cSave::getLoad();
	sXlSaveLoad xl;
	sav >> xl.v;
	lvs[0] = xl.lv1;
	lvs[1] = xl.lv2;
	lvs[2] = xl.lv3;
	lvs[3] = xl.lv4;
}



int sXl::getExp(int lv)
{
	if (lv == 0)
	{
		return 0;
	}
	int exp = 15;
	for (int i = 1; i < lv; ++i)
	{
		exp += (4 + i * 2) * 1;
	}
	return exp;
}


int sXl::getLv(int lv)
{
	if (lv < 25)
	{
		return 0;
	}
	lv = (lv - 20) / 5;
	if (lv > c25)
	{
		return c25;
	}
	return lv;
}

